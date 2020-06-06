#ifndef SURFACECONFIGURATIONDIALOG_H
#define SURFACECONFIGURATIONDIALOG_H

#include <memory>

#include <QDialog>

#include "logic/include/obj3d/surface/surface.h"
#include "ui/include/utils/tagsmanager.h"

namespace Ui {
class SurfaceConfigurationDialog;
}

class SurfaceConfigurationDialog : public QDialog {
    Q_OBJECT

public:
    SurfaceConfigurationDialog(QWidget *parent = nullptr);

    explicit SurfaceConfigurationDialog(const std::vector<std::string> &tags, QWidget *parent = nullptr);

    ~SurfaceConfigurationDialog();

    std::string getSelectedTag();

    std::shared_ptr<std::string> getSurfaceTag();

    std::shared_ptr<obj3d::SurfaceParameters> getSurfaceParameters();

    void setSurfaceParameters(std::shared_ptr<obj3d::SurfaceParameters> params);

    void setSurfaceTag(std::shared_ptr<std::string> tag);

    void showWith(const std::string &tag, bool tag_selectable = false);

    int execWith(const std::string &tag, bool tag_selectable = false);

    void setTags(const std::vector<std::string> &tags);

signals:
    void parametersChanged();

    void tagSelected();

private slots:
    void applyAndClose();

    void applyChanges();

    void cancelChanges();

    void selectTag();

    void surfaceTagChanged(); // TODO

    void changeNormalizationAccess(int enabled);

private:
    void disableTagSelecting(bool value);

    void setDefaultState();

    void setParamLines();

    void collectParams();

    void configureParamWidgets();

    void setConnections();

    Ui::SurfaceConfigurationDialog *ui;

    TagsManager tags_manager_;

    std::shared_ptr<std::string> surface_tag_;

    std::shared_ptr<obj3d::SurfaceParameters> surface_params_;

};

#endif // SURFACECONFIGURATIONDIALOG_H
