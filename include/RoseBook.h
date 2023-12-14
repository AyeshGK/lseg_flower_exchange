#ifndef ROSEBOOK_H
#define ROSEBOOK_H

#include "Book.h"

class RoseBook : public Book {
public:
    // Constructor
    // RoseBook(MachineEngineBase* machineEngineBase) : Book(machineEngineBase) {}
    RoseBook(std::shared_ptr<MachineEngineBase> machineEngineBase) : Book(machineEngineBase) {}

    // Add any additional member functions or variables here
};

#endif  // ROSEBOOK_H
