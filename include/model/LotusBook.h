#ifndef LOTUSBOOK_H
#define LOTUSBOOK_H

#include "Book.h"

class LotusBook : public Book {
public:
    // Constructor
    LotusBook(std::shared_ptr<MatchingEngineBase> matchingEngineeringBase) : Book(matchingEngineeringBase) {}

    // Add any additional member functions or variables here
};

#endif  // LOTUSBOOK_H
