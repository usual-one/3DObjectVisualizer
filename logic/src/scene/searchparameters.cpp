#include "config.h"
#include "logic/include/scene/searchparameters.h"
#include "logic/include/scene/exception/unknowntagexception.h"

SearchParameters::SearchParameters() {
    available_.clear();
    selected_.clear();
    is_selected_ = false;
}

SearchParameters::SearchParameters(const std::vector<std::string> &available_tags) {
    available_ = available_tags;
    selected_.clear();
    is_selected_ = false;
}

std::vector<std::string> &SearchParameters::getAvailable() {
    return available_;
}

std::string SearchParameters::getSelected() {
    return selected_;
}

void SearchParameters::selectTag(const std::string &tag) {
    if (!contains(tag)) {
        throw UnknownTagException(UNKNOWN_TAG_MESSAGE);
    }
    is_selected_ = true;
    selected_ = tag;
}

bool SearchParameters::isEmpty() {
    return !available_.size() || available_.size() == 1;
}

bool SearchParameters::isSelected() {
    return is_selected_;
}

bool SearchParameters::contains(const std::string &tag) {
    bool presence = false;
    for (auto available_tag : available_) {
        if (available_tag == tag) {
            presence = true;
            break;
        }
    }
    return presence;
}
