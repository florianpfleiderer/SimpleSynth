//
// Created by Dennis Waniek on 31.05.2023.
//

#include "../../include/modules/Sequencer.h"
#include "imnodes.h"

Sequencer::Sequencer(unsigned int input_size) : Module("Sequencer"), _id_bpm(IdGenerator::generateId()), _id_output(IdGenerator::generateId()){
    _ids_input = std::vector<int>(input_size);
    std::generate(_ids_input.begin(), _ids_input.end(), IdGenerator::generateId);
    }

Sequencer::~Sequencer(){
}

bool Sequencer::tick(stk::StkFrames &frames, double streamTime, int output_id){

    bool valid_result = false;
    unsigned long step_duration = 1 / (_bpm/60); // step duration is one divided by beats per second
    int step_index = (int)( ( (long)(streamTime / step_duration) ) % _ids_input.size() );
    int frame_start_ind = (int)(streamTime / (1 / frames.dataRate())); // position in frame via index according to streamTime and dataRate
    int frame_len = (int)(step_duration / (1 / frames.dataRate()));

    stk::StkFrames input_frame = stk::StkFrames(frame_len, 1);
    std::shared_ptr<Module> module = nullptr;
    int module_output = -1;
    (void) output_id; // not used because only one output exists

    for(auto c : _connections){
        if(_ids_input[step_index] == c.input_id){
            module = c.module;
            module_output = c.output_id;
            valid_result = true;
            break;
        }
    }

    if(valid_result){
        valid_result = module->tick(input_frame, streamTime, module_output);

        if(valid_result){
            for(int index = 0; index < frame_len; index++){
                frames[frame_start_ind + index] = input_frame[index];
            }
            return true;
        }
    }
    return false;

    // 1. create empty frame
    // 1.1 find correct input module
    // 2. get data from appropiate input
    // 3. select data range
    // 4. iterate and copy data accordingly
}

void Sequencer::draw() {

    ImNodes::BeginNode(getId());

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginStaticAttribute(_id_bpm);
    ImGui::PushItemWidth(150.0f);
    ImGui::SliderInt("BPM (1-500)", &_bpm, 1, 500);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

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

