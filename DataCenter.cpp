#include "DataCenter.h"

DataCenter::DataCenter() {
    // initialize array of servers and linked list
    // (with exception handle)
}

DataCenter::~DataCenter() {
    // free

}

StatusType DataCenter::RequestServer(int serverID, int os, int *assignedID) {
    // check if requested is not used.
    // if used:
        // go to first in wanted os list, or the second list if wanted empty

    // change os
    // delete from list
    // set used
    // assignedID = serverID/

    // update linuxNum and winNum

}

StatusType DataCenter::FreeServer(int serverID) {
    // insert node in end of list
    // mark as unused
}

int DataCenter::GetLinuxNum() const {
    // return linuxNum
}

int DataCenter::GetWinNum() const {
    // reuturn winNum
}
