#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H
#include <persondisplaywindow.h>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <mainwindow.h>
class ImageWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ImageWindow(QWidget *parent = nullptr);
    ~ImageWindow();
signals:
    void requestShowParent();





public slots:
    void onViewPersonnel();   // 查看人员
    void onAddPerson();       // 添加人员
    void onDeletePerson();    // 删除人员
    void onQuitAction();


private:
    // 按钮
    QPushButton *viewButton;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *quitButton;

    // 布局和容器
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;


};

#endif // IMAGEWINDOW_
