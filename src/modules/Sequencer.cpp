//
// Created by Dennis Waniek on 31.05.2023.
//

#include "../../include/modules/Sequencer.h"
#include "imnodes.h"

Sequencer::Sequencer(unsigned int input_size) : Module("Sequencer"), _id_bpm(IdGenerator::generateId()), _id_output(IdGenerator::generateId()){
    _ids_input = std::vector<int>(input_size);
    std::generate(_ids_input.begin(), _ids_input.end(), IdGenerator::generateId);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    for(auto id : _ids_input){
        _connectors.emplace_back(ConnectorType::INPUT, id);
    }
}

//Sequencer::~Sequencer(){
//}

bool Sequencer::tick(stk::StkFrames &frames, double streamTime, int output_id){




    bool valid_result = false;
    unsigned int frame_len = frames.size();
    double step_duration = 1 / (_bpm/60); // step duration in seconds is one divided by beats per second
    int step_index = (int)( ( (long)(streamTime / step_duration) ) % _ids_input.size() );
    // int frame_start_ind = (int) ( (long)(streamTime / (1 / frames.dataRate())) % frame_len ); // position in frame via index according to streamTime and dataRate

    stk::StkFrames input_frame = stk::StkFrames(frame_len, 1);
    std::shared_ptr<Module> module = nullptr;
    int module_output = -1;
    (void) output_id; // not used because only one output exists

    for(auto c : _connections){
        std::cout << _ids_input[step_index];
        std::cout << c.input_id;
        if(_ids_input[step_index] == c.input_id){
            module = c.module;
            module_output = c.output_id;
            valid_result = true;
            break;
        }
    }

    if(valid_result){
        module->tick(frames, streamTime, module_output);
    }
    return true;
//
//    if(valid_result){
//        valid_result = module->tick(input_frame, streamTime, module_output);
//
//        if(valid_result){
//            for(unsigned int index = 0; index < frame_len; index++){
//                frames[frame_start_ind + index] = input_frame[index];
//            }
//            return true;
//        }
//    }
//    return false;

    // 1. create empty frame
    // 1.1 find correct input module
    // 2. get data from appropiate input
    // 3. select data range
    // 4. iterate and copy data accordingly
/*
    bool valid_result = false;
    unsigned int frame_len = frames.size();
    double delta_t = 1 / frames.dataRate();
    int step_index = calc_step_index(streamTime);
    int last_step_index = step_index;
    int frame_start_ind = (int) ( (long)(streamTime / (1 / frames.dataRate())) % frame_len ); // position in frame via index according to streamTime and dataRate
    stk::StkFrames input_frame = stk::StkFrames(frame_len, 1);    // empty frame for input data
    std::shared_ptr<Module> module = nullptr;
    int module_output = -1;
    (void) output_id; // not used because only one output exists

    for(auto c : _connections){    // get corresponding input module
        if(_ids_input[step_index] == c.input_id){
            module = c.module;
            module_output = c.output_id;
            valid_result = true;
            break;
        }
    }

    for(unsigned int index = frame_start_ind; index < frame_len; index++){   // copy data to resulting frame
        step_index = calc_step_index(streamTime + delta_t * index - frame_start_ind);    // check if step_index has changed
        if(step_index != last_step_index){    // change input source
            last_step_index = step_index;

            for(auto c : _connections){    // get corresponding input module
                if(_ids_input[step_index] == c.input_id){
                    module = c.module;
                    module_output = c.output_id;
                    valid_result = true;
                    break;
                }
            }
            if(valid_result){
                valid_result = module->tick(input_frame, streamTime, module_output);
            }
        }
        if(valid_result){
            frames[index] = input_frame[index];
        }
    }
    return true;
    */
}

int Sequencer::calc_step_index(double streamTime){
    double step_duration = 1 / (_bpm/60); // step duration in seconds is one divided by beats per second
    int step_index = (int)( ( (long)(streamTime / step_duration) ) % _ids_input.size() );

    return step_index;
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

void Sequencer::serialize_settings(std::ostream &ostream){
    (void) ostream;
}

