#include "logic/include/dto/sessionstatedto.h"

SessionStateDTO::SessionStateDTO(bool hidden, const std::string &tag) :
    hidden_(hidden),
    tag_(tag) {}

bool SessionStateDTO::getHidden() {
    return hidden_;
}

std::string &SessionStateDTO::getTag() {
    return tag_;
}

void SessionStateDTO::setHidden(bool hidden) {
    hidden_ = hidden;
}

void SessionStateDTO::setTag(const std::string &tag) {
    tag_ = tag;
}
