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
    int numOfServers = 1000, numOfFarms = 1000;

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

    cout << "try to request a server (all should be used)" << endl;
    for (int i=1; i<numOfFarms; i++) {
        auto res = RequestServer(DS, i, 0, 0, &dummy);
        if (res != FAILURE) printRes(res);
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

    cout << "try to request a server (all should be used)" << endl;
    for (int i=1; i<numOfFarms; i++) {
        auto res = RequestServer(DS, i, 0, 0, &dummy);
        if (res != FAILURE) printRes(res);
    }
    cout << endl;

 /*   // RemoveDataCenter
    cout << "RemoveDataCenter: " << endl;
    for (int i=1; i<numOfFarms; i++) {
        auto res = RemoveDataCenter(DS, i);
        if (res != SUCCESS) printRes(res);
    }
    cout << endl;*/

    Quit(&DS);
    cout << "finished";

    return 0;
}