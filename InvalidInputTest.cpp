#include <iostream>
#include "library1.h"
#include "AVL.h"
using std::cout;
using std::endl;

int main() {
    void* DS = Init();
    if (DS) cout << "init done." << endl;

    // New data center with 5 servers
    cout << "AddDataCenter: ";
    if (AddDataCenter(DS,123,5) == SUCCESS) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "FAILURE" << endl;
    }

    int assignedID1, assignedID2, assignedID3;
    RequestServer(DS, 123, 3, 1, &assignedID1); // Assigns server 3 as Windows
    cout << "RequestServer: " << assignedID1 << endl;
    RequestServer(DS, 123, 3, 0, &assignedID2); // Assigns server 0 as Linux
    cout << "RequestServer: " << assignedID2 << endl;
    RequestServer(DS, 123, 0, 1, &assignedID3); // Assigns server 1 as Windows
    cout << "RequestServer: " << assignedID3 << endl;

    // Frees server 1
    cout << "FreeServer: ";
    if (FreeServer(DS, 123, 1) == SUCCESS) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "FAILURE" << endl;
    }

    // Frees server 3
    cout << "FreeServer: ";
    if (FreeServer(DS, 123, 3) == SUCCESS) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "FAILURE" << endl;
    }

    // Server 3 is already free
    cout << "FreeServer: ";
    if (FreeServer(DS, 123, 3) == SUCCESS) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "FAILURE" << endl;
    }

    // New data center with 2 servers
    cout << "AddDataCenter: ";
    if (AddDataCenter(DS, 456, 2) == SUCCESS){
        cout << "SUCCESS" << endl;
    } else {
        cout << "FAILURE" << endl;
    }

    int assignedID4;
    RequestServer(DS, 456, 0, 1, &assignedID4); // Assigns server 0 as Windows
    cout << "RequestServer: " << assignedID4 << endl;

    // Sorted by Windows
    int* dataCenters1;
    int numOfDataCenters1;
    cout << "GetDataCentersByOS: ";
    if (GetDataCentersByOS(DS, 1, &dataCenters1, &numOfDataCenters1) == SUCCESS) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "FAILURE" << endl;
    }
    for (int i=0; i<numOfDataCenters1; i++) {
        cout << dataCenters1[i] << " ";
    }
    cout << endl;
    free(dataCenters1);

    cout << "AddDataCenter: ";
    if (AddDataCenter(DS, 789, 10) == SUCCESS) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "FAILURE" << endl;
    }

    // Sorted by Linux
    int* dataCenters2;
    int numOfDataCenters2;
    cout << "GetDataCentersByOS: ";
    if (GetDataCentersByOS(DS, 0, &dataCenters2, &numOfDataCenters2) == SUCCESS){
        cout << "SUCCESS" << endl;
    } else {
        cout << "FAILURE" << endl;
    }
    for (int i=0; i<numOfDataCenters2; i++) {
        cout << dataCenters2[i] << " ";
    }
    cout << endl;
    free(dataCenters2);

    cout << "RemoveDataCenter: ";
    if (RemoveDataCenter(DS, 123) == SUCCESS){
        cout << "SUCCESS" << endl;
    } else {
        cout << "FAILURE" << endl;
    }

    int assignedID5;
    // Data center does not exist anymore
    cout << "RequestServer: ";
    if (RequestServer(DS, 123, 3, 1, &assignedID5) == SUCCESS) {
        cout << assignedID5 << endl;
    } else {
        cout << "FAILURE" << endl;
    }

    // Invalid input is checked first
    cout << "AddDataCenter: ";
    if (AddDataCenter(DS, 123, -5) == SUCCESS) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "FAILURE" << endl;
    }

    Quit(&DS);

/*
    AVL<int, int> tree;

    tree.insert(1, 1);
    tree.insert(0, 0);
    tree.insert(2, 2);
    tree.insert(6, 6);
    tree.insert(4, 4);
    tree.insert(10, 10);
    tree.insert(18, 18);
    tree.insert(13, 13);

    //tree.remove(4);

    AVL<int, int>::TreeIterator iter = tree.find(8);
    if (iter == tree.end())
        cout << "NOT FOUND - 8";
    else cout << "FOUND - 8";

    cout << endl;

    iter = tree.find(6);
    if (iter == tree.end())
        cout << "NOT FOUND - 6";
    else cout << "FOUND - 6";

    tree.printTree();
    */
    return 0;
}
