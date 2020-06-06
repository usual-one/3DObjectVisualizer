#ifndef SURFACEVIEWDIALOG_H
#define SURFACEVIEWDIALOG_H

#include <QDialog>

#include "logic/include/obj3d/surface/surface.h"
#include "logic/include/scene/searchparameters.h"

namespace Ui {
class SurfaceViewDialog;
}

class SurfaceViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SurfaceViewDialog(std::shared_ptr<obj3d::Surface> surface,
                               std::shared_ptr<SearchParameters> params, QWidget *parent = nullptr);
    ~SurfaceViewDialog();

private slots:
    void select();

    void close();

private:
    void setTagLines();

    void setSurfaceTable();

    Ui::SurfaceViewDialog *ui;

    std::shared_ptr<obj3d::Surface> surface_;

    std::shared_ptr<SearchParameters> params_;
};

#endif // SURFACEVIEWDIALOG_H
