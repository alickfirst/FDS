#include "ImageWindow.h"
#include <QLabel>
#include <QMessageBox>
#include "AddPersonDialog.h"
#include "managesystem.h"


/*********************************重要********************************/
         /*这个其实是人员管理系统的界面，点进入后提供录入照片的功能*/

ImageWindow::ImageWindow(QWidget *parent)
    : QMainWindow(parent) {
    // 设置窗口属性
    setWindowTitle("人员管理系统");
    resize(1600, 900);
    this->setStyleSheet(
        "ImageWindow {"
        "   background-image: url(:/background2.png);" // 图片背景
        "   background-position: center;"        // 图片居中
        "   background-size: cover;"             // 自适应缩放
        "}"
    );

    // 创建中央部件
    centralWidget = new QWidget(this);
    centralWidget->setStyleSheet("background-color: transparent;"); // 设置透明背景以显示主窗口背景图

    // 使用水平布局将内容靠右对齐
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 50, 100); // 右侧和下边留出空间
    mainLayout->setSpacing(0);

    // 左侧弹簧 - 将内容推到右侧
    mainLayout->addStretch(1);

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
    viewButton = new QPushButton("查看现有人员", rightContainer);
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

    // 应用不同的淡色样式
    viewButton->setStyleSheet(lightBlueStyle);
    addButton->setStyleSheet(lightYellowStyle);
    deleteButton->setStyleSheet(lightBlueStyle);

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
    buttonLayout->addWidget(viewButton);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(quitButton);

    // 添加按钮布局到右侧容器
    rightLayout->addLayout(buttonLayout);
    rightLayout->addStretch(1);  // 添加弹性空间使按钮居中

    // 设置中央部件
    setCentralWidget(centralWidget);

    // 连接信号和槽
    connect(viewButton, &QPushButton::clicked, this, &ImageWindow::onViewPersonnel);
    connect(addButton, &QPushButton::clicked, this, &ImageWindow::onAddPerson);
    connect(deleteButton, &QPushButton::clicked, this, &ImageWindow::onDeletePerson);
    connect(quitButton, &QPushButton::clicked, this, &ImageWindow::onQuitAction);
}

ImageWindow::~ImageWindow() {}



void ImageWindow::onAddPerson() {
    AddPersonDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        // 获取用户输入
        int id = dialog.getID();
        QString name = dialog.getName();
        QString department = dialog.getDepartment();

        ManageSystem* system = ManageSystem::getInstance();

        if (system->addPerson(id, name, department)) {
            // 成功添加 - 显示信息框
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("添加成功");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setMinimumSize(800, 600);
            msgBox.setText(QString("成功添加人员:\nID: %1\n姓名: %2\n部门: %3")
                          .arg(id).arg(name).arg(department));
            msgBox.exec(); // 关键：需要调用 exec() 显示对话框
        } else {
            // 添加失败 - 显示警告
            QMessageBox::warning(this, "添加失败",
                                QString("ID %1 已存在，请使用不同的ID").arg(id));
        }
    }
}

void ImageWindow::onDeletePerson() {
    QMessageBox::information(this, "删除人员", "删除人员功能");
    // 这里将调用ManageSystem的deletePerson方法
}
void ImageWindow::onViewPersonnel(){
    QMessageBox::information(this, "尚未实现", "敬请期待");
}

void ImageWindow::onQuitAction(){
    // 发出返回主窗口的信号
    emit requestShowParent();

    // 关闭当前窗口
    this->close();
}

