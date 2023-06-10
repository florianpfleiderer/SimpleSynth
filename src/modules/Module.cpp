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

const Connector * Module::getConnectorById(int id) const {
    auto found = std::find_if(_connectors.begin(), _connectors.end(),
                              [id](const Connector& m) -> bool { return m.id == id; });
    if (found == _connectors.end()) {
        return nullptr;
    }
    return &(*found);
}
