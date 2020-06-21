#include "config.h"
#include "ui/include/windows/figureconfigurationdialog.h"
#include "ui_figureconfigurationdialog.h"

#include <QMenu>

FigureConfigurationDialog::FigureConfigurationDialog(QWidget *parent) :
    BaseTagSelectingDialog(parent),
    ui(new Ui::FigureConfigurationDialog) {
    ui->setupUi(this);

    tags_manager_.setWidget(ui->cmbx_figure);
    vertex_manager_.setWidget(ui->lst_vertices);
    connections_manager_.setWidget(ui->lst_connections);

    configureWidgets();
    connectSignals();
}

FigureConfigurationDialog::FigureConfigurationDialog(const std::vector<std::string> &tags, QWidget *parent) :
    BaseTagSelectingDialog(parent),
    ui(new Ui::FigureConfigurationDialog) {
    ui->setupUi(this);

    vertex_manager_.setWidget(ui->lst_vertices);
    connections_manager_.setWidget(ui->lst_connections);
    tags_manager_.setWidget(ui->cmbx_figure);
    setTags(tags);

    configureWidgets();
    connectSignals();
}

FigureConfigurationDialog::~FigureConfigurationDialog() {
    delete ui;
}

void FigureConfigurationDialog::enableFigureDeleting(bool value) {
    ui->btn_delete->setEnabled(value);
}

int FigureConfigurationDialog::exec() {
    enableVertexEditing(vertex_manager_.hasSelected());
    return BaseTagSelectingDialog::exec();
}

int FigureConfigurationDialog::execWith(const std::string &tag, bool tag_selectable) {
    enableTagSelection(tag_selectable);
    return BaseTagSelectingDialog::execWith(tag, tag_selectable);
}

std::shared_ptr<SessionStateDTO> FigureConfigurationDialog::getFigureSessionState() {
    figure_tag_ = ui->ln_tag->text().toStdString();
    return std::make_shared<SessionStateDTO>(ui->chbx_hide->isChecked(), figure_tag_);
}

std::shared_ptr<FigureVerticesDTO> FigureConfigurationDialog::getVertices() {
    return std::make_shared<FigureVerticesDTO>(*vertex_manager_.getVertices());
}

void FigureConfigurationDialog::setVertices(std::shared_ptr<FigureVerticesDTO> vertices) {
    vertex_manager_.setVertices(vertices->getVertices());
    clearVertexWidgets();
}

void FigureConfigurationDialog::setFigureSessionState(std::shared_ptr<SessionStateDTO> state) {
    figure_tag_ = state->getTag();
    ui->ln_tag->setText(QString::fromStdString(figure_tag_));

    ui->chbx_hide->setChecked(state->getHidden());
}

void FigureConfigurationDialog::showEvent(QShowEvent *event) {
    enableVertexEditing(vertex_manager_.hasSelected());
    event->accept();
}

void FigureConfigurationDialog::showWith(const std::string &tag, bool tag_selectable) {
    enableTagSelection(tag_selectable);
    BaseTagSelectingDialog::showWith(tag, tag_selectable);
}

void FigureConfigurationDialog::addVertex() {
    size_t id = vertex_manager_.add();
    vertex_manager_.setCurrentID(id);
    selectVertex();
}

void FigureConfigurationDialog::applyAndClose() {
    applyChanges();
    accept();
    setDefaultState();
}

void FigureConfigurationDialog::applyChanges() {
    emit figureChanged();
    tags_manager_.changeSelectedText(figure_tag_);
}

void FigureConfigurationDialog::cancelChanges() {
    reject();
}

void FigureConfigurationDialog::editVertex() {
    obj3d::Vertex vertex = vertex_manager_.getCurrent();
    vertex.getPosition()->setX(ui->spbx_point_ox->value());
    vertex.getPosition()->setY(ui->spbx_point_oy->value());
    vertex.getPosition()->setZ(ui->spbx_point_oz->value());
    vertex_manager_.updateCurrent(vertex);
}

void FigureConfigurationDialog::deleteVertex() {
    clearVertexWidgets();
    vertex_manager_.removeCurrent();
}

void FigureConfigurationDialog::deleteFigure() {
    emit figureDeleted();

    tags_manager_.removeSelected();
    if (tags_manager_.isEmpty()) {
        reject();
    } else {
        emit tagSelected();
    }
}

void FigureConfigurationDialog::selectVertex() {
    enableVertexEditing(vertex_manager_.hasSelected());
    vertex_manager_.updateCurrent();
    obj3d::Vertex current = vertex_manager_.getCurrent();
    ui->lbl_id_value->setNum((int) current.getID());
    ui->spbx_point_ox->setValue(current.getPosition()->getX());
    ui->spbx_point_oy->setValue(current.getPosition()->getY());
    ui->spbx_point_oz->setValue(current.getPosition()->getZ());
    setConnections();
}

