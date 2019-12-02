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
    auto DS = Init();

    cout << "by linux: 4 with 14, 3 with 13 and so on..." << endl;
    AddDataCenter(DS, 1, 11);
    AddDataCenter(DS, 2, 12);
    AddDataCenter(DS, 3, 13);
    AddDataCenter(DS, 4, 14);

    int numOfDataCenters;
    int* dataCenters;

    GetDataCentersByOS(DS, 0, &dataCenters, &numOfDataCenters);

    for (int i=0; i < numOfDataCenters; i++) {
        cout << dataCenters[i] << ", ";
    }
    free(dataCenters);
    cout << endl;

    int dummy;
    RequestServer(DS, 2, 0, 1, &dummy);
    RequestServer(DS, 2, 0, 1, &dummy);
    RequestServer(DS, 2, 0, 1, &dummy);
    RequestServer(DS, 2, 0, 1, &dummy);

    RequestServer(DS, 3, 0, 1, &dummy);
    RequestServer(DS, 3, 0, 1, &dummy);
    RequestServer(DS, 3, 0, 1, &dummy);

    RequestServer(DS, 1, 0, 1, &dummy);
    RequestServer(DS, 1, 0, 1, &dummy);

    RequestServer(DS, 4, 0, 1, &dummy);
    RequestServer(DS, 4, 0, 1, &dummy);

    GetDataCentersByOS(DS, 1, &dataCenters, &numOfDataCenters);

    cout << "by windows: 2 with 4, 3 with 3, 1 with 2, 4 with 2" << endl;
    for (int i=0; i < numOfDataCenters; i++) {
        cout << dataCenters[i] << ", ";
    }
    free(dataCenters);
    cout << endl;

    GetDataCentersByOS(DS, 0, &dataCenters, &numOfDataCenters);

    cout << "by linux" << endl;
    for (int i=0; i < numOfDataCenters; i++) {
        cout << dataCenters[i] << ", ";
    }
    free(dataCenters);
    cout << endl;

    Quit(&DS);
}