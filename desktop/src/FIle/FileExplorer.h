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

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    Ui::FileExplorer *ui;
    FileListModel m_model;
    RightMenu m_menu;
};

#endif // FILEEXPLORER_H
