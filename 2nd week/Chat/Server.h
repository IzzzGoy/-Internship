//
// Created by Alex on 20.08.2020.
//

#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <WinSock2.h>
#include <cstdint>
#include <thread>
#include <vector>
#include <mutex>
#include "POJOUser.h"

using namespace std;

class Server {
public:
    vector<POJOUser> users;
    bool is_working;

    explicit Server(uint16_t port);
    bool start();
    void stop();
private:


    mutex mtx;
    uint16_t port;
    SOCKET serv_socket;
    WSAData w_data;
    vector<thread> handling_threads;
    thread handle_accept_thread;

    void join_handling_thread();

    void handle(const POJOUser& user);
    void handle_accept();
};


#endif //CHAT_SERVER_H
