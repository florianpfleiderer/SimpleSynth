//
// Created by Cheetah on 08.06.2023.
//
#include "../../include/modules/NoiseGenerator.h"
#include "imnodes.h"
#include <iostream>
#include "Stk.h"

NoiseGenerator::NoiseGenerator() : Oscillator("Noise"), _id_output(IdGenerator::generateId()) {
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
}

bool NoiseGenerator::tick(stk::StkFrames &frames, double streamTime, int output_id) {
    (void)output_id;
    (void)streamTime;

    // for (unsigned int i = 0; i < nBufferFrames; i++)
    //     *buffer++ = rectangle.tick();
    
    frames = noise.tick(frames);
    return true;
}

void NoiseGenerator::draw() {
    Oscillator::draw();

    ImNodes::BeginOutputAttribute(_id_output);

    ImGui::Text("out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}