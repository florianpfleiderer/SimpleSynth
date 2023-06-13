//
// Created by Cheetah on 08.06.2023.
//
#include "../../include/modules/NoiseGenerator.h"
#include "imnodes.h"
#include <iostream>
#include "Stk.h"

NoiseGenerator::NoiseGenerator() : Oscillator("Noise") {
    updateFrequency(0);
}

NoiseGenerator::NoiseGenerator(int id, int id_output, float frequency)
                                : Oscillator("Noise", id, id_output, frequency) {}

bool NoiseGenerator::tick(stk::StkFrames &frames, double streamTime, int output_id) {
    (void)output_id;
    (void)streamTime;
    
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

// dummy method, no use for noise
// TODO: don't inherit from Oscillator
void NoiseGenerator::updateFrequency(float frequency) {
    _frequency = frequency;
}

std::shared_ptr<Module> NoiseGenerator::unserialize(std::stringstream &module_str, int module_id) {
    int id_output;
    float frequency;
    Oscillator::getSettingsFromText(module_str, id_output, frequency);
    // create module with read data
    return std::make_shared<NoiseGenerator>(NoiseGenerator(module_id, id_output, frequency));
}