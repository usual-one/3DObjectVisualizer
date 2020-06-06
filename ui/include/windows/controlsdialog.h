#ifndef CONTROLSDIALOG_H
#define CONTROLSDIALOG_H

#include "logic/include/obj3d/figure/components/meta/location.h"
#include "ui/include/utils/tagsmanager.h"

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

    int execWith(const std::string &tag, bool tag_selectable = false);

    std::string getSelectedTag();

    bool hasLocation();

    std::shared_ptr<Location> getLocation();

    void setLocation(std::shared_ptr<Location> new_location);

    void setTags(const std::vector<std::string> &tags);

    void showWith(const std::string &tag, bool tag_selectable = false);

signals:
    void locationChanged();

    void tagSelected();

private slots:
    void applyChanges();

    void cancelChanges();

    void changeLocation();

    void selectTag();

private:
    void configureParamLines();

    void disableTagSelecting(bool value);

    void fillWidgetValues();

    void getWidgetValues();

    void fillStateValues();

    double getSliderValue(double begin, double end, QSlider *slider);

    void setDefaultState();

    void setSliderValue(QSlider *slider, double value, double begin, double end);

    double getDialValue(QDial *dial);

    void setDialValue(QDial *dial, double value);

    void setConnections();

    Ui::ControlsDialog *ui;

    std::shared_ptr<Location> location_;

    TagsManager tags_manager_;

};

#endif // CONTROLSDIALOG_H
