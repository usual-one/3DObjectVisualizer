#include "config.h"
#include "ui/include/windows/controlsdialog.h"
#include "ui_controlsdialog.h"

ControlsDialog::ControlsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlsDialog),
    location_(std::make_shared<Location>()) {
    ui->setupUi(this);

    tags_manager_.setWidget(ui->cmbx_object);
    configureParamLines();

    connectSignals();
}

ControlsDialog::ControlsDialog(const std::vector<std::string> &tags, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlsDialog),
    location_(std::make_shared<Location>()) {
    ui->setupUi(this);

    tags_manager_.setWidget(ui->cmbx_object);
    setTags(tags);
    configureParamLines();
    fillWidgetValues();
    fillStateValues();

    connectSignals();
}

ControlsDialog::~ControlsDialog() {
    delete ui;
}


void ControlsDialog::applyChanges() {
    getWidgetValues();
    emit locationChanged();
}

void ControlsDialog::cancelChanges() {
    reject();
    disableTagSelecting(false);
}

void ControlsDialog::changeBorders() {
    ox_movement_manager_.updateWithBorders();
    oy_movement_manager_.updateWithBorders();
    oz_movement_manager_.updateWithBorders();
    ox_scaling_manager_.updateWithBorders();
    oy_scaling_manager_.updateWithBorders();
    oz_scaling_manager_.updateWithBorders();
}

void ControlsDialog::disableTagSelecting(bool value) {
    ui->lbl_object->setDisabled(value);

    ui->cmbx_object->setDisabled(value);
}

int ControlsDialog::execWith(const std::string &tag, bool tag_selectable) {
    tags_manager_.setSelectable(tag_selectable);
    tags_manager_.setCurrent(tag);
    if (!tags_manager_.isSelectable()) {
        disableTagSelecting(true);
    }
    emit tagSelected();
    return exec();
}

bool ControlsDialog::hasLocation() {
    return location_ != nullptr;
}

std::shared_ptr<Location> ControlsDialog::getLocation() {
    return location_;
}

void ControlsDialog::setLocation(std::shared_ptr<Location> new_location) {
    location_->copy(*new_location);
    fillWidgetValues();
    fillStateValues();
}

void ControlsDialog::setTags(const std::vector<std::string> &tags) {
    tags_manager_.setTags(tags);
    if (tags.size()) {
        tags_manager_.setCurrent();
        emit tagSelected();
    }
}

void ControlsDialog::showWith(const std::string &tag, bool tag_selectable) {
    tags_manager_.setSelectable(tag_selectable);
    tags_manager_.setCurrent(tag);
    if (!tags_manager_.isSelectable()) {
        disableTagSelecting(true);
    }
    emit tagSelected();
    show();
}

std::string ControlsDialog::getSelectedTag() {
    return tags_manager_.getCurrent();
}

void ControlsDialog::changeLocation() {
    getWidgetValues();
    fillStateValues();
    emit locationChanged();
}

void ControlsDialog::changeState() {
    ox_movement_manager_.updateWithValue();
    oy_movement_manager_.updateWithValue();
    oz_movement_manager_.updateWithValue();
    ox_rotation_manager_.updateWithValue();
    oy_rotation_manager_.updateWithValue();
    oz_rotation_manager_.updateWithValue();
    ox_scaling_manager_.updateWithValue();
    oy_scaling_manager_.updateWithValue();
    oz_scaling_manager_.updateWithValue();
}


void ControlsDialog::selectTag() {
    if (!ui->cmbx_object->count()) {
        return;
    }
    tags_manager_.setCurrent();
    emit tagSelected();
}

