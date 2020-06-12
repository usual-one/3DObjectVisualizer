#include "ui/include/utils/slidermanager.h"

SliderManager::SliderManager() :
    value_(0),
    begin_spinbox_(nullptr),
    end_spinbox_(nullptr),
    value_spinbox_(nullptr),
    slider_(nullptr) {}

void SliderManager::configureBorders(double minimum, double maximum) {
    begin_spinbox_->setMinimum(minimum);
    end_spinbox_->setMaximum(maximum);
}

double SliderManager::getValue() {
    updateWithValue();
    return value_;
}

bool SliderManager::isValid() {
    return begin_spinbox_ != nullptr &&
            end_spinbox_ != nullptr &&
            value_spinbox_ != nullptr &&
            slider_ != nullptr;
}

void SliderManager::setEnabled(bool enabled) {
    begin_spinbox_->setEnabled(enabled);
    end_spinbox_->setEnabled(enabled);
    value_spinbox_->setEnabled(enabled);
    slider_->setEnabled(enabled);
}

void SliderManager::setValue(double value) {
    setSpinBoxValue(value_spinbox_, value);
    updateWithValue();
}

void SliderManager::setWidgets(QSlider *slider, QDoubleSpinBox *begin, QDoubleSpinBox *end, QDoubleSpinBox *value) {
    begin_spinbox_ = begin;
    end_spinbox_ = end;
    value_spinbox_ = value;
    slider_ = slider;
    updateWithBorders();
    updateWithValue();
}

void SliderManager::updateWithBorders() {
    value_spinbox_->setMinimum(begin_spinbox_->value());
    value_spinbox_->setMaximum(end_spinbox_->value());
    setSliderValue(slider_, value_, begin_spinbox_->value(), end_spinbox_->value());
}

void SliderManager::updateWithSlider() {
    value_ = getSliderValue(slider_, begin_spinbox_->value(), end_spinbox_->value());
    setSpinBoxValue(value_spinbox_, value_);
}

void SliderManager::updateWithValue() {
    value_ = value_spinbox_->value();
    setSliderValue(slider_, value_, begin_spinbox_->value(), end_spinbox_->value());
    begin_spinbox_->setMaximum(value_);
    end_spinbox_->setMinimum(value_);
}

double SliderManager::getSliderValue(QSlider *slider, double begin, double end) {
    double value = begin + (end - begin) * (slider->value() - slider->minimum()) / (slider->maximum() - slider->minimum());
    return value;
}

void SliderManager::setSliderValue(QSlider *slider, double value, double begin, double end) {
    value = slider->minimum() + (slider->maximum() - slider->minimum()) * (value - begin) / (end - begin);
    slider->setValue(value);
}

void SliderManager::setSpinBoxValue(QDoubleSpinBox *spinbox, double value) {
    if (value < spinbox->minimum()) {
        spinbox->setMinimum(value);
    }
    if (value > spinbox->maximum()) {
        spinbox->setMaximum(value);
    }
    spinbox->setValue(value);
}
