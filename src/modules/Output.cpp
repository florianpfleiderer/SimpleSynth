//
// Created by Robert Ristic on 15.05.23.
//

#include "imnodes.h"

#include "../../include/modules/Output.h"

Output::Output() : Module("Output"), _id_input(IdGenerator::generateId()) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
}

void Output::draw()
{
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(_id_input);
    ImGui::Text("out");
    ImNodes::EndInputAttribute();

    ImNodes::EndNode();
}

bool Output::tick(stk::StkFloat *buffer, unsigned int nBufferFrames, double streamTime, int output_id)
{
    (void)buffer;
    (void)nBufferFrames;
    (void)streamTime;
    (void)output_id;
    return false;
}

void Output::serialize_settings(std::ostream &ostream)
{  
    ostream << "[module_settings]" << std::endl;
    ostream << "Output was here!" << std::endl;
}

std::shared_ptr<Module> Output::unserialize(std::stringstream &module_str){
    return std::shared_ptr<Module>();
}