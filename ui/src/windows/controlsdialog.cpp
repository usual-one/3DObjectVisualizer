#include "ui/include/windows/controlsdialog.h"
#include "ui_controlsdialog.h"

ControlsDialog::ControlsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlsDialog),
    location_(std::make_shared<Location>()) {
    ui->setupUi(this);

    setConnections();
}

ControlsDialog::ControlsDialog(const std::vector<std::string> &tags, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlsDialog),
    location_(std::make_shared<Location>()) {
    ui->setupUi(this);

    tags_ = tags;
    setTagValues();

    setConnections();
}

ControlsDialog::~ControlsDialog() {
    delete ui;
}

bool ControlsDialog::hasLocation() {
    return location_ != nullptr;
}

std::shared_ptr<Location> ControlsDialog::getLocation() {
    return location_;
}

void ControlsDialog::setLocation(std::shared_ptr<Location> new_location) {
    *location_ = *new_location;
    fillWidgetValues();
    setStateValues();
}

void ControlsDialog::setTags(const std::vector<std::string> &tags) {
    tags_ = tags;
    setTagValues();
}

std::string ControlsDialog::getSelectedTag() {
    return ui->cmbx_object->currentText().toStdString();
}

void ControlsDialog::close() {
    reject();
}

void ControlsDialog::changeLocation() {
    getWidgetValues();
    setStateValues();
    emit locationChanged();
}

void ControlsDialog::selectTag() {
    emit tagSelected();
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

void ControlsDialog::setStateValues() {
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

void ControlsDialog::setTagValues() {
    for (auto tag : tags_) {
        ui->cmbx_object->addItem(QString::fromStdString(tag));
    }
}

double ControlsDialog::getSliderValue(double begin, double end, QSlider *slider) {
    return (end - begin) * slider->value() / (slider->maximum() - slider->minimum());
}

void ControlsDialog::setSliderValue(QSlider *slider, double value, double begin, double end) {
    slider->setValue((slider->maximum() - slider->minimum()) * value / (end - begin));
}

double ControlsDialog::getDialValue(QDial *dial) {
    double value = 180 + dial->value();
    while (value >= 360) {
        value -= 360;
    }
    return 180 + dial->value();
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
    connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btn_select, SIGNAL(clicked()), this, SLOT(selectTag()));

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
}

