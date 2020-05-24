#include "UI/include/windows/connectionadditiondialog.h"
#include "ui_connectionadditiondialog.h"

ConnectionAdditionDialog::ConnectionAdditionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionAdditionDialog)
{
    ui->setupUi(this);
}

ConnectionAdditionDialog::~ConnectionAdditionDialog()
{
    delete ui;
}
