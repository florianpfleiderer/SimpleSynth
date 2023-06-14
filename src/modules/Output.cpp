//
// Created by Robert Ristic on 15.05.23.
//

#include "imnodes.h"
#include <regex>

#include "../../include/modules/Output.h"

Output::Output() : Module("Output"), _id_input(IdGenerator::generateId()), _frames(stk::RT_BUFFER_SIZE, 1) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);

    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = 1;

    try {
        dac.openStream( &parameters,
                        NULL,
                        format,
                        (unsigned int)stk::Stk::sampleRate(),
                        &bufferFrames,
                        &tick_output,
                        this);
    }
    catch ( RtAudioError &error ) {
        error.printMessage();
    }

    
}

Output::Output(int module_id, int id_input)
                : Module("Output", module_id), _id_input(id_input), _frames(stk::RT_BUFFER_SIZE, 1) {
                    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
                    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = 1;

    try {
        dac.openStream( &parameters,
                        NULL,
                        format,
                        (unsigned int)stk::Stk::sampleRate(),
                        &bufferFrames,
                        &tick_output,
                        this);
    }
    catch ( RtAudioError &error ) {
        error.printMessage();
    }

    
}

//Destructor
Output::~Output() {
    try {
        dac.closeStream();
    }
    catch (RtAudioError &error) {
        error.printMessage();
    }
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
    if (_connections.empty() == false){
        _connections[0].module->tick(frames, streamTime, output_id);
    } else {
        for (unsigned int i=0; i < bufferFrames; i++){
            frames[i] = 0;
        }
    }

    return true;
}

int tick_output( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                 double streamTime, RtAudioStreamStatus status, void *dataPointer )
{
    (void)inputBuffer;
    (void)streamTime;
    (void)status;
    (void)nBufferFrames;
    Output* module = (Output*) dataPointer;

    module->tick(module->_frames, streamTime, 0); /* TODO output */

    /* copy frame to output */
    stk::StkFloat *samples = (stk::StkFloat *) outputBuffer;
    for ( unsigned int i=0; i<nBufferFrames; i++ )
        *samples++ = module->_frames[i];

    return 0;
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

bool Output::play(bool state){
    if (state && !dac.isStreamRunning()){
        dac.startStream();
    } else if(!state && dac.isStreamRunning()){
        dac.stopStream();
    }
    return dac.isStreamRunning();
}