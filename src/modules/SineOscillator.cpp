//
// Created by Theresa Freibauer on 31.05.23.
//
#include "../../include/modules/SineOscillator.h"
#include "imnodes.h"
#include <iostream>

SineOscillator::SineOscillator() : Oscillator("SineOscillator"), _id_output(IdGenerator::generateId()) {
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    sine.setFrequency(440.0);
}

bool SineOscillator::tick(stk::StkFloat *buffer, unsigned int nBufferFrames, double streamTime, int output_id) {
    (void)output_id;
    (void)streamTime;

    for (unsigned int i = 0; i < nBufferFrames; i++)
        *buffer++ = sine.tick();
    return true;
}

void SineOscillator::draw() {
    Oscillator::draw();

    ImNodes::BeginOutputAttribute(_id_output);

    ImGui::Text("out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}
