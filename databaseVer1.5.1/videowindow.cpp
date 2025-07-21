#include "videowindow.h"




/*************************重要****************************/
/*这个其实是人脸识别界面*/
/*页面内含多个button，按照功能实现获取照片，比对等功能*/
/*此页面主要功能要用openCV实现*/


VideoWindow::VideoWindow(QWidget *parent)
    :QMainWindow(parent)
{
    // 设置窗口属性
     setWindowTitle("图像处理窗口");
     resize(1600, 900);

     // 创建中央部件
     QWidget *centralWidget = new QWidget(this);
     setCentralWidget(centralWidget);

     // 主布局 - 垂直
     QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
     mainLayout->setSpacing(20);
     mainLayout->setContentsMargins(20, 20, 20, 20);


     QHBoxLayout *topButtonLayout = new QHBoxLayout();

     // 打开图片按钮 (左上角)
     openImageButton = new QPushButton("打开图片");
     openImageButton->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
     openImageButton->setMinimumSize(120, 40);
     openImageButton->setStyleSheet("QPushButton {"
                                   "  background-color: #4CAF50;"
                                   "  color: white;"
                                   "  font-weight: bold;"
                                   "  border-radius: 5px;"
                                   "  padding: 8px;"
                                   "}");

     // 返回按钮
     btnBack = new QPushButton("返回");
     btnBack->setIcon(style()->standardIcon(QStyle::SP_ArrowBack));
     btnBack->setMinimumSize(120, 40);
     btnBack->setStyleSheet("QPushButton {"
                              "  background-color: #2196F3;"
                              "  color: white;"
                              "  font-weight: bold;"
                              "  border-radius: 5px;"
                              "  padding: 8px;"
                              "}");

     // 切换视频模式按钮
     switchVideoButton = new QPushButton("切换视频模式");
     switchVideoButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
     switchVideoButton->setMinimumSize(150, 40);
     switchVideoButton->setStyleSheet("QPushButton {"
                                     "  background-color: #FF9800;"
                                     "  color: white;"
                                     "  font-weight: bold;"
                                     "  border-radius: 5px;"
                                     "  padding: 8px;"
                                     "}");

     // 添加到顶部布局
     topButtonLayout->addWidget(openImageButton);
     topButtonLayout->addWidget(btnBack);
     topButtonLayout->addWidget(switchVideoButton);
     topButtonLayout->addStretch(); // 添加弹性空间

     mainLayout->addLayout(topButtonLayout);

     // ================= 图片显示区域 =================
     imageDisplay = new QLabel("图片显示区域");
     imageDisplay->setAlignment(Qt::AlignCenter);
     imageDisplay->setStyleSheet(
         "QLabel {"
         "   background-color: #F0F0F0;"
         "   border: 2px dashed #C0C0C0;"
         "   border-radius: 10px;"
         "   color: #808080;"
         "   font-size: 24px;"
         "   padding: 20px;"
         "}"
     );
     imageDisplay->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     mainLayout->addWidget(imageDisplay, 1);  // 设置伸缩因子为1

     // ================= 底部按钮区域 =================
     QHBoxLayout *bottomButtonLayout = new QHBoxLayout();

     // 左侧按钮
     leftButton = new QPushButton("左侧功能");
     leftButton->setMinimumSize(150, 50);
     leftButton->setStyleSheet("QPushButton {"
                              "  background-color: #9C27B0;"
                              "  color: white;"
                              "  font-size: 16px;"
                              "  border-radius: 5px;"
                              "}");

     // 右侧按钮
     rightButton = new QPushButton("右侧功能");
     rightButton->setMinimumSize(150, 50);
     rightButton->setStyleSheet("QPushButton {"
                               "  background-color: #E91E63;"
                               "  color: white;"
                               "  font-size: 16px;"
                               "  border-radius: 5px;"
                               "}");

     // 添加到底部布局
     bottomButtonLayout->addWidget(leftButton);
     bottomButtonLayout->addStretch();  // 添加弹性空间使按钮分开
     bottomButtonLayout->addWidget(rightButton);

     mainLayout->addLayout(bottomButtonLayout);
     connect(btnBack,&QPushButton::clicked,this, &VideoWindow::onBackButtonClicked);
}
void VideoWindow::onBackButtonClicked()
{
        // 发出返回主窗口的信号
        emit requestShowParent();

        // 关闭当前窗口
        this->close();
}

VideoWindow::~VideoWindow()
{

}
