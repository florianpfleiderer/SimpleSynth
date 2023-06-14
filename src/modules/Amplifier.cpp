//
// Created by Moritz Mairhofer on 30.05.23.
//

#include "imnodes.h"

#include "../../include/modules/Amplifier.h"
#include "Stk.h"
#include <regex>


Amplifier::Amplifier(unsigned int g) : Module("Amplifier"), _id_output(IdGenerator::generateId()),
                           _id_input(IdGenerator::generateId()),_gain(g), _id_gain(IdGenerator::generateId()) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
}

Amplifier::Amplifier(int module_id, int id_input, int id_output, unsigned int gain) 
                : Module("Amplifier", module_id), _id_output(id_output), _id_input(id_input), _gain(gain) {
                    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
                    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
                }

//! Set the gain factor
void Amplifier::setGain(unsigned int g) {
    _gain  = g;
}

void Amplifier::amplify(stk::StkFrames& frames, unsigned int g) {
    // Amplify and call copy constructor
    frames = frames * g;
}


bool Amplifier::tick(stk::StkFrames& frames, double streamTime, int output_id) {
    // Fill frames with audio data and amplify the data
    for(auto & conn : this->_connections){
        conn.module->tick(frames, streamTime, output_id);
    }
    // Return false if the no audio data was provided
    if(frames.empty())
        return false;
    // Amplify the audio data (signal) stored in frames
    amplify(frames, _gain);

    return true;
}


void Amplifier::draw()
{
    // Create empty node
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    // Input pin
    ImNodes::BeginInputAttribute(_id_input);
    ImGui::Text("in");
    ImNodes::EndInputAttribute();

    // Output pin
    ImNodes::BeginOutputAttribute(_id_output);
    ImGui::Indent(160);
    ImGui::Text("out");
    ImNodes::EndInputAttribute();

    // Fader
    ImNodes::BeginStaticAttribute(_id_gain);
    ImGui::PushItemWidth(100.0f);
    ImGui::SliderFloat("Gain factor", &_gain, 0.1f, 10.f);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    ImNodes::EndNode();
}

Amplifier::~Amplifier() {

}

//TODO: implement
void Amplifier::serialize_settings(std::ostream &ostream)
{
    ostream << "[module_settings]" << std::endl
            << "_id_output=" << _id_output << std::endl
            << "_id_input=" << _id_input << std::endl
            << "_gain=" << _gain << std::endl;
}

std::shared_ptr<Module> Amplifier::unserialize(std::stringstream& module_str, int module_id) {
    // variables
    int id_output(-1);
    int id_input(-1);
    int gain(-1);

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
        pattern = "_id_input=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_input = std::stoi(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_input=(\\d+)\":\n" + line );
            }
        }
        pattern = "_gain=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                gain = std::stoi(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_gain=(\\d+)\":\n" + line );
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
    unsigned int unsigned_gain;
    if (gain == -1) {
        throw std::invalid_argument("Can not create an EchoNode module with gain= " + std::to_string(gain));
    } else {
        unsigned_gain = static_cast<unsigned int>(gain);
    }   
    return std::make_shared<Amplifier>(Amplifier(module_id, id_input, id_output, unsigned_gain));
}

bool Amplifier::play(bool state){
    /*TODO Clear everything*/
    return state;
}