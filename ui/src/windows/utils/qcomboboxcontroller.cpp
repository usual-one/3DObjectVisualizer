#include "ui/include/utils/qcomboboxcontroller.h"

void QComboBoxController::updateValues(QComboBox *box, const std::vector<std::string> &values) {
    box->clear();
    for (auto value : values) {
        addValue(box, value);
    }
}

void QComboBoxController::updateCurrentValue(QComboBox *box, const std::string &new_value) {
    updateCurrentValue(box, QString::fromStdString(new_value));
}

void QComboBoxController::updateCurrentValue(QComboBox *box, const QString &new_value) {
    box->setItemText(box->currentIndex(), new_value);
}

void QComboBoxController::setCurrentValue(QComboBox *box, const std::string &new_value) {
    if (!contains(box, new_value)) {
        addValue(box, new_value);
    }
    box->setCurrentText(QString::fromStdString(new_value));
}

bool QComboBoxController::contains(QComboBox *box, const std::string &value) {
    return contains(box, QString::fromStdString(value));
}

bool QComboBoxController::contains(QComboBox *box, const QString &value) {
    for (int i = 0; i < box->count(); i++) {
        if (box->itemText(i) == value) {
            return true;
        }
    }
    return false;
}

void QComboBoxController::addValue(QComboBox *box, const std::string &value) {
    box->addItem(QString::fromStdString(value));
}

std::string QComboBoxController::getCurrentValue(QComboBox *box) {
    return box->currentText().toStdString();
}
