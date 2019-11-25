#ifndef DATACENTERS_WET1_DATACENTER_H
#define DATACENTERS_WET1_DATACENTER_H

typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;
enum OS {LINUX, WINDOWS};

class DataCenter {
public:
    DataCenter(int numOfServers);
    ~DataCenter();
    StatusType RequestServer(int serverID, OS os, int *assignedID);
    StatusType FreeServer(int serverID);
    int GetLinuxNum() const;
    int GetWinNum() const;

private:
    class ServerNode {
    public:
        int idx;
        ServerNode *next, *prev;

        ServerNode(int idx) :
            idx( idx ), next( nullptr ), prev( nullptr ) {};
    };

    class Server {
    public:
        ServerNode* inList;
        bool isUsed;
        OS os;

        Server() :
            inList( new ServerNode(i) ), isUsed( false ), os( LINUX ) {};
    };

    Server* servers;
    ServerNode *winDummy, *linuxDummy;
    int linuxNum, winNum;

    static void DeleteServersList(ServerNode* root);
};


#endif //DATACENTERS_WET1_DATACENTER_H
