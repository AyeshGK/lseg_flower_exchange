#ifndef ORCHIDBOOK_H
#define ORCHIDBOOK_H

#include "Book.h"

class OrchidBook : public Book {
public:
    // Constructor
    OrchidBook(std::shared_ptr<MatchingEngineBase> matchingEngineeringBase) : Book(matchingEngineeringBase) {}

    // Add any additional member functions or variables here
};

#endif  // ORCHIDBOOK_H