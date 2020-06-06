#ifndef CONNECTIONADDITIONDIALOG_H
#define CONNECTIONADDITIONDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectionAdditionDialog;
}

class ConnectionAdditionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionAdditionDialog(QWidget *parent = nullptr);
    ~ConnectionAdditionDialog();

private:
    Ui::ConnectionAdditionDialog *ui;
};

#endif // CONNECTIONADDITIONDIALOG_H
