#ifndef SURFACEMOVEMENTDIALOG_H
#define SURFACEMOVEMENTDIALOG_H

#include <QDialog>

namespace Ui {
class SurfaceMovementDialog;
}

class SurfaceMovementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SurfaceMovementDialog(QWidget *parent = nullptr);
    ~SurfaceMovementDialog();

private:
    Ui::SurfaceMovementDialog *ui;
};

#endif // SURFACEMOVEMENTDIALOG_H
