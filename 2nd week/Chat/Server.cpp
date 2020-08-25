//
// Created by Alex on 20.08.2020.
//

#include <iostream>
#include "Server.h"
#include <chrono>

Server::Server(uint16_t port) : port(port){}

bool Server::start() {
    WSAStartup(MAKEWORD(2,2), &w_data);
    SOCKADDR_IN address;
    address.sin_addr.S_un.S_addr = INADDR_ANY;
    address.sin_port = htons(port);
    address.sin_family = AF_INET;

    if (static_cast<int>(serv_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR){
        return false;
    }

    if(bind(serv_socket, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        return false;
    }

    if(listen(serv_socket, SOMAXCONN) == SOCKET_ERROR) {
        return false;
    }

    handle_accept_thread = thread(&Server::handle_accept, this);
    return true;
}

void Server::handle(const POJOUser& user) {
    char buffer[1024];
    char b = '1';
    while(true){
        recv(user.socket, &b,1,0);
        if (b == '0'){
            cout << user.username << endl;
            break;
        }
        int size;
        recv(user.socket,(char*)&size,sizeof(int),0);
        recv(user.socket, buffer, sizeof(buffer),0);

        if (size > 0){
            for (auto & i : users) {
                if (i.socket != user.socket){
                    send(i.socket, user.username.data(), 32,0);
                    send(i.socket,(char*)&size, sizeof(int), 0);
                    send(i.socket, buffer, size, 0);
                }
            }
        }
    }
    mtx.lock();
    for (int j = 0; j < users.size(); ++j) {
        if (users.at(j).socket == user.socket) {
            users.erase(users.begin() + j);
            break;
        }
    }
    char end[1024]{"Was lived from chat"};
    for (auto& u : users) {
        send(u.socket,user.username.data(), 32,0);
        send(u.socket, end, 1024, 0);
    }
    mtx.unlock();
    closesocket(user.socket);
    if (users.empty()){
        is_working = false;
    }
}

void Server::join_handling_thread() {
    closesocket(serv_socket);
    WSACleanup();
    handle_accept_thread.join();
    for (auto & handling_thread : handling_threads) {
        if (handling_thread.joinable())handling_thread.join();
    }
}

void Server::handle_accept() {
    is_working = true;
    users = vector<POJOUser>();
    char hello[] = {"was connected"};
    int hello_size = sizeof(hello);
    while (Server::is_working){
        SOCKADDR_IN client_addr; //Адресс клиента
        int addrlen = sizeof(client_addr); //Размер адреса клиента
        SOCKET client = accept(serv_socket, (struct sockaddr*)&client_addr, &addrlen);
        char buffer[32];
        if (is_working){
            cout << client << endl;
            recv(client,buffer,sizeof(buffer),0);
            POJOUser user(string(buffer),client);
            mtx.lock();
            users.push_back(user);
            mtx.unlock();
            for (auto& iter : users) {
                send(iter.socket, user.username.data(), 32,0);
                send(iter.socket, (char*)&hello_size, sizeof(int),0);
                send(iter.socket, hello, hello_size ,0);
            }
            handling_threads.emplace_back(&Server::handle, this ,user);
        }

    }
}

void Server::stop() {
    join_handling_thread();
}
