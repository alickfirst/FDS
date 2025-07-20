#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口属性
    setWindowTitle("主窗口");
    resize(1200, 960);
    QWidget *firstPage = new QWidget();


    // 创建显示标签
    displayLabel = new QLabel("初始文本", firstPage);
    displayLabel->setAlignment(Qt::AlignCenter);
    displayLabel->setStyleSheet("border: 1px solid black; padding: 10px;");

    // 创建按钮
    btnSwitch = new QPushButton("跳转到新窗口", this);
    btnSwitch->resize(400,300);
    btnSwitch->setGeometry(500, 130, 150, 150);

    // 连接信号槽
    connect(btnSwitch, &QPushButton::clicked,
            this, &MainWindow::openSecondWindow);

}

MainWindow::~MainWindow()
{
}

void MainWindow::openSecondWindow()
{
    // 创建并显示新窗口
    secondWindow = new SecondWindow();
    secondWindow->show();

    // 关闭当前窗口
    this->close();
}
