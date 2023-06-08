//
// Created by Robert Ristic on 16.05.23.
//

#include <utility>
#include <map>

#include "../../include/modules/Module.h"
#include "../../include/modules/Oscillator.h"
#include "../../include/modules/Output.h"

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

const std::vector<Connector> &Module::getConnections() const
{
    return _connectors;
}

void Module::addConnection(Connection &conn) {
    _connections.emplace_back(conn);
}

void Module::serialize(std::ostream &ostream) {
    ostream << "[module_name]" << std::endl;
    ostream << _name << std::endl;
    ostream << "[module_id]" << std::endl;
    ostream << _id << std::endl;

    ostream << "[module_connectors]" << std::endl;
    if(_connectors.size() != 0) {
        for(auto& connector : _connectors) {
            ostream << "id=" << connector.id
            << " type=" << connector.type << std::endl;
        }
    } else {
        ostream << "null" << std::endl;
    }

    ostream << "[module_connections]" << std::endl;
    if(_connections.size() != 0) {
        for(auto& connection : _connections) {
            ostream << "con_id=" << connection.conn_id
            << " out_id=" << connection.output_id
            << " in_id=" << connection.input_id << std::endl;
        }
    } else {
        ostream << "null" << std::endl;
    }

    this->serialize_settings(ostream);
    ostream << std::endl;
}