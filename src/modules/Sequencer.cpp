//
// Created by waniek on 31.05.2023.
//

#include "../../include/modules/Sequencer.h"
#include "imnodes.h"

Sequencer::Sequencer(int beats_per_minute) : Module("Sequencer"), _id_output(IdGenerator::generateId()) {
    bpm = beats_per_minute;
}

void Sequencer::draw() {


    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(_id_output);
    ImGui::Text("out_1");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}
