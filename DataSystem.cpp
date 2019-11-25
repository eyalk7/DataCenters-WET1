#include "DataSystem.h"

// OSKey class implementation
bool OSKey::operator<(const OSKey& other) const {
    // if same numbers of servers, than smaller ID come first in INORDER traversal
    if (serverCount == other.serverCount) return dataCenterID < other.dataCenterID;

    // else, more servers means to come first in INORDER traversal
    return serverCount > other.serverCount;
}

bool OSKey::operator==(const OSKey& other) const {
    return serverCount == other.serverCount && dataCenterID == other.dataCenterID;
}

// DataSystem class implementation
StatusType DataSystem::AddDataCenter(int dataCenterID, int numOfServers) {
    if (dataCenterID <= 0 || numOfServers <= 0) return INVALID_INPUT;

    try {
        // initialize keys and data
        auto dataCenter = new DataCenter(numOfServers);

        OSKey linuxTreeKey(numOfServers, dataCenterID);
        OSKey winTreeKey(0, dataCenterID);

        // insert to the avl trees
        if (dataCenters.insert(dataCenterID, dataCenter) != AVL_SUCCESS) return FAILURE;
        if (windowsSorted.insert(winTreeKey, dataCenterID) != AVL_SUCCESS) return FAILURE;
        if (linuxSorted.insert(linuxTreeKey, dataCenterID) != AVL_SUCCESS) return FAILURE;

    } catch (std::bad_alloc& ba) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType DataSystem::RemoveDataCenter(int dataCenterID) {
    if (dataCenterID <= 0) return INVALID_INPUT;

    // create OSKey from the data in the dataCenters tree
    auto dataCenter = dataCenters.get(dataCenterID);
    if (!dataCenter) return FAILURE; // no such DC

    OSKey linuxTreeKey(dataCenter->GetLinuxNum(), dataCenterID);
    OSKey winTreeKey(dataCenter->GetWinNum(), dataCenterID);

    // delete dataCenter
    delete dataCenter;

    // remove from the avl trees
    dataCenters.remove(dataCenterID);
    linuxSorted.remove(linuxTreeKey);
    windowsSorted.remove(winTreeKey);

    return SUCCESS;
}

StatusType DataSystem::RequestServer(int dataCenterID, int serverID, OS os, int *assignedID) {
    if (dataCenterID <= 0 || serverID < 0) return INVALID_INPUT;
    if (!assignedID) return INVALID_INPUT; // null pointer

    // find the data center on the tree
    auto dataCenter = dataCenters.get(dataCenterID);
    if (!dataCenter) return FAILURE; // no such DC

    // Create OSKey from the current data
    OSKey linuxTreeKeyBefore(dataCenter->GetLinuxNum(), dataCenterID);
    OSKey winTreeKeyBefore(dataCenter->GetWinNum(), dataCenterID);

    // request the server from the data center
    auto res = dataCenter->RequestServer(serverID, os, assignedID);
    if (res != SUCCESS) return res;

    // Create OSKey from the new data
    OSKey linuxTreeKeyAfter(dataCenter->GetLinuxNum(), dataCenterID);
    OSKey winTreeKeyAfter(dataCenter->GetWinNum(), dataCenterID);

    // remove from the two OS avl trees the old oskey and insert the new ones
    linuxSorted.remove(linuxTreeKeyBefore);
    windowsSorted.remove(winTreeKeyBefore);
    linuxSorted.insert(linuxTreeKeyAfter, dataCenterID);
    windowsSorted.insert(winTreeKeyAfter, dataCenterID);

    // how to handle bad alloc?

    return SUCCESS;
}

StatusType DataSystem::FreeServer(int dataCenterID, int serverID) {
    if (dataCenterID <= 0 || serverID < 0) return INVALID_INPUT;

    // find the data center on the tree
    auto dataCenter = dataCenters.get(dataCenterID);
    if (!dataCenter) return FAILURE; // no such DC

    // free the server from the data center
    return dataCenter->FreeServer(serverID);
}

StatusType DataSystem::GetDataCentersByOS(OS os, int **dataCentersArr, int *numOfDataCenters) {
    if (!dataCenters || !numOfDataCenters) return INVALID_INPUT;
    if (dataCenters.size() == 0) return FAILURE; // no data centers

    *numOfDataCenters = dataCenters.size();
    *dataCentersArr = malloc((sizeof(int))*dataCenters.size());
    if (*dataCentersArr == NULL) return ALLOCATION_ERROR;

    // inorder traversal on the OS tree
    if (os == LINUX) {
        for (auto i=linuxSorted.begin(), j = 0; i != linuxSorted.end(); i++, j++) {
            (*dataCentersArr)[j] = *i;
        }
    } else {
        for (auto i=windowsSorted.begin(), j = 0; i != windowsSorted.end(); i++, j++) {
            (*dataCentersArr)[j] = *i;
        }
    }

    return SUCCESS;
}