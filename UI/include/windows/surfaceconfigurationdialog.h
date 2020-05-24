#ifndef SURFACECONFIGURATIONDIALOG_H
#define SURFACECONFIGURATIONDIALOG_H

#include <QDialog>

namespace Ui {
class SurfaceConfigurationDialog;
}

class SurfaceConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SurfaceConfigurationDialog(QWidget *parent = nullptr);
    ~SurfaceConfigurationDialog();

private:
    Ui::SurfaceConfigurationDialog *ui;
};

#endif // SURFACECONFIGURATIONDIALOG_H
