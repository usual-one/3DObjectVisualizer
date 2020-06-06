#include "config.h"
#include "ui/include/windows/controlsdialog.h"
#include "ui_controlsdialog.h"

ControlsDialog::ControlsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlsDialog),
    location_(std::make_shared<Location>()) {
    ui->setupUi(this);

    tags_manager_.setBox(ui->cmbx_object);
    configureParamLines();

    setConnections();
}

ControlsDialog::ControlsDialog(const std::vector<std::string> &tags, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlsDialog),
    location_(std::make_shared<Location>()) {
    ui->setupUi(this);

    tags_manager_.setBox(ui->cmbx_object);
    setTags(tags);
    configureParamLines();
    fillWidgetValues();
    fillStateValues();

    setConnections();
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


void ControlsDialog::selectTag() {
    if (!ui->cmbx_object->count()) {
        return;
    }
    tags_manager_.setCurrent();
    emit tagSelected();
}

void ControlsDialog::configureParamLines() {

    ui->spbx_ox_move_begin->setMinimum(MIN_VALUE);
    ui->spbx_ox_move_begin->setMaximum(MAX_VALUE);
    ui->spbx_ox_move_begin->setValue(MOVE_VALUE_BEGIN);
    ui->spbx_oy_move_begin->setMinimum(MIN_VALUE);
    ui->spbx_oy_move_begin->setMaximum(MAX_VALUE);
    ui->spbx_oy_move_begin->setValue(MOVE_VALUE_BEGIN);
    ui->spbx_oz_move_begin->setMinimum(MIN_VALUE);
    ui->spbx_oz_move_begin->setMaximum(MAX_VALUE);
    ui->spbx_oz_move_begin->setValue(MOVE_VALUE_BEGIN);

    ui->spbx_ox_move_end->setMinimum(MIN_VALUE);
    ui->spbx_ox_move_end->setMaximum(MAX_VALUE);
    ui->spbx_ox_move_end->setValue(MOVE_VALUE_END);
    ui->spbx_oy_move_end->setMinimum(MIN_VALUE);
    ui->spbx_oy_move_end->setMaximum(MAX_VALUE);
    ui->spbx_oy_move_end->setValue(MOVE_VALUE_END);
    ui->spbx_oz_move_end->setMinimum(MIN_VALUE);
    ui->spbx_oz_move_end->setMaximum(MAX_VALUE);
    ui->spbx_oz_move_end->setValue(MOVE_VALUE_END);

    ui->spbx_ox_scale_begin->setMinimum(MIN_VALUE);
    ui->spbx_ox_scale_begin->setMaximum(MAX_VALUE);
    ui->spbx_ox_scale_begin->setValue(SCALE_VALUE_BEGIN);
    ui->spbx_oy_scale_begin->setMinimum(MIN_VALUE);
    ui->spbx_oy_scale_begin->setMaximum(MAX_VALUE);
    ui->spbx_oy_scale_begin->setValue(SCALE_VALUE_BEGIN);
    ui->spbx_oz_scale_begin->setMinimum(MIN_VALUE);
    ui->spbx_oz_scale_begin->setMaximum(MAX_VALUE);
    ui->spbx_oz_scale_begin->setValue(SCALE_VALUE_BEGIN);

    ui->spbx_ox_scale_end->setMinimum(MIN_VALUE);
    ui->spbx_ox_scale_end->setMaximum(MAX_VALUE);
    ui->spbx_ox_scale_end->setValue(SCALE_VALUE_END);
    ui->spbx_oy_scale_end->setMinimum(MIN_VALUE);
    ui->spbx_oy_scale_end->setMaximum(MAX_VALUE);
    ui->spbx_oy_scale_end->setValue(SCALE_VALUE_END);
    ui->spbx_oz_scale_end->setMinimum(MIN_VALUE);
    ui->spbx_oz_scale_end->setMaximum(MAX_VALUE);
    ui->spbx_oz_scale_end->setValue(SCALE_VALUE_END);

}

void ControlsDialog::fillWidgetValues() {
    setSliderValue(ui->sldr_ox_move, location_->getMovement()->getX(),
                     ui->spbx_ox_move_begin->value(), ui->spbx_ox_move_end->value());
    setSliderValue(ui->sldr_oy_move, location_->getMovement()->getY(),
                     ui->spbx_oy_move_begin->value(), ui->spbx_oy_move_end->value());
    setSliderValue(ui->sldr_oz_move, location_->getMovement()->getZ(),
                     ui->spbx_oz_move_begin->value(), ui->spbx_oz_move_end->value());

    setDialValue(ui->dial_ox_rotate, location_->getRotation()->getX());
    setDialValue(ui->dial_oy_rotate, location_->getRotation()->getY());
    setDialValue(ui->dial_oz_rotate, location_->getRotation()->getZ());

    setSliderValue(ui->sldr_ox_scale, location_->getScaling()->getX(),
                   ui->spbx_ox_scale_begin->value(), ui->spbx_ox_scale_end->value());
    setSliderValue(ui->sldr_oy_scale, location_->getScaling()->getY(),
                   ui->spbx_oy_scale_begin->value(), ui->spbx_oy_scale_end->value());
    setSliderValue(ui->sldr_oz_scale, location_->getScaling()->getZ(),
                   ui->spbx_oz_scale_begin->value(), ui->spbx_oz_scale_end->value());
}

void ControlsDialog::getWidgetValues() {
    location_->getMovement()->setX(getSliderValue(ui->spbx_ox_move_begin->value(),
                                                      ui->spbx_ox_move_end->value(), ui->sldr_ox_move));
    location_->getMovement()->setY(getSliderValue(ui->spbx_oy_move_begin->value(),
                                                      ui->spbx_oy_move_end->value(), ui->sldr_oy_move));
    location_->getMovement()->setZ(getSliderValue(ui->spbx_oz_move_begin->value(),
                                                      ui->spbx_oz_move_end->value(), ui->sldr_oz_move));

    location_->getRotation()->setX(getDialValue(ui->dial_ox_rotate));
    location_->getRotation()->setY(getDialValue(ui->dial_oy_rotate));
    location_->getRotation()->setZ(getDialValue(ui->dial_oz_rotate));

    location_->getScaling()->setX(getSliderValue(ui->spbx_ox_scale_begin->value(),
                                                 ui->spbx_ox_scale_end->value(), ui->sldr_ox_scale));
    location_->getScaling()->setY(getSliderValue(ui->spbx_oy_scale_begin->value(),
                                                 ui->spbx_oy_scale_end->value(), ui->sldr_oy_scale));
    location_->getScaling()->setZ(getSliderValue(ui->spbx_oz_scale_begin->value(),
                                                 ui->spbx_oz_scale_end->value(), ui->sldr_oz_scale));
}

void ControlsDialog::fillStateValues() {
    ui->lbl_moved_ox->setNum(location_->getMovement()->getX());
    ui->lbl_moved_oy->setNum(location_->getMovement()->getY());
    ui->lbl_moved_oz->setNum(location_->getMovement()->getZ());

    ui->lbl_rotated_ox->setNum(location_->getRotation()->getX());
    ui->lbl_rotated_oy->setNum(location_->getRotation()->getY());
    ui->lbl_rotated_oz->setNum(location_->getRotation()->getZ());

    ui->lbl_scaled_ox->setNum(location_->getScaling()->getX());
    ui->lbl_scaled_oy->setNum(location_->getScaling()->getY());
    ui->lbl_scaled_oz->setNum(location_->getScaling()->getZ());
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

void ControlsDialog::setConnections() {
    // buttons
    connect(ui->btn_cancel, SIGNAL(clicked()), this, SLOT(cancelChanges()));
    connect(ui->btn_apply, SIGNAL(clicked()), this, SLOT(applyChanges()));

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

