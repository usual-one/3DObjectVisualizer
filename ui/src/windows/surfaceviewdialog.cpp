#include "ui/include/windows/surfaceviewdialog.h"
#include "ui_surfaceviewdialog.h"

#include <QStandardItemModel>

SurfaceViewDialog::SurfaceViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SurfaceViewDialog) {
    ui->setupUi(this);

    tags_manager_.setWidget(ui->cmbx_surface);

    connectSignals();
}

SurfaceViewDialog::SurfaceViewDialog(const std::vector<std::string> &tags, QWidget *parent):
    QDialog(parent),
    ui(new Ui::SurfaceViewDialog) {
    ui->setupUi(this);

    tags_manager_.setWidget(ui->cmbx_surface);
    setTags(tags);

    connectSignals();
}

SurfaceViewDialog::~SurfaceViewDialog() {
    delete ui;
}

int SurfaceViewDialog::execWith(const std::string &tag, bool tag_selectable) {
    tags_manager_.setSelected(tag);
    enableTagSelection(tag_selectable);
    emit tagSelected();
    return exec();
}

std::string SurfaceViewDialog::getSelectedTag() {
    return tags_manager_.getSelected();
}

void SurfaceViewDialog::setSurface(std::shared_ptr<obj3d::Surface> &surface) {
    ui->tbl_surface->setRowCount(surface->getValues().size());
    ui->tbl_surface->setColumnCount(surface->getValues()[0].size());
    for (size_t i = 0; i < surface->getValues().size(); i++) {
        for (size_t j = 0; j < surface->getValues()[i].size(); j++) {
            ui->tbl_surface->setItem(i, j, new QTableWidgetItem(QString::number(surface->getValues()[i][j])));
        }
    }
}

void SurfaceViewDialog::setTags(const std::vector<std::string> &tags) {
    tags_manager_.setTags(tags);
    if (!tags.empty()) {
        emit tagSelected();
    }
}

void SurfaceViewDialog::showWith(const std::string &tag, bool tag_selectable) {
    tags_manager_.setSelected(tag);
    enableTagSelection(tag_selectable);
    emit tagSelected();
    show();
}

void SurfaceViewDialog::selectTag() {
    if (tags_manager_.isEmpty()) {
        return;
    }
    emit tagSelected();
}

void SurfaceViewDialog::close() {
    reject();
}

void SurfaceViewDialog::connectSignals() {
    connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(close()));

    connect(ui->cmbx_surface, SIGNAL(activated(int)), this, SLOT(selectTag()));
}

void SurfaceViewDialog::enableTagSelection(bool enable) {
    tags_manager_.setSelectable(enable);
    ui->lbl_surface->setEnabled(enable);
}
