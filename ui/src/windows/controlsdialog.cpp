#include "config.h"
#include "ui/include/windows/controlsdialog.h"
#include "ui_controlsdialog.h"

ControlsDialog::ControlsDialog(QWidget *parent) :
    BaseTagSelectingDialog(parent),
    ui(new Ui::ControlsDialog),
    state_(std::make_shared<State>()) {
    ui->setupUi(this);

    tags_manager_.setWidget(ui->cmbx_object);
    configureWidgets();

    connectSignals();
}

ControlsDialog::ControlsDialog(const std::vector<std::string> &tags, QWidget *parent) :
    BaseTagSelectingDialog(parent),
    ui(new Ui::ControlsDialog),
    state_(std::make_shared<State>()) {
    ui->setupUi(this);

    tags_manager_.setWidget(ui->cmbx_object);
    setTags(tags);

    configureWidgets();
    fillWidgetValues();
    fillStateValues();

    connectSignals();
}

ControlsDialog::~ControlsDialog() {
    delete ui;
}

void ControlsDialog::close() {
    reject();
    enableTagSelection(true);
}

void ControlsDialog::changeBorders() {
    ox_movement_manager_.updateWithBorders();
    oy_movement_manager_.updateWithBorders();
    oz_movement_manager_.updateWithBorders();
    ox_scaling_manager_.updateWithBorders();
    oy_scaling_manager_.updateWithBorders();
    oz_scaling_manager_.updateWithBorders();
}

void ControlsDialog::enableTagSelection(bool value) {
    ui->lbl_object->setEnabled(value);
}

int ControlsDialog::execWith(const std::string &tag, bool tag_selectable) {
    enableTagSelection(tag_selectable);
    return BaseTagSelectingDialog::execWith(tag, tag_selectable);
}

bool ControlsDialog::hasState() {
    return state_ != nullptr;
}

std::shared_ptr<FigureStateDTO> ControlsDialog::getState() {
    return std::make_unique<FigureStateDTO>(state_);
}

void ControlsDialog::setState(std::shared_ptr<FigureStateDTO> new_state) {
    state_->copy(new_state->getState());
    fillWidgetValues();
    fillStateValues();
}

void ControlsDialog::showWith(const std::string &tag, bool tag_selectable) {
    enableTagSelection(tag_selectable);
    BaseTagSelectingDialog::showWith(tag, tag_selectable);
}

void ControlsDialog::changeStateWithSliders() {
    ox_movement_manager_.updateWithSlider();
    oy_movement_manager_.updateWithSlider();
    oz_movement_manager_.updateWithSlider();

    ox_rotation_manager_.updateWithDial();
    oy_rotation_manager_.updateWithDial();
    oz_rotation_manager_.updateWithDial();

    ox_scaling_manager_.updateWithSlider();
    if (ui->chbx_all->isChecked()) {
        oy_scaling_manager_.setValue(oy_scaling_manager_.getBegin() +
                                     (ox_scaling_manager_.getValue() - ox_scaling_manager_.getBegin())
                                     * oy_scaling_manager_.getRangeSize() / ox_scaling_manager_.getRangeSize());
        oz_scaling_manager_.setValue(oz_scaling_manager_.getBegin() +
                                     (ox_scaling_manager_.getValue() - ox_scaling_manager_.getBegin()) * oz_scaling_manager_.getRangeSize() /
                                     ox_scaling_manager_.getRangeSize());
    } else {
        oy_scaling_manager_.updateWithSlider();
        oz_scaling_manager_.updateWithSlider();
    }

    getWidgetValues();
    emit stateChanged();
}

void ControlsDialog::changeStateWithValues() {
    ox_movement_manager_.updateWithValue();
    oy_movement_manager_.updateWithValue();
    oz_movement_manager_.updateWithValue();

    ox_rotation_manager_.updateWithValue();
    oy_rotation_manager_.updateWithValue();
    oz_rotation_manager_.updateWithValue();

    ox_scaling_manager_.updateWithValue();
    if (ui->chbx_all->isChecked()) {
        oy_scaling_manager_.setValue(oy_scaling_manager_.getBegin() +
                                     (ox_scaling_manager_.getValue() - ox_scaling_manager_.getBegin()) * oy_scaling_manager_.getRangeSize() /
                                     ox_scaling_manager_.getRangeSize());
        oz_scaling_manager_.setValue(oz_scaling_manager_.getBegin() +
                                     (ox_scaling_manager_.getValue() - ox_scaling_manager_.getBegin()) * oz_scaling_manager_.getRangeSize() /
                                     ox_scaling_manager_.getRangeSize());
    } else {
        oy_scaling_manager_.updateWithValue();
        oz_scaling_manager_.updateWithValue();
    }

    getWidgetValues();
    emit stateChanged();
}

