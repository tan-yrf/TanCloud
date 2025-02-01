#include <QInputDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QtGlobal>

#include "Home.h"
#include "ui_Home.h"

Home::Home(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::Home) {
    ui->setupUi(this);
    connect(ui->explorer, &Explorer::pathChanged, this, &Home::onPathChanged);
    connect(ui->explorer, &Explorer::countChanged, this, &Home::onCountChanged);
}

Home::~Home()
{
    delete ui;
}

void Home::root() const {
    ui->explorer->cd("");
}

bool Home::isFolderNameValid(const QString &folder_name, QString &error_message) {
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

void Home::on_btn_pattern_clicked() {
    if (m_pattern == Pattern::List) {
        ui->explorer->setImagePattern();
        m_pattern = Pattern::Image;
        ui->btn_pattern->setIcon(QIcon(":/FIle/cell.svg"));
        ui->btn_pattern->setToolTip(u8"缩略图");
    } else if(m_pattern == Pattern::Image) {
        ui->explorer->setListPattern();
        m_pattern = Pattern::List;
        ui->btn_pattern->setIcon(QIcon(":/FIle/list.svg"));
        ui->btn_pattern->setToolTip(u8"列表");
    }
}


void Home::on_btn_refresh_clicked() {
    ui->explorer->refresh();
}


void Home::on_btn_home_clicked() {
    ui->explorer->cd("");
}


void Home::on_btn_bak_clicked() {
    ui->explorer->back();
}

void Home::onPathChanged(QString path) {
    if (path == '.')
        ui->lab_path->setText("");
    else
        ui->lab_path->setText(path);
}

void Home::onCountChanged(int selected, int sum) {
    if (selected == 0){
        ui->lab_count->setText(" ");
    } else {
        ui->lab_count->setText(tr(u8"已选中%1个文件/文件夹").arg(selected));
    }
}

void Home::on_create_folder_clicked() {
    bool ok = false;
    QString folder_name;
    QString error_message;
    // 循环直到用户输入合法的文件夹名或取消
    while (true) {
        folder_name = QInputDialog::getText(this, tr("输入文件夹名"), tr("请输入文件夹名"), QLineEdit::Normal, "", &ok);
        if (!ok) {
            return;
        }
        if (isFolderNameValid(folder_name, error_message)) {
            break;
        } else {
            QMessageBox::warning(this, tr("错误"), error_message);
        }
    }

    QString message;
    if (ui->explorer->createFolder(message, folder_name) == true) {
        QMessageBox::information(this, tr("成功"), tr("文件夹创建成功"));
    } else {
        QMessageBox::information(this, tr("失败"), tr("文件夹创建失败"));
    }
}


void Home::on_btn_delete_clicked() {
    QMessageBox msg_box;
    msg_box.setWindowIcon(QIcon(":/ico.svg"));
    msg_box.setWindowTitle(tr("确认删除"));
    msg_box.setText(tr("您确定要彻底删除吗？"));
    msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    msg_box.button(QMessageBox::Yes)->setText(tr("确定"));
    msg_box.button(QMessageBox::No)->setText(tr("取消"));
    int reply = msg_box.exec();
    if (reply == QMessageBox::Yes) {
        QString message;
        ui->explorer->deleteSelected(message);

        QMessageBox msg;
        msg.setWindowIcon(QIcon(":/ico.svg"));
        msg.setIcon(QMessageBox::Information);
        msg.setWindowTitle(" ");
        msg.setText(message);
        msg.addButton(QMessageBox::Ok);
        msg.button(QMessageBox::Ok)->hide();
        msg.exec();
    }
}

void Home::on_box_select_all_stateChanged(int state) {
    qDebug() << state;
    if (state == 0) {
        ui->explorer->checkAll(false);
    } else {
        ui->explorer->checkAll(true);
    }
}

