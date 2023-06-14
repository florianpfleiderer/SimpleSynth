//
// Created by Robert Ristic on 16.05.23.
//

#include <utility>
#include <algorithm>
#include <map>

#include "../../include/modules/Module.h"

Module::Module(std::string name) : _id(IdGenerator::generateId()), _name(std::move(name)) {}

Module::Module(std::string name, int id) : _id(id), _name(std::move(name)) {}

const std::string& Module::getName() const
{
    return _name;
}

int Module::getId() const
{
    return _id;
}

Module::~Module() = default;

const std::vector<Connection> &Module::getConnections() const
{
    return _connections;
}

const std::vector<Connector> & Module::getConnectors() const
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
            << _id << std::endl;
    this->serialize_settings(ostream);
    ostream << std::endl;
}

void Module::removeConnection(int id) {
    _connections.erase(std::remove_if(_connections.begin(), _connections.end(),
                                      [id](const auto c){ return c.conn_id == id || c.input_id == id || c.output_id == id; }), _connections.end());
}

void Module::removeAllConnections() {
    _connections.clear();
}