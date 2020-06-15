#include "ui/include/windows/connectionadditiondialog.h"
#include "ui_connectionadditiondialog.h"

ConnectionAdditionDialog::ConnectionAdditionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionAdditionDialog) {
    ui->setupUi(this);

    connection_manager_.setWidget(ui->lst_connections);
    vertex_manager_.setWidget(ui->lst_vertices);

    connectSignals();
}

ConnectionAdditionDialog::~ConnectionAdditionDialog() {
    delete ui;
}

void ConnectionAdditionDialog::setCurrent(obj3d::Vertex &vertex) {
    ui->lbl_vertex_value->setText(QString::fromStdString(VertexListManager::toString(vertex)));
}

void ConnectionAdditionDialog::setVertices(std::shared_ptr<std::vector<obj3d::Vertex>> vertices) {
    vertex_manager_.setVertices(*vertices);
}

void ConnectionAdditionDialog::setConnections(std::shared_ptr<std::vector<obj3d::Vertex>> connections) {
    connection_manager_.setVertices(*connections);
}

std::shared_ptr<std::vector<obj3d::Vertex>> ConnectionAdditionDialog::getVertices() {
    return vertex_manager_.getVertices();
}

std::shared_ptr<std::vector<obj3d::Vertex>> ConnectionAdditionDialog::getConnections() {
    return connection_manager_.getVertices();
}

void ConnectionAdditionDialog::addConnection() {
    obj3d::Vertex vertex = vertex_manager_.getCurrent();
    connection_manager_.add(vertex);
    vertex_manager_.removeCurrent();
}

void ConnectionAdditionDialog::applyChanges() {
    accept();
}

void ConnectionAdditionDialog::cancelChanges() {
    reject();
}

void ConnectionAdditionDialog::removeConnection() {
    obj3d::Vertex vertex = connection_manager_.getCurrent();
    vertex_manager_.add(vertex);
    connection_manager_.removeCurrent();
}

void ConnectionAdditionDialog::connectSignals() {
    // vertex lists
    connect(ui->lst_vertices, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(addConnection()));
    connect(ui->lst_connections, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(removeConnection()));

    // action buttons
    connect(ui->btn_ok, SIGNAL(clicked()), this, SLOT(applyChanges()));
    connect(ui->btn_cancel, SIGNAL(clicked()), this, SLOT(cancelChanges()));
}
