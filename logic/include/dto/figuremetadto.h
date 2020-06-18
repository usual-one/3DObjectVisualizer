#ifndef FIGUREMETADTO_H
#define FIGUREMETADTO_H

#include <string>

class FigureMetaDTO {
public:
    FigureMetaDTO(const std::string &path);

    std::string &getPath();

    void setPath(const std::string &path);

private:
    std::string path_;

};

#endif // FIGUREMETADTO_H
