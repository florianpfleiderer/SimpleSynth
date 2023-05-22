//
// Created by Robert Ristic on 15.05.23.
//

#ifndef SIMPLESYNTH_MODULE_H
#define SIMPLESYNTH_MODULE_H

#include <string>
#include "Stk.h"
#include "../IdGenerator.h"

class Module {
    const int _id; //! module id
    const std::string _name; //! module name
public:
    Module(std::string name);
    int getId() const;
    const std::string getName() const;
    virtual void draw() = 0;
    virtual ~Module();
};


#endif // SIMPLESYNTH_MODULE_H
