#include "DataSystem.h"

// OSKey class implementation
bool OSKey::operator<(const OSKey& other) const {
    // by num of servers and by id
}

bool OSKey::operator==(const OSKey& other) const {
    // by num of servers and by id
}

// DataSystem class implementation
StatusType DataSystem::AddDataCenter(int dataCenterID, int numOfServers) {
    // insert to the avl trees
}

StatusType DataSystem::RemoveDataCenter(int dataCenterID) {
    // create oskey by from the data in the ID tree
    // remove from the avl trees
}

StatusType DataSystem::RequestServer(int dataCenterID, int serverID, int os, int *assignedID) {
    // find the data center on the tree
    // remove from the two os avl trees the oskey
    // request the server from the data center
    // insert to the two os avl trees the new oskey
}

StatusType DataSystem::FreeServer(int dataCenterID, int serverID) {
    // find the data center on the tree
    // free the server from the data center
}

StatusType DataSystem::GetDataCentersByOS(int os, int **dataCenters, int *numOfDataCenters) {
    // inorder traversal on the os tree
    // fill array backwards
}