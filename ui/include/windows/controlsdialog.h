#ifndef CONTROLSDIALOG_H
#define CONTROLSDIALOG_H

#include "logic/include/obj3d/figure/components/meta/location.h"

#include <QDialog>
#include <QSlider>
#include <QDial>

namespace Ui {
class ControlsDialog;
}

class ControlsDialog : public QDialog
{
    Q_OBJECT

public:
    ControlsDialog(QWidget *parent = nullptr);

    explicit ControlsDialog(const std::vector<std::string> &tags, QWidget *parent = nullptr);

    ~ControlsDialog();

    bool hasLocation();

    std::shared_ptr<Location> getLocation();

    void setLocation(std::shared_ptr<Location> new_location);

    void setTags(const std::vector<std::string> &tags);

    std::string getSelectedTag();

signals:
    void locationChanged();

    void tagSelected();

public slots:
    void selectTag();

private slots:
    void close();

    void changeLocation();

private:
    void fillWidgetValues();

    void getWidgetValues();

    void setStateValues();

    void setTagValues();

    double getSliderValue(double begin, double end, QSlider *slider);

    void setSliderValue(QSlider *slider, double value, double begin, double end);

    double getDialValue(QDial *dial);

    void setDialValue(QDial *dial, double value);

    void setConnections();

    Ui::ControlsDialog *ui;

    std::shared_ptr<Location> location_;

    std::vector<std::string> tags_;

};

#endif // CONTROLSDIALOG_H
