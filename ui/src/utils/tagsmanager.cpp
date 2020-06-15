#include "ui/include/utils/tagsmanager.h"
#include "ui/include/utils/qcomboboxcontroller.h"

TagsManager::TagsManager() :
    box_(nullptr) {}

void TagsManager::addAvailable(const std::string &tag) {
    if (isAvailable(tag)) {
        return;
    }
    QComboBoxController::addItem(box_, tag);
}

void TagsManager::changeSelectedText(const std::string &tag) {
    QComboBoxController::setCurrentText(box_, tag);
}

std::string TagsManager::getSelected() {
    return QComboBoxController::getCurrentText(box_);
}

bool TagsManager::isAvailable(const std::string &tag) {
    return QComboBoxController::contains(box_, tag);
}

bool TagsManager::isEmpty() {
    return QComboBoxController::isEmpty(box_);
}

bool TagsManager::isValid() {
    return box_ != nullptr;
}

bool TagsManager::isSelectable() {
    return box_->isEnabled();
}

void TagsManager::removeAvailable(const std::string &tag) {
    if (!isAvailable(tag)) {
        return;
    }
    QComboBoxController::removeItem(box_, tag);
}

void TagsManager::setWidget(QComboBox *widget) {
    box_ = widget;
}

void TagsManager::setTags(const std::vector<std::string> &tags) {
    QComboBoxController::setItems(box_, tags);
}

void TagsManager::setSelected(const std::string &tag) {
    QComboBoxController::setCurrentItem(box_, tag);
}

void TagsManager::setSelectable(bool selectable) {
    box_->setEnabled(selectable);
}
