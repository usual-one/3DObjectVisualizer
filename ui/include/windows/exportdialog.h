#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>

#include "ui/include/windows/basetagselectingdialog.h"

namespace Ui {
class ExportDialog;
}

class ExportDialog : public BaseTagSelectingDialog {
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = nullptr);

    ExportDialog(const std::vector<std::string> &tags, QWidget *parent = nullptr);

    ~ExportDialog();

    int execWith(const std::string &tag, bool tag_selectable);

    std::shared_ptr<std::string> getPath();

    void setPath(const std::string &path);

    void showWith(const std::string &tag, bool tag_selectable);

signals:
    void exportRequested();

    void pathChanged();

private slots:
    void cancelExport();

    void requestExport();

    void selectPath();

    void setPath();

private:
    void enableTagSelection(bool enable);

    void enableExport(bool enable);

    void setConnections();

    Ui::ExportDialog *ui;

    std::shared_ptr<std::string> path_;
};

#endif // EXPORTDIALOG_H
