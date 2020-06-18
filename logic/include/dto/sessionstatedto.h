#ifndef FIGURESESSIONSTATEDTO_H
#define FIGURESESSIONSTATEDTO_H

#include <string>

class SessionStateDTO {
public:
    SessionStateDTO(bool hidden, const std::string &tag);

    bool getHidden();

    std::string &getTag();

    void setHidden(bool hidden);

    void setTag(const std::string &tag);

private:
    bool hidden_;

    std::string tag_;

};

#endif // FIGURESESSIONSTATEDTO_H
