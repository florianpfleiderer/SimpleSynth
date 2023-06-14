//
// Created by Cheetah on 08.06.2023.
//
#include "../../include/modules/NoiseGenerator.h"
#include "imnodes.h"
#include <iostream>
#include "Stk.h"
#include <regex>

NoiseGenerator::NoiseGenerator() : Module("Noise"), _id_output(IdGenerator::generateId()) {
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
}

NoiseGenerator::NoiseGenerator(int id, int id_output)
    : Module("Noise", id), _id_output(id_output) {
        _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    }


bool NoiseGenerator::tick(stk::StkFrames &frames, double streamTime, int output_id)
{
    (void)output_id;
    (void)streamTime;
    
    frames = noise.tick(frames);
    return true;
}

void NoiseGenerator::draw() {
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginOutputAttribute(_id_output);
    ImGui::Text("out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

void NoiseGenerator::serialize_settings(std::ostream& ostream) {
    ostream << "[module_settings]" << std::endl
            << "_id_output=" << _id_output << std::endl;
}


std::shared_ptr<Module> NoiseGenerator::unserialize(std::stringstream &module_str, int module_id) {
    // variables
    int id_output(-1);

    // read stringstream
    std::string line;
    std::regex pattern;
    std::smatch matches;
    while(std::getline(module_str, line)) {
        pattern = "_id_output=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_output = std::stoi(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_output=(\\d+)\":\n" + line );
            }
        }
    }

    // create module with read data
    if (id_output == -1) {
        throw std::invalid_argument("Can not create an output module with id_output= " + std::to_string(id_output));
    }
    return std::make_shared<NoiseGenerator>(NoiseGenerator(module_id, id_output));
}

bool NoiseGenerator::play(bool state){
    /*TODO Clear everything*/
    return state;
} 