#include "ui/include/utils/qcomboboxcontroller.h"

void QComboBoxController::setItems(QComboBox *box, const std::vector<std::string> &items) {
    box->clear();
    for (auto item : items) {
        addItem(box, item);
    }
}

void QComboBoxController::setCurrentText(QComboBox *box, const std::string &text) {
    setCurrentText(box, QString::fromStdString(text));
}

void QComboBoxController::setCurrentText(QComboBox *box, const QString &text) {
    box->setItemText(box->currentIndex(), text);
}

void QComboBoxController::setCurrentItem(QComboBox *box, const std::string &item) {
    if (!contains(box, item)) {
        addItem(box, item);
    }
    box->setCurrentText(QString::fromStdString(item));
}

bool QComboBoxController::contains(QComboBox *box, const std::string &item) {
    return contains(box, QString::fromStdString(item));
}

bool QComboBoxController::contains(QComboBox *box, const QString &item) {
    for (int i = 0; i < box->count(); i++) {
        if (box->itemText(i) == item) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> QComboBoxController::getItems(QComboBox *box) {
    std::vector<std::string> items;
    for (int i = 0; i < box->count(); i++) {
        items.push_back(box->itemText(i).toStdString());
    }
    return items;
}

bool QComboBoxController::isEmpty(QComboBox *box) {
    return !box->count();
}

void QComboBoxController::addItem(QComboBox *box, const std::string &item) {
    box->addItem(QString::fromStdString(item));
}

std::string QComboBoxController::getCurrentText(QComboBox *box) {
    return box->currentText().toStdString();
}

void QComboBoxController::removeItem(QComboBox *box, const std::string &item) {
    box->removeItem(box->findText(QString::fromStdString(item)));
}
