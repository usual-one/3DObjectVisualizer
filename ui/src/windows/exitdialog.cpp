#include "ui/include/windows/exitdialog.h"
#include "ui_exitdialog.h"

ExitDialog::ExitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExitDialog) {
    ui->setupUi(this);

    connectSignals();
}

ExitDialog::~ExitDialog() {
    delete ui;
}

int ExitDialog::execIrrevocable() {
    enableCanceling(false);
    return exec();
}

bool ExitDialog::isSaveNeeded() {
    return save_needed_;
}

void ExitDialog::close() {
    save_needed_ = false;
    accept();
    enableCanceling(true);
}

void ExitDialog::cancel() {
    reject();
    enableCanceling(true);
}

void ExitDialog::save() {
    save_needed_ = true;
    accept();
    enableCanceling(true);
}

void ExitDialog::connectSignals() {
    // Action buttons
    connect(ui->btn_save, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->btn_not_save, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btn_cancel, SIGNAL(clicked()), this, SLOT(cancel()));
}

void ExitDialog::enableCanceling(bool enable) {
    ui->btn_cancel->setEnabled(enable);
}
