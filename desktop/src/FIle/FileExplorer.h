#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QWidget>

#include "FileListModel.h"
#include "RightMenu.h"

namespace Ui {
class FileExplorer;
}

class FileExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit FileExplorer(QWidget *parent = nullptr);
    ~FileExplorer();

    void setListPattern();
    void setImagePattern();

    void refresh();
    void cd(const QString path);

protected:
    void mousePressEvent(QMouseEvent* event) override;
private:
    bool isImage(const QString& file_name) const;
private:
    Ui::FileExplorer *ui;
    QString m_current_path;
    FileListModel m_model;
    RightMenu m_menu;
};

#endif // FILEEXPLORER_H
