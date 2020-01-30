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
        iter->server_id=i;
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
    delete[] servers;
}

DSStatusType DataCenter::RequestServer(unsigned int serverID, OS os, int *assignedID) {
    if ((int)serverID > winNum + linuxNum - 1) return DS_INVALID_INPUT; // no such server in DC
    if (!assignedID) return DS_INVALID_INPUT; // null pointer

    // if the wanted server is used
    if (servers[serverID].isUsed) {
        // get the required pointers based on the given OS
        ServerNode *os_dummy = linuxDummy;
        ServerNode *other_os_dummy = winDummy;
        if (os == WINDOWS) {
            os_dummy = winDummy;
            other_os_dummy = linuxDummy;
        }

        // change the server ID we want accordingly
        if (os_dummy->next != os_dummy) {
            // try to get first free server from the requested OS
            serverID = os_dummy->next->server_id;
        } else if (other_os_dummy->next != other_os_dummy) {
            // else, try to get first free server from the other OS
            serverID = other_os_dummy->next->server_id;
        } else {
            return DS_FAILURE;  // no servers available
        }
    }

    // get the server we're going to return
    Server& server = servers[serverID];

    // update OS and server counts accordingly
    if (os != server.os) {
        if (os == LINUX) {
            linuxNum++;
            winNum--;
        } else { // os == WINDOWS
            winNum++;
            linuxNum--;
        }
    }
    server.os = os;

    // remove server's node from "free servers" list
    auto nextServer = server.index_node->next;
    auto prevServer = server.index_node->prev;
    prevServer->next = nextServer;
    nextServer->prev = prevServer;
    server.index_node->next = nullptr;
    server.index_node->prev = nullptr;

    // set as used
    server.isUsed = true;

    // return the server's ID in assignedID
    *assignedID = serverID;

    return DS_SUCCESS;
}

DSStatusType DataCenter::FreeServer(unsigned int serverID) {
    if ((int) serverID > winNum + linuxNum - 1) return DS_INVALID_INPUT; // no such server in DC
    if (!servers[serverID].isUsed) return DS_FAILURE; // the server is already free

    // get the server we're going to free and it's corresponding node
    Server &server = servers[serverID];
    ServerNode* node = server.index_node;

    // get the pointer for the "free servers" list of the given OS
    ServerNode *dummy = linuxDummy;
    if (server.os == WINDOWS)
        dummy = winDummy;

    // insert the server's node at end of the list
    ServerNode *lastInList = dummy->prev;
    node->next = dummy;
    dummy->prev = node;
    lastInList->next = node;
    node->prev = lastInList;

    // mark server as unused
    server.isUsed = false;

    return DS_SUCCESS;
}

int DataCenter::GetLinuxNum() const {
    return linuxNum;
}

int DataCenter::GetWinNum() const {
    return winNum;
}