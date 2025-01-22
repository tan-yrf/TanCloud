#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QWidget>

namespace Ui {
class FileExplorer;
}

class FileExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit FileExplorer(QWidget *parent = nullptr);
    ~FileExplorer();

private:
    Ui::FileExplorer *ui;
};

#endif // FILEEXPLORER_H