void ControlsDialog::configureParamLines() {
    ox_movement_manager_.setWidgets(ui->sldr_ox_move, ui->spbx_ox_move_begin, ui->spbx_ox_move_end, ui->spbx_moved_ox);
    oy_movement_manager_.setWidgets(ui->sldr_oy_move, ui->spbx_oy_move_begin, ui->spbx_oy_move_end, ui->spbx_moved_oy);
    oz_movement_manager_.setWidgets(ui->sldr_oz_move, ui->spbx_oz_move_begin, ui->spbx_oz_move_end, ui->spbx_moved_oz);
    ox_rotation_manager_.setWidgets(ui->dial_ox_rotate, ui->spbx_rotated_ox);
    oy_rotation_manager_.setWidgets(ui->dial_oy_rotate, ui->spbx_rotated_oy);
    oz_rotation_manager_.setWidgets(ui->dial_oz_rotate, ui->spbx_rotated_oz);
    ox_scaling_manager_.setWidgets(ui->sldr_ox_scale, ui->spbx_ox_scale_begin, ui->spbx_ox_scale_end, ui->spbx_scaled_ox);
    oy_scaling_manager_.setWidgets(ui->sldr_oy_scale, ui->spbx_oy_scale_begin, ui->spbx_oy_scale_end, ui->spbx_scaled_oy);
    oz_scaling_manager_.setWidgets(ui->sldr_oz_scale, ui->spbx_oz_scale_begin, ui->spbx_oz_scale_end, ui->spbx_scaled_oz);

    ox_rotation_manager_.setBorders(MIN_ROTATION_VALUE, MAX_ROTATION_VALUE);
    oy_rotation_manager_.setBorders(MIN_ROTATION_VALUE, MAX_ROTATION_VALUE);
    oz_rotation_manager_.setBorders(MIN_ROTATION_VALUE, MAX_ROTATION_VALUE);

    ox_movement_manager_.configureBorders(MIN_VALUE, MAX_VALUE);
    oy_movement_manager_.configureBorders(MIN_VALUE, MAX_VALUE);
    oz_movement_manager_.configureBorders(MIN_VALUE, MAX_VALUE);

    ui->spbx_ox_move_begin->setValue(MOVE_VALUE_BEGIN);
    ui->spbx_oy_move_begin->setValue(MOVE_VALUE_BEGIN);
    ui->spbx_oz_move_begin->setValue(MOVE_VALUE_BEGIN);
    ui->spbx_ox_move_end->setValue(MOVE_VALUE_END);
    ui->spbx_oy_move_end->setValue(MOVE_VALUE_END);
    ui->spbx_oz_move_end->setValue(MOVE_VALUE_END);

    ox_scaling_manager_.configureBorders(MIN_VALUE, MAX_VALUE);
    oy_scaling_manager_.configureBorders(MIN_VALUE, MAX_VALUE);
    oz_scaling_manager_.configureBorders(MIN_VALUE, MAX_VALUE);

    ui->spbx_ox_scale_begin->setValue(SCALE_VALUE_BEGIN);
    ui->spbx_oy_scale_begin->setValue(SCALE_VALUE_BEGIN);
    ui->spbx_oz_scale_begin->setValue(SCALE_VALUE_BEGIN);
    ui->spbx_ox_scale_end->setValue(SCALE_VALUE_END);
    ui->spbx_oy_scale_end->setValue(SCALE_VALUE_END);
    ui->spbx_oz_scale_end->setValue(SCALE_VALUE_END);

}

void ControlsDialog::fillWidgetValues() {
    ox_movement_manager_.setValue(location_->getMovement()->getX());
    oy_movement_manager_.setValue(location_->getMovement()->getY());
    oz_movement_manager_.setValue(location_->getMovement()->getZ());
    ox_rotation_manager_.setValue(location_->getRotation()->getX());
    oy_rotation_manager_.setValue(location_->getRotation()->getY());
    oz_rotation_manager_.setValue(location_->getRotation()->getZ());
    ox_scaling_manager_.setValue(location_->getScaling()->getX());
    oy_scaling_manager_.setValue(location_->getScaling()->getY());
    oz_scaling_manager_.setValue(location_->getScaling()->getZ());

//    setSliderValue(ui->sldr_ox_move, location_->getMovement()->getX(),
//                     ui->spbx_ox_move_begin->value(), ui->spbx_ox_move_end->value());
//    setSliderValue(ui->sldr_oy_move, location_->getMovement()->getY(),
//                     ui->spbx_oy_move_begin->value(), ui->spbx_oy_move_end->value());
//    setSliderValue(ui->sldr_oz_move, location_->getMovement()->getZ(),
//                     ui->spbx_oz_move_begin->value(), ui->spbx_oz_move_end->value());

//    setDialValue(ui->dial_ox_rotate, location_->getRotation()->getX());
//    setDialValue(ui->dial_oy_rotate, location_->getRotation()->getY());
//    setDialValue(ui->dial_oz_rotate, location_->getRotation()->getZ());

//    setSliderValue(ui->sldr_ox_scale, location_->getScaling()->getX(),
//                   ui->spbx_ox_scale_begin->value(), ui->spbx_ox_scale_end->value());
//    setSliderValue(ui->sldr_oy_scale, location_->getScaling()->getY(),
//                   ui->spbx_oy_scale_begin->value(), ui->spbx_oy_scale_end->value());
//    setSliderValue(ui->sldr_oz_scale, location_->getScaling()->getZ(),
//                   ui->spbx_oz_scale_begin->value(), ui->spbx_oz_scale_end->value());
}

void ControlsDialog::getWidgetValues() {
    location_->getMovement()->setX(ox_movement_manager_.getValue());
    location_->getMovement()->setY(oy_movement_manager_.getValue());
    location_->getMovement()->setZ(oz_movement_manager_.getValue());
    location_->getRotation()->setX(ox_rotation_manager_.getValue());
    location_->getRotation()->setY(oy_rotation_manager_.getValue());
    location_->getRotation()->setZ(oz_rotation_manager_.getValue());
    location_->getScaling()->setX(ox_scaling_manager_.getValue());
    location_->getScaling()->setY(oy_scaling_manager_.getValue());
    location_->getScaling()->setZ(oz_scaling_manager_.getValue());

//    location_->getMovement()->setX(getSliderValue(ui->spbx_ox_move_begin->value(),
//                                                      ui->spbx_ox_move_end->value(), ui->sldr_ox_move));
//    location_->getMovement()->setY(getSliderValue(ui->spbx_oy_move_begin->value(),
//                                                      ui->spbx_oy_move_end->value(), ui->sldr_oy_move));
//    location_->getMovement()->setZ(getSliderValue(ui->spbx_oz_move_begin->value(),
//                                                      ui->spbx_oz_move_end->value(), ui->sldr_oz_move));

//    location_->getRotation()->setX(getDialValue(ui->dial_ox_rotate));
//    location_->getRotation()->setY(getDialValue(ui->dial_oy_rotate));
//    location_->getRotation()->setZ(getDialValue(ui->dial_oz_rotate));

//    location_->getScaling()->setX(getSliderValue(ui->spbx_ox_scale_begin->value(),
//                                                 ui->spbx_ox_scale_end->value(), ui->sldr_ox_scale));
//    location_->getScaling()->setY(getSliderValue(ui->spbx_oy_scale_begin->value(),
//                                                 ui->spbx_oy_scale_end->value(), ui->sldr_oy_scale));
//    location_->getScaling()->setZ(getSliderValue(ui->spbx_oz_scale_begin->value(),
//                                                 ui->spbx_oz_scale_end->value(), ui->sldr_oz_scale));
}

