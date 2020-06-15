#ifndef QCOMBOBOXCONTROLLER_H
#define QCOMBOBOXCONTROLLER_H

#include <QComboBox>

class QComboBoxController {
public:
    static void addItem(QComboBox *box, const std::string &item);
    // adds item to combobox (duplicates are acceptable)

    static bool contains(QComboBox *box, const std::string &item);
    // checks if combobox contains given item

    static bool contains(QComboBox *box, const QString &value);
    // checks if combobox contains given item

    static std::string getCurrentText(QComboBox *box);
    // returns text of current item

    static std::vector<std::string> getItems(QComboBox *box);
    // returns list of all items in combobox in their index order

    static bool isEmpty(QComboBox *box);
    // checks if combobox contains no items

    static void removeItem(QComboBox *box, const std::string &item);
    // removes from combobox item equal to given. if there's not such item, undefined behavior

    static void setCurrentItem(QComboBox *box, const std::string &item);
    // sets current item to item equal to given. if there's no such item, new item is added

    static void setCurrentText(QComboBox *box, const std::string &text);
    // changes text of current item

    static void setCurrentText(QComboBox *box, const QString &text);
    // changes text of current item

    static void setItems(QComboBox *box, const std::vector<std::string> &items);
    // clears combobox and adds given items

};

#endif // QCOMBOBOXCONTROLLER_H
