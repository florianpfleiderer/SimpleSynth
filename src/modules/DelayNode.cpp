//
// Created by Florian Pfleiderer on 04.06.2023.
//

#include <imnodes.h>
#include "../../include/modules/DelayNode.h"
#include <regex>

DelayNode::DelayNode() : Module("Delay"), 
                 _id_input(IdGenerator::generateId()), 
                 _id_output(IdGenerator::generateId()), 
                 _id_delay_length(IdGenerator::generateId()), 
                 _delay_length(0.0f) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    
    // set Delay with default values
    _delay = stk::Delay();
}

DelayNode::DelayNode(int module_id, int id_input, int id_output, int _id_delay_length, float _delay_length)
                    : Module("Delay", module_id), 
                    _id_input(id_input), 
                    _id_output(id_output), 
                    _id_delay_length(_id_delay_length), 
                    _delay_length(_delay_length) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);

    // set Delay with default values
    _delay = stk::Delay();
}


void DelayNode::draw()
{

    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();
    ImNodes::BeginStaticAttribute(_id_delay_length);
    ImGui::PushItemWidth(100.0f);
    ImGui::SliderFloat("delay_length", &_delay_length, 0.0f, _delay.getMaximumDelay());
    ImGui::PopItemWidth();
    setDelayLength(_delay_length);
    ImGui::Text("delay_length=%03f", static_cast<float>(_delay.getDelay()));
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

bool DelayNode::tick(stk::StkFrames &frames, double streamTime, int output_id) {
    if(_connections.empty() == false)
        _connections[0].module->tick(frames, streamTime, output_id);

    _delay.tick(frames);
    if(frames.empty())
        return false;
    return true;
}

bool DelayNode::setDelayLength(float delay_length) {
    if (delay_length < 0.0f) {
        return false;
    }
    _delay.setDelay(delay_length);
    return true;
}

float DelayNode::getDelayLength() const {
    return _delay.getDelay();
}

void DelayNode::serialize_settings(std::ostream &ostream)
{   //int module_id, std::vector<Connector> connectors, 
    //int id_input, int id_output, int id_echo_delay, float echo_delay)
    ostream << "[module_settings]" << std::endl
            << "_id_input=" << _id_input << std::endl
            << "_id_output=" << _id_output << std::endl
            << "_id_delay_length=" << _id_delay_length << std::endl
            << "_delay_length=" << _delay_length << std::endl;
}

std::shared_ptr<Module> DelayNode::unserialize(std::stringstream& module_str, int module_id) {
    // variables
    int id_input(-1);
    int id_output(-1);
    int id_delay_length(-1);
    float delay_length(-1);

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
        pattern = "_id_delay_length=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_delay_length = std::stoi(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_delay_length=(\\d+)\":\n" + line );
            }
        }
        pattern = "_delay_length=([+-]?\\d+(\\.\\d+)?)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 3) {
                delay_length = std::stof(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_delay_length=([+-]?\\d+(\\.\\d+)?)\":\n" + line );
            }
        }
    }

    // create module with read data
    if (id_input == -1) {
        throw std::invalid_argument("Can not create an DelayNode module with id_input= " + std::to_string(id_input));
    }
    if (id_output == -1) {
        throw std::invalid_argument("Can not create an DelayNode module with id_output= " + std::to_string(id_output));
    }
    if (id_delay_length == -1) {
        throw std::invalid_argument("Can not create an DelayNode module with id_delay_length= " + std::to_string(id_delay_length));
    }
    if (delay_length == -1) {
        throw std::invalid_argument("Can not create an DelayNode module with delay_length= " + std::to_string(delay_length));
    }
    return std::make_shared<DelayNode>(DelayNode(module_id, id_input, id_output, id_delay_length, delay_length));
}

bool DelayNode::play(bool state){
    /*TODO Clear everything*/
    return state;
}