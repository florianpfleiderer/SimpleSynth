//
// Created by Florian Pfleiderer on 13.06.2023.
//

#include <imnodes.h>
#include "../../include/modules/ChorusNode.h"
#include <regex>

/**
 * @brief Default constructor
*/
ChorusNode::ChorusNode() : Module("Chorus"), 
                 _id_input(IdGenerator::generateId()), 
                 _id_output(IdGenerator::generateId()), 
                 _id_chorus(IdGenerator::generateId()), 
                 _mod_depth(0.0f), 
                 _mod_freq(0.0f) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    
    // set Chorus with default values
    _chorus = stk::Chorus();
}

/**
 * @brief Construct a new Chorus Node object with fixed parameters
 * 
 * @param module_id
 * @param id_input
 * @param id_output
 * @param id_chorus
 * @param mod_depth
 * @param mod_freq
 * 
 */
ChorusNode::ChorusNode(int module_id, int id_input, int id_output, int id_chorus, float mod_depth, float mod_freq)
                 : Module("Chorus", module_id), 
                 _id_input(id_input), 
                 _id_output(id_output), 
                 _id_chorus(id_chorus), 
                 _mod_depth(mod_depth), 
                 _mod_freq(mod_freq) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    
    // set Chorus with default values
    _chorus = stk::Chorus();
}

void ChorusNode::draw() {

    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginStaticAttribute(_id_chorus);
    ImGui::PushItemWidth(100.0f);
    ImGui::SliderFloat("mod_depth", &_mod_depth, 0.0f, 1.0f);
    ImGui::SliderFloat("mod_freq", &_mod_freq, 0.0f, 1.0f);
    ImGui::PopItemWidth();
    setModDepth(_mod_depth);
    setModFreq(_mod_freq);
    ImGui::Text("mod_depth=%03f", _mod_depth);
    ImGui::Text("mod_freq=%03f", _mod_freq);
    ImNodes::EndStaticAttribute();

    ImNodes::BeginInputAttribute(_id_input);
    ImGui::Text("Input");
    ImNodes::EndInputAttribute();

    ImNodes::BeginOutputAttribute(_id_output);
    ImGui::Indent(40.0f);
    ImGui::Text("Output");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

bool ChorusNode::tick(stk::StkFrames &frames, double streamTime, int output_id) {
    if(!_connections.empty())
        _connections[0].module->tick(frames, streamTime, output_id);

    _chorus.tick(frames);
    return true;
}

void ChorusNode::setModDepth(float mod_depth) {
    _chorus.setModDepth(mod_depth);
}

void ChorusNode::setModFreq(float mod_freq) {
    _chorus.setModFrequency(mod_freq);
}

void ChorusNode::serialize_settings(std::ostream &ostream) {

    ostream << "[module_settings]" << std::endl
            << "_id_input=" << _id_input << std::endl
            << "_id_output=" << _id_output << std::endl
            << "_id_chorus=" << _id_chorus << std::endl
            << "_mod_depth=" << _mod_depth << std::endl
            << "_mod_freq=" << _mod_freq << std::endl;
}

std::shared_ptr<Module> ChorusNode::unserialize(std::stringstream& module_str, int module_id) {
    // variables
    int id_input(-1);
    int id_output(-1);
    int id_chorus(-1);
    float mod_depth(-1);
    float mod_freq(-1);

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
        pattern = "_id_chorus=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_chorus = std::stoi(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_chorus=(\\d+)\":\n" + line );
            }
        }
        pattern = "_mod_depth=([+-]?\\d+(\\.\\d+)?)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 3) {
                mod_depth = std::stof(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_mod_depth=([+-]?\\d+(\\.\\d+)?)\":\n" + line );
            }
        }
        pattern = "_mod_freq=([+-]?\\d+(\\.\\d+)?)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 3) {
                mod_freq = std::stof(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_mod_freq=([+-]?\\d+(\\.\\d+)?)\":\n" + line );
            }
        }
    }

    // create module with read data
    if (id_input == -1) {
        throw std::invalid_argument("Can not create an ChorusNode module with id_input= " + std::to_string(id_input));
    }
    if (id_output == -1) {
        throw std::invalid_argument("Can not create an ChorusNode module with id_output= " + std::to_string(id_output));
    }
    if (id_chorus == -1) {
        throw std::invalid_argument("Can not create an ChorusNode module with id_chorus= " + std::to_string(id_chorus));
    }
    if (mod_depth == -1) {
        throw std::invalid_argument("Can not create an ChorusNode module with mod_depth= " + std::to_string(mod_depth));
    }
    if (mod_freq == -1) {
        throw std::invalid_argument("Can not create an ChorusNode module with mod_freq= " + std::to_string(mod_freq));
    }
    return std::make_shared<ChorusNode>(module_id, id_input, id_output, id_chorus, mod_depth, mod_freq);
}

bool ChorusNode::play(bool state){
    /*TODO Clear everything*/
    return state;
}