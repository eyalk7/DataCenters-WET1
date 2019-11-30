#include <new>
#include "library1.h"
#include "DataSystem.h"

void* Init(){
    try {
        auto *DS = new DataSystem();
        return (void*)DS;
    } catch (std::bad_alloc& ba) {
        return nullptr;
    }
}

StatusType AddDataCenter(void *DS, int dataCenterID, int numOfServers) {
    if (!DS) return INVALID_INPUT;
    if (dataCenterID <= 0 || numOfServers <= 0) return INVALID_INPUT;
    return (StatusType)((DataSystem*)DS)->AddDataCenter(dataCenterID,numOfServers);
}

StatusType RemoveDataCenter(void *DS, int dataCenterID) {
    if (!DS) return INVALID_INPUT;
    if (dataCenterID <= 0) return INVALID_INPUT;
    return (StatusType)((DataSystem*)DS)->RemoveDataCenter(dataCenterID);
}

StatusType RequestServer(void *DS, int dataCenterID, int serverID, int os, int *assignedID) {
    if (!DS || !assignedID) return INVALID_INPUT;
    if (dataCenterID <= 0 || serverID < 0 || os > 1 || os < 0) return INVALID_INPUT;
    return (StatusType)((DataSystem*)DS)->RequestServer(dataCenterID,serverID,(OS)os,assignedID);
}

StatusType FreeServer(void *DS, int dataCenterID, int serverID) {
    if (!DS) return INVALID_INPUT;
    if (dataCenterID <= 0 || serverID < 0) return INVALID_INPUT;
    return (StatusType)((DataSystem*)DS)->FreeServer(dataCenterID,serverID);
}

StatusType GetDataCentersByOS(void *DS, int os, int **dataCenters, int* numOfDataCenters) {
    if (!DS || !dataCenters || !numOfDataCenters) return INVALID_INPUT;
    if (os > 1 || os < 0) return INVALID_INPUT;
    return (StatusType)((DataSystem*)DS)->GetDataCentersByOS((OS)os,dataCenters,numOfDataCenters);
}

void Quit(void** DS) {
    delete DS;
}
