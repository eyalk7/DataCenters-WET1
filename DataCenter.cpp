#include "DataCenter.h"

DataCenter::DataCenter(int numOfServers) {
    // initialize servers array (c'tor fills automatically)
    // if bad alloc DataSystem will catch
    servers = new Server[numOfServers];

    // initialize roots of doubly linked lists
    winDummy = new ServerNode(-1);
    linuxDummy = new ServerNode(-1);

    // connect the linux linked list
    // next: lower in priority, prev: upper in priority
    // dummy node's next: first in priority
    // dummy node's prev: last in priority
    ServerNode* iter = linuxDummy;
    for (int i=0; i<numOfServers; i++) {
        iter->next = servers[i].inList;
        servers[i].inList->prev = iter;
        iter = iter->next;
    }
    iter->next = linuxDummy;
    linuxDummy->prev = iter;
}

DataCenter::~DataCenter() {
    // delete all nodes in linked lists
    DeleteServersList(linuxDummy);
    DeleteServersList(winDummy);

    // delete array
    delete servers;
}

StatusType DataCenter::RequestServer(int serverID, OS os, int *assignedID) {
    if (serverID > winNum + linuxNum - 1) return INVALID_INPUT; // no such server in DC
    if (!assignedID) return INVALID_INPUT; // null pointer

    if ( servers[serverID].isUsed ) { // wanted server is used, get other
        if (os == LINUX) {
            if (linuxDummy->next != linuxDummy) {
                serverID = linuxDummy->next->idx;
            } else if (winDummy->next != winDummy) {
                serverID = winDummy->next->idx;
            } else {
                return FAILURE; // no server available
            }
        } else { // os == WINDOWS
            if (winDummy->next != winDummy) {
                serverID = winDummy->next->idx;
            } else if (linuxDummy->next != linuxDummy) {
                serverID = linuxDummy->next->idx;
            } else {
                return FAILURE; // no server available
            }
        }
    }

    // change OS if needed
    if (os != servers[serverID].os) {
        if (os == LINUX) {
            linuxNum++;
            winNum--;
            servers[serverID].os = LINUX;
        } else { // os == WINDOWS
            winNum++;
            linuxNum--;
            servers[serverID].os == WINDOWS;
        }
    }

    // remove from list
    auto nextServer = servers[serverID].inList->next;
    auto prevServer = servers[serverID].inList->prev;
    prevServer->next = nextServer;
    nextServer->prev = prevServer;

    // set used
    servers[serverID].isUsed = true;

    // return serverID in assignedID
    *assignedID = serverID;

    return SUCCESS;
}

StatusType DataCenter::FreeServer(int serverID) {
    if (serverID > winNum + linuxNum - 1) return INVALID_INPUT; // no such server in DC
    if (!servers[serverID].isUsed) return FAILURE; // the server is already free

    // insert node in end of list
    ServerNode* lastInList;
    if (servers[serverID].os == LINUX) {
        lastInList = linuxDummy->prev;
        servers[serverID].inList->next = linuxDummy;
        linuxDummy->prev = servers[serverID].inList;
    } else { // os == WINDOWS
        lastInList = winDummy->prev;
        servers[serverID].inList->next = winDummy;
        winDummy->prev = servers[serverID].inList;
    }
    lastInList->next = servers[serverID].inList;
    servers[serverID].inList->prev = lastInList;

    // mark as unused
    servers[serverID].isUsed = false;
}

int DataCenter::GetLinuxNum() const {
    return linuxNum;
}

int DataCenter::GetWinNum() const {
    return winNum;
}

static void DeleteServersList(ServerNode* root) {
    ServerNode* iter = root->next;
    while (iter == root) {
        auto to_delete = iter;
        iter = iter->next;
        delete to_delete;
    }
    delete root;
}