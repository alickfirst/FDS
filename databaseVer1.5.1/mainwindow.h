#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "videowindow.h"
#include <QMainWindow>
#include <QPushButton>
#include "imagewindow.h"
#include <QObject>
#include <QMap>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QVector>
#include <person.h>
#include <QMultiHash>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFontDialog>
#include <QVBoxLayout>
#include <QTabWidget>
#include <scalebackgroundwidget.h>
class VideoWindow;
class ImageWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openVideoWindow();
    void openImageWindow();
    void showParentWindowImage();
    void showParentWindowVideo();
private:
    QTabWidget *tabWidget;
    QLabel *displayLabel;
    QLineEdit *textInput;
    QPushButton *fontButton;

    QPushButton *btnSwitch1;
    QPushButton *btnSwitch2;
    VideoWindow *videoWindow;
    ImageWindow* imageWindow = nullptr;

};

#endif // MAINWINDOW_H
