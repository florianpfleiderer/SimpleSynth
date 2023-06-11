//
// Created by Robert Ristic on 16.05.23.
//

#include <utility>
#include <algorithm>
#include <map>

#include "../../include/modules/Module.h"

Module::Module(std::string name) : _id(IdGenerator::generateId()), _name(std::move(name)) {}

Module::Module(std::string name, int id, std::vector<Connector> connectors) : _id(id), _name(std::move(name))
{
    for (auto &connector : connectors) {
        _connectors.emplace_back(connector);
    }
}

const std::string& Module::getName() const
{
    return _name;
}

int Module::getId() const
{
    return _id;
}

Module::~Module() = default;

const std::vector<Connector> &Module::getConnections() const
{
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

void Module::serialize(std::ostream &ostream) {
    ostream << "[module_name]" << std::endl
            << _name << std::endl
            << "[module_id]" << std::endl
            << _id << std::endl
            << "[module_connectors]" << std::endl;
    if(_connectors.size() != 0) {
        for(auto& connector : _connectors) {
            ostream << "id=" << connector.id
                    << " type=" << connector.type
                    << std::endl;
        }
    } else {
        ostream << "null" << std::endl;
    }
    this->serialize_settings(ostream);
    ostream << std::endl;
}