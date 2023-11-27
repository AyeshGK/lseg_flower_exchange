#ifndef CSV_READER_H
#define CSV_READER_H

#include <vector>
#include "Order.h"
#include <memory>


class CSVReader {
public:
    CSVReader(const std::string& filename);

    std::vector<OrderPtr> readCSV();

private:
    OrderPtr parseCSVLine(const std::string& line);

    std::string filename;
};

#endif  // CSV_READER_H
