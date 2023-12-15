#ifndef LAVENDERBOOK_H
#define LAVENDERBOOK_H

#include "Book.h"

class LavenderBook : public Book {
public:
    // Constructor
    LavenderBook(std::shared_ptr<MatchingEngineBase> matchingEngineBase) : Book(matchingEngineBase) {}

    // Add any additional member functions or variables here
};

#endif  // LAVENDERBOOK_H