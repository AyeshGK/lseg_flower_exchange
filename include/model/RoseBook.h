#ifndef ROSEBOOK_H
#define ROSEBOOK_H

#include "Book.h"

class RoseBook : public Book {
public:
    // Constructor
    RoseBook(std::shared_ptr<MatchingEngineBase> matchingEngineeringBase) : Book(matchingEngineeringBase) {}

    // Add any additional member functions or variables here
};

#endif  // ROSEBOOK_H
