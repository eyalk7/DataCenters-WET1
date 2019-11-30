#include "library1.h"

int main() {
    void* DS = Init();
    AddDataCenter(DS,123,5); // New data center with 5 servers

    int assignedID1, assignedID2, assignedID3;
    RequestServer(DS, 123, 3, 1, &assignedID1); // Assigns server 3 as Windows
    RequestServer(DS, 123, 3, 0, &assignedID2); // Assigns server 0 as Linux
    RequestServer(DS, 123, 0, 1, &assignedID3); // Assigns server 1 as Windows

    FreeServer(DS, 123, 1); // Frees server 1
    FreeServer(DS, 123, 3); // Frees server 3
    FreeServer(DS, 123, 3); // Server 3 is already free

    AddDataCenter(DS, 456, 2); // New data center with 2 servers

    int assignedID4;
    RequestServer(DS, 456, 0, 1, &assignedID4); // Assigns server 0 as Windows

    int* dataCenters1;
    int numOfDataCenters1;
    GetDataCentersByOS(DS, 1, &dataCenters1, &numOfDataCenters1); // Sorted by Windows

    AddDataCenter(DS, 789, 10);

    int* dataCenters2;
    int numOfDataCenters2;
    GetDataCentersByOS(DS, 0, &dataCenters2, &numOfDataCenters2); // Sorted by Linux

    RemoveDataCenter(DS, 123);

    int assignedID5;
    RequestServer(DS, 123, 3, 1, &assignedID5); // Data center does not exist anymore

    AddDataCenter(DS, 123, -5); // Invalid input is checked first

    Quit(&DS);
}