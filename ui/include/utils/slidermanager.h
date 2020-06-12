#ifndef SLIDERMANAGER_H
#define SLIDERMANAGER_H

#include <QSlider>
#include <QDoubleSpinBox>

class SliderManager {
public:
    SliderManager();

    void configureBorders(double minimum, double maximum);

    double getValue();

    bool isValid();

    void setEnabled(bool enabled);

    void setValue(double value);

    void setWidgets(QSlider *slider, QDoubleSpinBox *begin, QDoubleSpinBox *end, QDoubleSpinBox *value);

    void updateWithBorders();

    void updateWithSlider();

    void updateWithValue();

private:
    static double getSliderValue(QSlider *slider, double begin, double end);

    static void setSliderValue(QSlider *slider, double value, double begin, double end);

    static void setSpinBoxValue(QDoubleSpinBox *spinbox, double value);

    double value_;

    QDoubleSpinBox *begin_spinbox_;

    QDoubleSpinBox *end_spinbox_;

    QDoubleSpinBox *value_spinbox_;

    QSlider *slider_;

};

#endif // SLIDERMANAGER_H
