#include "videowindow.h"

VideoWindow::VideoWindow(QWidget *parent)
    :QMainWindow(parent)
{
    setWindowTitle("新窗口");
    resize(800, 600);

    // 添加提示标签
    lbInfo = new QLabel("这是第二个窗口", this);
    lbInfo->setGeometry(0, 100, 200, 150);
    lbInfo->setAlignment(Qt::AlignCenter);
    lbInfo2 = new QLabel("这里理论上可以图像识别", this);
    lbInfo2->setGeometry(400, 100, 400, 150);
    lbInfo2->setAlignment(Qt::AlignCenter);

    btnBack = new QPushButton("返回上个界面", this);
    btnBack->setGeometry(150,400,300,100);
    connect(btnBack,&QPushButton::clicked,this, &VideoWindow::onBackButtonClicked);
}
void VideoWindow::onBackButtonClicked(){

    if(parentWidget()) {
        parentWidget()->show();  // 显示父窗口
        this->hide();            // 隐藏当前窗口
    }
}

VideoWindow::~VideoWindow()
{

}
