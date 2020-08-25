//
// Created by Alex on 20.08.2020.
//

#include "Client.h"
#include <iostream>
#include <fcntl.h>

Client::Client(uint16_t port, const string& address) {
    WSADATA WSAData;
    WSAStartup(514,&WSAData);
    c_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    c_addr.sin_addr.S_un.S_addr = inet_addr(address.data());
    c_addr.sin_family = AF_INET;
    c_addr.sin_port = htons(port);

    int con_stat = connect(c_sock, (SOCKADDR *)&c_addr, sizeof(c_addr));
    if (con_stat == -1){
        cout << "Server error" << endl;
        closesocket(c_sock);
        WSACleanup();
        exit(0);
    }


    cin >> name;
    system("cls");
    send(c_sock, name, 32,0);
    input_handler = thread(&Client::input_handle_fun, this);
    char b = '1';
    while (is_working){
        string mess;
        while(mess.empty()){
            getline(cin, mess);
        }
        if (mess == "exit"){
            stop();
        }
        int size = mess.size();
        send(c_sock, &b,1,0);
        send(c_sock, (char*)&size, sizeof(int),0);
        send(c_sock, mess.data(),size,0);
    }
}

void Client::stop() {
    char b = '0';send(c_sock,&b,1,0);
    closesocket(c_sock);
    WSACleanup();
    is_working = false;

    if (input_handler.joinable()) input_handler.join();
}

void Client::input_handle_fun() {
    u_long block = 0;
    int status = ioctlsocket(c_sock, FIONBIO, &block);

    if (status == -1){
        perror("calling fcntl");
    }
    char* buffer;
    char nickname[32]{' '};
    while (is_working){
        int res = recv(c_sock, nickname, 32,0);
        if (res != -1)cout << endl << nickname << ':' << endl;
        int size;
        recv(c_sock, (char*)&size, sizeof(int),0);
        buffer = new char[size];
        res = recv(c_sock, buffer, size, 0);
        if (res != -1)cout << buffer << endl << endl;
        delete[] buffer;
    }
}

bool Client::is_work() {
    return is_working;
}
