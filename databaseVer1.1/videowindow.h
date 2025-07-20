#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class VideoWindow : public QMainWindow
{
    Q_OBJECT
public:
    VideoWindow(QWidget *parent = nullptr);
    ~VideoWindow();
    void onBackButtonClicked();  // 新增槽函数
private:
    QLabel *lbInfo;
    QLabel *lbInfo2;
    QPushButton *btnBack;

};


#endif // VIDEOWINDOW_H
