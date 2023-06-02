//
// Created by Robert Ristic on 16.05.23.
//

#include <utility>

#include "../../include/modules/Module.h"

Module::Module(std::string name) : _id(IdGenerator::generateId()), _name(std::move(name)) {}

const std::string& Module::getName() const
{
    return _name;
}
int Module::getId() const
{
    return _id;
}
Module::~Module() = default;

const std::vector<Connector> &Module::getConnections() const {
    return _connectors;
}

void Module::addConnection(Connection &conn) {
    _connections.emplace_back(conn);
}