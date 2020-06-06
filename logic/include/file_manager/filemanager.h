#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class FileManager {
public:
    FileManager();

    std::string read(const std::string &path);

    void write(const std::string &data);

    void writeTo(const std::string &path, const std::string &data);

private:
    bool isPathSpecified();

    std::string path_;

};

#endif // FILEMANAGER_H
