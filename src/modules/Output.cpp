//
// Created by Robert Ristic on 15.05.23.
//

#include "imnodes.h"
#include <regex>

#include "../../include/modules/Output.h"

Output::Output() : Module("Output"), _id_input(IdGenerator::generateId()), _frames(stk::RT_BUFFER_SIZE, 1) {
    _connectors.emplace_back(ConnectorType::INPUT, _id_input);
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = _frames.channels();

    // open Stream
    try {
            dac.openStream(&parameters, NULL, format, (unsigned int)stk::Stk::sampleRate(), &bufferFrames, &tick_output,
                        this);
        }
        catch (RtAudioError &error) {
            error.printMessage();
    //      goto cleanup;
        }
        //start Stream
    try {
            dac.startStream();
        }
        catch (RtAudioError &error) {
            error.printMessage();
        //  goto cleanup;
        }
    this->tick(_frames, 0, 0); /* TODO output_id */
}

Output::Output(int id, std::vector<Connector> connectors, int id_in)
                : Module("Output", id, connectors), _id_input(id_in),  _frames(stk::RT_BUFFER_SIZE, 1) {
    this->tick(_frames, 0, 0); /* TODO output_id */
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

    // Button to trigger action
    if (ImGui::Button("Play"))
    {
        PLAY = true;
    }
    ImNodes::EndNode();
}
    

bool Output::tick(stk::StkFrames &frames, double streamTime, int output_id) {

    //go thru all connections and tick them
        for(auto &conn: this->_connections) {
            conn.module->tick(frames, streamTime, output_id); /* TODO ouput id */
        }
    return true;
}


int tick_output( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *dataPointer ) {
        Output* module = (Output*)dataPointer;
        module->tick(module->_frames, streamTime, 0); /* TODO output_id */
        stk::StkFloat *samples = (stk::StkFloat *) outputBuffer;
        for ( unsigned int i=0; i<nBufferFrames; i++ ) {
            *samples++ = module->_frames[i*module->_frames.channels()];
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