#include "ImageWindow.h"
#include <QLabel>
#include <QMessageBox>
#include "AddPersonDialog.h"
#include "managesystem.h"

ImageWindow::ImageWindow(QWidget *parent)
    : QMainWindow(parent) {
    // 设置窗口属性
    setWindowTitle("人员管理系统");
    resize(800, 600);  // 稍微增大窗口尺寸

    // 创建中央部件和布局
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    // 创建按钮
    viewButton = new QPushButton("查看现有人员", centralWidget);
    addButton = new QPushButton("添加人员", centralWidget);
    deleteButton = new QPushButton("删除人员", centralWidget);
    quitButton = new QPushButton("返回上一个界面", centralWidget);

    // 方法1：使用样式表设置字体大小
    QString buttonStyle = "QPushButton {"
                          "  background-color: #4A90E2;"
                          "  color: white;"
                          "  border-radius: 5px;"
                          "  padding: 12px;"  // 增加内边距
                          "  font-size: 16px;"  // 设置字体大小为16px
                          "  min-height: 50px;"  // 设置最小高度
                          "}"
                          "QPushButton:hover {"
                          "  background-color: #357ABD;"
                          "}";

    viewButton->setStyleSheet(buttonStyle);
    addButton->setStyleSheet(buttonStyle);
    deleteButton->setStyleSheet(buttonStyle);
    quitButton->setStyleSheet(buttonStyle);

    // 添加按钮到布局
    mainLayout->addWidget(viewButton);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(deleteButton);
    mainLayout->addWidget(quitButton);

    // 添加标题
    QLabel *titleLabel = new QLabel("人员管理系统", centralWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel {"
                             "  font-size: 24px;"  // 增大标题字体
                             "  font-weight: bold;"
                             "  color: #333333;"
                             "  padding: 20px;"
                             "}");
    mainLayout->insertWidget(0, titleLabel);

    // 设置布局间距
    mainLayout->setSpacing(20);  // 增加按钮间距
    mainLayout->setContentsMargins(40, 20, 40, 40);  // 增加边距

    // 设置中央部件
    setCentralWidget(centralWidget);

    // 连接信号和槽
    connect(viewButton, &QPushButton::clicked, this, &ImageWindow::onViewPersonnel);
    connect(addButton, &QPushButton::clicked, this, &ImageWindow::onAddPerson);
    connect(deleteButton, &QPushButton::clicked, this, &ImageWindow::onDeletePerson);
    connect(quitButton, &QPushButton::clicked, this, &QMainWindow::close);


    // 设置中央部件
    setCentralWidget(centralWidget);

    // 连接信号和槽
    connect(viewButton, &QPushButton::clicked, this, &ImageWindow::onViewPersonnel);
    connect(addButton, &QPushButton::clicked, this, &ImageWindow::onAddPerson);
    connect(deleteButton, &QPushButton::clicked, this, &ImageWindow::onDeletePerson);
    connect(quitButton,&QPushButton::clicked,this,&ImageWindow::onQuitAction);
}

ImageWindow::~ImageWindow() {}

void ImageWindow::onViewPersonnel() {
    QMessageBox::information(this, "查看人员", "查看现有人员功能");
    // 这里将调用ManageSystem的query方法
}

void ImageWindow::onAddPerson() {
    AddPersonDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        // 获取用户输入
        int id = dialog.getID();
        QString name = dialog.getName();
        QString department = dialog.getDepartment();

        ManageSystem* system = ManageSystem::getInstance();

        if (system->addPerson(id, name, department)) {
            QMessageBox::information(this, "添加成功",
                                   QString("成功添加人员:\nID: %1\n姓名: %2\n部门: %3")
                                   .arg(id).arg(name).arg(department));
        } else {
            QMessageBox::warning(this, "添加失败",
                                QString("ID %1 已存在，请使用不同的ID").arg(id));
        }
    }
}

void ImageWindow::onDeletePerson() {
    QMessageBox::information(this, "删除人员", "删除人员功能");
    // 这里将调用ManageSystem的deletePerson方法
}
void ImageWindow::onQuitAction() {
    if(parentWidget()) {
        parentWidget()->show();  // 显示父窗口
        this->hide();            // 隐藏当前窗口
    }
}
