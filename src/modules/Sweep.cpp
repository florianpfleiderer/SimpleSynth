//
// Created by Cheetah on 09.06.2023.
//
#include <iostream>
#include "../../include/modules/Sweep.h"
#include "imnodes.h"
#include "Stk.h"
#include <chrono>
#include <regex>

Sweep::Sweep(float startFreq, float endFreq, float duration)
        : Module("Sweep"), sweepStartFrequency(startFreq), sweepEndFrequency(endFreq),
          sweepDuration(duration), startTime(0.0), isSweeping(false)
{
    _id_output = IdGenerator::generateId();
    _id_start_frequency = IdGenerator::generateId();
    _id_end_frequency = IdGenerator::generateId();
    _id_duration = IdGenerator::generateId();
    _connectors.emplace_back(ConnectorType::OUTPUT, _id_output);
}

Sweep::Sweep(float startFreq, float endFreq, float duration, int module_id, int id_output, int id_start_frequency, int id_end_frequency, int id_duration )
        : Module("Sweep", module_id), sweepStartFrequency(startFreq), sweepEndFrequency(endFreq),
          sweepDuration(duration), startTime(0.0), isSweeping(false), _id_output(id_output),
          _id_start_frequency(id_start_frequency), _id_end_frequency(id_end_frequency), _id_duration(id_duration){
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

void Sweep::restartSweep()
{
    if (isSweeping) {
        stopSweep();
        startSweep();
    }
}

void Sweep::draw()
{
    ImNodes::BeginNode(getId());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(getName().c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginStaticAttribute(_id_start_frequency);
    ImGui::PushItemWidth(150.0f);
    if (ImGui::SliderFloat("Start Frequency", &sweepStartFrequency, 0, 16000.0)) {
        restartSweep();
    }
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    if (sweepStartFrequency > sweepEndFrequency) {
        sweepEndFrequency = sweepStartFrequency;
    }

    ImNodes::BeginStaticAttribute(_id_end_frequency);
    ImGui::PushItemWidth(150.0f);
    if (ImGui::SliderFloat("End Frequency", &sweepEndFrequency, sweepStartFrequency, 16000)) {
        restartSweep();
    }
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    ImNodes::BeginStaticAttribute(_id_duration);
    ImGui::PushItemWidth(150.0f);
    if (ImGui::SliderFloat("Duration", &sweepDuration, 0.0f, 20.0)) {
        restartSweep();
    }
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    ImNodes::BeginOutputAttribute(_id_output);
    ImGui::Text("out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

void Sweep::serialize_settings(std::ostream &ostream) {
    /*
    ostream << "[module_settings]" << std::endl
            << "_id_output=" << _id_output << std::endl
            << "_id_start_frequency=" << _id_output << std::endl
            << "_id_end_frequency=" << _id_output << std::endl
            << "_id_duration=" << _id_output << std::endl
            << "sweepStartFrequency=" << sweepStartFrequency << std::endl
            << "sweepEndFrequency=" << sweepEndFrequency << std::endl
            << "sweepDuration=" << sweepDuration << std::endl;
    */
    ostream << "[module_settings]" << std::endl
            << "_id_output=" << _id_output << std::endl
            << "_id_start_frequency=" << _id_start_frequency << std::endl
            << "_id_end_frequency=" << _id_end_frequency << std::endl
            << "_id_duration=" << _id_duration << std::endl
            << "sweepStartFrequency=" << sweepStartFrequency << std::endl
            << "sweepEndFrequency=" << sweepEndFrequency << std::endl
            << "sweepDuration=" << sweepDuration << std::endl;

}

std::shared_ptr<Module> Sweep::unserialize(std::stringstream &module_str, int module_id) {
    // variables
    int id_output(-1);
    int id_start_frequency(-1);
    int id_end_frequency(-1);
    int id_duration(-1);
    float sweep_start_frequency(-1);
    float sweep_end_frequency(-1);
    float sweep_duration(-1);

    // read stringstream
    std::string line;
    std::regex pattern;
    std::smatch matches;
    while(std::getline(module_str, line)) {
        pattern = "_id_output=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_output = std::stoi(matches[1].str());
                continue;;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_output=(\\d+)\":\n" + line );
            }
        }
        pattern = "_id_start_frequency=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_start_frequency = std::stoi(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_start_frequency=(\\d+)\":\n" + line );
            }
        }
        pattern = "_id_end_frequency=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_end_frequency = std::stoi(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_end_frequency=(\\d+)\":\n" + line );
            }
        }
        pattern = "_id_duration=(\\d+)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 2) {
                id_duration = std::stof(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"_id_duration=(\\d+)\":\n" + line );
            }
        }
        pattern = "sweepStartFrequency=([+-]?\\d+(\\.\\d+)?)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 3) {
                sweep_start_frequency = std::stof(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"sweepStartFrequency=([+-]?\\d+(\\.\\d+)?)\":\n" + line );
            }
        }
        pattern = "sweepEndFrequency=([+-]?\\d+(\\.\\d+)?)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 3) {
                sweep_end_frequency = std::stof(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"sweepEndFrequency=([+-]?\\d+(\\.\\d+)?)\":\n" + line );
            }
        }
        pattern = "sweepDuration=([+-]?\\d+(\\.\\d+)?)";
        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 3) {
                sweep_duration = std::stof(matches[1].str());
                continue;
            } else {
                throw std::invalid_argument("Following line does not follow the pattern \"sweepDuration=([+-]?\\d+(\\.\\d+)?)\":\n" + line );
            }
        }
    }

    // create module with read data
    if (id_output == -1) {
        throw std::invalid_argument("Can not create an DelayNode module with id_output= " + std::to_string(id_output));
    }
    if (id_start_frequency == -1) {
        throw std::invalid_argument("Can not create an DelayNode module with id_start_frequency= " + std::to_string(id_start_frequency));
    }
    if (id_end_frequency == -1) {
        throw std::invalid_argument("Can not create an DelayNode module with id_end_frequency= " + std::to_string(id_end_frequency));
    }
    if (id_duration == -1) {
        throw std::invalid_argument("Can not create an DelayNode module with id_duration= " + std::to_string(id_duration));
    }
    if (sweep_start_frequency == -1) {
        throw std::invalid_argument("Can not create an DelayNode module with sweep_start_frequency= " + std::to_string(sweep_start_frequency));
    }
    if (sweep_end_frequency == -1) {
        throw std::invalid_argument("Can not create an DelayNode module with sweep_end_frequency= " + std::to_string(sweep_end_frequency));
    }
    if (sweep_duration == -1) {
        throw std::invalid_argument("Can not create an DelayNode module with sweep_duration= " + std::to_string(sweep_duration));
    }
    return std::make_shared<Sweep>(Sweep(sweep_start_frequency, sweep_end_frequency, sweep_duration, module_id, id_output, id_start_frequency, id_end_frequency, id_duration));
}

bool Sweep::tick(stk::StkFrames &frames, double streamTime, int output_id)
{
    (void)output_id;
    (void)streamTime;

    if (isSweeping)
    {
        double currentTime = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - startTime) / 1000.0;
        if (currentTime <= sweepDuration)
        {
            double t = currentTime / sweepDuration;
            double currentFrequency = sweepStartFrequency + (sweepEndFrequency - sweepStartFrequency) * t;
            sineWave.setFrequency(currentFrequency);
        }
        else
        {
            stopSweep();
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
