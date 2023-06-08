//
// Created by Dennis Waniek on 31.05.2023.
//

#include "../../include/modules/Sequencer.h"
#include "imnodes.h"

Sequencer::Sequencer(int input_size, int beats_per_minute) : Module("Sequencer"), _id_output(IdGenerator::generateId()) {
    bpm = beats_per_minute;
    _ids_input = std::vector<int>(input_size);
    std::generate(_ids_input.begin(), _ids_input.end(), IdGenerator::generateId);
}

Sequencer::~Sequencer(){

}

bool Sequencer::tick(stk::StkFrames &frames, double streamTime, int output_id){
    (void) frames;
    (void) streamTime;
    (void) output_id;
    return false;
}

void Sequencer::draw() {

    ImNodes::BeginNode(getId());

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginOutputAttribute(_id_output);
    ImGui::TextUnformatted("out");
    ImNodes::EndOutputAttribute();

    for(int _id : _ids_input){
        ImNodes::BeginInputAttribute(_id);
        ImGui::TextUnformatted(std::to_string(_id).c_str());
        ImNodes::EndInputAttribute();
    }

    ImNodes::EndNode();
}
