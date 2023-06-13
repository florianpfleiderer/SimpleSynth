//
// Created by Florian Pfleiderer on 13.06.2023.
//

#include <imnodes.h>
#include "../../include/modules/ChorusNode.h"
#include <regex>

/**
 * @brief Default constructor
*/
ChorusNode::ChorusNode() : Module("Chorus"), 
                 _id_input(IdGenerator::generateId()), 
                 _id_output(IdGenerator::generateId()), 
                 _id_chorus(IdGenerator::generateId()), 
                 _mod_depth(0.0f), 
                 _mod_freq(0.0f) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    
    // set Chorus with default values
    _chorus = stk::Chorus();
}

/**
 * @brief Construct a new Chorus Node object with fixed parameters
 * 
 * @param module_id
 * @param id_input
 * @param id_output
 * @param id_chorus
 * @param mod_depth
 * @param mod_freq
 * 
 */
ChorusNode::ChorusNode(int module_id, int id_input, int id_output, int id_chorus, float mod_depth, float mod_freq)
                 : Module("Chorus", module_id), 
                 _id_input(id_input), 
                 _id_output(id_output), 
                 _id_chorus(id_chorus), 
                 _mod_depth(mod_depth), 
                 _mod_freq(mod_freq) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    
    // set Chorus with default values
    _chorus = stk::Chorus();
}

void ChorusNode::draw() {

    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginStaticAttribute(_id_chorus);
    ImGui::PushItemWidth(100.0f);
    ImGui::SliderFloat("mod_depth", &_mod_depth, 0.0f, 1.0f);
    ImGui::SliderFloat("mod_freq", &_mod_freq, 0.0f, 1.0f);
    ImGui::PopItemWidth();
    setModDepth(_mod_depth);
    setModFreq(_mod_freq);
    ImGui::Text("mod_depth=%03f", _mod_depth);
    ImGui::Text("mod_freq=%03f", _mod_freq);
    ImNodes::EndStaticAttribute();

    ImNodes::BeginInputAttribute(_id_input);
    ImGui::Text("Input");
    ImNodes::EndInputAttribute();

    ImNodes::BeginOutputAttribute(_id_output);
    ImGui::Indent(40.0f);
    ImGui::Text("Output");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

bool ChorusNode::tick(stk::StkFrames &frames, double streamTime, int output_id) {
    if(!_connections.empty())
        _connections[0].module->tick(frames, streamTime, output_id);

    _chorus.tick(frames);
    return true;
}

void ChorusNode::setModDepth(float mod_depth) {
    _chorus.setModDepth(mod_depth);
}

void ChorusNode::setModFreq(float mod_freq) {
    _chorus.setModFrequency(mod_freq);
}

void ChorusNode::serialize_settings(std::ostream &ostream) {

    ostream << "[module_settings]" << std::endl
            << "_id_input=" << _id_input << std::endl
            << "_id_output=" << _id_output << std::endl
            << "_id_chorus=" << _id_chorus << std::endl
            << "_mod_depth=" << _mod_depth << std::endl
            << "_mod_freq=" << _mod_freq << std::endl;
}
