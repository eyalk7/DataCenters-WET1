#include "DataCenter.h"
#include "AVL.h"

DataCenter::DataCenter(int numOfServers) :
    servers(new Server[numOfServers]),
    winDummy(new ServerNode(-1)),
    linuxDummy(new ServerNode(-1)),
    linuxNum(numOfServers), winNum(0) {

    // connect the windows linked list
    winDummy->next=winDummy;
    winDummy->prev=winDummy;

    // connect the linux linked list
    // next: lower in priority, prev: upper in priority
    // dummy node's next: first in priority
    // dummy node's prev: last in priority
    ServerNode* iter = linuxDummy;
    for (int i=0; i<numOfServers; i++) {
        iter->next = servers[i].index_node;
        servers[i].index_node->prev = iter;
        iter = iter->next;
        iter->idx=i;
    }
    iter->next = linuxDummy;
    linuxDummy->prev = iter;
}

DataCenter::~DataCenter() {
    // delete all nodes in linked lists
    int numOfServers = linuxNum + winNum;
    for (int i=0; i<numOfServers; i++) {
        delete servers[i].index_node;
    }

    // delete dummy nodes
    delete linuxDummy;
    delete winDummy;

    // delete array
    delete servers;
}

DSStatusType DataCenter::RequestServer(unsigned int serverID, OS os, int *assignedID) {
    if ((int)serverID > winNum + linuxNum - 1) return DS_INVALID_INPUT; // no such server in DC
    if (!assignedID) return DS_INVALID_INPUT; // null pointer

    if (servers[serverID].isUsed) { // wanted server is used, get other
        if (os == LINUX) {
            if (linuxDummy->next != linuxDummy) {
                serverID = linuxDummy->next->idx;
            } else if (winDummy->next != winDummy) {
                serverID = winDummy->next->idx;
            } else {
                return DS_FAILURE; // no server available
            }
        } else { // os == WINDOWS
            if (winDummy->next != winDummy) {
                serverID = winDummy->next->idx;
            } else if (linuxDummy->next != linuxDummy) {
                serverID = linuxDummy->next->idx;
            } else {
                return DS_FAILURE; // no server available
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
            servers[serverID].os = WINDOWS;
        }
    }

    // remove from list
    auto nextServer = servers[serverID].index_node->next;
    auto prevServer = servers[serverID].index_node->prev;
    prevServer->next = nextServer;
    nextServer->prev = prevServer;

    // set used
    servers[serverID].isUsed = true;

    // return serverID in assignedID
    *assignedID = serverID;

    return DS_SUCCESS;
}

DSStatusType DataCenter::FreeServer(unsigned int serverID) {
    if ((int)serverID > winNum + linuxNum - 1) return DS_INVALID_INPUT; // no such server in DC
    if (!servers[serverID].isUsed) return DS_FAILURE; // the server is already free

    // insert node in end of list
    ServerNode* lastInList;
    if (servers[serverID].os == LINUX) {
        lastInList = linuxDummy->prev;
        servers[serverID].index_node->next = linuxDummy;
        linuxDummy->prev = servers[serverID].index_node;
    } else { // os == WINDOWS
        lastInList = winDummy->prev;
        servers[serverID].index_node->next = winDummy;
        winDummy->prev = servers[serverID].index_node;
    }
    lastInList->next = servers[serverID].index_node;
    servers[serverID].index_node->prev = lastInList;

    // mark as unused
    servers[serverID].isUsed = false;
    return DS_SUCCESS;
}

int DataCenter::GetLinuxNum() const {
    return linuxNum;
}

int DataCenter::GetWinNum() const {
    return winNum;
}