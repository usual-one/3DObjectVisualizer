#ifndef EXITDIALOG_H
#define EXITDIALOG_H

#include <QDialog>

namespace Ui {
    class ExitDialog;
}

class ExitDialog : public QDialog {
    Q_OBJECT

public:
    explicit ExitDialog(QWidget *parent = nullptr);

    ~ExitDialog();

    int execIrrevocable();

    bool isSaveNeeded();

private slots:
    void close();

    void cancel();

    void save();

private:
    void connectSignals();

    void enableCanceling(bool enable);

    Ui::ExitDialog *ui;

    bool save_needed_;
};

#endif // EXITDIALOG_H
