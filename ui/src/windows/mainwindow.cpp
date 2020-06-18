#include "ui/include/windows/mainwindow.h"
#include "ui/include/windows/surfaceviewdialog.h"
#include "ui/include/windows/exitdialog.h"
#include "ui_mainwindow.h"
#include "logic/include/file_manager/obj3dfilemanager.h"
#include "logic/include/scene/scenemanager.h"
#include "logic/include/scene/drawer/scenedrawer.h"

#include "config.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ctrls_dialog_(ControlsDialog(nullptr)) {
    ui->setupUi(this);

    facade_ = Facade(std::make_unique<Obj3DFileManager>(),
                     std::make_unique<SceneManager>(
                         std::make_unique<SceneDrawer>(ui->wdg_res)));

    connectSignals();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::addNewFigure() {
    std::string figure_tag = *facade_.addNewFigure();
    figure_cfg_dialog_.setTags(facade_.getFiguresTags());
    figure_cfg_dialog_.enableFigureDeleting(false);
    int dialog_status = figure_cfg_dialog_.execWith(figure_tag, false);
    if (dialog_status == QDialog::Rejected) {
        facade_.deleteFigure(figure_tag);
    }
    figure_cfg_dialog_.enableFigureDeleting(true);
}

void MainWindow::applyExport() {
    ExportDialog *dialog = (ExportDialog *) sender();
    facade_.saveFigure(dialog->getSelectedTag(), dialog->getMeta()->getPath());
    dialog->reject();
}

void MainWindow::applyNewSurfaceParams() {
    std::shared_ptr<obj3d::Surface> surface = facade_.getSurface(surface_cfg_dialog_.getSelectedTag());

    surface->updateParameters(surface_cfg_dialog_.getSurfaceParameters());
    facade_.recalculateSurface(*surface->getTag());

    facade_.updateFigureSessionState(surface_cfg_dialog_.getSelectedTag(), surface_cfg_dialog_.getSurfaceSessionState());
    facade_.drawScene();
}

void MainWindow::applyNewFigureLocation() {
    facade_.updateFigureState(ctrls_dialog_.getSelectedTag(), ctrls_dialog_.getState());
    facade_.redrawScene();
}

void MainWindow::applyNewFigureVertices() {
    facade_.updateFigureVertices(figure_cfg_dialog_.getSelectedTag(), figure_cfg_dialog_.getVertices());
    facade_.updateFigureSessionState(figure_cfg_dialog_.getSelectedTag(), figure_cfg_dialog_.getFigureSessionState());

    facade_.redrawScene();
}

void MainWindow::open() {
    QStringList paths = QFileDialog::getOpenFileNames(
                this, tr("Open"), QString::fromStdString(DEFAULT_FIGURES_DIR), tr("Figures *.csv *.xml"));

    for (auto path : paths) {
        if (path.endsWith(QString::fromStdString(SURFACE_FILE_FORMAT))) {
            loadSurface(path);
        } else if (path.endsWith(QString::fromStdString(FIGURE_FILE_FORMAT))) {
            loadFigure(path);
        }
    }
}

bool MainWindow::exit() {
    if (!facade_.hasUnsaved()) {
        QCoreApplication::quit();
    }
    int exit_status = exit_dialog_.exec();
    if (exit_status == QDialog::Rejected) {
        return false;
    } else if (exit_status == QDialog::Accepted) {
        if (exit_dialog_.isSaveNeeded()) {
            for (auto figure_tag : facade_.getFiguresTags()) {
                if (!facade_.getFigure(figure_tag)->getMeta()->isSaved()) {
                    export_dialog_.execWith(figure_tag, false);
                }
            }
        }
        QCoreApplication::quit();
    }
    return true;
}

void MainWindow::viewSurfaceViewDialog() {
    surface_view_dialog_.setTags(facade_.getSurfacesTags());
    surface_view_dialog_.show();
}

void MainWindow::viewControlsDialog() {
    ctrls_dialog_.setTags(facade_.getFiguresTags());
    ctrls_dialog_.show();
}

void MainWindow::viewExportDialog() {
    export_dialog_.setTags(facade_.getFiguresTags());
    export_dialog_.show();
}

void MainWindow::viewFigureConfigDialog() {
    figure_cfg_dialog_.setTags(facade_.getFiguresTags());
    figure_cfg_dialog_.show();
}

void MainWindow::viewSurfaceConfigDialog() {
    surface_cfg_dialog_.setTags(facade_.getSurfacesTags());
    surface_cfg_dialog_.show();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (!exit()) {
        event->ignore();
    }
}

void MainWindow::changeControlsObject() {
    std::shared_ptr<obj3d::Figure> figure = facade_.getFigure(ctrls_dialog_.getSelectedTag());
    ctrls_dialog_.setState(figure->getStateDTO());
}

void MainWindow::changeConfigFigure() {
    std::shared_ptr<obj3d::Figure> figure = facade_.getFigure(figure_cfg_dialog_.getSelectedTag());
    figure_cfg_dialog_.setFigureSessionState(figure->getSessionStateDTO());
    figure_cfg_dialog_.setVertices(figure->getVerticesDTO());
}

void MainWindow::changeConfigSurface() {
    surface_cfg_dialog_.setSurfaceSessionState(facade_.getFigure(surface_cfg_dialog_.getSelectedTag())->getSessionStateDTO());
    surface_cfg_dialog_.setSurfaceParameters(facade_.getSurface(surface_cfg_dialog_.getSelectedTag())->getParametersDTO());
}

