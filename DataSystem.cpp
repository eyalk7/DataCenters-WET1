#include <new>
#include <cstdlib>
#include "AVL.h"
#include "DataSystem.h"

/*------------------ OSKey class implementation ----------------------*/
bool OSKey::operator<(const OSKey& other) const {
    // if same num of servers, then one with smaller ID comes first in the INORDER traversal
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

/*------------------MultiOSDataSystem class implementation----------------------*/
DataSystem::~DataSystem() {
    for (auto iter = dataCenters.begin(); iter != dataCenters.end(); iter++) {
        delete (*iter);
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
        if (dataCenters.insert(dataCenterID, dataCenterPtr) != AVL_SUCCESS)  {
            delete dataCenterPtr;
            return DS_FAILURE;
        }
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

    OSKey linuxKey(dataCenterPtr->GetLinuxNum(), dataCenterID);
    OSKey windowsKey(dataCenterPtr->GetWinNum(), dataCenterID);

    // request the server from the data center
    auto status = dataCenterPtr->RequestServer(serverID, os, assignedID);
    if (status != DS_SUCCESS) return status;

    // remove from the two OS avl trees the old OSkeys
    linuxSorted.remove(linuxKey);
    windowsSorted.remove(windowsKey);

    // update the OSKeys' data
    linuxKey.serverCount = dataCenterPtr->GetLinuxNum();
    linuxKey.dataCenterID = dataCenterID;
    windowsKey.serverCount = dataCenterPtr->GetWinNum();
    windowsKey.dataCenterID = dataCenterID;

    // insert the updated OSkeys to the OS avl trees
    try {
        linuxSorted.insert(linuxKey, dataCenterID);
        windowsSorted.insert(windowsKey, dataCenterID);
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

    int size = dataCenters.getSize();
    if (size == 0) return DS_FAILURE; // no data centers

    *numOfDataCenters = size;
    *dataCentersArr = (int*)malloc((sizeof(int))*size);
    if (*dataCentersArr == nullptr) return DS_ALLOCATION_ERROR;

    // inorder traversal on the OS tree to fill the array
    auto node = linuxSorted.begin();
    auto end = linuxSorted.end();

    if (os == WINDOWS) {
        node = windowsSorted.begin();
        end = windowsSorted.end();
    }

    int index = 0;
    for (; node != end; node++, index++) {
        (*dataCentersArr)[index] = *node;
    }

    return DS_SUCCESS;
}