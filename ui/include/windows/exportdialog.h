#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>

#include "ui/include/utils/tagsmanager.h"

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = nullptr);

    ExportDialog(const std::vector<std::string> &tags, QWidget *parent = nullptr);

    ~ExportDialog();

    int execWith(const std::string &tag, bool tag_selectable);

    std::string getSelectedTag();

    std::shared_ptr<std::string> getPath();

    void setPath(const std::string &path);

    void setTags(const std::vector<std::string> &tags);

    void showWith(const std::string &tag, bool tag_selectable);

signals:
    void exportRequested();

    void tagSelected();

    void pathChanged();

private slots:
    void cancelExport();

    void requestExport();

    void selectTag();

    void selectPath();

    void setPath();

private:
    void enableTagSelection(bool enable);

    void enableExport(bool enable);

    void setConnections();

    Ui::ExportDialog *ui;

    TagsManager tags_manager_;

    std::shared_ptr<std::string> path_;
};

#endif // EXPORTDIALOG_H
