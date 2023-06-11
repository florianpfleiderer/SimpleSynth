//
// Created by Robert Ristic on 16.05.23.
//

#ifndef SIMPLESYNTH_OSCILLATOR_H
#define SIMPLESYNTH_OSCILLATOR_H

#include "Module.h"

class Oscillator : public Module {
    int _id_output;
public:
    Oscillator(std::string name);
    Oscillator(int id, std::vector<Connector> connectors, int id_out);

    void draw() override;
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
    void serialize_settings(std::ostream &ostream) override;
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id, std::vector<Connector> module_connectors);

    ~Oscillator() override;
};

#endif // OSCILLATOR_H