#ifndef CONTROLSDIALOG_H
#define CONTROLSDIALOG_H

#include "logic/include/obj3d/figure/components/state.h"
#include "ui/include/utils/tagsmanager.h"
#include "ui/include/utils/slidermanager.h"
#include "ui/include/utils/dialmanager.h"

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
    explicit ControlsDialog(QWidget *parent = nullptr);

    explicit ControlsDialog(const std::vector<std::string> &tags, QWidget *parent = nullptr);

    ~ControlsDialog();

    int execWith(const std::string &tag, bool tag_selectable = false);

    std::string getSelectedTag();

    bool hasLocation();

    std::shared_ptr<State> getState();

    void setState(std::shared_ptr<State> new_state);

    void setTags(const std::vector<std::string> &tags);

    void showWith(const std::string &tag, bool tag_selectable = false);

signals:
    void stateChanged();

    void tagSelected();

private slots:
    void changeBorders();

    void changeStateWithSliders();

    void changeStateWithValues();

    void close();

    void disableSeparateScaling(int disable);

    void selectTag();

private:
    void configureWidgets();

    void connectSignals();

    void disableTagSelecting(bool value);

    void fillWidgetValues();

    void getWidgetValues();

    void fillStateValues();

    void setDefaultState();

    Ui::ControlsDialog *ui;

    std::shared_ptr<State> location_;

    TagsManager tags_manager_;

    SliderManager ox_movement_manager_;

    SliderManager oy_movement_manager_;

    SliderManager oz_movement_manager_;

    SliderManager ox_scaling_manager_;

    SliderManager oy_scaling_manager_;

    SliderManager oz_scaling_manager_;

    DialManager ox_rotation_manager_;

    DialManager oy_rotation_manager_;

    DialManager oz_rotation_manager_;

};

#endif // CONTROLSDIALOG_H
