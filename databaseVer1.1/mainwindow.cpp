#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口属性
    setWindowTitle("主窗口");
    resize(800, 600);
    QWidget *firstPage = new QWidget();


    // 创建显示标签
    displayLabel = new QLabel("初始文本", firstPage);
    displayLabel->setAlignment(Qt::AlignCenter);
    displayLabel->setStyleSheet("border: 1px solid black; padding: 10px;");

    // 创建按钮
    btnSwitch1 = new QPushButton("跳转到视频窗口", this);
    btnSwitch1->setGeometry(100, 125, 200, 150);

    // 连接信号槽
    connect(btnSwitch1, &QPushButton::clicked,
            this, &MainWindow::openVideoWindow);

    btnSwitch2 = new QPushButton("跳转到图像窗口", this);
    btnSwitch2->setGeometry(500, 125, 200, 150);

    // 连接信号槽
    connect(btnSwitch2, &QPushButton::clicked,
            this, &MainWindow::openImageWindow);


}

MainWindow::~MainWindow()
{
}

void MainWindow::openVideoWindow(){
    // 创建并显示新窗口
    videoWindow = new VideoWindow(this);
    videoWindow->show();
    this->hide();

    // 关闭当前窗口
}
void MainWindow::openImageWindow(){
    imageWindow = new ImageWindow(this);
    imageWindow->show();
    this->hide();
}

