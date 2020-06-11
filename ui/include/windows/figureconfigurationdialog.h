#ifndef FIGURECONFIGURATIONDIALOG_H
#define FIGURECONFIGURATIONDIALOG_H

#include <QDialog>

#include "logic/include/obj3d/figure/components/vertex3d.h"

#include "ui/include/windows/connectionadditiondialog.h"
#include "ui/include/utils/tagsmanager.h"
#include "ui/include/utils/vertexlistmanager.h"

namespace Ui {
class FigureConfigurationDialog;
}

class FigureConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FigureConfigurationDialog(QWidget *parent = nullptr);

    FigureConfigurationDialog(const std::vector<std::string> &tags, QWidget *parent = nullptr);

    ~FigureConfigurationDialog();

    int execWith(const std::string &tag, bool tag_selectable = false);

    std::string getSelectedTag();

    std::shared_ptr<std::vector<obj3d::Vertex3D>> getVertices();

    void setTags(const std::vector<std::string> &tags);

    void setVertices(const std::vector<obj3d::Vertex3D> &vertices);

    void showWith(const std::string &tag, bool tag_selectable = false);

signals:
    void tagSelected();

    void figureChanged();

private slots:
    void addVertex();

    void applyAndClose();

    void applyChanges();

    void cancelChanges();

    void editVertex();

    void deleteVertex();

    void selectTag();

    void selectVertex();

    void showVertexContexMenu(const QPoint &pos);

    void viewConnectionAdditionDialog();

private:
    void clearVertexWidgets();

    void configureWidgets();

    void connectSignals();

    void enableTagSelection(bool enable);

    void setDefaultState();

    void setConnections();

    Ui::FigureConfigurationDialog *ui;

    VertexListManager vertex_manager_;

    VertexListManager connections_manager_;

    ConnectionAdditionDialog connection_addition_dialog_;

    TagsManager tags_manager_;

};

#endif // FIGURECONFIGURATIONDIALOG_H
