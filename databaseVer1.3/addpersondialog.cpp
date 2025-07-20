#include "addpersondialog.h"
#include<ioexception.h>

AddPersonDialog::AddPersonDialog(QWidget *parent)
    :QDialog(parent)
{setWindowTitle("添加新人员");
    setFixedSize(800,600);
    mainLayout = new QVBoxLayout(this);

    formLayout = new QFormLayout();

    idEdit = new QLineEdit(this);
    idEdit->setPlaceholderText("请输入唯一ID");
    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("请输入姓名");
    departmentEdit = new QLineEdit(this);
    departmentEdit->setPlaceholderText("请输入部门");

    QString inputStyle = "QLineEdit {"
                             "  padding: 16px;"
                             "  font-size: 20px;"
                             "  border: 1px solid #ccc;"
                             "  border-radius: 6px;"
                             "}";
    idEdit->setStyleSheet(inputStyle);
    nameEdit->setStyleSheet(inputStyle);
    departmentEdit->setStyleSheet(inputStyle);


    formLayout->addRow("ID:", idEdit);
    formLayout->addRow("姓名:", nameEdit);
    formLayout->addRow("部门:", departmentEdit);

    // 按钮布局
    buttonLayout = new QHBoxLayout();

    // 提示按钮
    addButton = new QPushButton("添加", this);
    cancelButton = new QPushButton("取消", this);

    buttonLayout->addStretch();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    // 添加所有布局到主布局
    mainLayout->addLayout(formLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    connect(addButton,&QPushButton::clicked,this,&AddPersonDialog::onAddClicked);
    connect(cancelButton,&QPushButton::clicked,this,&AddPersonDialog::reject);
    connect(departmentEdit, &QLineEdit::textChanged, this, &AddPersonDialog::validateInput);
    validateInput();


}
AddPersonDialog::~AddPersonDialog() {}

int AddPersonDialog::getID() const {
    return idEdit->text().toInt();
}

QString AddPersonDialog::getName() const {
    return nameEdit->text().trimmed();
}

QString AddPersonDialog::getDepartment() const {
    return departmentEdit->text().trimmed();
}
void AddPersonDialog::onAddClicked() {
    if(idEdit->text().isEmpty()||getName().isEmpty()||getDepartment().isEmpty()){
        QMessageBox::warning(this, "输入错误", "请填写所有字段");
        return;
    }
    bool validId = false;
    //判断输入是否有效
    int id = idEdit->text().toInt(&validId);
    id = 0;
    if (!validId) {
        QMessageBox::warning(this, "输入错误", "ID必须是数字");
        idEdit->setFocus();
        return;
    }
    QString name = getName();
       for (const QChar &ch : name) {
           if (ch.unicode() < 0x4E00 || ch.unicode() > 0x9FA5) { // 基本汉字范围
               QMessageBox::warning(this, "输入错误", "名字含非中文字符");
               nameEdit->setFocus();
               return;
           }
       }


    QString department = getDepartment();
       for (const QChar &ch : department) {
           if (ch.unicode() < 0x4E00 || ch.unicode() > 0x9FA5) { // 基本汉字范围
               QMessageBox::warning(this, "输入错误", "部门名称含非中文字符");
               departmentEdit->setFocus(); // 假设departmentEdit是部门输入框的指针
               return;
           }
       }

    accept();
}

void AddPersonDialog::validateInput() {
    bool isValid = !idEdit->text().isEmpty() &&
                  !nameEdit->text().isEmpty() &&
                  !departmentEdit->text().isEmpty();

    addButton->setEnabled(isValid);
}
