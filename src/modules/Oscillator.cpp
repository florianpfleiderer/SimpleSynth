//
// Created by Robert Ristic on 16.05.23.
//
#include "imnodes.h"

#include "../../include/modules/Oscillator.h"

Oscillator::Oscillator() : Module("Oscillator"), _id_output(IdGenerator::generateId()) {
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
}

void Oscillator::draw()
{
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginOutputAttribute(_id_output);
    ImGui::Text("out");
    ImNodes::EndInputAttribute();

    ImNodes::EndNode();
}

bool Oscillator::tick(stk::StkFloat *buffer, unsigned int nBufferFrames, double streamTime, int output_id) {
    (void)buffer;
    (void)nBufferFrames;
    (void)streamTime;
    (void)output_id;
    return false;
}
