//
// Created by Alex on 22.08.2020.
//

#include "POJOUser.h"

POJOUser::POJOUser(string username, const SOCKET &socket) : username(std::move(username)), socket(socket){

}

void POJOUser::operator=(const POJOUser &other) {
    *this = POJOUser(other.username,other.socket);
}
