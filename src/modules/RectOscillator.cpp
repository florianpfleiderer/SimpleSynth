//
// Created by Cheetah on 02.06.2023.
//
#include "../../include/modules/RectOscillator.h"
#include "imnodes.h"
#include <iostream>

RectOscillator::RectOscillator() : Oscillator("RectOscillator") {
    updateFrequency(440.0);
}

RectOscillator::RectOscillator(int module_id, int id_output, float frequency)
                                : Oscillator("RectOscillator", module_id, id_output, frequency) {}

bool RectOscillator::tick(stk::StkFrames &frames, double streamTime, int output_id) {
    (void)output_id;
    (void)streamTime;
    
    frames = rectangle.tick(frames);
    return true;
}

void RectOscillator::draw() {
    Oscillator::draw();

    ImNodes::BeginOutputAttribute(_id_output);

    ImGui::Text("out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();

    updateFrequency(_frequency);
}

void RectOscillator::updateFrequency(float frequency) {
    rectangle.setFrequency(frequency);
    _frequency = frequency;
}

std::shared_ptr<Module> RectOscillator::unserialize(std::stringstream &module_str, int module_id) {
    int id_output;
    float frequency;
    Oscillator::getSettingsFromText(module_str, id_output, frequency);
    // create module with read data
    return std::make_shared<RectOscillator>(module_id, id_output, frequency);
}