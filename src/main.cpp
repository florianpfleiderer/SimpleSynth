#include <iostream>

#include "imnodes.h"

#include "backends/imgui_impl_glfw.h"
#include "GLFW/glfw3.h"

#include "SineWave.h"
#include "RtAudio.h"

#include "../include/ModuleEditor.h"

using namespace stk;
// This tick() function handles sample computation only.  It will be
// called automatically when the system needs a new buffer of audio
// samples.
int tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
          double streamTime, RtAudioStreamStatus status, void *dataPointer )
{
    /* supress warnings */
    (void)inputBuffer;
    (void)streamTime;
    (void)status;

    SineWave *sine = (SineWave *) dataPointer;
    StkFloat *samples = (StkFloat *) outputBuffer;
    for ( unsigned int i=0; i<nBufferFrames; i++ )
        *samples++ = sine->tick();
    return 0;
}


int main() {

    // Set the global sample rate before creating class instances.
    Stk::setSampleRate( 44100.0 );
    SineWave sine;
    RtAudio dac;
    // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = 1;
    RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    unsigned int bufferFrames = RT_BUFFER_SIZE;
    try {
        dac.openStream( &parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&sine );
    }
    catch ( RtAudioError &error ) {
        error.printMessage();
        goto cleanup;
    }
    sine.setFrequency(440.0);
    try {
        dac.startStream();
    }
    catch ( RtAudioError &error ) {
        error.printMessage();
        goto cleanup;
    }
    // Block waiting here.
    char keyhit;
    std::cout << "\nPlaying ... press <enter> to quit.\n";
    std::cin.get( keyhit );
    // Shut down the output stream.
    try {
        dac.closeStream();
    }
    catch ( RtAudioError &error ) {
        error.printMessage();
    }
    cleanup:

    ModuleEditor editor;

    while (!glfwWindowShouldClose(editor.getWindow())) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        glfwPollEvents();

        editor.show();

    }

    return 0;
}
