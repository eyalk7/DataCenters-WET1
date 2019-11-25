#ifndef DATACENTERS_WET1_DATACENTER_H
#define DATACENTERS_WET1_DATACENTER_H

enum StatusType {SUCCESS, FAILURE, INVALID_INPUT, ALLOCATION_ERROR };
enum OS {LINUX, WINDOWS};

class DataCenter {
    DataCenter();
    ~DataCenter();
    StatusType RequestServer(int serverID, int os, int *assignedID);
    StatusType FreeServer(int serverID);
    int GetLinuxNum() const;
    int GetWinNum() const;

private:
    class ServerNode {
    public:
        int idx;
        ServerNode *next, *prev;

        ServerNode(int idx, ServerNode* next = nullptr, ServerNode* prev = nullptr) :
                idx( idx ), next( next ), prev( prev ) {};
    };

    class Server {
    public:
        ServerNode* inList;
        bool isUsed;
        OS os;

        Server(Node* inList = nullptr) :
            inList( inList ), isUsed( false ), os( LINUX ) {};
    };

    Server* servers;
    ServerNode *winDummy, *linuxDummy;
    int linuxNum, winNum;
};


#endif //DATACENTERS_WET1_DATACENTER_H
