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
    stk::StkFrames _frames;

    Output();
    Output(int id, int id_input);
    ~Output();
    
    /**
     * @brief creates a Output object from the given module string of the save-file
     *
     * @param module_str Output module string from the save-file
     * @param module_id id of the Output object
     * @return std::shared_ptr<Module> to unserialized Output object
     */
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);

    void draw() override;
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    void serialize_settings(std::ostream &ostream) override;
};

int tick_output( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void *dataPointer );

#endif // SIMPLESYNTH_OUTPUT_H
