#include "ui/include/windows/figureconfigurationdialog.h"
#include "ui_figureconfigurationdialog.h"

FigureConfigurationDialog::FigureConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FigureConfigurationDialog) {
    ui->setupUi(this);
}

FigureConfigurationDialog::~FigureConfigurationDialog() {
    delete ui;
}
