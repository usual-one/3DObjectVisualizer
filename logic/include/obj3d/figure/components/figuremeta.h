#ifndef FIGUREMETA_H
#define FIGUREMETA_H

#include <memory>
#include <string>

class FigureMeta {
public:
    FigureMeta();

    std::shared_ptr<std::string> getPath();

    bool isSaved();

    void setPath(const std::string &path);

    void setSaved(bool saved);

private:
    bool saved_;

    std::shared_ptr<std::string> path_;

};

#endif // FIGUREMETA_H
