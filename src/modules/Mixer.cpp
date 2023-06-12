//
// Created by Moritz Mairhofer on 30.05.23.
//

#include "imnodes.h"

#include "../../include/modules/Mixer.h"

Mixer::Mixer() : Module("Mixer"), _id_output(IdGenerator::generateId()),
                         _id_input_1(IdGenerator::generateId()), _id_input_2(IdGenerator::generateId())   {}

void Mixer::draw()
{
    // Create empty node
    std::cout << "MixId: " << getId() << std::endl;
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    // Input pin 1
    ImNodes::BeginInputAttribute(_id_input_1);
    ImGui::Text("in_1");
    ImNodes::EndInputAttribute();

    // Input pin 2
    ImNodes::BeginInputAttribute(_id_input_2);
    ImGui::Text("in_2");
    ImNodes::EndInputAttribute();

    // Output pin
    ImNodes::BeginOutputAttribute(_id_output);
    ImGui::Text("out");
    ImNodes::EndInputAttribute();

    ImNodes::EndNode();
}