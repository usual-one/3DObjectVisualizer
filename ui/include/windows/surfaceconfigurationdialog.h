#ifndef SURFACECONFIGURATIONDIALOG_H
#define SURFACECONFIGURATIONDIALOG_H

#include <memory>

#include <QDialog>

#include "logic/include/obj3d/surface/surface.h"
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

    std::shared_ptr<std::string> getSurfaceTag();

    std::shared_ptr<obj3d::SurfaceParameters> getSurfaceParameters();

    void setSurfaceParameters(std::shared_ptr<obj3d::SurfaceParameters> params);

    void setSurfaceTag(std::shared_ptr<std::string> tag);

    void showWith(const std::string &tag, bool tag_selectable = false);

    int execWith(const std::string &tag, bool tag_selectable = false);

signals:
    void surfaceChanged();

    void surfaceDeleted();

    void surfaceHidden(int hidden);

private slots:
    void applyAndClose();

    void applyChanges();

    void cancelChanges();

    void deleteSurface();

    void surfaceTagChanged(); // TODO

    void changeNormalizationAccess(int enabled);

private:
    void closeEvent(QCloseEvent *event) override;

    void enableTagSelection(bool value);

    void setDefaultState();

    void setParamLines();

    void collectParams();

    void configureParamWidgets();

    void connectSignals();

    Ui::SurfaceConfigurationDialog *ui;

    std::shared_ptr<std::string> surface_tag_;

    std::shared_ptr<obj3d::SurfaceParameters> surface_params_;

};

#endif // SURFACECONFIGURATIONDIALOG_H
