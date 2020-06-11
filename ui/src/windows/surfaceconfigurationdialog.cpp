#include "config.h"
#include "ui/include/windows/surfaceconfigurationdialog.h"
#include "ui_surfaceconfigurationdialog.h"

#include "ui/include/utils/qcomboboxcontroller.h"

SurfaceConfigurationDialog::SurfaceConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SurfaceConfigurationDialog) {
    ui->setupUi(this);

    tags_manager_.setWidget(ui->cmbx_surface);

    surface_tag_ = std::make_shared<std::string>();
    surface_params_ = std::make_shared<obj3d::SurfaceParameters>();

    configureParamWidgets();
    connectSignals();
}

SurfaceConfigurationDialog::SurfaceConfigurationDialog(const std::vector<std::string> &tags,
                                                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SurfaceConfigurationDialog) {
    ui->setupUi(this);

    tags_manager_.setWidget(ui->cmbx_surface);
    setTags(tags);

    configureParamWidgets();
    setParamLines();
    changeNormalizationAccess(ui->chbx_normalized->isChecked());

    connectSignals();
}

SurfaceConfigurationDialog::~SurfaceConfigurationDialog() {
    delete ui;
}

void SurfaceConfigurationDialog::applyAndClose() {
    applyChanges();
    setDefaultState();
    accept();
}

void SurfaceConfigurationDialog::applyChanges() {
    collectParams();
    emit parametersChanged();
    tags_manager_.updateCurrent(*surface_tag_);
}

void SurfaceConfigurationDialog::cancelChanges() {
    setDefaultState();
    reject();
}

int SurfaceConfigurationDialog::execWith(const std::string &tag, bool tag_selectable) {
    tags_manager_.setSelectable(tag_selectable);
    tags_manager_.setCurrent(tag);
    if (!tags_manager_.isSelectable()) {
        disableTagSelection(true);
    }
    emit tagSelected();
    return exec();
}

std::string SurfaceConfigurationDialog::getSelectedTag() {
    return tags_manager_.getCurrent();
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

void SurfaceConfigurationDialog::selectTag() {
    if (!ui->cmbx_surface->count()) {
        return;
    }
    tags_manager_.setCurrent();
    emit tagSelected();
}

void SurfaceConfigurationDialog::surfaceTagChanged() {
    if (QComboBoxController::contains(ui->cmbx_surface, ui->ln_tag->text())) {
        if (ui->ln_tag->text().toStdString() != tags_manager_.getCurrent()) {
            // TODO
        }
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

void SurfaceConfigurationDialog::disableTagSelection(bool value) {
    ui->btn_apply->setDisabled(value);

    ui->lbl_surface->setDisabled(value);
    ui->cmbx_surface->setDisabled(value);
}

void SurfaceConfigurationDialog::setTags(const std::vector<std::string> &tags) {
    tags_manager_.setTags(tags);
    if (tags.size()) {
        tags_manager_.setCurrent();
        emit tagSelected();
    }
}

void SurfaceConfigurationDialog::setDefaultState() {
    disableTagSelection(false);
}

void SurfaceConfigurationDialog::setParamLines() {
    ui->chbx_normalized->setChecked(surface_params_->isNormalizationNeeded());

    ui->spbx_ox_step->setValue(surface_params_->getXStep());
    ui->spbx_oy_step->setValue(surface_params_->getYStep());
    ui->spbx_range_begin->setValue(surface_params_->getMin());
    ui->spbx_range_end->setValue(surface_params_->getMax());
}

void SurfaceConfigurationDialog::showWith(const std::string &tag, bool tag_selectable) {
    tags_manager_.setSelectable(tag_selectable);
    tags_manager_.setCurrent(tag);
    if (!tags_manager_.isSelectable()) {
        disableTagSelection(true);
    }
    emit tagSelected();
    show();
}

void SurfaceConfigurationDialog::collectParams() {
    *surface_tag_ = ui->ln_tag->text().toStdString();

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

void SurfaceConfigurationDialog::connectSignals() {
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
