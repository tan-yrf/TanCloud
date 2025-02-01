#ifndef HOME_H
#define HOME_H

#include <QFrame>

namespace Ui {
class Home;
}

class Home : public QFrame
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

    void root() const;

private:
    bool isFolderNameValid(const QString& folder_name, QString& error_message);

private slots:
    void onPathChanged(QString path);
    void onCountChanged(int selected, int sum);
private slots:
    void on_btn_pattern_clicked();
    void on_btn_refresh_clicked();
    void on_btn_home_clicked();
    void on_btn_bak_clicked();
    void on_create_folder_clicked();
    void on_btn_delete_clicked();
    void on_box_select_all_stateChanged(int state);

private:
    Ui::Home *ui;
    enum Pattern {
        List,
        Image
    };
    Pattern m_pattern = Pattern::List;
};

#endif // HOME_H
