#ifndef PERSONDISPLAYWINDOW_H
#define PERSONDISPLAYWINDOW_H
#include <QtWidgets>
#include "ManageSystem.h"
#include <addpersondialog.h>
#include <imagewindow.h>
class PersonDisplayWindow : public QWidget {
    Q_OBJECT
public:
    explicit PersonDisplayWindow(QWidget *parent = nullptr);

private slots:
    void refreshTable();
    void onDeleteClicked();
    void onAddClicked();
    void onCellDoubleClicked(int row, int column);

private:
    QTableWidget *table;
    QLineEdit *searchEdit;
    ManageSystem *system;
};


#endif // PERSONDISPLAYWINDOW_H
