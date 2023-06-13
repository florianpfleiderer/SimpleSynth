//
// Created by Robert Ristic on 15.05.23.
//

#ifndef SIMPLESYNTH_OUTPUT_H
#define SIMPLESYNTH_OUTPUT_H

#include "Module.h"
#include "Stk.h"
#include "RtAudio.h"

class Output : public Module {
    int _id_input;
    RtAudio dac;
    RtAudio::StreamParameters parameters;
    RtAudioFormat format = ( sizeof(stk::StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    unsigned int bufferFrames = stk::RT_BUFFER_SIZE;

public:
    Output();
    Output(int id, std::vector<Connector> connectors, int id_in);
    ~Output();
    stk::StkFrames _frames;
    bool PLAY = false;
    void draw() override;
    void serialize_settings(std::ostream &ostream) override;
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id, std::vector<Connector> module_connectors);
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
    
};
int tick_output( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void *dataPointer );
#endif // SIMPLESYNTH_OUTPUT_H
