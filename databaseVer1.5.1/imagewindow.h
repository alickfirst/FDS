#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H
#include <persondisplaywindow.h>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <mainwindow.h>
#include <modifypersonclass.h>
#include <addpersondialog.h>
#include <QGridLayout>


#include <QLineEdit>
#include <QLabel>

class ModifyPersonDialog;
class ImageWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ImageWindow(QWidget *parent = nullptr);
    ~ImageWindow();
signals:
    void requestShowParent();

public:
    void refreshPersonList();





public slots:

    void onAddPerson();       // 添加人员
    void onDeletePerson();    // 删除人员
    void onQuitAction();
    void onModifyAction();



private:
    // 按钮
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *quitButton;
    QPushButton *modifyButton;

    // 布局和容器
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;

private:
    QWidget *listContainer;      // 列表容器
    QVBoxLayout *listLayout;     // 列表布局


};

#endif // IMAGEWINDOW_
