#include "AVL.h"
#include "DataCenter.h"
#ifndef DATACENTERS_WET1_DATASYSTEM_H
#define DATACENTERS_WET1_DATASYSTEM_H

// KeyType for the trees that are sorted by operation system
struct OSKey {
    int serverCount, dataCenterID;

    OSKey(int serverCount, int dataCenterID) :
        serverCount(serverCount), dataCenterID(dataCenterID) {};

    bool operator<(const OSKey& other) const;
    bool operator==(const OSKey& other) const;
};

class DataSystem {
public:
    DataSystem() = default;
    DSStatusType AddDataCenter(int dataCenterID, int numOfServers);
    DSStatusType RemoveDataCenter(int dataCenterID);
    DSStatusType RequestServer(int dataCenterID, unsigned int serverID, OS os, int* assignedID);
    DSStatusType FreeServer(int dataCenterID, unsigned int serverID);
    DSStatusType GetDataCentersByOS(OS os, int** dataCenters, int* numOfDataCenters);

private:
    AVL<int, DataCenter*> dataCenters;
    AVL<OSKey, int> windowsSorted;
    AVL<OSKey, int> linuxSorted;
};

#endif //DATACENTERS_WET1_DATASYSTEM_H
