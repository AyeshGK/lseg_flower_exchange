#ifndef TULIPBOOK_H
#define TULIPBOOK_H


#include "Book.h"

class TulipBook : public Book {
public:
    // Constructor
    TulipBook(std::shared_ptr<MatchingEngineBase> matchingEngineBase) : Book(matchingEngineBase) {}

    // Add any additional member functions or variables here
};

#endif  // TULIPBOOK_H
