#include "UI/include/windows/surfaceviewdialog.h"
#include "ui_surfaceviewdialog.h"

SurfaceViewDialog::SurfaceViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SurfaceViewDialog)
{
    ui->setupUi(this);
}

SurfaceViewDialog::~SurfaceViewDialog()
{
    delete ui;
}
