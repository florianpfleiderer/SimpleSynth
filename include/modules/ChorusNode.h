//
// Created by Florian Pfleiderer on 13.06.2023.
//

#include "Module.h"
#include "Stk.h"
#include "Chorus.h"

/**
 * @brief Chorus Module
 * @details This module adds a chorus effect to the input signal
 * 
 * @param _id_input
 * @param _id_output
 * @param _id_chorus
 * @param _chorus
 * @param _mod_depth
 * @param _mod_freq
 */
class ChorusNode : public Module {
    const int _id_input;
    const int _id_output;
    const int _id_chorus;
    float _mod_depth;
    float _mod_freq;

    /*
    * @brief Chorus object from stk library
    * @see https://ccrma.stanford.edu/software/stk/classstk_1_1Chorus.html
    */
    stk::Chorus _chorus;

public:
    /**
     * @brief Constructor for initialising default values
     */
    explicit ChorusNode();

    /**
     * @brief Construct a new Chorus Node object with full control
     * 
     * @param module_id
     * @param id_input 
     * @param id_output 
     * @param _id_chorus 
     * @param _mod_depth 
     * @param _mod_freq 
     */
    explicit ChorusNode(int module_id, int id_input, int id_output, int _id_chorus, float _mod_depth, float _mod_freq);

    void draw() override;
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    /**
     * @brief Sets the modulation depth
     * @param mod_depth
     * @return true if successful
     */
    void setModDepth(float mod_depth);

    /**
     * @brief Sets the modulation frequency
     * @param mod_freq
     * @return true if successful
     */
    void setModFreq(float mod_freq);

    void serialize_settings(std::ostream &ostream) override;

    /**
     * @brief creates a ChorusNode object from the given module string of the save-file
     * 
     * @param module_str ChorusNode module string from the save-file
     * @param module_id id of the ChorusNode object
     * @return std::shared_ptr<Module> to unserialized ChorusNode object
     */
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);
};

