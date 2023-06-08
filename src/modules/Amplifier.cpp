//
// Created by Moritz Mairhofer on 30.05.23.
//

#include "imnodes.h"

#include "../../include/modules/Amplifier.h"


Amplifier::Amplifier() : Module("Amplifier"), _id_output(IdGenerator::generateId()),
                           _id_input(IdGenerator::generateId())  {}


void Amplifier::amplify(stk::StkFloat signal , double amp_val) {
    //...


}

virtual void tick(stk::StkFloat* buffer, unsigned int nBufferFrames, int output_id) {
    /*
     WIE VERSTÄRKT WIRD
     buffer_oscilattor.copy(buffer)
     pairs(0)->osc->tick(buffer_osc, nBufferFrames, output_id)

     WAS VERSTÄRKT WIRD
     buffer_ton
     pairs(1)->osc->tick(buffer_ton, nBufferFrames, output_id)

     amplify(buffer_oscillator, buffer_ton)
    */
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