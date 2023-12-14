#ifndef LAVENDERBOOK_H
#define LAVENDERBOOK_H

#include "Book.h"

class LavenderBook : public Book {
public:
    // Constructor
    LavenderBook(std::shared_ptr<MachineEngineBase> machineEngineBase) : Book(machineEngineBase) {}

    // Add any additional member functions or variables here
};

#endif  // LAVENDERBOOK_H