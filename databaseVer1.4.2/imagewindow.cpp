#include "ImageWindow.h"
#include <QLabel>
#include <QMessageBox>
#include "AddPersonDialog.h"
#include "managesystem.h"
#include <personitem.h>
#include <modifypersonclass.h>


/*********************************重要********************************/
         /*这个其实是人员管理系统的界面，点进入后提供录入照片的功能*/

ImageWindow::ImageWindow(QWidget *parent)
    : QMainWindow(parent) {
    // 设置窗口属性
    setWindowTitle("人员管理系统");
    resize(1600, 900);
    this->setStyleSheet(
        "ImageWindow {"
        "   background-image: url(:/background2.webp);" // 图片背景
        "   background-position: center;"        // 图片居中
        "   background-size: cover;"             // 自适应缩放
        "}"
    );
    //创建列表项




    // 创建中央部件
    centralWidget = new QWidget(this);
    centralWidget->setStyleSheet("background-color: transparent;"); // 设置透明背景以显示主窗口背景图

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);

    // ================= 左侧滚动区域 =================
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);  // 关键设置：允许内部widget调整大小
    scrollArea->setStyleSheet("QScrollArea { border: none; }");

    // 创建列表容器
    listContainer = new QWidget();
    listContainer->setStyleSheet(
        "background-color: transparent;"
        "border: 2px solid #B0B0B0;"
        "border-radius: 8px;"
        "padding: 2px;"
    );
    listContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 设置列表布局
    listLayout = new QVBoxLayout(listContainer);
    listLayout->setContentsMargins(5, 5, 5, 5);
    listLayout->setSpacing(10);

    // 将列表容器设置为滚动区域的widget
    scrollArea->setWidget(listContainer);

    // 将滚动区域添加到主布局（占据70%空间）
    mainLayout->addWidget(scrollArea, 7);  // 拉伸因子7



    // ================= 右侧内容区域 =================
    QWidget *rightContainer = new QWidget(centralWidget);
    rightContainer->setFixedWidth(500); // 固定宽度使按钮区域不会过宽
    rightContainer->setStyleSheet("background-color: rgba(255, 255, 255, 200); border-radius: 15px;");

    QVBoxLayout *rightLayout = new QVBoxLayout(rightContainer);
    rightLayout->setContentsMargins(40, 30, 40, 30); // 内部边距
    rightLayout->setSpacing(20);

    mainLayout->addWidget(rightContainer);

    // 添加标题
    QLabel *titleLabel = new QLabel("人员管理系统", rightContainer);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel {"
                             "  font-size: 36px;"
                             "  font-weight: bold;"
                             "  color: #2C3E50;"
                             "  padding: 20px;"
                             "  margin-bottom: 20px;"
                             "  background-color: rgba(173, 216, 230, 150);"  // 淡蓝色背景
                             "  border-radius: 10px;"
                             "}");
    rightLayout->addWidget(titleLabel);

    // 创建按钮容器
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->setSpacing(25);
    buttonLayout->setContentsMargins(0, 0, 0, 0);

    // 创建按钮
    modifyButton = new QPushButton("修改信息",rightContainer);
    addButton = new QPushButton("添加人员", rightContainer);
    deleteButton = new QPushButton("删除人员", rightContainer);
    quitButton = new QPushButton("返回上一个界面", rightContainer);

    // 使用现代字体
    QString fontFamily = "Segoe UI, Microsoft YaHei, sans-serif";

    // 淡色系按钮样式
    QString lightBlueStyle = "QPushButton {"
                             "  background-color: rgba(173, 216, 230, 180);"  // 淡蓝色
                             "  color: #2C3E50;"
                             "  border-radius: 8px;"
                             "  padding: 15px;"
                             "  font-size: 24px;"
                             "  min-height: 60px;"
                             "  font-weight: bold;"
                             "  border: none;"
                             "  font-family: '" + fontFamily + "';"
                             "}"
                             "QPushButton:hover {"
                             "  background-color: rgba(135, 206, 250, 200);"  // 悬停时更亮的淡蓝
                             "  transform: translateY(-2px);"
                             "  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);"
                             "}"
                             "QPushButton:pressed {"
                             "  background-color: rgba(100, 149, 237, 220);"
                             "}";

    QString lightYellowStyle = "QPushButton {"
                               "  background-color: rgba(255, 250, 205, 180);"  // 淡黄色
                               "  color: #2C3E50;"
                               "  border-radius: 8px;"
                               "  padding: 15px;"
                               "  font-size: 24px;"
                               "  min-height: 60px;"
                               "  font-weight: bold;"
                               "  border: none;"
                               "  font-family: '" + fontFamily + "';"
                               "}"
                               "QPushButton:hover {"
                               "  background-color: rgba(255, 255, 153, 200);"  // 悬停时更亮的淡黄
                               "  transform: translateY(-2px);"
                               "  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);"
                               "}"
                               "QPushButton:pressed {"
                               "  background-color: rgba(255, 215, 0, 220);"
                               "}";
    QString lightGreenStyle = "QPushButton {"
                              "  background-color: rgba(144, 238, 144, 180);"  // 淡绿色
                              "  color: #2C3E50;"
                              "  border-radius: 8px;"
                              "  padding: 15px;"
                              "  font-size: 24px;"
                              "  min-height: 60px;"
                              "  font-weight: bold;"
                              "  border: none;"
                              "  font-family: '" + fontFamily + "';"
                              "}"
                              "QPushButton:hover {"
                              "  background-color: rgba(152, 251, 152, 200);"  // 悬停时更亮的淡绿
                              "  transform: translateY(-2px);"
                              "  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);"
                              "}"
                              "QPushButton:pressed {"
                              "  background-color: rgba(50, 205, 50, 220);"    // 按下时深绿色
                              "}";

    // 应用不同的淡色样式
    addButton->setStyleSheet(lightYellowStyle);
    deleteButton->setStyleSheet(lightBlueStyle);
    modifyButton->setStyleSheet(lightGreenStyle);

    // 退出按钮使用特殊样式
    QString quitButtonStyle = "QPushButton {"
                              "  background-color: rgba(255, 228, 225, 180);"  // 淡粉色
                              "  color: #2C3E50;"
                              "  border-radius: 8px;"
                              "  padding: 15px;"
                              "  font-size: 24px;"
                              "  min-height: 60px;"
                              "  font-weight: bold;"
                              "  border: none;"
                              "  font-family: '" + fontFamily + "';"
                              "}"
                              "QPushButton:hover {"
                              "  background-color: rgba(255, 182, 193, 200);"  // 悬停时更亮的粉色
                              "  transform: translateY(-2px);"
                              "  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);"
                              "}"
                              "QPushButton:pressed {"
                              "  background-color: rgba(219, 112, 147, 220);"
                              "}";
    quitButton->setStyleSheet(quitButtonStyle);

    // 添加按钮到布局

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(modifyButton);
    buttonLayout->addWidget(quitButton);

    // 添加按钮布局到右侧容器
    rightLayout->addLayout(buttonLayout);
    rightLayout->addStretch(1);  // 添加弹性空间使按钮居中
    mainLayout->addWidget(rightContainer, 3);

    // 设置中央部件
    setCentralWidget(centralWidget);

    // 连接信号和槽
    connect(addButton, &QPushButton::clicked, this, &ImageWindow::onAddPerson);
    connect(deleteButton, &QPushButton::clicked, this, &ImageWindow::onDeletePerson);
    connect(quitButton, &QPushButton::clicked, this, &ImageWindow::onQuitAction);
    connect(modifyButton, &QPushButton::clicked, this, &ImageWindow::onModifyAction);
}

