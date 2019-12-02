#include <iostream>
#include <vector>
#include <limits>
#include "library1.h"

using std::vector;
using std::cout;
using std::endl;

void printRes(StatusType res) {
    switch (res) {
        case SUCCESS: cout << "SUCCESS" << endl; break;
        case ALLOCATION_ERROR: cout << "ALLOCATION_ERROR" << endl; break;
        case INVALID_INPUT: cout << "INVALID_INPUT" << endl; break;
        case FAILURE: cout << "FAILURE" << endl; break;
    }
}

int main() {
    // Init
    void* DS = Init();
    if (DS) cout << "init done." << endl;
    cout << endl;

    // AddDataCenter
    cout << "AddDataCenter:" << endl;
    cout << "DS is nullptr" << endl;
    printRes( AddDataCenter(nullptr,1,2) );
    cout << "DataCenterID <= 0" << endl;
    printRes( AddDataCenter(DS,0,2) );
    cout << "NumOfServers <= 0" << endl;
    printRes( AddDataCenter(DS,1,0) );
    AddDataCenter(DS,1,10);
    cout << "try to add DataCenter with ID that is already used" << endl;
    printRes( AddDataCenter(DS,1,1) );
    cout << endl;

    // RequestServer
    cout << "RequestServer:" << endl;
    int dummy;
    cout << "DS is nullptr" << endl;
    printRes( RequestServer(nullptr, 23, 234, 0, &dummy) );
    cout << "DataCenterID <= 0" << endl;
    printRes( RequestServer(DS, 0, 234, 0, &dummy) );
    cout << "serverID < 0" << endl;
    printRes( RequestServer(DS, 1, -1, 0, &dummy) );
    cout << "serverID >= numOfServers" << endl;
    printRes( RequestServer(DS, 1, 10, 0, &dummy) );
    cout << "os < 0" << endl;
    printRes( RequestServer(DS, 1, 9, -1, &dummy) );
    cout << "os > 1" << endl;
    printRes( RequestServer(DS, 1, 9, 2, &dummy) );
    cout << "assignedID is nullptr" << endl;
    printRes( RequestServer(DS, 1, 9, 1, nullptr) );
    cout << "no DataCenter with given ID" << endl;
    printRes( RequestServer(DS, 2, 9, 1, &dummy) );
    AddDataCenter(DS, 2, 1);
    RequestServer(DS, 2, 0, 0, &dummy);
    cout << "no unused server" << endl;
    printRes( RequestServer(DS, 2, 0, 0, &dummy) );
    cout << endl;

    // FreeServer
    cout << "FreeServer:" << endl;
    cout << "DS is nullptr" << endl;
    printRes( FreeServer(nullptr, 1, 0) );
    cout << "dataCenterID <= 0:" << endl;
    printRes( FreeServer(DS, 0, 0) );
    cout << "serverID < 0:" << endl;
    printRes( FreeServer(DS, 1, -1) );
    cout << "serverID >= numOfServers:" << endl;
    printRes( FreeServer(DS, 1, 10) );
    cout << "no DataCenter with given ID" << endl;
    printRes( FreeServer(DS, 3, 10) );
    cout << "given server already free" << endl;
    printRes( FreeServer(DS, 1, 0) );
    cout << endl;

    // GetDataCentersByOS
    int* dummy_arr;
    cout << "GetDataCentersByOS:" << endl;
    cout << "DS is nullptr" << endl;
    printRes( GetDataCentersByOS(nullptr, 0, &dummy_arr, &dummy) );
    cout << "os < 0" << endl;
    printRes( GetDataCentersByOS(DS, -1, &dummy_arr, &dummy) );
    cout << "os > 1" << endl;
    printRes( GetDataCentersByOS(DS, 2, &dummy_arr, &dummy) );
    cout << "dataCenter is nullptr" << endl;
    printRes( GetDataCentersByOS(DS, 0, nullptr, &dummy) );
    cout << "numOfDataCenters is nullptr" << endl;
    printRes( GetDataCentersByOS(DS, 0, &dummy_arr, nullptr) );
    void* DS2 = Init();
    cout << "no DataCenters in DS" << endl;
    printRes( GetDataCentersByOS(DS2, 0, &dummy_arr, &dummy) );
    cout << endl;

    // RemoveDataCenter
    cout << "RemoveDataCenter: " << endl;
    cout << "DS is nullptr" << endl;
    printRes( RemoveDataCenter(nullptr, 1) );
    cout << "dataCenterID <= 0" << endl;
    printRes( RemoveDataCenter(DS, 0) );
    cout << "no dataCenter with given ID" << endl;
    printRes( RemoveDataCenter(DS, 3) );
    cout << endl;

    Quit(&DS);
    cout << "finished";

    return 0;
}