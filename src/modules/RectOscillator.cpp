//
// Created by Cheetah on 02.06.2023.
//
#include "../../include/modules/RectOscillator.h"
#include "imnodes.h"
#include <iostream>
#include "Stk.h"

RectOscillator::RectOscillator() : Oscillator(), _id_output(IdGenerator::generateId()) {
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    rectangle.setFrequency(440.0);
}

bool RectOscillator::tick(stk::StkFloat *buffer, unsigned int nBufferFrames, double streamTime, int output_id) {
    (void)output_id;
    (void)streamTime;

    for (unsigned int i = 0; i < nBufferFrames; i++)
        *buffer++ = rectangle.tick();
    return true;
}

void RectOscillator::draw() {
    Oscillator::draw();

    ImNodes::BeginOutputAttribute(_id_output);

    ImGui::Text("out");
    ImNodes::EndOutputAttribute();
}