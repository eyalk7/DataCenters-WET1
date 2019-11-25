#ifndef DATACENTERS_WET1_DATASYSTEM_H
#define DATACENTERS_WET1_DATASYSTEM_H

#include "DataCenter.h"

enum StatusType { /* by manual */ };

class OSKey {
public:
    OSKey()
    operator<();
    operator==();

private:
    int server_count, data_center_id;

};

class DataSystem {
public:
    // all functions in manual (targil)
private:
    AVL<int, DataCenter> data_centers;
    AVL<OSKey, int> windows_sorted
    AVL<OSKey, int> linux_sorted;

};


#endif //DATACENTERS_WET1_DATASYSTEM_H
