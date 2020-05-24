#include "UI/include/windows/surfacemovementdialog.h"
#include "ui_surfacemovementdialog.h"

SurfaceMovementDialog::SurfaceMovementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SurfaceMovementDialog)
{
    ui->setupUi(this);
}

SurfaceMovementDialog::~SurfaceMovementDialog()
{
    delete ui;
}