void ControlsDialog::configureWidgets() {
    ox_movement_manager_.setWidgets(ui->sldr_ox_move, ui->spbx_ox_move_begin,
                                    ui->spbx_ox_move_end, ui->spbx_moved_ox);
    oy_movement_manager_.setWidgets(ui->sldr_oy_move, ui->spbx_oy_move_begin,
                                    ui->spbx_oy_move_end, ui->spbx_moved_oy);
    oz_movement_manager_.setWidgets(ui->sldr_oz_move, ui->spbx_oz_move_begin,
                                    ui->spbx_oz_move_end, ui->spbx_moved_oz);

    ox_rotation_manager_.setWidgets(ui->dial_ox_rotate, ui->spbx_rotated_ox);
    oy_rotation_manager_.setWidgets(ui->dial_oy_rotate, ui->spbx_rotated_oy);
    oz_rotation_manager_.setWidgets(ui->dial_oz_rotate, ui->spbx_rotated_oz);

    ox_scaling_manager_.setWidgets(ui->sldr_ox_scale, ui->spbx_ox_scale_begin,
                                   ui->spbx_ox_scale_end, ui->spbx_scaled_ox);
    oy_scaling_manager_.setWidgets(ui->sldr_oy_scale, ui->spbx_oy_scale_begin,
                                   ui->spbx_oy_scale_end, ui->spbx_scaled_oy);
    oz_scaling_manager_.setWidgets(ui->sldr_oz_scale, ui->spbx_oz_scale_begin,
                                   ui->spbx_oz_scale_end, ui->spbx_scaled_oz);

    ox_movement_manager_.configureBorders(MIN_VALUE, MAX_VALUE);
    oy_movement_manager_.configureBorders(MIN_VALUE, MAX_VALUE);
    oz_movement_manager_.configureBorders(MIN_VALUE, MAX_VALUE);

    ox_rotation_manager_.configureBorders(MIN_ROTATION_VALUE, MAX_ROTATION_VALUE);
    oy_rotation_manager_.configureBorders(MIN_ROTATION_VALUE, MAX_ROTATION_VALUE);
    oz_rotation_manager_.configureBorders(MIN_ROTATION_VALUE, MAX_ROTATION_VALUE);

    ox_scaling_manager_.configureBorders(SCALE_VALUE_BEGIN, MAX_VALUE);
    oy_scaling_manager_.configureBorders(SCALE_VALUE_BEGIN, MAX_VALUE);
    oz_scaling_manager_.configureBorders(SCALE_VALUE_BEGIN, MAX_VALUE);

    ui->spbx_ox_move_begin->setValue(MOVE_VALUE_BEGIN);
    ui->spbx_oy_move_begin->setValue(MOVE_VALUE_BEGIN);
    ui->spbx_oz_move_begin->setValue(MOVE_VALUE_BEGIN);

    ui->spbx_ox_move_end->setValue(MOVE_VALUE_END);
    ui->spbx_oy_move_end->setValue(MOVE_VALUE_END);
    ui->spbx_oz_move_end->setValue(MOVE_VALUE_END);

    ui->spbx_ox_scale_begin->setValue(SCALE_VALUE_BEGIN);
    ui->spbx_oy_scale_begin->setValue(SCALE_VALUE_BEGIN);
    ui->spbx_oz_scale_begin->setValue(SCALE_VALUE_BEGIN);

    ui->spbx_ox_scale_end->setValue(SCALE_VALUE_END);
    ui->spbx_oy_scale_end->setValue(SCALE_VALUE_END);
    ui->spbx_oz_scale_end->setValue(SCALE_VALUE_END);
}

void ControlsDialog::fillWidgetValues() {
    ox_movement_manager_.setValue(state_->getMovement()->getX());
    oy_movement_manager_.setValue(state_->getMovement()->getY());
    oz_movement_manager_.setValue(state_->getMovement()->getZ());

    ox_rotation_manager_.setValue(state_->getRotation()->getX());
    oy_rotation_manager_.setValue(state_->getRotation()->getY());
    oz_rotation_manager_.setValue(state_->getRotation()->getZ());

    ox_scaling_manager_.setValue(state_->getScaling()->getX());
    oy_scaling_manager_.setValue(state_->getScaling()->getY());
    oz_scaling_manager_.setValue(state_->getScaling()->getZ());
}

void ControlsDialog::getWidgetValues() {
    state_->getMovement()->setX(ox_movement_manager_.getValue());
    state_->getMovement()->setY(oy_movement_manager_.getValue());
    state_->getMovement()->setZ(oz_movement_manager_.getValue());

    state_->getRotation()->setX(ox_rotation_manager_.getValue());
    state_->getRotation()->setY(oy_rotation_manager_.getValue());
    state_->getRotation()->setZ(oz_rotation_manager_.getValue());

    state_->getScaling()->setX(ox_scaling_manager_.getValue());
    state_->getScaling()->setY(oy_scaling_manager_.getValue());
    state_->getScaling()->setZ(oz_scaling_manager_.getValue());
}

void ControlsDialog::fillStateValues() {
    ui->spbx_moved_ox->setValue(state_->getMovement()->getX());
    ui->spbx_moved_oy->setValue(state_->getMovement()->getY());
    ui->spbx_moved_oz->setValue(state_->getMovement()->getZ());

    ui->spbx_rotated_ox->setValue(state_->getRotation()->getX());
    ui->spbx_rotated_oy->setValue(state_->getRotation()->getY());
    ui->spbx_rotated_oz->setValue(state_->getRotation()->getZ());

    ui->spbx_scaled_ox->setValue(state_->getScaling()->getX());
    ui->spbx_scaled_oy->setValue(state_->getScaling()->getY());
    ui->spbx_scaled_oz->setValue(state_->getScaling()->getZ());
}

