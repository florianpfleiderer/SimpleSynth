//
// Created by Dennis Waniek on 31.05.2023.
//

#include "../../include/modules/Sequencer.h"
#include "imnodes.h"

Sequencer::Sequencer(int input_size, int beats_per_minute) : Module("Sequencer"), _id_output(IdGenerator::generateId()) {
    bpm = beats_per_minute;
    _ids_input = std::vector<unsigned int>(input_size);
    std::generate(_ids_input.begin(), _ids_input.end(), IdGenerator::generateId);

    for(auto i: _ids_input){
        std::cout << i << ", ";
    }
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

    int input_number = 1;
    for(unsigned int _id : _ids_input){
        std::string input_name = "in " + std::to_string(input_number);
        ImNodes::BeginInputAttribute(_id);
        ImGui::TextUnformatted(input_name.c_str());
        ImNodes::EndInputAttribute();

        input_number++;
    }

    ImNodes::EndNode();
}

