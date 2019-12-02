#include <iostream>
#include <vector>
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
    vector<int> assignedIDs(10000000);

    // Init
    void* DS = Init();
    if (DS) cout << "init done." << endl;
    cout << endl;

    // AddDataCenter
    cout << "New data center with 500000 servers:" << endl;
    printRes( AddDataCenter(DS,123,500000) );
    cout << endl;

    // RequestServer
    int dummy;
    cout << "request first 250000 servers as windows";
    for (int i=0; i<250000; i++) {
        auto res = RequestServer(DS, 123, i, 1, &dummy);
        if (res != SUCCESS) printRes(res);
    }
    cout << "request all the rest as linux";
    for (int i=250000; i<500000; i++) {
        auto res = RequestServer(DS, 123, i, 0, &dummy);
        if (res != SUCCESS) printRes(res);
    }
    cout << endl;

    // FreeServer
    cout << "free all even numbered servers" << endl;
    for (int i=0; i<500000; i+=2) {
        auto res = FreeServer(DS, 123, i);
        if (res != SUCCESS) printRes(res);
    }
    cout << endl;

    // RequestServer
    cout << "Assigns 250000 servers as windows" << endl;
    for (int i=0; i<250000; i++) {
        auto res = RequestServer(DS, 123, i, 1, &assignedIDs[i]);
        if (res != SUCCESS) printRes(res);
        cout << assignedIDs[i] << endl;
    }

    // Sorted by Windows
    int* dataCenters1;
    int numOfDataCenters1;
    cout << "GetDataCentersByOS: (windows)" << endl;
    printRes( GetDataCentersByOS(DS, 1, &dataCenters1, &numOfDataCenters1) );
    for (int i=0; i<numOfDataCenters1; i++) {
        cout << dataCenters1[i] << endl;
    }
    cout << endl;
    free(dataCenters1);
    cout << endl;

    // Sorted by Linux
    int* dataCenters2;
    int numOfDataCenters2;
    cout << "GetDataCentersByOS: (linux)" << endl;
    printRes( GetDataCentersByOS(DS, 0, &dataCenters2, &numOfDataCenters2) );
    for (int i=0; i<numOfDataCenters2; i++) {
        cout << dataCenters2[i] << " ";
    }
    cout << endl;
    free(dataCenters2);
    cout << endl;

    // RemoveDataCenter
    cout << "RemoveDataCenter: " << endl;
    printRes( RemoveDataCenter(DS, 123) );
    cout << endl;

    Quit(&DS);

    return 0;
}