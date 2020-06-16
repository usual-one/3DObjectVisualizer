#ifndef FIGURECONFIGURATIONDIALOG_H
#define FIGURECONFIGURATIONDIALOG_H

#include <QDialog>

#include "logic/include/obj3d/figure/components/vertex.h"

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

    void enableFigureDeleting(bool value);

    int execWith(const std::string &tag, bool tag_selectable = false);

    std::string getFigureTag();

    std::string getSelectedTag();

    std::shared_ptr<std::vector<obj3d::Vertex>> getVertices();

    void setTags(const std::vector<std::string> &tags);

    void setVertices(const std::vector<obj3d::Vertex> &vertices);

    void setFigureTag(const std::string &tag);

    void showWith(const std::string &tag, bool tag_selectable = false);

signals:
    void tagSelected();

    void figureChanged();

    void figureDeleted();

    void figureHidden(int hidden);

private slots:
    void addVertex();

    void applyAndClose();

    void applyChanges();

    void cancelChanges();

    void editVertex();

    void deleteVertex();

    void deleteFigure();

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

    std::string figure_tag_;

};

#endif // FIGURECONFIGURATIONDIALOG_H
