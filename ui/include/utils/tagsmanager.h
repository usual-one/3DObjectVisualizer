#ifndef TAGSMANAGER_H
#define TAGSMANAGER_H

#include <string>

#include <QComboBox>

class TagsManager {
public:
    TagsManager();

    void addAvailable(const std::string &tag);
    // adds tag to the list of tags that can be selected if no tag equal to given is in list

    void changeSelectedText(const std::string &tag);
    // changes text of selected tag to given

    std::string getSelected();
    // returns value of selected tag

    bool isAvailable(const std::string &tag);
    // checks if given tag is in list of tags that can be selected

    bool isEmpty();
    // checks if there are any tags in list of tags that can be selected

    bool isSelectable();
    // checks if user is able to manually select tag

    bool isValid();
    // checks if combobox widget is set

    void removeAvailable(const std::string &tag);
    // removes tag from list of tags that can be selected

    void removeSelected();
    // removes selected tag from list of tags that can be selected

    void setWidget(QComboBox *widget);
    // sets combobox widget

    void setTags(const std::vector<std::string> &tags);
    // clears tag list and adds every tag from given list

    void setSelected(const std::string &tag);
    // sets selected tag equal to given. if no such tags in list of tags that can be selected, tag is added

    void setSelectable(bool selectable);
    // sets ability to manually select tags in combobox

private:
    QComboBox *box_;

};

#endif // TAGSMANAGER_H