ImageWindow::~ImageWindow() {}



void ImageWindow::onAddPerson() {
    AddPersonDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        int id = dialog.getID();
        QString name = dialog.getName();
        QString department = dialog.getDepartment();

        ManageSystem* system = ManageSystem::getInstance();

        if (system->addPerson(id, name, department)) {
            // 成功添加 - 使用无图标对话框
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("添加成功");
            msgBox.setIcon(QMessageBox::NoIcon);
            msgBox.setText(QString("成功添加人员:\nID: %1\n姓名: %2\n部门: %3")
                          .arg(id).arg(name).arg(department));
            msgBox.exec();
        } else {
            // 添加失败 - 使用无图标对话框
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("添加失败");
            msgBox.setIcon(QMessageBox::NoIcon);
            msgBox.setText(QString("ID %1 已存在，请使用不同的ID").arg(id));
            msgBox.exec();
        }
    }
}


void ImageWindow::onQuitAction(){

    emit requestShowParent();

    this->close();
}

void ImageWindow::onModifyAction() {
    // 获取要修改的人员ID
    bool ok;
    int id = QInputDialog::getInt(this, "修改人员",
                                "请输入要修改的人员ID:",
                                0, 0, INT_MAX, 1, &ok);
    if (!ok) return;

    // 查询人员信息
    ManageSystem* system = ManageSystem::getInstance();
    Person* target = system->queryById(id);

    if (!target) {
        QMessageBox::critical(this, "错误", "该ID不存在！");
        return;
    }

    // 获取新信息（非UI方式实现）
    QString newName = QInputDialog::getText(this, "修改姓名",
                                          "请输入新姓名:",
                                          QLineEdit::Normal,
                                          target->getName(), &ok);
    if (!ok) return;

    QString newDept = QInputDialog::getText(this, "修改部门",
                                          "请输入新部门:",
                                          QLineEdit::Normal,
                                          target->getDepartment(), &ok);
    if (!ok) return;

    // 执行修改操作
    if (system->modifyPerson(id, newName, newDept)) {
        QMessageBox::information(this, "成功",
            QString("ID %1 信息已更新\n新姓名：%2\n新部门：%3")
                .arg(id).arg(newName).arg(newDept));

        // 刷新显示（如果需要）
    } else {
        QMessageBox::warning(this, "失败",
            "修改失败，可能原因：\n"
            "1. 新姓名已存在\n"
            "2. 数据未发生变化");
    }
}