void ControlsDialog::setDefaultState() {
    enableTagSelection(true);
}

void ControlsDialog::connectSignals() {
    // buttons
    connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(close()));

    // Scaling CheckBox
    connect(ui->chbx_all, SIGNAL(stateChanged(int)), this, SLOT(disableSeparateScaling(int)));

    // current state values
    connect(ui->spbx_moved_ox, SIGNAL(editingFinished()), this, SLOT(changeStateWithValues()));
    connect(ui->spbx_moved_oy, SIGNAL(editingFinished()), this, SLOT(changeStateWithValues()));
    connect(ui->spbx_moved_oz, SIGNAL(editingFinished()), this, SLOT(changeStateWithValues()));
    connect(ui->spbx_rotated_ox, SIGNAL(editingFinished()), this, SLOT(changeStateWithValues()));
    connect(ui->spbx_rotated_oy, SIGNAL(editingFinished()), this, SLOT(changeStateWithValues()));
    connect(ui->spbx_rotated_oz, SIGNAL(editingFinished()), this, SLOT(changeStateWithValues()));
    connect(ui->spbx_scaled_ox, SIGNAL(editingFinished()), this, SLOT(changeStateWithValues()));
    connect(ui->spbx_scaled_oy, SIGNAL(editingFinished()), this, SLOT(changeStateWithValues()));
    connect(ui->spbx_scaled_oz, SIGNAL(editingFinished()), this, SLOT(changeStateWithValues()));

    // border values
    connect(ui->spbx_ox_move_begin, SIGNAL(editingFinished()), this, SLOT(changeBorders()));
    connect(ui->spbx_oy_move_begin, SIGNAL(editingFinished()), this, SLOT(changeBorders()));
    connect(ui->spbx_oz_move_begin, SIGNAL(editingFinished()), this, SLOT(changeBorders()));
    connect(ui->spbx_ox_move_end, SIGNAL(editingFinished()), this, SLOT(changeBorders()));
    connect(ui->spbx_oy_move_end, SIGNAL(editingFinished()), this, SLOT(changeBorders()));
    connect(ui->spbx_oz_move_end, SIGNAL(editingFinished()), this, SLOT(changeBorders()));
    connect(ui->spbx_ox_scale_begin, SIGNAL(editingFinished()), this, SLOT(changeBorders()));
    connect(ui->spbx_oy_scale_begin, SIGNAL(editingFinished()), this, SLOT(changeBorders()));
    connect(ui->spbx_oz_scale_begin, SIGNAL(editingFinished()), this, SLOT(changeBorders()));
    connect(ui->spbx_ox_scale_end, SIGNAL(editingFinished()), this, SLOT(changeBorders()));
    connect(ui->spbx_oy_scale_end, SIGNAL(editingFinished()), this, SLOT(changeBorders()));
    connect(ui->spbx_oz_scale_end, SIGNAL(editingFinished()), this, SLOT(changeBorders()));

    // controls
    connect(ui->dial_ox_rotate, SIGNAL(sliderMoved(int)), this, SLOT(changeStateWithSliders()));
    connect(ui->dial_oy_rotate, SIGNAL(sliderMoved(int)), this, SLOT(changeStateWithSliders()));
    connect(ui->dial_oz_rotate, SIGNAL(sliderMoved(int)), this, SLOT(changeStateWithSliders()));
    connect(ui->sldr_ox_move, SIGNAL(sliderMoved(int)), this, SLOT(changeStateWithSliders()));
    connect(ui->sldr_oy_move, SIGNAL(sliderMoved(int)), this, SLOT(changeStateWithSliders()));
    connect(ui->sldr_oz_move, SIGNAL(sliderMoved(int)), this, SLOT(changeStateWithSliders()));
    connect(ui->sldr_ox_scale, SIGNAL(sliderMoved(int)), this, SLOT(changeStateWithSliders()));
    connect(ui->sldr_oy_scale, SIGNAL(sliderMoved(int)), this, SLOT(changeStateWithSliders()));
    connect(ui->sldr_oz_scale, SIGNAL(sliderMoved(int)), this, SLOT(changeStateWithSliders()));

    // Tags Combobox
    connect(ui->cmbx_object, SIGNAL(activated(int)), this, SLOT(selectTag()));
}

void ControlsDialog::disableSeparateScaling(int disable) {
    oy_scaling_manager_.setEnabled(!disable);
    oz_scaling_manager_.setEnabled(!disable);

    ui->lbl_ox_scale->setDisabled(disable);
    ui->lbl_oy_scale->setDisabled(disable);
    ui->lbl_oz_scale->setDisabled(disable);

    if (disable) {
        oy_scaling_manager_.updateWithOther(&ox_scaling_manager_);
        oz_scaling_manager_.updateWithOther(&ox_scaling_manager_);
    }
}

