#ifndef MACHINEENGINEBASE_H
#define MACHINEENGINEBASE_H

#include "Order.h"
#include "OrderBuffer.h"

class MachineEngineBase {
public:
    virtual void match(const OrderPtr& orderPtr,OrderBuffer& writerBuffer) = 0;
    virtual ~MachineEngineBase() = default;
};

#endif // MACHINEENGINEBASE_H
