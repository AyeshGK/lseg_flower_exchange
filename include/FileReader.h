#ifndef FILEREADER_H
#define FILEREADER_H

#include <vector>
#include <string>

class FileReader {
public:
    virtual ~FileReader() {}

    virtual std::vector<std::string> readLines(const std::string& filename) const = 0;
};

#endif  // FILEREADER_H
