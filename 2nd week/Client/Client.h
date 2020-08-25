//
// Created by Alex on 20.08.2020.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <WinSock2.h>
#include <cstdint>
#include <string>
#include <thread>

using namespace std;

class Client {
public:
    Client(uint16_t port, const string& address);
    void stop();
    bool is_work();
private:
    bool is_working = true;
    char name[32];
    SOCKET c_sock;
    SOCKADDR_IN c_addr;

    void input_handle_fun();
    void output_handle_fun();

    thread input_handler;
    thread output_handler;
};


#endif //CLIENT_CLIENT_H
