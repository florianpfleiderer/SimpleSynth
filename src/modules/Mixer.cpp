//
// Created by Moritz Mairhofer on 30.05.23.
//

#include "imnodes.h"

#include "../../include/modules/Mixer.h"
#include "Stk.h"


Mixer::Mixer() : Module("Mixer"), _id_output(IdGenerator::generateId()),
                         _id_input_1(IdGenerator::generateId()), _id_input_2(IdGenerator::generateId())   {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input_1);
    _connectors.emplace_back(ConnectorType::INPUT, _id_input_2);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
}

stk::StkFrames Mixer::mix(stk::StkFrames& audio_signal_1, stk::StkFrames& audio_signal_2) {

    stk::StkFrames mixed_signal = audio_signal_1 + audio_signal_2;

    return mixed_signal;
}

bool Mixer::tick(stk::StkFrames &frames, double streamTime, int output_id) {

    //Create Frame variables for mixing
    stk::StkFrames *audio_signals = new stk::StkFrames[_connectors.size()];

    for(unsigned int i = 0; i < this->_connections.size(); i++) {
        this->_connections[i].module->tick(audio_signals[i], streamTime, output_id);
    }

    stk::StkFrames mixed_signal = mix(audio_signals[0], audio_signals[1]);
    frames = mixed_signal;

    delete [] audio_signals;

    return  true;
}

void Mixer::draw()
{
    // Create empty node
    std::cout << "MixId: " << getId() << std::endl;
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    // Input pin 1
    ImNodes::BeginInputAttribute(_id_input_1);
    ImGui::Text("in_1");
    ImNodes::EndInputAttribute();

    // Input pin 2
    ImNodes::BeginInputAttribute(_id_input_2);
    ImGui::Text("in_2");
    ImNodes::EndInputAttribute();

    // Output pin
    ImNodes::BeginOutputAttribute(_id_output);
    ImGui::Text("out");
    ImNodes::EndInputAttribute();

    ImNodes::EndNode();
}

void Mixer::serialize_settings(std::ostream &ostream) {
    ostream << "Mixer" << std::endl;
}