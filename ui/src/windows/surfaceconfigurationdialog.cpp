#include "config.h"
#include "ui/include/windows/surfaceconfigurationdialog.h"
#include "ui_surfaceconfigurationdialog.h"

#include "ui/include/utils/qcomboboxcontroller.h"

SurfaceConfigurationDialog::SurfaceConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SurfaceConfigurationDialog) {
    ui->setupUi(this);

    surface_tag_ = std::make_shared<std::string>();
    surface_params_ = std::make_shared<obj3d::SurfaceParameters>();

    configureParamWidgets();
    setConnections();
}

SurfaceConfigurationDialog::SurfaceConfigurationDialog(const std::vector<std::string> &tags,
                                                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SurfaceConfigurationDialog) {
    ui->setupUi(this);
    tags_ = tags;

    configureParamWidgets();
    setParamLines();
    setTagLines();
    changeNormalizationAccess(ui->chbx_normalized->isChecked());

    setConnections();
}

SurfaceConfigurationDialog::~SurfaceConfigurationDialog() {
    delete ui;
}

std::string SurfaceConfigurationDialog::getSelectedTag() {
    return selected_tag_;
}

std::shared_ptr<std::string> SurfaceConfigurationDialog::getSurfaceTag() {
    return surface_tag_;
}

std::shared_ptr<obj3d::SurfaceParameters> SurfaceConfigurationDialog::getSurfaceParameters() {
    return surface_params_;
}

void SurfaceConfigurationDialog::setSurfaceParameters(std::shared_ptr<obj3d::SurfaceParameters> params) {
    *surface_params_ = *params;
    setParamLines();
    changeNormalizationAccess(ui->chbx_normalized->isChecked());
}

void SurfaceConfigurationDialog::setSurfaceTag(std::shared_ptr<std::string> tag) {
    *surface_tag_ = *tag;
    ui->ln_tag->setText(QString::fromStdString(*tag));
}

void SurfaceConfigurationDialog::applyAndClose() {
    applyChanges();
    setDefaultState();
    accept();
}

void SurfaceConfigurationDialog::applyChanges() {
    collectParams();
    emit surfaceChanged();
    selected_tag_ = *surface_tag_;
}

void SurfaceConfigurationDialog::cancelChanges() {
    setDefaultState();
    reject();
}

void SurfaceConfigurationDialog::selectTag() {
    if (!ui->cmbx_surface->count()) {
        return;
    }
    selected_tag_ = QComboBoxController::getCurrentValue(ui->cmbx_surface);
    emit tagSelected();
}

void SurfaceConfigurationDialog::surfaceTagChanged() {
    if (QComboBoxController::contains(ui->cmbx_surface, ui->ln_tag->text())) {
        if (ui->ln_tag->text().toStdString() != selected_tag_) {
            // TODO
        }
    } else {
        QComboBoxController::updateCurrentValue(ui->cmbx_surface, ui->ln_tag->text());
    }
//    std::string tag = ui->ln_tag->text().toStdString();
//    bool exists = false;
//    for (auto existing_tag : tags_) {
//        if (tag == existing_tag) {
//            if (tag == *surface_tag_) {
//                continue;
//            }
//            exists = true;
//            break;
//        }
//    }

//    QPalette palette = ui->ln_tag->palette();
//    if (exists) {
//        ui->btn_ok->setDisabled(true);
//        ui->btn_apply->setDisabled(true);
//        palette.setColor(QPalette::Base, QColor(255, 0, 0, 120));
//    } else {
//        ui->btn_ok->setDisabled(false);
//        ui->btn_apply->setDisabled(false);
//        palette.setColor(QPalette::Base, QColor(255, 255, 255));
//    }
//    ui->ln_tag->setPalette(palette);
}

void SurfaceConfigurationDialog::changeNormalizationAccess(int enabled) {
    ui->spbx_range_begin->setEnabled(enabled);
    ui->spbx_range_end->setEnabled(enabled);
}

void SurfaceConfigurationDialog::disableTagSelecting(bool value) {
    ui->btn_apply->setDisabled(value);

    ui->lbl_surface->setDisabled(value);
    ui->cmbx_surface->setDisabled(value);
}

