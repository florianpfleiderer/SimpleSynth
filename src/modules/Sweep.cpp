//
// Created by Cheetah on 09.06.2023.
//

#include "Sweep.h"
#include "imnodes.h"
#include "Stk.h"
#include <chrono>

Sweep::Sweep(double startFreq, double endFreq, double duration)
        : Oscillator("Sweep"), sweepStartFrequency(startFreq), sweepEndFrequency(endFreq),
          sweepDuration(duration), startTime(0.0), isSweeping(false)
{
}

void Sweep::startSweep()
{
    isSweeping = true;
    startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Sweep::stopSweep()
{
    isSweeping = false;
}

void Sweep::draw()
{
    Oscillator::draw();

    ImNodes::BeginOutputAttribute(_id_output);

    ImGui::Text("out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

bool Sweep::tick(stk::StkFrames &frames, double streamTime, int output_id)
{
    (void)output_id;
    (void)streamTime;

    if (isSweeping)
    {
        double currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - startTime;;
        if (currentTime <= sweepDuration)
        {
            double t = currentTime / sweepDuration;
            double currentFrequency = sweepStartFrequency + (sweepEndFrequency - sweepStartFrequency) * t;
            sineWave.setFrequency(currentFrequency);
        }
        else
        {
            isSweeping = false;
            sineWave.setFrequency(sweepEndFrequency);
        }
    }
    else
    {
        sineWave.setFrequency(sweepEndFrequency);
    }

    sineWave.tick(frames);
    return true;
}

