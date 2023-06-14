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

stk::StkFrames Mixer::mix(stk::StkFrames& ads_1, stk::StkFrames& ads_2) {
    // Dimension checking. Can be removed for purpose of performance
    if ( ads_1.frames() != ads_2.frames() || ads_1.channels() != ads_2.channels() ) {
        std::ostringstream error;
        error << "StkFrames::operator+: frames argument must be of equal dimensions!";
        stk::Stk::handleError(error.str(), stk::StkError::MEMORY_ACCESS);
    }
    //Mix
    return ads_1 + ads_2;
}

bool Mixer::tick(stk::StkFrames &frames, double streamTime, int output_id) {

    //Check if enough signals for mixing are available
    auto number_of_connections = _connections.size();

    if(number_of_connections <= 1) {
        return false;
    } else{

        // Create StkFrames variables (signals) for mixing
        stk::StkFrames audio_signals[2] = {stk::StkFrames (frames.frames(), frames.channels())
                                           , stk::StkFrames(frames.frames(), frames.channels())};
        // Pass the signals to the sound generators to fill them with audio data
        for(unsigned int i = 0; i < this->_connections.size(); i++) {
            this->_connections[i].module->tick(audio_signals[i], streamTime, output_id);
        }
        stk::StkFrames mixed_signal = mix(audio_signals[0], audio_signals[1]);
        frames = mixed_signal;

        return  true;
    }
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

Mixer::~Mixer() {

}