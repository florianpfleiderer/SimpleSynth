//
// Created by Robert Ristic on 16.05.23.
// Changed by Theresa Freibauer on 31.05.2023
//
#include "imnodes.h"

#include "../../include/modules/Oscillator.h"
#include "../../include/modules/SineOscillator.h"
#include "../../include/IdGenerator.h"

Oscillator::Oscillator(std::string name) : Module(name), _id_output(IdGenerator::generateId()) {
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
}

void Oscillator::draw()
{
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();
}



Oscillator::~Oscillator() {

}

bool Oscillator::tick(stk::StkFloat *buffer, unsigned int nBufferFrames, double streamTime, int output_id) {
    (void) buffer;
    (void) nBufferFrames;
    (void) streamTime;
    (void) output_id;
    return false;
}

