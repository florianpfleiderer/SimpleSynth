//
// Created by Dennis Waniek on 31.05.2023.
//

#include "../../include/modules/Sequencer.h"
#include "imnodes.h"
#include <regex>

Sequencer::Sequencer(unsigned int input_size) : Module("Sequencer"), _id_bpm(IdGenerator::generateId()), _id_output(IdGenerator::generateId()){
    _ids_input = std::vector<int>(input_size);
    std::generate(_ids_input.begin(), _ids_input.end(), IdGenerator::generateId);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    for(auto id : _ids_input){
        _connectors.emplace_back(ConnectorType::INPUT, id);
    }
}

Sequencer::Sequencer(int module_id, int id_output, int id_bpm, int bpm, std::vector<int> ids_input)
                        : Module("Sequencer", module_id), _id_bpm(id_bpm), _id_output(id_output), _ids_input(ids_input), _bpm(bpm) {
                            for(auto &id : ids_input){
                                _connectors.emplace_back(ConnectorType::INPUT, id);
                            }
}

Sequencer::~Sequencer(){

}

bool Sequencer::tick(stk::StkFrames &frames, double streamTime, int output_id){

    bool result_flag = false;
    bool valid_input = false;
    unsigned int frame_len = frames.size();
    int step_index = calc_step_index(streamTime);
    stk::StkFrames temp_frame = stk::StkFrames(frame_len, 1);    // empty frame for input data
    std::shared_ptr<Module> module = nullptr;
    int module_output = -1;
    (void) output_id; // not used because only one output exists

    for(int id_in : _ids_input){
        for(auto c : _connections){
            if(id_in == c.output_id){
                module = c.module;
                module_output = c.output_id;
                valid_input = true;
                break;
            }
        }
        if(valid_input){
            if(id_in == _ids_input[step_index]){
                result_flag = module->tick(frames, streamTime, module_output);
            }
            else{
                module->tick(temp_frame, streamTime, module_output);
            }
            valid_input = false;
        }
    }
    if(result_flag == false){
        frames *= 0;
    }
    return result_flag;


















// std::cout <<_bpm;

//    bool valid_result = false;
//    unsigned int frame_len = frames.size();
//    double step_duration = 1 / (_bpm/60); // step duration in seconds is one divided by beats per second
//    int step_index = (int)( ( (long)(streamTime / step_duration) ) % _ids_input.size() );
//    // int frame_start_ind = (int) ( (long)(streamTime / (1 / frames.dataRate())) % frame_len ); // position in frame via index according to streamTime and dataRate
//
//    stk::StkFrames input_frame = stk::StkFrames(frame_len, 1);
//    std::shared_ptr<Module> module = nullptr;
//    int module_output = -1;
//    (void) output_id; // not used because only one output exists
//
//    for(auto c : _connections){
//        std::cout << _ids_input[step_index];
//        std::cout << c.input_id;
//        if(_ids_input[step_index] == c.output_id){
//            module = c.module;
//            module_output = c.output_id;
//            valid_result = true;
//            break;
//        }
//    }
//
//    if(valid_result){
//        module->tick(frames, streamTime, module_output);
//    }
//    return true;
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
        if(_ids_input[step_index] == c.output_id){
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
                if(_ids_input[step_index] == c.output_id){
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
    double step_duration = 1 / ((double)_bpm/60); // step duration in seconds is one divided by beats per second
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
    ostream << "[module_settings]" << std::endl
            << "_id_bpm=" << _id_bpm << std::endl
            << "_id_output=" << _id_output << std::endl
            << "_bpm=" << _bpm << std::endl
            << "_ids_input:" << std::endl;
    for(auto &id_input : _ids_input) {
        ostream << id_input << std::endl;
    }
}

std::shared_ptr<Module> Sequencer::unserialize(std::stringstream& module_str, int module_id) {
    // variables
    int id_bpm(-1);
    int id_output(-1);
    int bpm(-1);
    std::vector<int> ids_input;

    // read stringstream
    std::string line;
    std::regex pattern;
    std::smatch matches;
    while(std::getline(module_str, line)) {
        pattern = "_id_bpm=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_bpm = std::stoi(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_bpm=(\\d+)\":\n" + line );
            }
        }
        pattern = "_id_output=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_output = std::stoi(matches[1].str());
                continue;;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_output=(\\d+)\":\n" + line );
            }
        }
        pattern = "_bpm=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                bpm = std::stoi(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_bpm=(\\d+)\":\n" + line );
            }
        }
        if (line == "_ids_input:") { break; }
    }
    while(std::getline(module_str, line)){
        ids_input.emplace_back(std::stoi(line));
    }


    // create module with read data
    if (id_output == -1) {
        throw std::invalid_argument("Can not create an Sequencer module with id_output= " + std::to_string(id_output));
    }
    if (id_bpm == -1) {
        throw std::invalid_argument("Can not create an Sequencer module with id_bpm= " + std::to_string(id_bpm));
    }
    if (bpm == -1) {
        throw std::invalid_argument("Can not create an Sequencer module with bpm= " + std::to_string(bpm));
    }
    if (ids_input.empty() == true) {
        throw std::invalid_argument("Can not create an Sequencer module with bpm= " + std::to_string(bpm));
    }
    return std::make_shared<Sequencer>(Sequencer(module_id, id_output, id_bpm, bpm, ids_input));
}

bool Sequencer::play(bool state) {
    /*TODO Clear everything*/
    return state;
}