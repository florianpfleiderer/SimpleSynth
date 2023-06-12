//
// Created by Robert Ristic on 15.05.23.
//

#include "imnodes.h"
#include <regex>

#include "../../include/modules/Output.h"

Output::Output() : Module("Output"), _id_input(IdGenerator::generateId()) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
}

Output::Output(int id, std::vector<Connector> connectors, int id_in)
                : Module("Output", id, connectors), _id_input(id_in) {}

void Output::draw()
{
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(_id_input);
    ImGui::Text("out");
    ImNodes::EndInputAttribute();

    // Button to trigger action
    if (ImGui::Button("Play"))
    {
        PLAY = true;
    }

    ImNodes::EndNode();
}
    

bool Output::tick(stk::StkFrames &frames, double streamTime, int output_id) {

    if(frames.empty())
        return false;

    //set StreamParameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = frames.channels();
    //set dataPointer to first sample of frames
    void *dataPointer = &frames[0];
    
    // open Stream
    try {
        dac.openStream(&parameters, NULL, format, (unsigned int)stk::Stk::sampleRate(), &bufferFrames, &tick_output, (void *)dataPointer );
    }
    catch (RtAudioError &error) {
        error.printMessage();
        goto cleanup;
    }

    //go thru all connections and tick them
    for(auto &conn: this->_connections) {
        streamTime = dac.getStreamTime();
        conn.module->tick(frames, streamTime, output_id);
    }
    
    
    //start Stream
    try {
        dac.startStream();
    }
    catch (RtAudioError &error) {
        error.printMessage();
        goto cleanup;
    }

    //wait for keypress
    (void)output_id;
    dac.closeStream();
    return true;

cleanup:
    dac.closeStream();
    return false;
}


int tick_output( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *dataPointer ) {
        
        stk::StkFloat *samples = (stk::StkFloat *) outputBuffer;
        stk::StkFloat *frame = (stk::StkFloat *) dataPointer;
        for ( unsigned int i=0; i<nBufferFrames; i++ ) {
            *samples++ = *frame++;
        }
        (void)inputBuffer; // We're not using inputBuffer here, but it's required by the RtAudio API.
        (void)streamTime;  // We're not using streamTime here, but it's required by the RtAudio API.
        //print status message
        if ( status ) std::cout << "Stream underflow detected!" << std::endl;


        return 0;
}

void Output::serialize_settings(std::ostream &ostream)
{
    ostream << "[module_settings]" << std::endl
            << "_id_input=" << _id_input << std::endl;
}

std::shared_ptr<Module> Output::unserialize(std::stringstream& module_str, int module_id, std::vector<Connector> module_connectors)
{
    // variables
    int id_in(-1);

    // flags
    bool module_settings_f(false);

    // read stringstream
    std::string line;
    std::regex pattern;
    std::smatch matches;
    while(std::getline(module_str, line)) {
        // search for settings
        if (line == "[module_settings]") {
            module_settings_f = true;
            continue;
        }
        // process flags
        if (module_settings_f) {
            pattern = "_id_input=(\\d+)";
            if (std::regex_search(line, matches, pattern)) {
                if (matches.size() == 2) {
                    id_in = std::stoi(matches[1].str());
                    break;
                } else {
                    throw std::invalid_argument("Following line does not follow the pattern \"_id_input=(\\d+)\":\n" + line );
                }
            }
        }
    }

    // create module with read data
    if (id_in == -1) {
        throw std::invalid_argument("Can not create an output module with id_in= " + std::to_string(id_in));
    }
    return std::make_shared<Output>(Output(module_id, module_connectors, id_in));
}