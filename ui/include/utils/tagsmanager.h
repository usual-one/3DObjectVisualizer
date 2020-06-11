#ifndef TAGSMANAGER_H
#define TAGSMANAGER_H

#include <QComboBox>

#include <string>
#include <vector>

class TagsManager {
public:
    TagsManager();

    void addAvailavle(const std::string &tag);

    std::string getCurrent();

    bool isAvailable(const std::string &tag);

    bool isSelectable();

    bool isValid();

    void removeAvailable(const std::string &tag);

    void setWidget(QComboBox *widget);

    void setTags(const std::vector<std::string> &tags);

    void setCurrent();

    void setCurrent(const std::string &tag);

    void setSelectable(bool selectable);

    void updateCurrent(const std::string &tag);

private:
    std::string current_;

    std::vector<std::string> available_;

    bool selectable_;

    QComboBox *box_;
};

#endif // TAGSMANAGER_H
