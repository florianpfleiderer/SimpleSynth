//
// Created by Moritz Mairhofer on 30.05.23.
//

#include "imnodes.h"

#include "../../include/modules/Amplifier.h"


Amplifier::Amplifier(unsigned int gain) : Module("Amplifier"), _id_output(IdGenerator::generateId()),
                           _id_input(IdGenerator::generateId()), _gain(gain)  {}

void Amplifier::setGain(unsigned int g) {
    _gain  = g;
}


void Amplifier::amplify(stk::StkFrames& frames) {
    frames.operator*(_gain);
}

bool Amplifier::tick(stk::StkFrames& frames, double streamTime, int output_id) {

    // Fill frames with audio data and amplify the data
    for(auto & conn : _connections){
        // Annahme: Jedes Module befüllt frames mit Werten
        conn.module->tick(frames, streamTime, output_id);

        amplify(frames);
    }

    return true;
}


void Amplifier::draw()
{
    // Create empty node
    std::cout << "AmpId: " << getId() << std::endl;
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    // Input pin
    ImNodes::BeginInputAttribute(_id_input);
    ImGui::Text("in");
    ImNodes::EndInputAttribute();

    // Output pin
    ImNodes::BeginOutputAttribute(_id_output);
    ImGui::Text("out");
    ImNodes::EndInputAttribute();

    ImNodes::EndNode();
}