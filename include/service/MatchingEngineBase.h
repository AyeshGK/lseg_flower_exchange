#ifndef MATCHINGENGINEBASE_H
#define MATCHINGENGINEBASE_H

#include "../dao/Order.h"
#include "../common/OrderBuffer.h"

class MatchingEngineBase {
public:
    virtual void match(const OrderPtr& orderPtr,OrderBuffer& writerBuffer) = 0;
    virtual ~MatchingEngineBase() = default;
};

#endif // MATCHINGENGINEBASE_H