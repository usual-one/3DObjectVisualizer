#ifndef DIALMANAGER_H
#define DIALMANAGER_H

#include <QDial>
#include <QDoubleSpinBox>

class DialManager {
public:
    DialManager();

    void configureBorders(double begin, double end);
    // sets const borders that will be used to set dial value

    double getValue();
    // returns value spinbox value

    bool isValid();
    // checks if all widgets are set

    void setValue(double value);
    // sets value spinbox and dial value with regard to border values
    // if value is outside border segment, fits borders to make value be inside.

    void setWidgets(QDial *dial, QDoubleSpinBox *value_spinbox);
    // sets all widgets

    void updateWithValue();
    // updates dial value with regard to value spinbox value

    void updateWithDial();
    // updates value spinbox value with regard to dial value

private:
    static double calculateDialValue(QDial *dial, double begin, double end);
    // calculates dial value with regard to given borders

    static void setDialValue(QDial *dial, double begin, double end, double value);
    // sets slider value with regard to given borders

    double begin_;

    double end_;

    QDial *dial_;

    QDoubleSpinBox *value_spinbox_;

};

#endif // DIALMANAGER_H
