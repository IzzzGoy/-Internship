//
// Created by Alex on 03.08.2020.
//

#ifndef DB_ENTITY_H
#define DB_ENTITY_H

enum class EntityType{
    STRING,
    DATE
};

class Entity {
public:
    EntityType type;

    Entity();

private:

    void* value;
};



#endif //DB_ENTITY_H
