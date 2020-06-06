#include "ui/include/windows/exitdialog.h"
#include "ui_exitdialog.h"

ExitDialog::ExitDialog(std::shared_ptr<bool> save_needed, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExitDialog) {
    ui->setupUi(this);

    save_needed_ = save_needed;

}

ExitDialog::~ExitDialog() {
    delete ui;
}

void ExitDialog::close() {
    accept();
}

void ExitDialog::cancel() {
    reject();
}

void ExitDialog::save() {
    *save_needed_ = true;
    accept();
}
