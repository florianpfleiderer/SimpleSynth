//
// Created by Robert Ristic on 16.05.23.
// Changed by Theresa Freibauer on 31.05.2023
//
#include <regex>
#include "imnodes.h"

#include "../../include/modules/Oscillator.h"
#include "../../include/modules/SineOscillator.h"
#include "../../include/IdGenerator.h"

Oscillator::Oscillator(std::string name) : Module(name), _id_output(IdGenerator::generateId()), _id_frequency(IdGenerator::generateId()) {
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    _frequency = 500;
}

Oscillator::Oscillator(std::string name, int id, int id_output, float frequency)
                        : Module(name, id), _id_output(id_output), _frequency(frequency) {
                            _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
                        }

void Oscillator::draw()
{
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginStaticAttribute(_id_frequency);
    ImGui::PushItemWidth(150.0f);
    ImGui::SliderFloat("Frequency", &_frequency, 0.1f, 16000.0f);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();
}

Oscillator::~Oscillator() {

}

void Oscillator::serialize_settings(std::ostream &ostream) {
    ostream << "[module_settings]" << std::endl
            << "_id_output=" << _id_output << std::endl
            << "_frequency=" << _frequency << std::endl;
}

void Oscillator::getSettingsFromText(std::stringstream &module_str, int &id_output, float &frequency)
{
    // variables
    id_output = -1;
    frequency = -1;

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
        pattern = "_frequency=([+-]?\\d+(\\.\\d+)?)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 3) {
                frequency = std::stof(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_frequency=(\\d+(\\.\\d+)\":\n" + line );
            }
        }
    }

    // check if everything was found
    if (id_output == -1) {
        throw std::invalid_argument("Can not create an Oscillator module with id_output= " + std::to_string(id_output));
    }
    if (frequency == -1) {
        throw std::invalid_argument("Can not create an Oscillator module with frequency= " + std::to_string(frequency));
    }
}