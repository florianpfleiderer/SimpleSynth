//
// Created by Cheetah on 02.06.2023.
//
#include    "../../include/modules/SawOscillator.h"
#include "imnodes.h"
#include <iostream>
#include "Stk.h"

SawOscillator::SawOscillator() : Oscillator("SawOscillator"), _id_output(IdGenerator::generateId()) {
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    saw.setFrequency(440.0);
}

bool SawOscillator::tick(stk::StkFrames &frames, double streamTime, int output_id) {
    (void)output_id;
    (void)streamTime;

    frames = saw.tick(frames);
    return true;
}

void SawOscillator::draw() {
    Oscillator::draw();

    ImNodes::BeginOutputAttribute(_id_output);

    ImGui::Text("out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}