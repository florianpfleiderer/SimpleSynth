//
// Created by Florian Pfleiderer on 04.06.2023.
//

#include <imnodes.h>
#include "../../include/modules/Delay.h"

Delay::Delay() : Module("Delay"), _id_input(IdGenerator::generateId()), _id_output(IdGenerator::generateId()), 
                 _delay_time(0.f), _feedback(0.f) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
}

void Delay::draw() {
    const float node_width = 100.f;

    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(_id_input);
    ImGui::Text("in");
    ImNodes::EndInputAttribute();

    ImNodes::BeginStaticAttribute(_id_input << 8);
    ImGui::PushItemWidth(120.0f);
    ImGui::DragFloat("delay_time", &_delay_time, 0.01f);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    ImNodes::BeginStaticAttribute(_id_input << 16);
    ImGui::PushItemWidth(120.0f);
    ImGui::DragFloat("feedback", &_feedback, 0.01f);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    ImNodes::BeginOutputAttribute(_id_output);
    const float label_width = ImGui::CalcTextSize("out").x;
    ImGui::Indent(node_width - label_width);
    ImGui::Text("out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

bool Delay::tick(stk::StkFloat *buffer, unsigned int nBufferFrames, double streamTime, int output_id) {
    (void)buffer;
    (void)nBufferFrames;
    (void)streamTime;
    (void)output_id;
    return false;
}