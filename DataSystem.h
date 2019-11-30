#ifndef DATACENTERS_WET1_DATASYSTEM_H
#define DATACENTERS_WET1_DATASYSTEM_H

#include "DataCenter.h"
#include "AVL.h"

// key class for the trees that are sorted by operation system
class OSKey {
public:
    OSKey(int serverCount, int dataCenterID) :
        serverCount( serverCount ), dataCenterID( dataCenterID ) {};
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
    StatusType RequestServer(int dataCenterID, int serverID, OS os, int *assignedID);
    StatusType FreeServer(int dataCenterID, int serverID);
    StatusType GetDataCentersByOS(OS os, int **dataCenters, int *numOfDataCenters);

private:
    AVL<int, DataCenter*> dataCenters;
    AVL<OSKey, int> windowsSorted
    AVL<OSKey, int> linuxSorted;

};


#endif //DATACENTERS_WET1_DATASYSTEM_H
