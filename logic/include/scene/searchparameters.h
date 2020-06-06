#ifndef SEARCHPARAMETERS_H
#define SEARCHPARAMETERS_H

#include <string>
#include <vector>

#include "logic/include/obj3d/object3d.h"

class SearchParameters {
public:
    SearchParameters();

    SearchParameters(const std::vector<std::string> &available_tags);

    std::vector<std::string> &getAvailable();

    std::string getSelected();

    void selectTag(const std::string &tag);

    bool isEmpty();

    bool isSelected();

private:
    bool contains(const std::string &tag);

    std::vector<std::string> available_;

    std::string selected_;

    bool is_selected_;
};

#endif // SEARCHPARAMETERS_H
