#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QWidget>

#include "FileListModel.h"

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

private:
    Ui::FileExplorer *ui;
    FileListModel m_model;
};

#endif // FILEEXPLORER_H
