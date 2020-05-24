#include "UI/include/windows/surfaceconfigurationdialog.h"
#include "ui_surfaceconfigurationdialog.h"

SurfaceConfigurationDialog::SurfaceConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SurfaceConfigurationDialog)
{
    ui->setupUi(this);
}

SurfaceConfigurationDialog::~SurfaceConfigurationDialog()
{
    delete ui;
}
