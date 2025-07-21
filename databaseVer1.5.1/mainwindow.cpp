#include "mainwindow.h"






/*********************************重要********************************/
/*用于创建初始页面，内涵两个button,可以转到另外两个页面*/





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口属性
    setWindowTitle("主窗口");
    resize(1600,900);
    QWidget *firstPage = new QWidget();
    this->setStyleSheet(
        "MainWindow {"
        "   background-image: url(:/ims.webp);"
        "   background-repeat: no-repeat;"    // 禁止平铺
        "   background-position: center;"     // 居中显示
        "   background-size: 100%;"          // 关键：覆盖整个窗口（可能裁剪）
        "}"
    );


    // 创建显示标签
    displayLabel = new QLabel("初始文本", firstPage);
    displayLabel->setAlignment(Qt::AlignCenter);
    displayLabel->setStyleSheet("border: 1px solid black; padding: 10px;");

    // 创建按钮
    btnSwitch1 = new QPushButton("跳转到视频窗口", this);
    btnSwitch1->setGeometry(800, 125, 600, 300);
    btnSwitch1->setStyleSheet(
                "QPushButton {"
                "  background-color: rgba(173, 216, 230, 70);"  // 浅蓝色背景，带透明度
                "  color: white;"                              // 深蓝色文字提高对比度
                "  border-radius: 8px;"                          // 圆角
                "  padding: 15px;"                               // 内边距
                "  font-size: 36px;"                             // 字体大小
                "  min-height: 60px;"                            // 最小高度
                "  font-weight: bold;"                           // 加粗
                "  border: none;"                                // 无边框
                "  font-family:'Microsoft YaHei';" // 现代无衬线字体
                "}"
                "QPushButton:hover {"
                "  background-color: rgba(135, 206, 250, 200);"  // 悬停时更亮的浅蓝色
                "  transform: translateY(-2px);"                 // 轻微上浮效果
                "  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);"    // 添加阴影增强浮起效果
                "}"
                "QPushButton:pressed {"
                "  background-color: rgba(100, 149, 237, 220);"  // 按下时深一点的浅蓝色
                "  transform: translateY(0);"                    // 取消上浮
                "}"
    );
    btnSwitch2 = new QPushButton("跳转到图像窗口", this);
    btnSwitch2->setGeometry(800, 525, 600, 300);

    // 连接信号槽
    btnSwitch2->setStyleSheet(
                "QPushButton {"
                "  background-color: rgba(173, 216, 230, 70);"  // 浅蓝色背景，带透明度
                "  color: white;"                              // 深蓝色文字提高对比度
                "  border-radius: 8px;"                          // 圆角
                "  padding: 15px;"                               // 内边距
                "  font-size: 36px;"                             // 字体大小
                "  min-height: 60px;"                            // 最小高度
                "  font-weight: bold;"                           // 加粗
                "  border: none;"                                // 无边框
                "  font-family:  'Microsoft YaHei';" // 现代无衬线字体
                "}"
                "QPushButton:hover {"
                "  background-color: rgba(135, 206, 250, 200);"  // 悬停时更亮的浅蓝色
                "  transform: translateY(-2px);"                 // 轻微上浮效果
                "  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);"    // 添加阴影增强浮起效果
                "}"
                "QPushButton:pressed {"
                "  background-color: rgba(100, 149, 237, 220);"  // 按下时深一点的浅蓝色
                "  transform: translateY(0);"                    // 取消上浮
                "}"
    );

    // 连接信号槽
    connect(btnSwitch1, &QPushButton::clicked,
            this, &MainWindow::openVideoWindow);


    connect(btnSwitch2, &QPushButton::clicked,
            this, &MainWindow::openImageWindow);


}
void MainWindow::openVideoWindow(){
    videoWindow = new VideoWindow();
    videoWindow->setWindowFlags(Qt::Window);

    // 连接子窗口的返回信号到父窗口的槽
    connect(videoWindow, &VideoWindow::requestShowParent, this, &MainWindow::showParentWindowVideo);

    videoWindow->show();
    this->hide();
}
void MainWindow::openImageWindow(){
    imageWindow = new ImageWindow();
    imageWindow->setWindowFlags(Qt::Window);

    // 连接子窗口的返回信号到父窗口的槽
    connect(imageWindow, &ImageWindow::requestShowParent, this, &MainWindow::showParentWindowImage);

    imageWindow->show();
    this->hide();
}
void MainWindow::showParentWindowImage() {
    this->show();

    // 清理图像窗口指针
    if (imageWindow) {
        imageWindow->deleteLater();  // 安全删除窗口
        imageWindow = nullptr;       // 防止野指针
    }
}
void MainWindow::showParentWindowVideo() {
    this->show();

    // 清理图像窗口指针
    if (videoWindow) {
        videoWindow->deleteLater();  // 安全删除窗口
        videoWindow = nullptr;       // 防止野指针
    }
}


MainWindow::~MainWindow()
{
}



