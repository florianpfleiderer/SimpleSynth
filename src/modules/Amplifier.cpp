//
// Created by Moritz Mairhofer on 30.05.23.
//

#include "imnodes.h"

#include "../../include/modules/Amplifier.h"
#include "Stk.h"


Amplifier::Amplifier(unsigned int gain) : Module("Amplifier"), _id_output(IdGenerator::generateId()),
                           _id_input(IdGenerator::generateId()), _gain(gain)
                           {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);

}

//! Set the gain factor
void Amplifier::setGain(unsigned int g) {
    _gain  = g;
}

//! Amplify the StkFloat values (audio data) contained in frame
void Amplifier::amplify(stk::StkFrames& frames, unsigned int g) {
    // Amplify and call copy constructor
    stk::StkFrames frames_amplified = frames * g;

    //Deep copy the amplified data to the original frames object
    // TODO: Fehlermöglichkeit, evtl. geht Information zu bufferSize_, dataRate_ etc. verloren
    frames = frames_amplified;
}

bool Amplifier::tick(stk::StkFrames& frames, double streamTime, int output_id) {

    // Fill frames with audio data and amplify the data
    for(auto & conn : this->_connections){
        // Annahme: Jedes Module befüllt frames mit seinen Werten
        conn.module->tick(frames, streamTime, output_id);
    }

    if(frames.empty())
        return false;

    // Amplify the audio signal stored in frames
    amplify(frames, _gain);

    return true;
}

//! Create the GUI (node) for the amplifier class
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

//TODO: implement
void Amplifier::serialize_settings(std::ostream &ostream)
{
    (void) ostream;
}