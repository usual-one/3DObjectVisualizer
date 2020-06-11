#ifndef CONNECTIONADDITIONDIALOG_H
#define CONNECTIONADDITIONDIALOG_H

#include "ui/include/utils/vertexlistmanager.h"

#include <QDialog>

namespace Ui {
class ConnectionAdditionDialog;
}

class ConnectionAdditionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionAdditionDialog(QWidget *parent = nullptr);

    ~ConnectionAdditionDialog();

    void setVertices(std::shared_ptr<std::vector<obj3d::Vertex3D>> vertices);

    void setConnections(std::shared_ptr<std::vector<obj3d::Vertex3D>> connections);

    std::shared_ptr<std::vector<obj3d::Vertex3D>> getVertices();

    std::shared_ptr<std::vector<obj3d::Vertex3D>> getConnections();

private slots:
    void addConnection();

    void applyChanges();

    void cancelChanges();

    void removeConnection();

private:
    void connectSignals();

    Ui::ConnectionAdditionDialog *ui;

    VertexListManager connection_manager_;

    VertexListManager vertex_manager_;
};

#endif // CONNECTIONADDITIONDIALOG_H
