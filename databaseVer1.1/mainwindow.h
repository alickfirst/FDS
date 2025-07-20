#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <videowindow.h>
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
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFontDialog>
#include <QVBoxLayout>
#include <QTabWidget>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openVideoWindow();
    void openImageWindow();
private:
    QTabWidget *tabWidget;
    QLabel *displayLabel;
    QLineEdit *textInput;
    QPushButton *fontButton;
private:
    QPushButton *btnSwitch1;
    QPushButton *btnSwitch2;
    VideoWindow *videoWindow;
    ImageWindow *imageWindow;
};

#endif // MAINWINDOW_H
