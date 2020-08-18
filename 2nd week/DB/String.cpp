//
// Created by Alex on 10.08.2020.
//

#include "String.h"

String::String(const string &value) : Entity(value, EntityType::STRING){

}

String::String(const Entity &entity) : Entity(entity.get(), EntityType::STRING) {

}