void MainWindow::changeExportObject() {
    std::shared_ptr<obj3d::Figure> figure = facade_.getFigure(export_dialog_.getSelectedTag());
    export_dialog_.setMeta(figure->getMetaDTO());
}

void MainWindow::changeViewSurface() {
    std::shared_ptr<obj3d::Surface> surface = facade_.getSurface(surface_view_dialog_.getSelectedTag());
    surface_view_dialog_.setSurface(surface);
}

void MainWindow::deleteFigure() {
    std::shared_ptr<obj3d::Figure> figure = facade_.getFigure(figure_cfg_dialog_.getSelectedTag());
    if (!figure->getMeta()->isSaved()) {
        exit_dialog_.execIrrevocable();
        if (exit_dialog_.isSaveNeeded()) {
            export_dialog_.execWith(*figure->getTag(), false);
        }
    }
    facade_.deleteFigure(*figure->getTag());
    facade_.redrawScene();
}

void MainWindow::deleteSurface() {
    std::shared_ptr<obj3d::Figure> figure = facade_.getFigure(surface_cfg_dialog_.getSelectedTag());
    if (!figure->getMeta()->isSaved()) {
        exit_dialog_.execIrrevocable();
        if (exit_dialog_.isSaveNeeded()) {
            export_dialog_.execWith(*figure->getTag(), false);
        }
    }
    facade_.deleteSurface(*figure->getTag());
    facade_.redrawScene();
}

void MainWindow::hideFigure(int hidden) {
    facade_.hideFigure(figure_cfg_dialog_.getSelectedTag(), hidden);
    facade_.redrawScene();
}

void MainWindow::hideSurface(int hidden) {
    facade_.hideSurface(surface_cfg_dialog_.getSelectedTag(), hidden);
    facade_.redrawScene();
}

void MainWindow::connectSignals() {
    connect(ui->act_open, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->act_quit, SIGNAL(triggered()), this, SLOT(exit()));

    // surface view dialog
    connect(ui->act_view_values, SIGNAL(triggered()), this, SLOT(viewSurfaceViewDialog()));
    connect(&surface_view_dialog_, SIGNAL(tagSelected()), this, SLOT(changeViewSurface()));

    // controls dialog
    connect(ui->act_view_ctrls, SIGNAL(triggered()), this, SLOT(viewControlsDialog()));
    connect(&ctrls_dialog_, SIGNAL(tagSelected()), this, SLOT(changeControlsObject()));
    connect(&ctrls_dialog_, SIGNAL(stateChanged()), this, SLOT(applyNewFigureLocation()));

    // export dialog
    connect(ui->act_export, SIGNAL(triggered()), this, SLOT(viewExportDialog()));
    connect(&export_dialog_, SIGNAL(tagSelected()), this, SLOT(changeExportObject()));
    connect(&export_dialog_, SIGNAL(exportRequested()), this, SLOT(applyExport()));

    // surface config dialog
    connect(ui->act_configure_surface, SIGNAL(triggered()), this, SLOT(viewSurfaceConfigDialog()));
    connect(&surface_cfg_dialog_, SIGNAL(tagSelected()), this, SLOT(changeConfigSurface()));
    connect(&surface_cfg_dialog_, SIGNAL(surfaceChanged()), this, SLOT(applyNewSurfaceParams()));
    connect(&surface_cfg_dialog_, SIGNAL(surfaceDeleted()), this, SLOT(deleteSurface()));
    connect(&surface_cfg_dialog_, SIGNAL(surfaceHidden(int)), this, SLOT(hideSurface(int)));

    // figures config dialog
    connect(ui->act_new_figure, SIGNAL(triggered()), this, SLOT(addNewFigure()));
    connect(ui->act_configure_figure, SIGNAL(triggered()), this, SLOT(viewFigureConfigDialog()));
    connect(&figure_cfg_dialog_, SIGNAL(tagSelected()), this, SLOT(changeConfigFigure()));
    connect(&figure_cfg_dialog_, SIGNAL(figureChanged()), this, SLOT(applyNewFigureVertices()));
    connect(&figure_cfg_dialog_, SIGNAL(figureDeleted()), this, SLOT(deleteFigure()));
    connect(&figure_cfg_dialog_, SIGNAL(figureHidden(int)), this, SLOT(hideFigure(int)));
}

void MainWindow::loadSurface(const QString &path) {
    Scene loaded_scene = facade_.loadScene(path.toStdString());

    for (auto tag : loaded_scene.getSurfacesTags()) {
        std::shared_ptr<obj3d::Surface> surface = loaded_scene.getSurface(*tag);
        surface_cfg_dialog_.enableSurfaceDeleting(false);
        int cfg_status = surface_cfg_dialog_.execWith(*surface->getTag());
        surface_cfg_dialog_.enableSurfaceDeleting(true);
        if (cfg_status == QDialog::Rejected) {
            facade_.deleteSurface(*surface->getTag());
        }
    }
}

void MainWindow::loadFigure(const QString &path) {
    facade_.loadScene(path.toStdString());
    facade_.drawScene();
}

void MainWindow::openControls(const std::string &figure_tag) {
    ctrls_dialog_.setTags(facade_.getFiguresTags());
    ctrls_dialog_.setState(facade_.getFigure(figure_tag)->getStateDTO());
    ctrls_dialog_.show();
}
