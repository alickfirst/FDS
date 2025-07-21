#ifndef ADDPERSONDIALOG_H
#define ADDPERSONDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <Qstring>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class ModifyPersonDialog : public QDialog {
    Q_OBJECT

public:
    explicit ModifyPersonDialog(QWidget *parent = nullptr);
    ~ModifyPersonDialog();

    int getID() const;
    QString getName() const;
    QString getDepartment() const;

private slots:
    void onAddClicked();
    void validateInput();

private:
    QLineEdit *idEdit;
    QLineEdit *nameEdit;
    QLineEdit *departmentEdit;
    QPushButton *addButton;
    QPushButton *cancelButton;
    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QHBoxLayout *buttonLayout;
};

#endif // ADDPERSONDIALOG_H