void FigureConfigurationDialog::showVertexContexMenu(const QPoint &pos) {
    QPoint globalPos = ui->lst_vertices->mapToGlobal(pos);

    QMenu menu;
    menu.addAction(QString::fromStdString(MENU_ACTION_DELETE), this, SLOT(deleteVertex()));

    menu.exec(globalPos);
}

void FigureConfigurationDialog::viewConnectionAdditionDialog() {
    std::shared_ptr<std::vector<obj3d::Vertex>> vertices =
            std::make_shared<std::vector<obj3d::Vertex>>(*vertex_manager_.getVertices());
    obj3d::Vertex current = vertex_manager_.getCurrent();

    for (auto it = vertices->begin(); it < vertices->end(); it++) {
        if (*it == current) {
            vertices->erase(it);
            it--;
            continue;
        }
        if (connections_manager_.contains(*it)) {
            vertices->erase(it);
            it--;
        }
    }

    connection_addition_dialog_.setCurrent(current);
    connection_addition_dialog_.setVertices(vertices);
    connection_addition_dialog_.setConnections(connections_manager_.getVertices());

    int status = connection_addition_dialog_.exec();
    if (status == QDialog::Accepted) {
        connections_manager_.setVertices(*connection_addition_dialog_.getConnections());
    }

    current.setConnections(connections_manager_.getVertexIDs());
    vertex_manager_.updateCurrent(current);
}

void FigureConfigurationDialog::clearVertexWidgets() {
    ui->lbl_id_value->clear();
    ui->spbx_point_ox->clear();
    ui->spbx_point_oy->clear();
    ui->spbx_point_oz->clear();
    connections_manager_.clear();
}

void FigureConfigurationDialog::closeEvent(QCloseEvent *event){
    event->ignore();
    cancelChanges();
}

void FigureConfigurationDialog::configureWidgets() {
    ui->lst_vertices->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->spbx_point_ox->setMinimum(MIN_COORD_VALUE);
    ui->spbx_point_oy->setMinimum(MIN_COORD_VALUE);
    ui->spbx_point_oz->setMinimum(MIN_COORD_VALUE);
    ui->spbx_point_ox->setMaximum(MAX_COORD_VALUE);
    ui->spbx_point_oy->setMaximum(MAX_COORD_VALUE);
    ui->spbx_point_oz->setMaximum(MAX_COORD_VALUE);
}

void FigureConfigurationDialog::connectSignals() {
    // Figure tags combobox
    connect(ui->cmbx_figure, SIGNAL(currentIndexChanged(int)), this, SLOT(selectTag()));

    // Vertex adding button
    connect(ui->btn_add, SIGNAL(clicked()), this, SLOT(addVertex()));

    // Connection adding button
    connect(ui->btn_edit_connections, SIGNAL(clicked()), this, SLOT(viewConnectionAdditionDialog()));

    // Delete button
    connect(ui->btn_delete, SIGNAL(clicked()), this, SLOT(deleteFigure()));

    // Hide CheckBox
    connect(ui->chbx_hide, SIGNAL(stateChanged(int)), this, SLOT(applyChanges()));

    // Vertices list
    connect(ui->lst_vertices, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(selectVertex()));
    connect(ui->lst_vertices, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showVertexContexMenu(const QPoint &)));

    // Action buttons
    connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(applyAndClose()));
    connect(ui->btn_apply, SIGNAL(clicked()), this, SLOT(applyChanges()));
    connect(ui->btn_cancel, SIGNAL(clicked()), this, SLOT(cancelChanges()));

    // Coords spinboxes
    connect(ui->spbx_point_ox, SIGNAL(editingFinished()), this, SLOT(editVertex()));
    connect(ui->spbx_point_oy, SIGNAL(editingFinished()), this, SLOT(editVertex()));
    connect(ui->spbx_point_oz, SIGNAL(editingFinished()), this, SLOT(editVertex()));
}

void FigureConfigurationDialog::enableTagSelection(bool enable) {
    ui->lbl_figure->setEnabled(enable);
}

void FigureConfigurationDialog::enableVertexEditing(bool enable) {
    ui->lbl_id->setEnabled(enable);
    ui->lbl_id_value->setEnabled(enable);

    ui->lbl_ox->setEnabled(enable);
    ui->lbl_oy->setEnabled(enable);
    ui->lbl_oz->setEnabled(enable);

    ui->spbx_point_ox->setEnabled(enable);
    ui->spbx_point_oy->setEnabled(enable);
    ui->spbx_point_oz->setEnabled(enable);

    ui->lbl_connections->setEnabled(enable);
    ui->lst_connections->setEnabled(enable);
    ui->btn_edit_connections->setEnabled(enable);
}

void FigureConfigurationDialog::setDefaultState() {
    enableTagSelection(true);
    clearVertexWidgets();
}

void FigureConfigurationDialog::setConnections() {
    connections_manager_.clear();
    obj3d::Vertex vertex = vertex_manager_.getCurrent();
    for (auto id : vertex.getConnections()) {
        obj3d::Vertex connection = vertex_manager_.getVertex(id);
        connections_manager_.add(connection);
    }
}
