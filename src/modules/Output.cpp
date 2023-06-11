//
// Created by Robert Ristic on 15.05.23.
//

#include "imnodes.h"
#include <regex>

#include "../../include/modules/Output.h"

Output::Output() : Module("Output"), _id_input(IdGenerator::generateId()) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
}

Output::Output(int module_id, int id_input)
                : Module("Output", module_id), _id_input(id_input) {
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

bool Output::tick(stk::StkFrames &frames, double streamTime, int output_id) {
    (void)frames;
    (void)streamTime;
    (void)output_id;
    return true;
}

void Output::serialize_settings(std::ostream &ostream)
{
    ostream << "[module_settings]" << std::endl
            << "_id_input=" << _id_input << std::endl;
}

std::shared_ptr<Module> Output::unserialize(std::stringstream& module_str, int module_id)
{   
    // variables
    int id_input(-1);

    // read stringstream
    std::string line;
    std::regex pattern;
    std::smatch matches;
    while(std::getline(module_str, line)) {
        pattern = "_id_input=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_input = std::stoi(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_input=(\\d+)\":\n" + line );
            }
        }
    }

    // create module with read data
    if (id_input == -1) {
        throw std::invalid_argument("Can not create an output module with id_input= " + std::to_string(id_input));
    }
    return std::make_shared<Output>(Output(module_id, id_input));
}