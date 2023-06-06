//
// Created by Florian Pfleiderer on 04.06.2023.
//

#include <imnodes.h>
#include "../../include/modules/DelayNode.h"

DelayNode::DelayNode() : Module("Delay"), 
                 _id_input(IdGenerator::generateId()), 
                 _id_output(IdGenerator::generateId()), 
                 _id_delay_length(IdGenerator::generateId()), 
                 _delay_length(0.0f) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
    
    // set Delay with default values
    _delay = stk::Delay();
}

void DelayNode::draw() {

    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    if (ImGui::Button("Save")){ 
        [[ maybe_unused ]] std::string filename = getName() + ".ini";
    }

    ImNodes::BeginStaticAttribute(_id_delay_length);
    ImGui::PushItemWidth(100.0f);
    ImGui::SliderFloat("delay_length", &_delay_length, 0.0f, _delay.getMaximumDelay());
    ImGui::PopItemWidth();
    setDelayLength(_delay_length);
    ImGui::Text("delay_length=%03f", static_cast<float>(_delay.getDelay()));
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

bool DelayNode::tick(stk::StkFrames &frames, double streamTime, int output_id) {
    frames = _delay.tick(frames);
    for(auto &conn: this->_connections) {
        conn.module->tick(frames, streamTime, output_id);
    }
    return true;
}

bool DelayNode::setDelayLength(float delay_length) {
    if (delay_length < 0.0f) {
        return false;
    }
    _delay.setDelay(delay_length);
    return true;
}

float DelayNode::getDelayLength() const {
    return _delay_length;
}