#include "ui/include/windows/mainwindow.h"
#include "ui/include/windows/surfaceconfigurationdialog.h"
#include "ui/include/windows/surfaceviewdialog.h"
#include "ui/include/windows/exitdialog.h"
#include "ui_mainwindow.h"
#include "logic/include/file_manager/obj3dfilemanager.h"
#include "logic/include/scene/scenemanager.h"
#include "logic/include/scene/drawer/scenedrawer.h"

#include "config.h"

#include <QFileDialog>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    facade_ = Facade(std::make_unique<Obj3DFileManager>(),
                     std::make_unique<SceneManager>(
                         std::make_unique<SceneDrawer>(ui->wdg_res)));

    setConnections();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::open() {
    QStringList paths = QFileDialog::getOpenFileNames(
                this, tr("Open"), "../3DSurfaceVisualizer/resource", tr("Figures *.csv *.xml"));

    for (auto path : paths) {
        if (path.endsWith(QString::fromStdString(SURFACE_FILE_FORMAT))) {
            loadSurface(path);
        } else if (path.endsWith(QString::fromStdString(FIGURE_FILE_FORMAT))) {
            loadFigure(path);
        }
    }
}

void MainWindow::exit() {
    if (!facade_.hasChanges()) {
        QCoreApplication::quit();
    }
    std::shared_ptr<bool> save_needed = std::make_shared<bool>(false);
    ExitDialog exit_dialog(save_needed, this);
    int exit_status = exit_dialog.exec();
    if (exit_status == QDialog::Rejected) {
        return;
    } else if (exit_status == QDialog::Accepted) {
        if (save_needed) {
            saveAs();
        }
        QCoreApplication::quit();
    }
}

void MainWindow::viewSurface() {
    openSurfaceView(nullptr);
}

void MainWindow::viewControls() {
    ctrls_dialog_.setTags(facade_.getFiguresTags());
    ctrls_dialog_.show();
}

void MainWindow::viewSurfaceConfiguration() {
    surface_cfg_dialog_.setTags(facade_.getSurfacesTags());
    surface_cfg_dialog_.show();
}

void MainWindow::saveAs() {
    QString path = QFileDialog::getSaveFileName(
                this, tr("Save as"), "../3DSurfaceVisualizer/resource/untitled.xml", tr("Figures *.xml"));
    if (!path.size()) {
        return;
    }
    facade_.saveScene(path.toStdString());
}

void MainWindow::ApplyNewFigureLocation() {
    ControlsDialog *dialog = (ControlsDialog *) sender();
    facade_.changeLocation(dialog->getSelectedTag(), dialog->getLocation());

    facade_.redrawScene();
}

void MainWindow::changeControlsFigure() {
    ControlsDialog *dialog = (ControlsDialog *) sender();
    std::shared_ptr<obj3d::Figure> figure = facade_.getFigure(dialog->getSelectedTag());

    dialog->setLocation(figure->getLocation());
}

void MainWindow::changeConfigSurface() {
    SurfaceConfigurationDialog *dialog = (SurfaceConfigurationDialog *) sender();
    std::shared_ptr<obj3d::Surface> surface = facade_.getSurface(dialog->getSelectedTag());

    dialog->setSurfaceTag(surface->getTag());
    dialog->setSurfaceParameters(surface->getParameters());
}

void MainWindow::applyNewSurfaceParams() {
    SurfaceConfigurationDialog *dialog = (SurfaceConfigurationDialog *) sender();
    std::shared_ptr<obj3d::Surface> surface = facade_.getSurface(dialog->getSelectedTag());

    surface->setTag(*dialog->getSurfaceTag());
    surface->setParameters(dialog->getSurfaceParameters());
    facade_.recalculateSurface(*surface->getTag());
    facade_.drawScene();
}

void MainWindow::loadSurface(const QString &path) {
    Scene loaded_scene = facade_.loadScene(path.toStdString());

    for (auto tag : loaded_scene.getSurfacesTags()) {
        std::shared_ptr<obj3d::Surface> surface = loaded_scene.getSurface(*tag);
        int cfg_status = surface_cfg_dialog_.execWith(*surface->getTag());
        if (cfg_status == QDialog::Rejected) {
            facade_.deleteSurface(*surface->getTag());
        }
        ctrls_dialog_.showWith(*surface->getTag());
    }
}

void MainWindow::loadFigure(const QString &path) {
    facade_.loadScene(path.toStdString());
}

void MainWindow::openSurfaceView(std::shared_ptr<obj3d::Surface> surface) {
    std::vector<std::string> tags = facade_.getSurfacesTags();
    std::shared_ptr<SearchParameters> params = std::make_shared<SearchParameters>(tags);
    SurfaceViewDialog surface_dialog(surface, params);
    int status_code = surface_dialog.exec();
    if (status_code == QDialog::Accepted) {
        openSurfaceView(facade_.getSurface(params->getSelected()));
    }
}

void MainWindow::openControls(const std::string &figure_tag) {
    ctrls_dialog_.setTags(facade_.getFiguresTags());
    ctrls_dialog_.setLocation(facade_.getFigure(figure_tag)->getLocation());
    ctrls_dialog_.show();
}

void MainWindow::setConnections() {
    connect(ui->act_open, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->act_exit, SIGNAL(triggered()), this, SLOT(exit()));
    connect(ui->act_view_values, SIGNAL(triggered()), this, SLOT(viewSurface()));

    // controls dialog
    connect(ui->act_view_ctrls, SIGNAL(triggered()), this, SLOT(viewControls()));
    connect(&ctrls_dialog_, SIGNAL(tagSelected()), this, SLOT(changeControlsFigure()));
    connect(&ctrls_dialog_, SIGNAL(locationChanged()), this, SLOT(ApplyNewFigureLocation()));

    // surface config dialog
    connect(ui->act_configure_surface, SIGNAL(triggered()), this, SLOT(viewSurfaceConfiguration()));
    connect(&surface_cfg_dialog_, SIGNAL(tagSelected()), this, SLOT(changeConfigSurface()));
    connect(&surface_cfg_dialog_, SIGNAL(parametersChanged()), this, SLOT(applyNewSurfaceParams()));
}
