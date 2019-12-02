#ifndef DATACENTERS_WET1_DATACENTER_H
#define DATACENTERS_WET1_DATACENTER_H

typedef enum {
    DS_SUCCESS = 0,
    DS_FAILURE = -1,
    DS_ALLOCATION_ERROR = -2,
    DS_INVALID_INPUT = -3
} DSStatusType;

enum OS {LINUX, WINDOWS};

class DataCenter {
public:
    explicit DataCenter(int numOfServers);
    ~DataCenter();
    DSStatusType RequestServer(unsigned int serverID, OS os, int *assignedID);
    DSStatusType FreeServer(unsigned int serverID);
    int GetLinuxNum() const;
    int GetWinNum() const;

private:
    struct ServerNode {
        unsigned int server_id; // the index of the server in the server array
        ServerNode *next, *prev;

        explicit ServerNode(int server_id) :
            server_id( server_id ), next( nullptr ), prev( nullptr ) {};
    };

    struct Server {
        ServerNode* index_node;
        bool isUsed;
        OS os;

        Server() :
            index_node( new ServerNode(0) ), isUsed( false ), os( LINUX ) {};
    };

    Server* servers;
    ServerNode* winDummy, *linuxDummy;
    int linuxNum, winNum;
};


#endif //DATACENTERS_WET1_DATACENTER_H
