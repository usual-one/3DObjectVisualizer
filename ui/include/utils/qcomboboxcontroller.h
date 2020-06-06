#ifndef QCOMBOBOXCONTROLLER_H
#define QCOMBOBOXCONTROLLER_H

#include <QComboBox>

class QComboBoxController {
public:
    static void updateValues(QComboBox *box, const std::vector<std::string> &values);

    static void updateCurrentValue(QComboBox *box, const std::string &new_value);

    static void updateCurrentValue(QComboBox *box, const QString &new_value);

    static void setCurrentValue(QComboBox *box, const std::string &new_value);

    static bool contains(QComboBox *box, const std::string &value);

    static bool contains(QComboBox *box, const QString &value);

    static void addValue(QComboBox *box, const std::string &value);

    static std::string getCurrentValue(QComboBox *box);

};

#endif // QCOMBOBOXCONTROLLER_H
