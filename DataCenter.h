#ifndef DATACENTERS_WET1_DATACENTER_H
#define DATACENTERS_WET1_DATACENTER_H

enum OS {LINUX, WINDOWS};

class DataCenter {
    DataCenter();
    ~DataCenter();
    RequestServer(); // if used, get an unused one
    FreeServer();
    GetLinuxNum();
    GetWinNum();

    class Node {
        int idx;
        Node *next, *prev;

        Node();

        friend DataCenter;
    };

private:
    class Server {
    public:
        Server();

        bool is_used;
        OS os;
        Node* in_list;
    };

    Server* servers;
    Node *win_first, *win_last;
    Node *linux_first, *linux_last;
    int linux_num, windows_num;
};


#endif //DATACENTERS_WET1_DATACENTER_H
