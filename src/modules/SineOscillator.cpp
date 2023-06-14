//
// Created by Theresa Freibauer on 31.05.23.
//
#include "../../include/modules/SineOscillator.h"
#include "imnodes.h"
#include <iostream>

SineOscillator::SineOscillator() : Oscillator("SineOscillator") {
    updateFrequency(440.0);
}

SineOscillator::SineOscillator(int module_id, int id_output, float frequency)
                                : Oscillator("SineOscillator", module_id, id_output, frequency) {}


bool SineOscillator::tick(stk::StkFrames &frames, double streamTime, int output_id)
{
    (void)output_id;
    (void)streamTime;

    // for (unsigned int i = 0; i < nBufferFrames; i++)
    //     *buffer++ = sine.tick();

    sine.tick(frames);
    return true;
}

void SineOscillator::draw() {
    Oscillator::draw();

    ImNodes::BeginOutputAttribute(_id_output);

    ImGui::Text("out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();

    updateFrequency(_frequency);
}

void SineOscillator::updateFrequency(float frequency) {
    sine.setFrequency(frequency);
    _frequency = frequency;
}

std::shared_ptr<Module> SineOscillator::unserialize(std::stringstream &module_str, int module_id) {
    int id_output;
    float frequency;
    Oscillator::getSettingsFromText(module_str, id_output, frequency);
    // create module with read data
    return std::make_shared<SineOscillator>(module_id, id_output, frequency);
}

bool SineOscillator::play(bool state){
    /*TODO Clear everything*/
    return state;
}