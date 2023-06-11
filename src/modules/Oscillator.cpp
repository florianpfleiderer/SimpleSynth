//
// Created by Robert Ristic on 16.05.23.
// Changed by Theresa Freibauer on 31.05.2023
//
#include <regex>
#include "imnodes.h"

#include "../../include/modules/Oscillator.h"
#include "../../include/modules/SineOscillator.h"
#include "../../include/IdGenerator.h"

Oscillator::Oscillator(std::string name) : Module(name) {}

Oscillator::Oscillator(int id, std::vector<Connector> connectors, int id_out)
                        : Module("Oscillator", id, connectors), _id_output(id_out) {}

void Oscillator::draw()
{
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();
}



Oscillator::~Oscillator() {

}

bool Oscillator::tick(stk::StkFrames &frames, double streamTime, int output_id) {
    (void) frames;
    (void) streamTime;
    (void) output_id;
    return false;
}


void Oscillator::serialize_settings(std::ostream &ostream)
{
    ostream << "[module_settings]" << std::endl
            << "_id_output=" << _id_output << std::endl;
}

std::shared_ptr<Module> Oscillator::unserialize(std::stringstream &module_str, int module_id, std::vector<Connector> module_connectors) {
    // variables
    int id_out(-1);

    // flags
    bool module_settings_f(false);

    // read stringstream
    std::string line;
    std::regex pattern;
    std::smatch matches;
    while(std::getline(module_str, line)) {
        // search for settings
        if (line == "[module_settings]") {
            module_settings_f = true;
            continue;
        }
        // process flags
        if (module_settings_f) {
            pattern = "_id_output=(\\d+)";
            if (std::regex_search(line, matches, pattern)) {
                if (matches.size() == 2) {
                    id_out = std::stoi(matches[1].str());
                    break;
                } else {
                    throw std::invalid_argument("Following line does not follow the pattern \"_id_output=(\\d+)\":\n" + line );
                }
            }
        }
    }

    // create module with read data
    if (id_out == -1) {
        throw std::invalid_argument("Can not create an output module with id_out= " + std::to_string(id_out));
    }
    return std::make_shared<Oscillator>(Oscillator(module_id, module_connectors, id_out));
}