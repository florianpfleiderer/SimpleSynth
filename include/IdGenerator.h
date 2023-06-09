//
// Created by Robert Ristic on 22.05.23.
//

#ifndef SIMPLESYNTH_IDGENERATOR_H
#define SIMPLESYNTH_IDGENERATOR_H

class IdGenerator {
    /** id */
    inline static int _id;

public:
    IdGenerator() {
        _id = 0;
    }

    /**
     * Generate unique new id
     * @return id
     */
    static int generateId() {
        return ++_id;
    }
    
    /**
     * @brief only used for loading id value from save-file
     * TODO: change access rights so it can only be accessed by ModuleEditor::load
     * 
     * @param id 
     */
    static void loadId(int id) {
        _id = id;
    }

    /**
     * @brief returns the current value of id without changing it
     * 
     * @return int current value of id
     */
    static int saveId() {
        return _id;
    }

    /**
     * Delete copy constructor
     */
    IdGenerator(IdGenerator const&)     = delete;
    /**
     * Delete = operator
     */
    void operator=(IdGenerator const&)  = delete;
};

#endif //SIMPLESYNTH_IDGENERATOR_H
