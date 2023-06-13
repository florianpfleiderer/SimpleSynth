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


    /**
     * @brief creates a Output object from the given module string of the save-file
     * 
     * @param module_str Output module string from the save-file
     * @param module_id id of the Output object
     * @return std::shared_ptr<Module> to unserialized Output object
     */
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);
    
    void draw() override;

    void serialize_settings(std::ostream &ostream) override;
    
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
};

#endif // SIMPLESYNTH_OUTPUT_H
