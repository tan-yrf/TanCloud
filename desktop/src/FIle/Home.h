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

private slots:
    void on_btn_pattern_clicked();

    void on_btn_refresh_clicked();

    void on_btn_home_clicked();

    void on_btn_bak_clicked();

private:
    Ui::Home *ui;
    enum Pattern {
        List,
        Image
    };
    Pattern m_pattern = Pattern::List;
};

#endif // HOME_H
