#include <new>
#include <cstdlib>
#include "AVL.h"
#include "DataSystem.h"

/*------------------ OSKey class implementation ----------------------*/
bool OSKey::operator<(const OSKey& other) const {
    // if same num of servers, than one with smaller ID come first in INORDER traversal
    if (serverCount == other.serverCount)
        return dataCenterID < other.dataCenterID;

    // else, more servers means to come first in INORDER traversal
    return serverCount > other.serverCount;
}

bool OSKey::operator==(const OSKey& other) const {
    return (serverCount == other.serverCount) && (dataCenterID == other.dataCenterID);
}

bool OSKey::operator!=(const OSKey& other) const {
    return !operator==(other);
}

/*------------------DataSystem class implementation----------------------*/
DataSystem::~DataSystem() {
    auto iter = dataCenters.begin();
    while (iter != dataCenters.end()) {
        delete( *iter );
    }
}

DSStatusType DataSystem::AddDataCenter(int dataCenterID, int numOfServers) {
    if (dataCenterID <= 0 || numOfServers <= 0) return DS_INVALID_INPUT;

    try {
        // initialize keys and data
        auto dataCenterPtr = new DataCenter(numOfServers);

        OSKey linuxTreeKey(numOfServers, dataCenterID);
        OSKey winTreeKey(0, dataCenterID);

        // insert to the avl trees
        if (dataCenters.insert(dataCenterID, dataCenterPtr) != AVL_SUCCESS) return DS_FAILURE;
        if (windowsSorted.insert(winTreeKey, dataCenterID) != AVL_SUCCESS) return DS_FAILURE;
        if (linuxSorted.insert(linuxTreeKey, dataCenterID) != AVL_SUCCESS) return DS_FAILURE;

    } catch (std::bad_alloc& ba) {
        return DS_ALLOCATION_ERROR;
    }

    return DS_SUCCESS;
}

DSStatusType DataSystem::RemoveDataCenter(int dataCenterID) {
    if (dataCenterID <= 0) return DS_INVALID_INPUT;

    // create OSKey from the data in the dataCenters tree
    auto iter = dataCenters.find(dataCenterID);
    if (iter == dataCenters.end()) return DS_FAILURE; // no such DataCenter
    auto dataCenterPtr = *iter;

    OSKey linuxTreeKey(dataCenterPtr->GetLinuxNum(), dataCenterID);
    OSKey winTreeKey(dataCenterPtr->GetWinNum(), dataCenterID);

    // delete the DataCenter
    delete dataCenterPtr;

    // remove from the avl trees
    dataCenters.remove(dataCenterID);
    linuxSorted.remove(linuxTreeKey);
    windowsSorted.remove(winTreeKey);

    return DS_SUCCESS;
}

DSStatusType DataSystem::RequestServer(int dataCenterID, unsigned int serverID, OS os, int *assignedID) {
    if (dataCenterID <= 0) return DS_INVALID_INPUT;
    if (!assignedID) return DS_INVALID_INPUT; // null pointer

    // find the data center on the tree
    auto iter = dataCenters.find(dataCenterID);
    if (iter == dataCenters.end()) return DS_FAILURE; // no such DataCenter
    auto dataCenterPtr = *iter;

    OSKey linuxTreeKeyBefore(dataCenterPtr->GetLinuxNum(), dataCenterID);
    OSKey winTreeKeyBefore(dataCenterPtr->GetWinNum(), dataCenterID);

    // request the server from the data center
    auto res = dataCenterPtr->RequestServer(serverID, os, assignedID);
    if (res != DS_SUCCESS) return res;

    // Create OSKey from the new data
    OSKey linuxTreeKeyAfter(dataCenterPtr->GetLinuxNum(), dataCenterID);
    OSKey winTreeKeyAfter(dataCenterPtr->GetWinNum(), dataCenterID);

    // remove from the two OS avl trees the old oskey and insert the new ones
    linuxSorted.remove(linuxTreeKeyBefore);
    windowsSorted.remove(winTreeKeyBefore);

    try {
        linuxSorted.insert(linuxTreeKeyAfter, dataCenterID);
        windowsSorted.insert(winTreeKeyAfter, dataCenterID);
    } catch (std::bad_alloc& ba) {
        return DS_ALLOCATION_ERROR;
    }

    return DS_SUCCESS;
}

DSStatusType DataSystem::FreeServer(int dataCenterID, unsigned int serverID) {
    if (dataCenterID <= 0) return DS_INVALID_INPUT;

    // find the data center on the tree
    auto iter = dataCenters.find(dataCenterID);
    if (iter == dataCenters.end()) return DS_FAILURE; // no such DataCenter
    auto dataCenterPtr = *iter;

    // free the server from the data center
    return dataCenterPtr->FreeServer(serverID);
}

DSStatusType DataSystem::GetDataCentersByOS(OS os, int** dataCentersArr, int* numOfDataCenters) {
    if (!dataCentersArr || !numOfDataCenters) return DS_INVALID_INPUT;
    if (dataCenters.getSize() == 0) return DS_FAILURE; // no data centers

    *numOfDataCenters = dataCenters.getSize();
    *dataCentersArr = (int*)malloc((sizeof(int))*dataCenters.getSize());
    if (*dataCentersArr == nullptr) return DS_ALLOCATION_ERROR;

    // inorder traversal on the OS tree to fill the array
    int j = 0;
    if (os == LINUX) {
        for (auto i=linuxSorted.begin(); i != linuxSorted.end(); i++, j++) {
            (*dataCentersArr)[j] = *i;
        }
    } else {
        for (auto i=windowsSorted.begin(); i != windowsSorted.end(); i++, j++) {
            (*dataCentersArr)[j] = *i;
        }
    }

    return DS_SUCCESS;
}