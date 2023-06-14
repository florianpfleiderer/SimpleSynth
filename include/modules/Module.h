//
// Created by Robert Ristic on 15.05.23.
//

#ifndef SIMPLESYNTH_MODULE_H
#define SIMPLESYNTH_MODULE_H

#include <string>
#include <utility>
#include "Stk.h"
#include "../IdGenerator.h"
#include <memory>

namespace ConnectorType{
    enum ConnectorType {
        INPUT,
        OUTPUT
    };
}

class Module;

/**
 * @brief Used to define Module in- and outputs
 * Create input and output definitions here
 */
struct Connector {
    ConnectorType::ConnectorType type;
    int id;

    Connector(ConnectorType::ConnectorType type, int id) : type(type), id(id) {}
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
     * @brief default constructor
     */
    explicit Module(std::string name);

    /**
     * @brief Construct a new Module object with full controll
     * 
     */
    explicit Module(std::string name, int id);


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
    [[nodiscard]] const std::vector<Connection> & getConnections() const;

    /**
     * @brief Returns all connectors
     * @return reference to the connection list
     */
    [[nodiscard]] const std::vector<Connector> & getConnectors() const;

    [[nodiscard]] const Connector *getConnectorById(int id) const;

    void removeConnection(int id);

    /**
     * @brief Returns the settings of the module
     * @return List of 
     */
    //[[nodiscard]] 

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
     * @param frames stkFrames file of audio data
     * @param streamTime time in seconds since the audio stream has started
     * @param output_id output id of the connected module (only used if module has multiple outputs)
     *
     * @return true if audio was processed correctly (else false)
     */
    virtual bool tick(stk::StkFrames& frames, double streamTime, int output_id) = 0;

    /**
     * @brief Function to start or stop the module
     * @param state true to start, false to stop
     * @return true if module was started and flase if stopped correctly
    */
   virtual bool play(bool state) = 0;


    /**
     * @brief writes the data of the module to a given outputstream
     * (structure example "/docs/save_example.txt")
     * 
     * @param ostream outputstream to write the serialized data to
     */
    void serialize(std::ostream &ostream);

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

    /**
     * @brief writes the settings of the specific module to the given outputsream 
     * (structure example from [module_settings] to empty line"/docs/save_example.txt")
     * 
     * @param ostream outputstream to write the serialized data to
     */
    virtual void serialize_settings(std::ostream &ostream) = 0;
};


#endif // SIMPLESYNTH_MODULE_H
