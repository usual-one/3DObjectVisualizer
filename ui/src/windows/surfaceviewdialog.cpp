#include "ui/include/windows/surfaceviewdialog.h"
#include "ui_surfaceviewdialog.h"

#include <QStandardItemModel>

SurfaceViewDialog::SurfaceViewDialog(std::shared_ptr<obj3d::Surface> surface,
                                     std::shared_ptr<SearchParameters> params, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SurfaceViewDialog) {
    ui->setupUi(this);
    surface_ = surface;
    params_ = params;

    setTagLines();
    setSurfaceTable();

    connect(ui->btn_select, SIGNAL(clicked()), this, SLOT(select()));
    connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(close()));
}


SurfaceViewDialog::~SurfaceViewDialog() {
    delete ui;
}

void SurfaceViewDialog::select() {
    params_->selectTag(ui->cmbx_surface->currentText().toStdString());
    accept();
}

void SurfaceViewDialog::close() {
    reject();
}

void SurfaceViewDialog::setTagLines() {
    if (params_->isEmpty()) {
        ui->lbl_surface->setDisabled(true);
        ui->cmbx_surface->setDisabled(true);
        ui->btn_select->setDisabled(true);
        return;
    }
    for (auto tag : params_->getAvailable()) {
        ui->cmbx_surface->addItem(QString::fromStdString(tag));
    }
}

void SurfaceViewDialog::setSurfaceTable() {
    if (surface_ == nullptr) {
        ui->tbl_surface->setDisabled(true);
        return;
    }

    QStandardItemModel *model = new QStandardItemModel();

    for (size_t i = 0; i < surface_->getValues().size(); i++) {
        for (size_t j = 0; j < surface_->getValues()[i].size(); j++) {
            model->setItem(i, j, new QStandardItem(QString::number(surface_->getValues()[i][j])));
        }
    }

    ui->tbl_surface->setModel(model);
}
