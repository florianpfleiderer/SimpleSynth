//
// Created by Robert Ristic on 15.05.23.
//

#ifndef SIMPLESYNTH_OUTPUT_H
#define SIMPLESYNTH_OUTPUT_H

#include "Module.h"

class Output : public Module {
    int _id_input;
public:
    Output();
    Output(int id, int id_input);

    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);
    
    void draw() override;
    void serialize_settings(std::ostream &ostream) override;
    
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
};

#endif // SIMPLESYNTH_OUTPUT_H
