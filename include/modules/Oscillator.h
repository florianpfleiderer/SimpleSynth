//
// Created by Robert Ristic on 16.05.23.
//

#ifndef SIMPLESYNTH_OSCILLATOR_H
#define SIMPLESYNTH_OSCILLATOR_H

#include "Module.h"
#include <regex>

/**
 * @brief The Oscillator class represents a basic oscillator module.
 */
class Oscillator : public Module {
public:
    /**
     * @brief Construct Oscillator object with given name.
     * @param name Name of the oscillator module
     */
    Oscillator(std::string name);

    /**
     * @brief Construct Oscillator object with specified parameters
     * @param name Name of oscillator module
     * @param id ID of the oscillator module
     * @param id_output ID of the output connector
     * @param frequency frequency of the oscillator
     */
    Oscillator(std::string name, int id, int id_output, float frequency);

    /**
     * @brief Draw the module
     * This function is called every frame to draw the module ui
     */
    void draw() override;

    /**
     * @brief Update the frequency of the oscillator
     * @param freq The new frequency value
     */
    virtual void updateFrequency(float freq) = 0;

    /**
     * @brief Serialize the settings of the oscillator module
     * @param ostream The output stream to write the serialized data to
     */
    void serialize_settings(std::ostream &ostream) override;

    /**
     * @brief Retrieve the settings of the oscillator module from the given text stream
     * @param module_str Input text stream containing the module settings
     * @param id_output ID of the output connector (output parameter)
     * @param frequency Frequency of the oscillator (output parameter)
     */
    static void getSettingsFromText(std::stringstream &module_str, int &id_output, float &frequency);

    /**
     * @brief Destroy the Oscillator object
     */
    ~Oscillator() override;
protected:
    int _id_output;       /**< ID of the output connector */
    int _id_frequency;    /**< ID of the frequency parameter */
    float _frequency;     /**< Frequency of the oscillator */
};

#endif // OSCILLATOR_H