void ImageWindow::onDeletePerson() {

    bool ok;
    int id = QInputDialog::getInt(this, "删除人员",
                                "请输入要删除的人员ID:",
                                0, 1, 2147483647, 1, &ok);
    if (!ok) return;

    ManageSystem* system = ManageSystem::getInstance();

    // 先尝试获取人员信息
    Person* target = system->queryById(id);

    if (target) {
        QMessageBox infoBox(this);
        infoBox.setWindowTitle("待删除人员信息");
        infoBox.setIcon(QMessageBox::Question);

        // 构建详细信息文本
        QString infoText = QString(
            "<p style='font-size: 14px;'>"
            "<b>ID：</b>%1<br/>"
            "<b>姓名：</b>%2<br/>"
            "<b>部门：</b>%3<br/>"
            "</p>"
            "<p style='color: #666; margin-top: 15px;'>"
            "确认要删除该人员吗？"
            "</p>"
        ).arg(id)
         .arg(target->getName())
         .arg(target->getDepartment());

        infoBox.setText(infoText);
        infoBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        infoBox.setDefaultButton(QMessageBox::No);

        if (infoBox.exec() == QMessageBox::Yes) {
            if (system->deletePerson(id)) {
                QMessageBox msgBox(this);
                msgBox.setWindowTitle("删除成功");
                msgBox.setIcon(QMessageBox::NoIcon);
                msgBox.setText(QString("ID %1 的人员已删除\n")
                              .arg(id));

                msgBox.exec(); // 添加此行显示对话框
            }
        }
    } else {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("删除失败");
        msgBox.setIcon(QMessageBox::NoIcon);
        msgBox.setText(QString("ID %1 不存在\n").arg(id));
        msgBox.exec();
    }
}
