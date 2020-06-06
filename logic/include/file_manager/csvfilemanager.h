#ifndef CSVFILEMANAGER_H
#define CSVFILEMANAGER_H

#include <string>
#include <vector>

#include "logic/include/file_manager/filemanager.h"

class CSVFileManager {
public:
    CSVFileManager();

    std::vector<std::vector<std::string>> read(const std::string &path, const std::string &sep);

    std::vector<std::vector<double>> readIntoDouble(const std::string &path, const std::string &sep);

private:
    std::vector<std::string> readIntoLines(const std::string &path, const std::string &line_sep);

    FileManager file_manager_;

};

#endif // CSVFILEMANAGER_H
