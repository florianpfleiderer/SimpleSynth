//
// Created by Robert Ristic on 16.05.23.
// Changed by Theresa Freibauer on 31.05.2023
//
#include "imnodes.h"

#include "../../include/modules/Oscillator.h"
#include "../../include/modules/SineOscillator.h"
#include "../../include/IdGenerator.h"

Oscillator::Oscillator() : Module("Oscillator"), _id_output(IdGenerator::generateId()) {
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    sine.setFrequency(440.0);
}

void Oscillator::draw()
{
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::EndNode();
}
