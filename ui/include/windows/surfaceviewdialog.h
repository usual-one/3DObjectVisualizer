#ifndef SURFACEVIEWDIALOG_H
#define SURFACEVIEWDIALOG_H

#include <QDialog>

#include "logic/include/obj3d/surface/surface.h"
#include "logic/include/scene/searchparameters.h"
#include "ui/include/utils/tagsmanager.h"

namespace Ui {
class SurfaceViewDialog;
}

class SurfaceViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SurfaceViewDialog(QWidget *parent = nullptr);

    explicit SurfaceViewDialog(const std::vector<std::string> &tags, QWidget *parent = nullptr);

    ~SurfaceViewDialog();

    int execWith(const std::string &tag, bool tag_selectable);

    std::string getSelectedTag();

    void setSurface(std::shared_ptr<obj3d::Surface> &surface);

    void setTags(const std::vector<std::string> &tags);

    void showWith(const std::string &tag, bool tag_selectable);

signals:
    void tagSelected();

private slots:
    void selectTag();

    void close();

private:
    void connectSignals();

    void enableTagSelection(bool enable);

    Ui::SurfaceViewDialog *ui;

    TagsManager tags_manager_;

};

#endif // SURFACEVIEWDIALOG_H
