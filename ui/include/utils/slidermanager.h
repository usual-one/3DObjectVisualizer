#ifndef SLIDERMANAGER_H
#define SLIDERMANAGER_H

#include <QSlider>
#include <QDoubleSpinBox>

class SliderManager {
public:
    SliderManager();

    void configureBorders(double minimum, double maximum);
    // sets const borders to border spinboxes. sets begin spinbox minimum to given, sets end spinbox maximum to given

    double getValue();
    // returns current slider value with regard to border spinboxes values

    bool isValid();
    // checks if all widgets are set

    void setEnabled(bool enabled);
    // sets enable state for all widgets

    void setValue(double value);
    // sets value spinbox and slider value with regard to border spinbox values
    // if value is outside border spinbox segment, fits borders spinboxes to make value be inside.

    void setWidgets(QSlider *slider, QDoubleSpinBox *begin, QDoubleSpinBox *end, QDoubleSpinBox *value);
    // sets all widgets

    void updateWithBorders();
    // updates slider value and value spinbox borders with regard to border spinbox values

    void updateWithSlider();
    // updates value spinbox value with regard to slider value

    void updateWithValue();
    // updates slider value with regard to value spinbox value

private:
    static double calculateSliderValue(QSlider *slider, double begin, double end);
    // calculates slider value with regard to given borders

    static void setSliderValue(QSlider *slider, double value, double begin, double end);
    // sets slider value with regard to given borders

    QDoubleSpinBox *begin_spinbox_;

    QDoubleSpinBox *end_spinbox_;

    QDoubleSpinBox *value_spinbox_;

    QSlider *slider_;

};

#endif // SLIDERMANAGER_H
