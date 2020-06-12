#include "ui/include/utils/dialmanager.h"

DialManager::DialManager() :
    begin_(0),
    end_(360),
    value_(0),
    dial_(nullptr),
    value_spinbox_(nullptr) {

}

double DialManager::getValue() {
    updateWithValue();
    return value_;
}

bool DialManager::isValid() {
    return dial_ != nullptr &&
            value_spinbox_ != nullptr;
}

void DialManager::setBorders(double begin, double end) {
    begin_ = begin;
    end_ = end;
    value_spinbox_->setMinimum(begin);
    value_spinbox_->setMaximum(end);
}

void DialManager::setValue(double value) {
    if (value < begin_ || value > end_) {
        return;
    }
    value_ = value;
    value_spinbox_->setValue(value);
    setDialValue(dial_, begin_, end_, value);
}

void DialManager::setWidgets(QDial *dial, QDoubleSpinBox *value_spinbox) {
    dial_ = dial;
    value_spinbox_ = value_spinbox;
}

void DialManager::updateWithValue() {
    value_ = value_spinbox_->value();
    setDialValue(dial_, begin_, end_, value_);
}

void DialManager::updateWithDial() {
    value_ = getDialValue(dial_, begin_, end_);
    value_spinbox_->setValue(value_);
}

double DialManager::getDialValue(QDial *dial, double begin, double end) {
    double value = (dial->maximum() - dial->minimum()) / 2 + dial->value();
    while (value >= 360) {
        value -= 360;
    }
    value = begin + (end - begin) * (value - dial->minimum()) / (dial->maximum() - dial->minimum());
    return value;
}

void DialManager::setDialValue(QDial *dial, double begin, double end, double value) {
    value = dial->minimum() + (dial->maximum() - dial->minimum()) * (value - begin) / (end - begin);
    value += dial->maximum() - dial->minimum();
    while (value > 360) {
        value -= 360;
    }
    dial->setValue(value);
}

