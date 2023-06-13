//
// Created by Cheetah on 08.06.2023.
//
#include "../../include/modules/NoiseGenerator.h"
#include "imnodes.h"
#include <iostream>
#include "Stk.h"

NoiseGenerator::NoiseGenerator() : Module("Noise") {
    _id_output = IdGenerator::generateId();
}

NoiseGenerator::NoiseGenerator(int id, int id_output)
    : Module("Noise", id), _id_output(id_output) {}

bool NoiseGenerator::tick(stk::StkFrames &frames, double streamTime, int output_id) {
    (void)output_id;
    (void)streamTime;
    
    frames = noise.tick(frames);
    return true;
}

void NoiseGenerator::draw() {
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginOutputAttribute(_id_output);
    ImGui::Text("out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

void NoiseGenerator::serialize_settings(std::ostream& ostream) {
    ostream << "[module_settings]" << std::endl
            << "_id_output=" << _id_output << std::endl;
}

/*
std::shared_ptr<Module> NoiseGenerator::unserialize(std::stringstream &module_str, int module_id) {
    int id_output;
    getSettingsFromText(module_str, id_output);
    // create module with read data
    return std::make_shared<NoiseGenerator>(NoiseGenerator(module_id, id_output));
}
 */