#include "ui/include/utils/slidermanager.h"

SliderManager::SliderManager() :
    begin_spinbox_(nullptr),
    end_spinbox_(nullptr),
    value_spinbox_(nullptr),
    slider_(nullptr) {}

void SliderManager::configureBorders(double minimum, double maximum) {
    begin_spinbox_->setMinimum(minimum);
    end_spinbox_->setMaximum(maximum);
}

double SliderManager::getBegin() {
    return begin_spinbox_->value();
}

double SliderManager::getEnd() {
    return end_spinbox_->value();
}

double SliderManager::getRangeSize() {
    return end_spinbox_->value() - begin_spinbox_->value();
}

double SliderManager::getValue() {
    return value_spinbox_->value();
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
    if (value < begin_spinbox_->value()) {
        begin_spinbox_->setMaximum(value);
        begin_spinbox_->setValue(value);
    }
    if (value > end_spinbox_->value()) {
        end_spinbox_->setMinimum(value);
        end_spinbox_->setValue(value);
    }
    updateWithBorders();
    value_spinbox_->setValue(value);
    updateWithValue();
}

void SliderManager::setWidgets(QSlider *slider, QDoubleSpinBox *begin,
                               QDoubleSpinBox *end, QDoubleSpinBox *value) {
    begin_spinbox_ = begin;
    end_spinbox_ = end;
    value_spinbox_ = value;
    slider_ = slider;
    updateWithValue();
}

void SliderManager::updateWithBorders() {
    value_spinbox_->setRange(begin_spinbox_->value(), end_spinbox_->value());
    setSliderValue(slider_, value_spinbox_->value(), begin_spinbox_->value(), end_spinbox_->value());
}

void SliderManager::updateWithOther(SliderManager *other) {
    end_spinbox_->setValue(getBegin() + other->getRangeSize() * (getValue() - getBegin()) / (other->getValue() - other->getBegin()));
    updateWithBorders();
}

void SliderManager::updateWithSlider() {
    double value = calculateSliderValue(slider_, begin_spinbox_->value(), end_spinbox_->value());
    value_spinbox_->setValue(value);
    begin_spinbox_->setMaximum(value_spinbox_->value());
    end_spinbox_->setMinimum(value_spinbox_->value());
}

void SliderManager::updateWithValue() {
    setSliderValue(slider_, value_spinbox_->value(), begin_spinbox_->value(), end_spinbox_->value());
    begin_spinbox_->setMaximum(value_spinbox_->value());
    end_spinbox_->setMinimum(value_spinbox_->value());
}

double SliderManager::calculateSliderValue(QSlider *slider, double begin, double end) {
    double value = begin + (end - begin) * (slider->value() - slider->minimum()) / (slider->maximum() - slider->minimum());
    return value;
}

void SliderManager::setSliderValue(QSlider *slider, double value, double begin, double end) {
    value = slider->minimum() + (slider->maximum() - slider->minimum()) * (value - begin) / (end - begin);
    slider->setValue(value);
}
