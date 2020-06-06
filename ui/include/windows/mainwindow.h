#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "logic/include/facade.h"
#include "ui/include/windows/controlsdialog.h"
#include "ui/include/windows/surfaceconfigurationdialog.h"

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
    void open();

    void exit();

    void viewSurface();

    void viewControls();

    void viewSurfaceConfiguration();

    void saveAs();

    void changeLocation();

    void changeControlsFigure();

    void changeConfigSurface();

    void applyNewSurfaceParams();

private:
    void loadSurface(const QString &path);

    void loadFigure(const QString &path);

    void openSurfaceView(std::shared_ptr<obj3d::Surface> surface);

    void openControls(const std::string &figure_tag);

    void setConnections();

    Ui::MainWindow *ui;

    Facade facade_;

    SurfaceConfigurationDialog surface_cfg_dialog_;

    ControlsDialog ctrls_dialog_;

};
#endif // MAINWINDOW_H
