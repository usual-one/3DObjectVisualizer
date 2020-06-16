#ifndef BASETAGSELECTINGDIALOG_H
#define BASETAGSELECTINGDIALOG_H

#include <QDialog>

#include "ui/include/utils/tagsmanager.h"

class BaseTagSelectingDialog : public QDialog {
    Q_OBJECT

public:
    BaseTagSelectingDialog(QWidget *parent = nullptr);

    int execWith(const std::string &tag, bool tag_selectable = false);

    std::string getSelectedTag();

    void setTags(const std::vector<std::string> &tags);

    void showWith(const std::string &tag, bool tag_selectable = false);

signals:
    void tagSelected();

protected slots:
    void selectTag();

protected:
    TagsManager tags_manager_;

};

#endif // BASETAGSELECTINGDIALOG_H
