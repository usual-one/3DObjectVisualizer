#include <QFileDialog>

#include "config.h"
#include "ui/include/windows/exportdialog.h"
#include "ui_exportdialog.h"

ExportDialog::ExportDialog(QWidget *parent) :
    BaseTagSelectingDialog(parent),
    ui(new Ui::ExportDialog),
    path_(std::make_shared<std::string>()) {
    ui->setupUi(this);

    setConnections();

    tags_manager_.setWidget(ui->cmbx_object);
}

ExportDialog::ExportDialog(const std::vector<std::string> &tags, QWidget *parent) :
    BaseTagSelectingDialog(parent),
    ui(new Ui::ExportDialog),
    path_(std::make_shared<std::string>()) {

    setConnections();

    tags_manager_.setWidget(ui->cmbx_object);
    setTags(tags);
}

ExportDialog::~ExportDialog() {
    delete ui;
}

int ExportDialog::execWith(const std::string &tag, bool tag_selectable) {
    enableTagSelection(tag_selectable);
    return BaseTagSelectingDialog::execWith(tag, tag_selectable);
}

std::shared_ptr<std::string> ExportDialog::getPath() {
    return path_;
}

void ExportDialog::setPath(const std::string &path) {
    ui->lbl_path->setText(QString::fromStdString(path));
    emit pathChanged();
}

void ExportDialog::showWith(const std::string &tag, bool tag_selectable) {
    enableTagSelection(tag_selectable);
    BaseTagSelectingDialog::showWith(tag, tag_selectable);
}

void ExportDialog::cancelExport() {
    reject();
}

void ExportDialog::requestExport() {
    emit exportRequested();
}

void ExportDialog::selectPath() {
    QString save_path = QString::fromStdString(DEFAULT_FIGURES_DIR + getSelectedTag() + FIGURE_FILE_FORMAT);
    if (path_->size()) {
        save_path = QString::fromStdString(*path_);
    }
    ui->lbl_path->setText(QFileDialog::getSaveFileName(this, "Export " + QString::fromStdString(getSelectedTag()),
                                                       save_path, tr("Figures (*.xml)")));
    emit pathChanged();
}

void ExportDialog::setPath() {
    *path_ = ui->lbl_path->text().toStdString();
    enableExport(path_->size());
}

void ExportDialog::enableTagSelection(bool enable) {
    ui->lbl_object->setEnabled(enable);
}

void ExportDialog::enableExport(bool enable) {
    ui->btn_export->setEnabled(enable);
}

void ExportDialog::setConnections() {
    // Browse button
    connect(ui->btn_browse, SIGNAL(clicked()), this, SLOT(selectPath()));
    connect(this, SIGNAL(pathChanged()), this, SLOT(setPath()));

    // Action buttons
    connect(ui->btn_cancel, SIGNAL(clicked()), this, SLOT(cancelExport()));
    connect(ui->btn_export, SIGNAL(clicked()), this, SLOT(requestExport()));

    // Tags ComboBox
    connect(ui->cmbx_object, SIGNAL(currentIndexChanged(int)), this, SLOT(selectTag()));
}
