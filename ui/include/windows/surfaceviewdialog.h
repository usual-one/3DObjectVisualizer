#ifndef SURFACEVIEWDIALOG_H
#define SURFACEVIEWDIALOG_H

#include <QDialog>

#include "ui/include/windows/basetagselectingdialog.h"
#include "logic/include/dto/surfacevaluesdto.h"
#include "ui/include/utils/tagsmanager.h"

namespace Ui {
class SurfaceViewDialog;
}

class SurfaceViewDialog : public BaseTagSelectingDialog {
    Q_OBJECT

public:
    explicit SurfaceViewDialog(QWidget *parent = nullptr);

    explicit SurfaceViewDialog(const std::vector<std::string> &tags, QWidget *parent = nullptr);

    ~SurfaceViewDialog();

    int execWith(const std::string &tag, bool tag_selectable);

    void setSurface(std::shared_ptr<SurfaceValuesDTO> values);

    void showWith(const std::string &tag, bool tag_selectable);

private slots:
    void close();

private:
    void connectSignals();

    void enableTagSelection(bool enable);

    Ui::SurfaceViewDialog *ui;

};

#endif // SURFACEVIEWDIALOG_H
