#include "../../include/model/Book.h"


Book::Book(std::shared_ptr<MatchingEngineBase> matchingEnigneBase){
    this->machineEngineBase = matchingEnigneBase;
}

void Book::orderBook(const OrderPtr& orderPtr,OrderBuffer& writerBuffer){
    machineEngineBase->match(orderPtr,writerBuffer);
}

// Path: src/model/Order.cpp