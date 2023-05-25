
#include "../../include/modules/Module.h"

//
// Created by Robert Ristic on 16.05.23.
//
Module::Module(std::string name) : _id(IdGenerator::generateId()), _name(name) {}

const std::string Module::getName() const
{
    return _name;
}
int Module::getId() const
{
    return _id;
}
Module::~Module()
{
}
