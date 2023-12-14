#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <vector>
#include "Order.h"
#include <memory>
#include <vector>
#include "OrderBuffer.h"


class CSVWriter {
public:
    CSVWriter(const std::string& filename, OrderBuffer& writerBuffer);
    

    void writeCSV();

    // std::vector<OrderPtr> appendCSV(std::vector<OrderPtr>& orders);

private:
    // OrderPtr parseCSVLine(const std::string& line);

    std::string filename;

    OrderBuffer& writerBuffer;

    void add_row(std::ofstream & file, OrderPtr order);

};

#endif  // CSV_WRITER_H
