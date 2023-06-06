//
// Created by Florian Pfleiderer on 05.06.2023.
//

#include <imnodes.h>
#include "../../include/modules/EchoNode.h"

EchoNode::EchoNode() : Module("Echo"), 
                 _id_input(IdGenerator::generateId()), 
                 _id_output(IdGenerator::generateId()),
                 _id_echo_delay(IdGenerator::generateId()),
                 _echo_delay(0.0f) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    
    // set Echo with default values
    _echo = stk::Echo();
}

void EchoNode::draw() {

    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    if (ImGui::Button("Save")){ 
        [[ maybe_unused ]] std::string filename = getName() + ".ini";
    }

    ImNodes::BeginStaticAttribute(_id_echo_delay);
    ImGui::PushItemWidth(100.0f);
    ImGui::SliderFloat("echo_delay", &_echo_delay, 0.0f, 100.0f);
    ImGui::PopItemWidth();
    setEchoDelay(_echo_delay);
    ImGui::Text("echo_delay=%03f", _echo_delay);
    ImNodes::EndStaticAttribute();

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

bool EchoNode::tick(stk::StkFrames &frames, double streamTime, int output_id) {
    (void)streamTime;
    frames = _echo.tick(frames);
    (void)output_id;
    return false;
}

bool EchoNode::setEchoDelay(float echo_delay) {
    if (echo_delay < 0.0f)
        return false;
    _echo.setDelay(_echo_delay);
    return true;
}