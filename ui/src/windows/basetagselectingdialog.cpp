#include "ui/include/windows/basetagselectingdialog.h"

BaseTagSelectingDialog::BaseTagSelectingDialog(QWidget *parent) :
    QDialog(parent) {}

void BaseTagSelectingDialog::enableTagSelection(bool enable) {
    tags_manager_.setSelectable(enable);
}

int BaseTagSelectingDialog::execWith(const std::string &tag, bool tag_selectable) {
    enableTagSelection(tag_selectable);
    tags_manager_.setSelected(tag);
    emit tagSelected();
    return exec();
}

std::string BaseTagSelectingDialog::getSelectedTag() {
    return tags_manager_.getSelected();
}

void BaseTagSelectingDialog::setTags(const std::vector<std::string> &tags) {
    tags_manager_.setTags(tags);
    if (!tags.empty()) {
        emit tagSelected();
    }
}

void BaseTagSelectingDialog::showWith(const std::string &tag, bool tag_selectable) {
    enableTagSelection(tag_selectable);
    tags_manager_.setSelected(tag);
    emit tagSelected();
    show();
}

void BaseTagSelectingDialog::selectTag() {
    if (tags_manager_.isEmpty()) {
        return;
    }
    emit tagSelected();
}
