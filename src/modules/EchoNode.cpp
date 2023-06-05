//
// Created by Florian Pfleiderer on 05.06.2023.
//

#include <imnodes.h>
#include "../../include/modules/EchoNode.h"

EchoNode::EchoNode() : Module("Echo"), 
                 _id_input(IdGenerator::generateId()), 
                 _id_output(IdGenerator::generateId()) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    
    // set Echo with default values
    _Echo = stk::Echo();
}

void EchoNode::draw() {
    // const float node_width = 100.0f;

    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    // ImNodes::BeginStaticAttribute(_id_Echo_time);
    // ImGui::PushItemWidth(100.0f);
    // ImGui::DragFloat("Echo_time", &_Echo_time, 0.01f);
    // ImGui::PopItemWidth();
    // ImNodes::EndStaticAttribute();

    // ImNodes::BeginStaticAttribute(_id_feedback);
    // ImGui::PushItemWidth(100.0f);
    // ImGui::DragFloat("feedback", &_feedback, 0.01f);
    // ImGui::PopItemWidth();
    // ImNodes::EndStaticAttribute();

    ImNodes::BeginInputAttribute(_id_input);
    ImGui::Text("in");
    ImNodes::EndInputAttribute();

    ImNodes::BeginOutputAttribute(_id_output);
    // const float label_width = ImGui::CalcTextSize("out").x;
    ImGui::Indent(150.0f);
    ImGui::Text("out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

bool EchoNode::tick(stk::StkFloat *buffer, unsigned int nBufferFrames, double streamTime, int output_id) {
    (void)buffer;
    (void)streamTime;
    for(unsigned int i = 0; i < nBufferFrames; i++) {
        *buffer++ = _Echo.tick(buffer[i]);
    }
    (void)output_id;
    return false;
}