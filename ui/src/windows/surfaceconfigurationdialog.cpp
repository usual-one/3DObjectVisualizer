#include <QCloseEvent>

#include "config.h"
#include "ui/include/windows/surfaceconfigurationdialog.h"
#include "ui_surfaceconfigurationdialog.h"

#include "ui/include/utils/qcomboboxcontroller.h"

SurfaceConfigurationDialog::SurfaceConfigurationDialog(QWidget *parent) :
    BaseTagSelectingDialog(parent),
    ui(new Ui::SurfaceConfigurationDialog) {
    ui->setupUi(this);

    tags_manager_.setWidget(ui->cmbx_surface);

    surface_params_ = std::make_shared<obj3d::SurfaceParameters>();

    configureParamWidgets();
    connectSignals();
}

SurfaceConfigurationDialog::SurfaceConfigurationDialog(const std::vector<std::string> &tags,
                                                       QWidget *parent) :
    BaseTagSelectingDialog(parent),
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
    accept();
    setDefaultState();
}

void SurfaceConfigurationDialog::applyChanges() {
    collectParams();
    emit surfaceChanged();
    tags_manager_.changeSelectedText(ui->ln_tag->text().toStdString());
}

void SurfaceConfigurationDialog::cancelChanges() {
    reject();
    setDefaultState();
}

void SurfaceConfigurationDialog::deleteSurface() {
    emit surfaceDeleted();

    tags_manager_.removeSelected();
    if (tags_manager_.isEmpty()) {
        reject();
    } else {
        emit tagSelected();
    }
}

int SurfaceConfigurationDialog::execWith(const std::string &tag, bool tag_selectable) {
    enableTagSelection(tag_selectable);
    return BaseTagSelectingDialog::execWith(tag, tag_selectable);
}

void SurfaceConfigurationDialog::changeSurfaceTag() {
    std::string tag = ui->ln_tag->text().toStdString();
    bool tag_invalid = tags_manager_.isAvailable(tag) && tag != tags_manager_.getSelected();
    if (!tag_invalid) {
        applyChanges();
    }
    showInvalidTag(tag_invalid);
}

void SurfaceConfigurationDialog::changeNormalizationAccess(int enabled) {
    ui->spbx_range_begin->setEnabled(enabled);
    ui->spbx_range_end->setEnabled(enabled);
}

void SurfaceConfigurationDialog::closeEvent(QCloseEvent *event) {
    event->ignore();
    if (ui->btn_cancel->isEnabled()) {
        cancelChanges();
    }
}

void SurfaceConfigurationDialog::enableSurfaceDeleting(bool value) {
    ui->btn_delete->setEnabled(value);
}

std::shared_ptr<SessionStateDTO> SurfaceConfigurationDialog::getSurfaceSessionState() {
    return std::make_shared<SessionStateDTO>(ui->chbx_hide->isChecked(), ui->ln_tag->text().toStdString());
}

std::shared_ptr<SurfaceParametersDTO> SurfaceConfigurationDialog::getSurfaceParameters() {
    return std::make_shared<SurfaceParametersDTO>(*surface_params_);
}

void SurfaceConfigurationDialog::setSurfaceParameters(std::shared_ptr<SurfaceParametersDTO> params) {
    *surface_params_ = params->getParameters();
    setParamLines();
    changeNormalizationAccess(ui->chbx_normalized->isChecked());
}

void SurfaceConfigurationDialog::setSurfaceSessionState(std::shared_ptr<SessionStateDTO> state) {
    ui->ln_tag->setText(QString::fromStdString(state->getTag()));
    ui->chbx_hide->setChecked(state->getHidden());
}

void SurfaceConfigurationDialog::enableTagSelection(bool enable) {
    ui->btn_apply->setEnabled(enable);

    ui->lbl_surface->setEnabled(enable);

    BaseTagSelectingDialog::enableTagSelection(enable);
}


void SurfaceConfigurationDialog::setDefaultState() {
    enableTagSelection(true);
}

void SurfaceConfigurationDialog::setParamLines() {
    ui->chbx_normalized->setChecked(surface_params_->isNormalizationNeeded());

    ui->spbx_ox_step->setValue(surface_params_->getXStep());
    ui->spbx_oy_step->setValue(surface_params_->getYStep());
    ui->spbx_range_begin->setValue(surface_params_->getMin());
    ui->spbx_range_end->setValue(surface_params_->getMax());
}

void SurfaceConfigurationDialog::showInvalidTag(bool value) {
    ui->btn_ok->setDisabled(value);
    ui->btn_apply->setDisabled(value);
    ui->btn_cancel->setDisabled(value);

    enableTagSelection(!value);

    QPalette palette = ui->ln_tag->palette();
    if (value) {
        palette.setColor(QPalette::Base, QColor(255, 0, 0, 80));
    } else {
        palette.setColor(QPalette::Base, QColor(255, 255, 255));
    }
    ui->ln_tag->setPalette(palette);
}

void SurfaceConfigurationDialog::showWith(const std::string &tag, bool tag_selectable) {
    enableTagSelection(tag_selectable);
    BaseTagSelectingDialog::showWith(tag, tag_selectable);
}

void SurfaceConfigurationDialog::collectParams() {
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

    // Hide CheckBox
    connect(ui->chbx_hide, SIGNAL(stateChanged(int)), this, SLOT(applyChanges()));

    // Delete Button
    connect(ui->btn_delete, SIGNAL(clicked()), this, SLOT(deleteSurface()));

    // Normalized CheckBox
    connect(ui->chbx_normalized, SIGNAL(stateChanged(int)), this, SLOT(changeNormalizationAccess(int)));

    // Tag LineEdit
    connect(ui->ln_tag, SIGNAL(textEdited(const QString &)), this, SLOT(changeSurfaceTag()));

    // Tags ComboBox
    connect(ui->cmbx_surface, SIGNAL(currentIndexChanged(int)), this, SLOT(selectTag()));
}
