#ifndef CONTROLSDIALOG_H
#define CONTROLSDIALOG_H

#include "logic/include/obj3d/figure/components/state.h"
#include "ui/include/windows/basetagselectingdialog.h"
#include "ui/include/utils/slidermanager.h"
#include "ui/include/utils/dialmanager.h"

#include <QDialog>
#include <QSlider>
#include <QDial>

namespace Ui {
class ControlsDialog;
}

class ControlsDialog : public BaseTagSelectingDialog {
    Q_OBJECT

public:
    explicit ControlsDialog(QWidget *parent = nullptr);

    explicit ControlsDialog(const std::vector<std::string> &tags, QWidget *parent = nullptr);

    ~ControlsDialog();

    int execWith(const std::string &tag, bool tag_selectable = false);

    bool hasLocation();

    std::shared_ptr<State> getState();

    void setState(std::shared_ptr<State> new_state);

    void showWith(const std::string &tag, bool tag_selectable = false);

signals:
    void stateChanged();

private slots:
    void changeBorders();

    void changeStateWithSliders();

    void changeStateWithValues();

    void close();

    void disableSeparateScaling(int disable);

private:
    void configureWidgets();

    void connectSignals();

    void enableTagSelection(bool value);

    void fillWidgetValues();

    void getWidgetValues();

    void fillStateValues();

    void setDefaultState();

    Ui::ControlsDialog *ui;

    std::shared_ptr<State> location_;

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
