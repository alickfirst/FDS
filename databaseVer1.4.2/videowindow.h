#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <mainwindow.h>

class VideoWindow : public QMainWindow
{
    Q_OBJECT
public:
    VideoWindow(QWidget *parent = nullptr);
    ~VideoWindow();
    void onBackButtonClicked();// 新增槽函数
signals:
    void requestShowParent();
private:
    QLabel *lbInfo;
    QLabel *lbInfo2;
    QPushButton *btnBack;
    QPushButton *openImageButton;
    QPushButton *switchVideoButton;
    QLabel *imageDisplay;
    QPushButton *leftButton;
    QPushButton *rightButton;


};


#endif // VIDEOWINDOW_H
