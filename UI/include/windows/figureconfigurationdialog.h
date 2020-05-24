#ifndef FIGURECONFIGURATIONDIALOG_H
#define FIGURECONFIGURATIONDIALOG_H

#include <QDialog>

namespace Ui {
class FigureConfigurationDialog;
}

class FigureConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FigureConfigurationDialog(QWidget *parent = nullptr);
    ~FigureConfigurationDialog();

private:
    Ui::FigureConfigurationDialog *ui;
};

#endif // FIGURECONFIGURATIONDIALOG_H
