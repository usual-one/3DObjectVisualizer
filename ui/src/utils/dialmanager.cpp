#include "ui/include/utils/dialmanager.h"

DialManager::DialManager() :
    begin_(0),
    end_(360),
    dial_(nullptr),
    value_spinbox_(nullptr) {}

void DialManager::configureBorders(double begin, double end) {
    begin_ = begin;
    end_ = end;
    value_spinbox_->setRange(begin, end);
}

double DialManager::getValue() {
    return value_spinbox_->value();
}

bool DialManager::isValid() {
    return dial_ != nullptr &&
            value_spinbox_ != nullptr;
}

void DialManager::setValue(double value) {
    if (value < begin_) {
        begin_ = value;
        value_spinbox_->setMinimum(value);
    }
    if (value > end_) {
        end_ = value;
        value_spinbox_->setMaximum(value);
    }
    value_spinbox_->setValue(value);
    updateWithValue();
}

void DialManager::setWidgets(QDial *dial, QDoubleSpinBox *value_spinbox) {
    dial_ = dial;
    value_spinbox_ = value_spinbox;
}

void DialManager::updateWithValue() {
    setDialValue(dial_, begin_, end_, value_spinbox_->value());
}

void DialManager::updateWithDial() {
    value_spinbox_->setValue(calculateDialValue(dial_, begin_, end_));
}

double DialManager::calculateDialValue(QDial *dial, double begin, double end) {
    double value = (dial->maximum() - dial->minimum()) / 2 + dial->value();
    while (value >= 360) {
        value -= 360;
    }
    value = begin + (end - begin) * (value - dial->minimum()) / (dial->maximum() - dial->minimum());
    return value;
}

void DialManager::setDialValue(QDial *dial, double begin, double end, double value) {
    value = dial->minimum() + (dial->maximum() - dial->minimum()) * (value - begin) / (end - begin);
    value += (dial->maximum() - dial->minimum()) / 2;
    while (value > 360) {
        value -= 360;
    }
    dial->setValue(value);
}

