#include "ui/include/utils/tagsmanager.h"
#include "ui/include/utils/qcomboboxcontroller.h"

TagsManager::TagsManager() :
    current_(""),
    available_({}),
    selectable_(true),
    box_(nullptr) {}

void TagsManager::addAvailavle(const std::string &tag) {
    if (isAvailable(tag)) {
        return;
    }
    available_.push_back(tag);
}

std::string TagsManager::getCurrent() {
    return current_;
}

bool TagsManager::isAvailable(const std::string &tag) {
    for (auto available_tag : available_) {
        if (tag == available_tag) {
            return true;
        }
    }
    return false;
}

bool TagsManager::isValid() {
    return box_ != nullptr;
}

void TagsManager::removeAvailable(const std::string &tag) {
    if (!isAvailable(tag)) {
        return;
    }
    available_.erase(std::find(available_.begin(), available_.end(), tag));
}

bool TagsManager::isSelectable() {
    return selectable_;
}

void TagsManager::setBox(QComboBox *box) {
    box_ = box;
}

void TagsManager::setTags(const std::vector<std::string> &tags) {
    available_ = tags;
    if (isValid()) {
        QComboBoxController::updateValues(box_, tags);
    }
}

void TagsManager::setCurrent() {
    setCurrent(QComboBoxController::getCurrentValue(box_));
}

void TagsManager::setCurrent(const std::string &tag) {
    current_ = tag;
    QComboBoxController::setCurrentValue(box_, tag);
}

void TagsManager::setSelectable(bool selectable) {
    selectable_ = selectable;
}

void TagsManager::updateCurrent(const std::string &tag) {
    removeAvailable(current_);
    addAvailavle(tag);
    current_ = tag;
    QComboBoxController::updateCurrentValue(box_, tag);
}
