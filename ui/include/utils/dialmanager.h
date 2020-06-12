#ifndef DIALMANAGER_H
#define DIALMANAGER_H

#include <QDial>
#include <QDoubleSpinBox>

class DialManager {
public:
    DialManager();

    double getValue();

    bool isValid();

    void setBorders(double begin, double end);

    void setValue(double value);

    void setWidgets(QDial *dial, QDoubleSpinBox *value_spinbox);

    void updateWithValue();

    void updateWithDial();

private:
    static double getDialValue(QDial *dial, double begin, double end);

    static void setDialValue(QDial *dial, double begin, double end, double value);

    double begin_;

    double end_;

    double value_;

    QDial *dial_;

    QDoubleSpinBox *value_spinbox_;

};

#endif // DIALMANAGER_H
