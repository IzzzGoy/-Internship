//
// Created by Alex on 22.08.2020.
//

#ifndef CHAT_POJOUSER_H
#define CHAT_POJOUSER_H

#include <string>
#include "WinSock2.h"

using namespace std;

class POJOUser {
public:
    const string username;
    const SOCKET socket;

    void operator=(const POJOUser& other);

    POJOUser(string  username, const SOCKET& socket);
};


#endif //CHAT_POJOUSER_H
