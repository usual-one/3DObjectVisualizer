#ifndef SURFACECONFIGURATIONDIALOG_H
#define SURFACECONFIGURATIONDIALOG_H

#include <memory>

#include <QDialog>

#include "logic/include/obj3d/surface/surface.h"
#include "logic/include/dto/sessionstatedto.h"
#include "logic/include/dto/surfaceparametersdto.h"
#include "ui/include/windows/basetagselectingdialog.h"

namespace Ui {
class SurfaceConfigurationDialog;
}

class SurfaceConfigurationDialog : public BaseTagSelectingDialog {
    Q_OBJECT

public:
    SurfaceConfigurationDialog(QWidget *parent = nullptr);

    explicit SurfaceConfigurationDialog(const std::vector<std::string> &tags, QWidget *parent = nullptr);

    ~SurfaceConfigurationDialog();

    void enableSurfaceDeleting(bool value);

    int execWith(const std::string &tag, bool tag_selectable = false) override;

    std::shared_ptr<SessionStateDTO> getSurfaceSessionState();

    std::shared_ptr<SurfaceParametersDTO> getSurfaceParameters();

    void setSurfaceParameters(std::shared_ptr<SurfaceParametersDTO> params);

    void setSurfaceSessionState(std::shared_ptr<SessionStateDTO> state);

    void showWith(const std::string &tag, bool tag_selectable = false) override;

signals:
    void surfaceChanged();

    void surfaceDeleted();

private slots:
    void applyAndClose();

    void applyChanges();

    void cancelChanges();

    void deleteSurface();

    void surfaceTagChanged(); // TODO

    void changeNormalizationAccess(int enabled);

private:
    void closeEvent(QCloseEvent *event) override;

    void connectSignals();

    void enableTagSelection(bool enable) override;

    void setDefaultState();

    void setParamLines();

    void collectParams();

    void configureParamWidgets();

    Ui::SurfaceConfigurationDialog *ui;

    std::shared_ptr<obj3d::SurfaceParameters> surface_params_;

};

#endif // SURFACECONFIGURATIONDIALOG_H
