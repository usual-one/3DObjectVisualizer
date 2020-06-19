#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "logic/include/facade.h"
#include "ui/include/windows/controlsdialog.h"
#include "ui/include/windows/exitdialog.h"
#include "ui/include/windows/exportdialog.h"
#include "ui/include/windows/figureconfigurationdialog.h"
#include "ui/include/windows/surfaceconfigurationdialog.h"
#include "ui/include/windows/surfaceviewdialog.h"

const int ERROR_DISPLAYING_TIMEOUT = 7000;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void addNewFigure();

    void applyExport();

    void applyNewFigureLocation();

    void applyNewFigureVertices();

    void applyNewSurfaceParams();

    void changeControlsObject();

    void changeConfigFigure();

    void changeConfigSurface();

    void changeExportObject();

    void changeViewSurface();

    void deleteFigure();

    void deleteSurface();

    void hideFigure(int hidden);

    void hideSurface(int hidden);

    bool exit();

    void open();

    void viewSurfaceViewDialog();

    void viewControlsDialog();

    void viewExportDialog();

    void viewFigureConfigDialog();

    void viewSurfaceConfigDialog();

private:
    void closeEvent(QCloseEvent *event) override;

    void connectSignals();

    void loadSurface(const QString &path);

    void loadFigure(const QString &path);

    void openSurfaceView(std::shared_ptr<obj3d::Surface> surface);

    void openControls(const std::string &figure_tag);

    void resizeEvent(QResizeEvent *event) override;

    void showEvent(QShowEvent *event) override;

    Ui::MainWindow *ui;

    Facade facade_;

    ControlsDialog ctrls_dialog_;

    ExitDialog exit_dialog_;

    ExportDialog export_dialog_;

    FigureConfigurationDialog figure_cfg_dialog_;

    SurfaceConfigurationDialog surface_cfg_dialog_;

    SurfaceViewDialog surface_view_dialog_;

};
#endif // MAINWINDOW_H
