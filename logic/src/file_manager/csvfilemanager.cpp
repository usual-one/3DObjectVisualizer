#include "logic/include/file_manager/csvfilemanager.h"
#include "logic/include/utils/stringsplitter.h"
#include "config.h"

CSVFileManager::CSVFileManager() {
    file_manager_ = FileManager();
}

std::vector<std::vector<std::string>> CSVFileManager::read(const std::string &path, const std::string &sep) {
    std::vector<std::string> lines = readIntoLines(path, CSV_LINE_SEPARATOR);

    std::vector<std::vector<std::string>> value_vec = {};
    for (size_t i = 0; i < lines.size(); i++) {
        value_vec.push_back({});
        value_vec[i] = StringSplitter::splitIntoStdString(lines[i], sep);
    }

    return value_vec;
}

std::vector<std::vector<double>> CSVFileManager::readIntoDouble(const std::string &path, const std::string &sep) {
    std::vector<std::string> lines = readIntoLines(path, CSV_LINE_SEPARATOR);

    std::vector<std::vector<double>> value_vec = {};
    for (auto line : lines) {
        if (line.size()) {
            value_vec.push_back(StringSplitter::splitIntoDouble(line, sep));
        }
    }

    return value_vec;
}

std::vector<std::string> CSVFileManager::readIntoLines(const std::string &path, const std::string &line_sep) {
    std::string data = file_manager_.read(path);
    return StringSplitter::splitIntoStdString(data, line_sep);
}
