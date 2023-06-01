//
// Created by Robert Ristic on 15.05.23.
//

#ifndef SIMPLESYNTH_MODULE_H
#define SIMPLESYNTH_MODULE_H

#include <string>
#include <utility>
#include "Stk.h"
#include "../IdGenerator.h"

enum ConnectorType {
    INPUT,
    OUTPUT
};

class Module;

/**
 * @brief Used to define Module in- and ouptuts
 * Create input and output definitions here
 */
struct Connector {
    ConnectorType type;
    int id;

    Connector(ConnectorType type, int id) : type(type), id(id) {}
};

/**
 * @brief used to define connections between to modules
 */
struct Connection {
    std::shared_ptr<Module> module;
    int conn_id;
    int input_id;
    int output_id;

    // TODO shared pointer initialization makes sense?
    Connection(std::shared_ptr<Module> module, int conn_id, int input_id, int output_id)
        : module(std::move(module)), conn_id(conn_id), input_id(input_id), output_id(output_id) {}
};

/**
 * @brief Module Interface
 */
class Module {
public:
    /**
     * @brief Constructor
     */
    explicit Module(std::string name);

    /**
     * @brief Returns the id of the module
     * @return id
     */
    [[nodiscard]] int getId() const;

    /**
     * @brief Returns the name of the module
     * @return name
     */
    [[nodiscard]] const std::string& getName() const;

    /**
     * @brief Returns all connections
     * @return reference to the connection list
     */
    [[nodiscard]] const std::vector<Connector>& getConnections() const;
    //[[nodiscard]] const Connector& getConnectionById(int id) const;

    /**
     * @brief Add new connection
     * @param conn
     */
    void addConnection(Connection &conn);

    /**
     * @brief Draw the module
     * This function is called every frame to draw the module ui.
     */
    virtual void draw() = 0;

    /**
     * @brief Function used for audio processing
     *
     * * check if all inputs are connected
     * * call tick functions of connected modules
     * * do the necessary calculations
     *
     * @param buffer vector of audio data
     * @param nBufferFrames buffer size
     * @param streamTime time in seconds since the audio stream has started
     * @param output_id output id of the connected module (only used if module has multiple outputs)
     *
     * @return true if audio was processed correctly (else false)
     */
    virtual bool tick(stk::StkFloat* buffer, unsigned int nBufferFrames, double streamTime, int output_id) = 0;

    /**
     * @brief Destructor
     */
    virtual ~Module();

protected:

    /**
     * @brief Contains all in and outputs of the module
     */
    std::vector<Connector> _connectors;

    /**
     * @brief Contains all input connections
     */
    std::vector<Connection> _connections;

private:
    /**
     * @brief module id
     */
    const int _id;

    /**
     * @brief module name
     */
    const std::string _name;
};


#endif // SIMPLESYNTH_MODULE_H