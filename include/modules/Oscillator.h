//
// Created by Robert Ristic on 16.05.23.
//

#ifndef SIMPLESYNTH_OSCILLATOR_H
#define SIMPLESYNTH_OSCILLATOR_H

#include "Module.h"
class Oscillator : public Module {
    int _id_output;
public:
    Oscillator();
    Oscillator(int id, std::vector<Connector> connectors, int id_out);
    bool tick(stk::StkFloat *buffer, unsigned int nBufferFrames, double streamTime, int output_id) override;
    void serialize_settings(std::ostream &ostream) override;
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id, std::vector<Connector> module_connectors);

    void draw() override;
    
};

#endif // SIMPLESYNTH_OSCILLATOR_H
