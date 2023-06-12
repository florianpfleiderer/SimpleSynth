//
// Created by Cheetah on 09.06.2023.
//
#include <iostream>
#include "../../include/modules/Sweep.h"
#include "imnodes.h"
#include "Stk.h"
#include <chrono>

Sweep::Sweep(std::string name, double startFreq, double endFreq, float duration)
        : Module(name), sweepStartFrequency(startFreq), sweepEndFrequency(endFreq),
          sweepDuration(duration), startTime(0.0), isSweeping(false)
{
    _id_output = IdGenerator::generateId();
    _id_start_frequency = IdGenerator::generateId();
    _id_end_frequency = IdGenerator::generateId();
    _id_duration = IdGenerator::generateId();
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
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
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginStaticAttribute(_id_start_frequency);
    ImGui::PushItemWidth(150.0f);
    ImGui::SliderFloat("Start Frequency", &sweepStartFrequency, 0, 16000.0);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    ImNodes::BeginStaticAttribute(_id_end_frequency);
    ImGui::PushItemWidth(150.0f);
    ImGui::SliderFloat("End Frequency", &sweepEndFrequency, sweepStartFrequency, 16000);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    ImNodes::BeginStaticAttribute(_id_duration);
    ImGui::PushItemWidth(150.0f);
    ImGui::SliderFloat("Duration", &sweepDuration, 0.0f, 20.0);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    ImNodes::BeginOutputAttribute(_id_output);
    ImGui::Text("out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

void Sweep::serialize_settings(std::ostream &ostream) {
    ostream << "[module_settings]" << std::endl
            << "_id_output=" << _id_output << std::endl
            << "_start_frequency=" << sweepStartFrequency << std::endl
            << "_end_frequency=" << sweepEndFrequency << std::endl
            << "_duration=" << sweepDuration << std::endl;
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

void Sweep::updateFrequency(float frequency) {
    std::cout<<frequency;
}