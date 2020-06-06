#include "logic/include/file_manager/filemanager.h"
#include "logic/include/file_manager/exception/fileopeningexception.h"
#include "logic/include/file_manager/exception/filewritingexception.h"

#include <fstream>
#include <sstream>

FileManager::FileManager() {
    path_ = "";
}

std::string FileManager::read(const std::string &path) {
    std::ifstream fd(path);
    if (!fd.is_open()) {
        throw FileOpeningException("failed to open the file", path);
    }
    std::stringstream file_data;
    file_data << fd.rdbuf();
    fd.close();
    return file_data.str();
}

void FileManager::write(const std::string &data) {
    if (!isPathSpecified()) {
        throw FileWritingException("path is not specified");
    }
    std::ofstream fd(path_);
    if (!fd.is_open()) {
        throw FileOpeningException("failed to open the file", path_);
    }
    fd.write(data.data(), data.size());
    fd.close();
}

void FileManager::writeTo(const std::string &path, const std::string &data) {
    path_ = path;
    write(data);
}

bool FileManager::isPathSpecified() {
    return path_.size();
}
