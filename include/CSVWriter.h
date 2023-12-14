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
    
private:
    // OrderPtr parseCSVLine(const std::string& line);

    std::string filename;

    OrderBuffer& writerBuffer;

    void add_row(std::ofstream & file, OrderPtr order);

    std::string transactionTime(std::chrono::system_clock::time_point timePoint) const;

    std::string getSide(int side);

    std::string getStatus(int status);

};

#endif  // CSV_WRITER_H