void ControlsDialog::fillStateValues() {
    ui->spbx_moved_ox->setValue(location_->getMovement()->getX());
    ui->spbx_moved_oy->setValue(location_->getMovement()->getY());
    ui->spbx_moved_oz->setValue(location_->getMovement()->getZ());

    ui->spbx_rotated_ox->setValue(location_->getRotation()->getX());
    ui->spbx_rotated_oy->setValue(location_->getRotation()->getY());
    ui->spbx_rotated_oz->setValue(location_->getRotation()->getZ());

    ui->spbx_scaled_ox->setValue(location_->getScaling()->getX());
    ui->spbx_scaled_oy->setValue(location_->getScaling()->getY());
    ui->spbx_scaled_oz->setValue(location_->getScaling()->getZ());
}

double ControlsDialog::getSliderValue(double begin, double end, QSlider *slider) {
    return begin + (end - begin) * (slider->value() - slider->minimum()) / (slider->maximum() - slider->minimum());
}

void ControlsDialog::setDefaultState() {
    disableTagSelecting(false);
}

void ControlsDialog::setSliderValue(QSlider *slider, double value, double begin, double end) {
    slider->setValue(slider->minimum() + (slider->maximum() - slider->minimum()) * (value - begin) / (end - begin));
}

double ControlsDialog::getDialValue(QDial *dial) {
    double value = 180 + dial->value();
    while (value >= 360) {
        value -= 360;
    }
    return value;
}

void ControlsDialog::setDialValue(QDial *dial, double value) {
    value += 180;
    while (value > 360) {
        value -=360;
    }
    dial->setValue(value);
}

void ControlsDialog::connectSignals() {
    // buttons
    connect(ui->btn_cancel, SIGNAL(clicked()), this, SLOT(cancelChanges()));
    connect(ui->btn_apply, SIGNAL(clicked()), this, SLOT(applyChanges()));

    // current state values
    connect(ui->spbx_moved_ox, SIGNAL(editingFinished()), this, SLOT(changeState()));
    connect(ui->spbx_moved_oy, SIGNAL(editingFinished()), this, SLOT(changeState()));
    connect(ui->spbx_moved_oz, SIGNAL(editingFinished()), this, SLOT(changeState()));
    connect(ui->spbx_rotated_ox, SIGNAL(editingFinished()), this, SLOT(changeState()));
    connect(ui->spbx_rotated_oy, SIGNAL(editingFinished()), this, SLOT(changeState()));
    connect(ui->spbx_rotated_oz, SIGNAL(editingFinished()), this, SLOT(changeState()));
    connect(ui->spbx_scaled_ox, SIGNAL(editingFinished()), this, SLOT(changeState()));
    connect(ui->spbx_scaled_oy, SIGNAL(editingFinished()), this, SLOT(changeState()));
    connect(ui->spbx_scaled_oz, SIGNAL(editingFinished()), this, SLOT(changeState()));

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
    connect(ui->dial_ox_rotate, SIGNAL(valueChanged(int)), this, SLOT(changeLocation()));
    connect(ui->dial_oy_rotate, SIGNAL(valueChanged(int)), this, SLOT(changeLocation()));
    connect(ui->dial_oz_rotate, SIGNAL(valueChanged(int)), this, SLOT(changeLocation()));
    connect(ui->sldr_ox_move, SIGNAL(valueChanged(int)), this, SLOT(changeLocation()));
    connect(ui->sldr_oy_move, SIGNAL(valueChanged(int)), this, SLOT(changeLocation()));
    connect(ui->sldr_oz_move, SIGNAL(valueChanged(int)), this, SLOT(changeLocation()));
    connect(ui->sldr_ox_scale, SIGNAL(valueChanged(int)), this, SLOT(changeLocation()));
    connect(ui->sldr_oy_scale, SIGNAL(valueChanged(int)), this, SLOT(changeLocation()));
    connect(ui->sldr_oz_scale, SIGNAL(valueChanged(int)), this, SLOT(changeLocation()));

    // Tags Combobox
    connect(ui->cmbx_object, SIGNAL(currentIndexChanged(int)), this, SLOT(selectTag()));
}

