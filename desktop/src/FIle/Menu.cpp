#include <QMouseEvent>
#include <QFocusEvent>
#include <QInputDialog>
#include <QMessageBox>
#include <QRegularExpression>

#include "Menu.h"
#include "InputDialog.h"
#include "ui_Menu.h"

Menu::Menu(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);  // 去掉标题栏和边框
}

Menu::~Menu()
{
    delete ui;
}

void Menu::setModel(Model *model) {
    m_model = model;
}

void Menu::showAtPosition(const QPointF pos) {
    this->move(pos.toPoint());
    this->show();
    this->setFocus();
    if (m_model && m_model->checkedCount() == 1) {
        ui->btn_rename->setVisible(true);
    } else {
        ui->btn_rename->setVisible(false);
    }
}


void Menu::focusOutEvent(QFocusEvent *event) {
    QFrame::focusOutEvent(event);
    this->close();
}

void Menu::mousePressEvent(QMouseEvent *event) {
    if (this->rect().contains(event->pos())) {
        return;
    }
    QFrame::mousePressEvent(event);
    this->close();
}

bool Menu::isFolderNameValid(const QString &folder_name, QString &error_message) {
    error_message.clear();

    if (folder_name.trimmed().isEmpty()) {
        error_message = tr("名称不能为空或全为空格");
        return false;
    }

    QRegularExpression universalIllegalChars(R"([\/\x00-\x1F])");
    if (folder_name.contains(universalIllegalChars)) {
        error_message = tr("名称不能包含以下字符: / 或控制字符");
        return false;
    }

    if (folder_name.length() > 255) {
        error_message = tr("名称长度不能超过 255 字符");
        return false;
    }

#ifdef Q_OS_WIN
    QRegularExpression windows_illegal_chars(R"([<>:"\\|?*])");
    if (folder_name.contains(windows_illegal_chars)) {
        error_message = tr("Windows 文件名不能包含以下字符: <>:\"\\/|?*");
        return false;
    }

    QStringList reserved_names = {
        "CON", "PRN", "AUX", "NUL",
        "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9",
        "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9"
    };
    if (reserved_names.contains(folder_name.toUpper())) {
        error_message = tr("不能使用保留名称（如 CON、LPT1 等）");
        return false;
    }

    if (folder_name.endsWith('.') || folder_name.endsWith(' ')) {
        error_message = tr("名称不能以空格或点结尾");
        return false;
    }

#elif defined(Q_OS_MACOS)
    if (folder_name.contains(':')) {
        error_message = tr("macOS 文件名不能包含冒号 (:)");
        return false;
    }

    if (folder_name.startsWith('.')) {
        error_message = tr("不能以点开头创建隐藏文件");
        return false;
    }
#endif

    return true;
}

void Menu::on_btn_rename_clicked() {
    // 循环直到用户输入合法的文件夹名或取消
    while (true) {
        bool ok = false;
        QString folder_name;
        QString error_message;
        InputDialog dialog;
        connect(&dialog, &InputDialog::inputText, this, [&](const QString& text){
            folder_name = text;
            ok = true;
        });
        dialog.exec();

        if (ok == false) {
            return;
        }
        if (isFolderNameValid(folder_name, error_message)) {
            emit rename(folder_name);
            break;
        } else {
            QMessageBox::warning(this, tr("错误"), error_message);
        }
    }
}


