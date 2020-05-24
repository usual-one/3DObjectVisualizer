#ifndef SURFACEVIEWDIALOG_H
#define SURFACEVIEWDIALOG_H

#include <QDialog>

namespace Ui {
class SurfaceViewDialog;
}

class SurfaceViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SurfaceViewDialog(QWidget *parent = nullptr);
    ~SurfaceViewDialog();

private:
    Ui::SurfaceViewDialog *ui;
};

#endif // SURFACEVIEWDIALOG_H
