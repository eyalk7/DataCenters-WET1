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
    int numOfServers = 10, numOfFarms = 1000000;

    // Init
    void* DS = Init();
    if (DS) cout << "init done." << endl;
    cout << endl;

    // AddDataCenter
    cout << "add New " << numOfFarms << " data centers with " << numOfServers << " servers:" << endl;
    for (int i=1; i<numOfFarms; i++) {
        auto res = AddDataCenter(DS,i,numOfServers);
        if (res != SUCCESS) printRes(res);
    }
    cout << endl;

    // RequestServer
    int dummy;
    cout << "request first " << numOfServers/2 << " servers as windows" << endl;
    for (int i=1; i<numOfFarms; i++) {
        for (int j = 0; j < numOfServers / 2; j++) {
            auto res = RequestServer(DS, i, j, 1, &dummy);
            if (res != SUCCESS) printRes(res);
        }
    }

    cout << "request all the rest as linux" << endl;
    for (int i=1; i<numOfFarms; i++) {
        for (int j = numOfServers / 2; j < numOfServers; j++) {
            auto res = RequestServer(DS, i, j, 0, &dummy);
            if (res != SUCCESS) printRes(res);
        }
    }
    cout << endl;

    // FreeServer
    cout << "free all even numbered servers" << endl;
    for (int i=1; i<numOfFarms; i++) {
        for (int j = 0; j < numOfServers; j += 2) {
            auto res = FreeServer(DS, i, j);
            if (res != SUCCESS) printRes(res);
        }
    }
    cout << endl;

    // RequestServer
    cout << "Assigns " << numOfServers/2 << " servers as windows" << endl;
    for (int i=1; i<numOfFarms; i++) {
        for (int j=0; j<numOfServers/2; j++) {
            auto res = RequestServer(DS, i, j, 1, &dummy);
            if (res != SUCCESS) printRes(res);
        }
    }
/*

    // Sorted by Windows
    int* dataCenters1;
    int numOfDataCenters1;
    cout << "GetDataCentersByOS: (windows)" << endl;
    printRes( GetDataCentersByOS(DS, 1, &dataCenters1, &numOfDataCenters1) );
//    for (int i=0; i<numOfDataCenters1; i++) {
//        cout << dataCenters1[i] << endl;
//    }
    cout << endl;
    free(dataCenters1);
    cout << endl;

    // Sorted by Linux
    int* dataCenters2;
    int numOfDataCenters2;
    cout << "GetDataCentersByOS: (linux)" << endl;
    printRes( GetDataCentersByOS(DS, 0, &dataCenters2, &numOfDataCenters2) );
//    for (int i=0; i<numOfDataCenters2; i++) {
//        cout << dataCenters2[i] << " ";
//    }
    cout << endl;
    free(dataCenters2);
    cout << endl;
*/

    // RemoveDataCenter
    cout << "RemoveDataCenter: " << endl;
    for (int i=1; i<numOfFarms; i++) {
        auto res = RemoveDataCenter(DS, i);
        if (res != SUCCESS) printRes(res);
    }
    cout << endl;

    Quit(&DS);

    return 0;
}