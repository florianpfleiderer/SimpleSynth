//
// Created by Cheetah on 02.06.2023.
//
#include    "../../include/modules/SawOscillator.h"
#include "imnodes.h"
#include <iostream>
#include "Stk.h"

SawOscillator::SawOscillator() : Oscillator("SawOscillator") {
    updateFrequency(440.0);
}

SawOscillator::SawOscillator(int id, int id_output, float frequency)
                                : Oscillator("SawOscillator", id, id_output, frequency) {}


bool SawOscillator::tick(stk::StkFrames &frames, double streamTime, int output_id) {
    (void)output_id;
    (void)streamTime;

    saw.tick(frames);
    return true;
}

void SawOscillator::draw() {
    Oscillator::draw();

    ImNodes::BeginOutputAttribute(_id_output);

    ImGui::Text("out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

void SawOscillator::updateFrequency(float frequency) {
    saw.setFrequency(frequency);
    _frequency = frequency;
}

std::shared_ptr<Module> SawOscillator::unserialize(std::stringstream &module_str, int module_id) {
    int id_output;
    float frequency;
    Oscillator::getSettingsFromText(module_str, id_output, frequency);
    // create module with read data
    return std::make_shared<SawOscillator>(SawOscillator(module_id, id_output, frequency));
}