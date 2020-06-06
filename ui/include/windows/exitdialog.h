#ifndef EXITDIALOG_H
#define EXITDIALOG_H

#include <QDialog>

namespace Ui {
    class ExitDialog;
}

class ExitDialog : public QDialog {
    Q_OBJECT

public:
    explicit ExitDialog(std::shared_ptr<bool> save_needed, QWidget *parent = nullptr);

    ~ExitDialog();

private slots:
    void close();

    void cancel();

    void save();

private:
    Ui::ExitDialog *ui;

    std::shared_ptr<bool> save_needed_;
};

#endif // EXITDIALOG_H
