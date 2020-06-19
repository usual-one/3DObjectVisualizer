#ifndef FIGURECONFIGURATIONDIALOG_H
#define FIGURECONFIGURATIONDIALOG_H

#include <QDialog>

#include "logic/include/obj3d/figure/components/vertex.h"
#include "logic/include/dto/sessionstatedto.h"
#include "logic/include/dto/figureverticesdto.h"

#include "ui/include/windows/connectionadditiondialog.h"
#include "ui/include/windows/basetagselectingdialog.h"
#include "ui/include/utils/vertexlistmanager.h"

namespace Ui {
class FigureConfigurationDialog;
}

class FigureConfigurationDialog : public BaseTagSelectingDialog {
    Q_OBJECT

public:
    explicit FigureConfigurationDialog(QWidget *parent = nullptr);

    FigureConfigurationDialog(const std::vector<std::string> &tags, QWidget *parent = nullptr);

    ~FigureConfigurationDialog();

    void enableFigureDeleting(bool value);

    int execWith(const std::string &tag, bool tag_selectable = false);

    std::shared_ptr<SessionStateDTO> getFigureSessionState();

    std::shared_ptr<FigureVerticesDTO> getVertices();

    void setVertices(std::shared_ptr<FigureVerticesDTO> vertices);

    void setFigureSessionState(std::shared_ptr<SessionStateDTO> state);

    void showWith(const std::string &tag, bool tag_selectable = false);

signals:
    void figureChanged();

    void figureDeleted();

private slots:
    void addVertex();

    void applyAndClose();

    void applyChanges();

    void cancelChanges();

    void editVertex();

    void deleteVertex();

    void deleteFigure();

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

    std::string figure_tag_;

};

#endif // FIGURECONFIGURATIONDIALOG_H
