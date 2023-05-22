//
// Created by Robert Ristic on 16.05.23.
//
#include "imnodes.h"

#include "../../include/modules/Oscillator.h"

Oscillator::Oscillator() : Module("Oscillator"), _id_output(IdGenerator::generateId()) {}

void Oscillator::draw()
{
    std::cout << "OscId: " << getId() << std::endl;
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginOutputAttribute(_id_output);
    ImGui::Text("out");
    ImNodes::EndInputAttribute();

    ImNodes::EndNode();
}