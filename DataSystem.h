#ifndef DATACENTERS_WET1_DATASYSTEM_H
#define DATACENTERS_WET1_DATASYSTEM_H

#include "DataCenter.h"

// key class for the trees that are sorted by operation system
class OSKey {
public:
    OSKey(int serverCount, int dataCenterID);
    bool operator<(const OSKey& other) const;
    bool operator==(const OSKey& other) const;

private:
    int serverCount, dataCenterID;
};

class DataSystem {
public:
    DataSystem();
    StatusType AddDataCenter(int dataCenterID, int numOfServers);
    StatusType RemoveDataCenter(int dataCenterID);
    StatusType RequestServer(int dataCenterID, int serverID, int os, int *assignedID);
    StatusType FreeServer(int dataCenterID, int serverID);
    StatusType GetDataCentersByOS(int os, int **dataCenters, int *numOfDataCenters);

private:
    AVL<int, DataCenter> data_centers;
    AVL<OSKey, int> windowsSorted
    AVL<OSKey, int> linuxSorted;

};


#endif //DATACENTERS_WET1_DATASYSTEM_H
