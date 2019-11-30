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
        unsigned int idx;
        ServerNode *next, *prev;

        explicit ServerNode(int idx) :
            idx( idx ), next( nullptr ), prev( nullptr ) {};
    };

    struct Server {
        ServerNode* inList;
        bool isUsed;
        OS os;

        Server() :
            inList( new ServerNode(0) ), isUsed( false ), os( LINUX ) {};
    };

    Server* servers;
    ServerNode* winDummy, * linuxDummy;
    int linuxNum, winNum;

    static void DeleteServersList(ServerNode* root);
};


#endif //DATACENTERS_WET1_DATACENTER_H
