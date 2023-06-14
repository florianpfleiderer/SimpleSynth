//
// Created by Florian Pfleiderer on 05.06.2023.
//

#include <imnodes.h>
#include "../../include/modules/EchoNode.h"
#include <regex>

/**
 * @brief Default constructor
 * 
*/
EchoNode::EchoNode() : Module("Echo"), 
                 _id_input(IdGenerator::generateId()), 
                 _id_output(IdGenerator::generateId()),
                 _id_echo_delay(IdGenerator::generateId()),
                 _echo_delay(0.0f) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    
    // set Echo with default values
    _echo = stk::Echo();
}

/**
 * @brief Construct a new Echo Node object with fixed parameters
 * 
 * @param module_id
 * @param id_input
 * @param id_output
 * @param id_echo_delay
 * @param echo_delay
 * 
*/
EchoNode::EchoNode(int module_id, int id_input, int id_output, int id_echo_delay, float echo_delay)
                 : Module("Echo", module_id), 
                 _id_input(id_input), 
                 _id_output(id_output),
                 _id_echo_delay(id_echo_delay),
                 _echo_delay(echo_delay) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    
    // set Echo with default values
    _echo = stk::Echo();
}

void EchoNode::draw() {

    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginStaticAttribute(_id_echo_delay);
    ImGui::PushItemWidth(100.0f);
    ImGui::SliderFloat("echo_delay", &_echo_delay, 0.0f, 1000.0f);
    ImGui::PopItemWidth();
    setEchoDelay(_echo_delay);
    ImGui::Text("echo_delay=%03f", _echo_delay);
    ImNodes::EndStaticAttribute();

    ImNodes::BeginInputAttribute(_id_input);
    ImGui::Text("in");
    ImNodes::EndInputAttribute();

    ImNodes::BeginOutputAttribute(_id_output);
    // const float label_width = ImGui::CalcTextSize("out").x;
    ImGui::Indent(150.0f);
    ImGui::Text("out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

bool EchoNode::tick(stk::StkFrames &frames, double streamTime, int output_id) {
    if(_connections.empty() == false)
        _connections[0].module->tick(frames, streamTime, output_id);

    _echo.tick(frames);
    if(frames.empty())
        return false;
    return true;
}

/**
 * @brief Sets the echo delay when changed with slider
 * 
 * @param echo_delay
 * 
 * @return true if successful
*/
bool EchoNode::setEchoDelay(float echo_delay) {
    if (echo_delay < 0.0f)
        return false;
    _echo.setDelay(_echo_delay);
    return true;
}

void EchoNode::serialize_settings(std::ostream &ostream)
{   
    ostream << "[module_settings]" << std::endl
            << "_id_input=" << _id_input << std::endl
            << "_id_output=" << _id_output << std::endl
            << "_id_echo_delay=" << _id_echo_delay << std::endl
            << "_echo_delay=" << _echo_delay << std::endl;
}

std::shared_ptr<Module> EchoNode::unserialize(std::stringstream& module_str, int module_id) {
    // variables
    int id_input(-1);
    int id_output(-1);
    int id_echo_delay(-1);
    float echo_delay(-1);

    // read stringstream
    std::string line;
    std::regex pattern;
    std::smatch matches;
    while(std::getline(module_str, line)) {
        pattern = "_id_input=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_input = std::stoi(matches[1].str());
                continue;;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_input=(\\d+)\":\n" + line );
            }
        }
        pattern = "_id_output=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_output = std::stoi(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_output=(\\d+)\":\n" + line );
            }
        }
        pattern = "_id_echo_delay=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_echo_delay = std::stoi(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_echo_delay=(\\d+)\":\n" + line );
            }
        }
        pattern = "_echo_delay=([+-]?\\d+(\\.\\d+)?)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 3) {
                echo_delay = std::stof(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_echo_delay=([+-]?\\d+(\\.\\d+)?)\":\n" + line );
            }
        }
    }


    // create module with read data
    if (id_input == -1) {
        throw std::invalid_argument("Can not create an EchoNode module with id_input= " + std::to_string(id_input));
    }
    if (id_output == -1) {
        throw std::invalid_argument("Can not create an EchoNode module with id_output= " + std::to_string(id_output));
    }
    if (id_echo_delay == -1) {
        throw std::invalid_argument("Can not create an EchoNode module with id_echo_delay= " + std::to_string(id_echo_delay));
    }
    if (echo_delay == -1) {
        throw std::invalid_argument("Can not create an EchoNode module with echo_delay= " + std::to_string(echo_delay));
    }
    return std::make_shared<EchoNode>(EchoNode(module_id, id_input, id_output, id_echo_delay, echo_delay));
}