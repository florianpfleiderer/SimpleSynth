//
// Created by Moritz Mairhofer on 30.05.23.
//

#include "imnodes.h"

#include "../../include/modules/Mixer.h"
#include "Stk.h"
#include <regex>


Mixer::Mixer() : Module("Mixer"), _id_output(IdGenerator::generateId()),
                         _id_input_1(IdGenerator::generateId()), _id_input_2(IdGenerator::generateId())   {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input_1);
    _connectors.emplace_back(ConnectorType::INPUT, _id_input_2);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
}

Mixer::Mixer(int module_id, int id_output, int id_input_1, int id_input_2) 
                : Module("Mixer", module_id), _id_output(id_output), _id_input_1(id_input_1), _id_input_2(id_input_2) {
                    _connectors.emplace_back(ConnectorType::INPUT, _id_input_1);
                    _connectors.emplace_back(ConnectorType::INPUT, _id_input_2);
                    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
                }

stk::StkFrames Mixer::mix(stk::StkFrames& audio_signal_1, stk::StkFrames& audio_signal_2) {

    stk::StkFrames mixed_signal = audio_signal_1 + audio_signal_2;

    return mixed_signal;
}

bool Mixer::tick(stk::StkFrames &frames, double streamTime, int output_id) {

    //Create Frame variables for mixing
    stk::StkFrames *audio_signals = new stk::StkFrames[_connectors.size()];

    for(unsigned int i = 0; i < this->_connections.size(); i++) {
        this->_connections[i].module->tick(audio_signals[i], streamTime, output_id);
    }

    stk::StkFrames mixed_signal = mix(audio_signals[0], audio_signals[1]);
    frames = mixed_signal;

    delete [] audio_signals;

    return  true;
}

void Mixer::draw()
{
    // Create empty node
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    // Input pin 1
    ImNodes::BeginInputAttribute(_id_input_1);
    ImGui::Text("in_1");
    ImNodes::EndInputAttribute();

    // Input pin 2
    ImNodes::BeginInputAttribute(_id_input_2);
    ImGui::Text("in_2");
    ImNodes::EndInputAttribute();

    // Output pin
    ImNodes::BeginOutputAttribute(_id_output);
    ImGui::Text("out");
    ImNodes::EndInputAttribute();

    ImNodes::EndNode();
}

void Mixer::serialize_settings(std::ostream &ostream) {
    ostream << "[module_settings]" << std::endl
            << "_id_output=" << _id_output << std::endl
            << "_id_input_1=" << _id_input_1 << std::endl
            << "_id_input_2=" << _id_input_2 << std::endl;
}

std::shared_ptr<Module> Mixer::unserialize(std::stringstream& module_str, int module_id) {
    // variables
    int id_output(-1);
    int id_input_1(-1);
    int id_input_2(-1);

    // read stringstream
    std::string line;
    std::regex pattern;
    std::smatch matches;
    while(std::getline(module_str, line)) {
        pattern = "_id_output=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_output = std::stoi(matches[1].str());
                continue;;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_output=(\\d+)\":\n" + line );
            }
        }
        pattern = "_id_input_1=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_input_1 = std::stoi(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_input_1=(\\d+)\":\n" + line );
            }
        }
        pattern = "_id_input_2=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_input_2 = std::stoi(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_input_2=(\\d+)\":\n" + line );
            }
        }
    }


    // create module with read data
    if (id_output == -1) {
        throw std::invalid_argument("Can not create an EchoNode module with id_output= " + std::to_string(id_output));
    }
    if (id_input_1 == -1) {
        throw std::invalid_argument("Can not create an EchoNode module with id_input_1= " + std::to_string(id_input_1));
    }
    if (id_input_2 == -1) {
        throw std::invalid_argument("Can not create an EchoNode module with id_input_2= " + std::to_string(id_input_2));
}   
    return std::make_shared<Mixer>(Mixer(module_id, id_output, id_input_1, id_input_2));
}