//
// Created by Cheetah on 08.06.2023.
//

#ifndef SIMPLESYNTH_NOISEGENERATOR_H
#define SIMPLESYNTH_NOISEGENERATOR_H

#include "Module.h"
#include "Stk.h"
#include <Noise.h>

class NoiseGenerator : public Module {
public:
    NoiseGenerator();
    NoiseGenerator(int id, int id_output);

    /**
     * @brief creates a NoiseGenerator object from the given module string of the save-file
     * 
     * @param module_str NoiseGenerator module string from the save-file
     * @param module_id id of the NoiseGenerator object
     * @return std::shared_ptr<Module> to unserialized NoiseGenerator object
     */
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);

    /**
     * Generate a tick of noise signal
     *
     * @param frames StkFrames object to store the generated samples
     * @param streamTime Current stream time
     * @param output_id ID of the output connector
     * @return True if successful, false otherwise
     */
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    /**
     * Draw the NoiseGenerator module node in the GUI
     */
    void draw() override;

    /**
     * Serialize the settings of the NoiseGenerator module
     *
     * @param ostream Output stream to write the settings to
     */
    void serialize_settings(std::ostream &ostream) override;

private:
    stk::Noise noise;  ///< TNoise generator object
    int _id_output;    ///< ID of the output connector
};

#endif //SIMPLESYNTH_NOISEGENERATOR_H