int SurfaceConfigurationDialog::execWith(const std::string &tag, bool tag_selectable) {
    tag_selectable_ = tag_selectable;
    selected_tag_ = tag;
    QComboBoxController::setCurrentValue(ui->cmbx_surface, selected_tag_);
    if (!tag_selectable) {
        disableTagSelecting(true);
    }
    emit tagSelected();
    return exec();
}

void SurfaceConfigurationDialog::setTags(const std::vector<std::string> &tags) {
    tags_ = tags;
    setTagLines();
}

void SurfaceConfigurationDialog::setDefaultState() {
    disableTagSelecting(false);
}

void SurfaceConfigurationDialog::setParamLines() {
    ui->chbx_normalized->setChecked(surface_params_->isNormalizationNeeded());
    ui->spbx_ox_step->setValue(surface_params_->getXStep());
    ui->spbx_oy_step->setValue(surface_params_->getYStep());
    ui->spbx_range_begin->setValue(surface_params_->getMin());
    ui->spbx_range_end->setValue(surface_params_->getMax());
}

void SurfaceConfigurationDialog::setTagLines() {
    QComboBoxController::updateValues(ui->cmbx_surface, tags_);
    selectTag();
}


void SurfaceConfigurationDialog::showWith(const std::string &tag, bool tag_selectable) {
    tag_selectable_ = tag_selectable;
    selected_tag_ = tag;
    QComboBoxController::setCurrentValue(ui->cmbx_surface, selected_tag_);
    if (!tag_selectable) {
        disableTagSelecting(true);
    }
    emit tagSelected();
    show();
}

void SurfaceConfigurationDialog::collectParams() {
    *surface_tag_ = ui->ln_tag->text().toStdString();
    if (selected_tag_ != ui->ln_tag->text().toStdString()) {
        auto current_tag = std::find(tags_.begin(), tags_.end(), selected_tag_);
        if (current_tag != tags_.end()) {
            tags_.erase(current_tag);
        }
        tags_.push_back(*surface_tag_);
    }

    surface_params_->setNormalizationNeeded(ui->chbx_normalized->isChecked());
    surface_params_->setXStep(ui->spbx_ox_step->value());
    surface_params_->setYStep(ui->spbx_oy_step->value());
    surface_params_->setMin(ui->spbx_range_begin->value());
    surface_params_->setMax(ui->spbx_range_end->value());
}

void SurfaceConfigurationDialog::configureParamWidgets() {
    ui->spbx_ox_step->setMinimum(MIN_SPBX_STEP_X);
    ui->spbx_ox_step->setMaximum(MAX_SPBX_STEP_X);
    ui->spbx_oy_step->setMinimum(MIN_SPBX_STEP_Y);
    ui->spbx_oy_step->setMaximum(MAX_SPBX_STEP_Y);
    ui->spbx_range_begin->setMinimum(MIN_SPBX_RANGE_MIN);
    ui->spbx_range_begin->setMaximum(MAX_SPBX_RANGE_MIN);
    ui->spbx_range_end->setMinimum(MIN_SPBX_RANGE_MAX);
    ui->spbx_range_end->setMaximum(MAX_SPBX_RANGE_MAX);
}

void SurfaceConfigurationDialog::setConnections() {
    // Actions Buttons
    connect(ui->btn_apply, SIGNAL(clicked()), this, SLOT(applyChanges()));
    connect(ui->btn_cancel, SIGNAL(clicked()), this, SLOT(cancelChanges()));
    connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(applyAndClose()));

    // Normalized Checkbox
    connect(ui->chbx_normalized, SIGNAL(stateChanged(int)),
            this, SLOT(changeNormalizationAccess(int)));

    // Tag LineEdit
    connect(ui->ln_tag, SIGNAL(editingFinished()), this, SLOT(surfaceTagChanged()));

    // Tags ComboBox
    connect(ui->cmbx_surface, SIGNAL(currentIndexChanged(int)), this, SLOT(selectTag()));
}
