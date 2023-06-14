//
// Created by Florian Pfleiderer on 13.06.2023.
//

#include <imnodes.h>
#include "../../include/modules/PitchShiftNode.h"
#include <regex>

/**
 * @brief Default constructor
 * 
 */
PitchShiftNode::PitchShiftNode() : Module("PitchShift"), 
                 _id_input(IdGenerator::generateId()), 
                 _id_output(IdGenerator::generateId()), 
                 _id_pitch_shift(IdGenerator::generateId()), 
                 _pitch_shift(0.0f) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    
    // set PitchShift with default values
    _pitch = stk::PitShift();
}

/**
 * @brief Construct a new Pitch Shift Node object with fixed parameters
 * 
 * @param module_id
 * @param id_input
 * @param id_output
 * @param id_pitch_shift
 * @param pitch_shift
 * 
 */
PitchShiftNode::PitchShiftNode(int module_id, int id_input, int id_output, int id_pitch_shift, float pitch_shift)
                 : Module("PitchShift", module_id), 
                 _id_input(id_input), 
                 _id_output(id_output), 
                 _id_pitch_shift(id_pitch_shift), 
                 _pitch_shift(pitch_shift) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    
    // set PitchShift with default values
    _pitch = stk::PitShift();
}

void PitchShiftNode::draw() {

    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginStaticAttribute(_id_pitch_shift);
    ImGui::PushItemWidth(100.0f);
    ImGui::SliderFloat("pitch_shift", &_pitch_shift, 0.0f, 1.0f);
    ImGui::PopItemWidth();
    setPitchShift(_pitch_shift);
    ImGui::Text("pitch_shift=%03f", _pitch_shift);

    ImNodes::EndStaticAttribute();

    ImNodes::BeginInputAttribute(_id_input);
    ImGui::Text("input");
    ImNodes::EndInputAttribute();

    ImNodes::BeginOutputAttribute(_id_output);
    ImGui::Indent(40.0f);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

bool PitchShiftNode::tick(stk::StkFrames &frames, double streamTime, int output_id) {
    if(!_connections.empty())
        _connections[0].module->tick(frames, streamTime, output_id);
    
    _pitch.tick(frames);
    return true;
}

void PitchShiftNode::setPitchShift(float pitch_shift) {
    _pitch.setShift(pitch_shift);
}

void PitchShiftNode::serialize_settings(std::ostream &ostream) {

    ostream << "[module_settings]" << std::endl
            << "_id_input=" << _id_input << std::endl
            << "_id_output=" << _id_output << std::endl
            << "_id_pitch_shift=" << _id_pitch_shift << std::endl
            << "_pitch_shift=" << _pitch_shift << std::endl;
}

std::shared_ptr<Module> PitchShiftNode::unserialize(std::stringstream& module_str, int module_id) {
    (void) module_str;
    (void) module_id;
    return nullptr;
}