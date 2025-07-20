#include <modifypersonclass.h>

ModifyPersonDialog::ModifyPersonDialog(QWidget *parent)
    :QDialog(parent)
    {setWindowTitle("修改现有人员");
    setFixedSize(800,600);
    mainLayout = new QVBoxLayout(this);

    formLayout = new QFormLayout();


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

    nameEdit->setStyleSheet(inputStyle);
    departmentEdit->setStyleSheet(inputStyle);



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

    connect(addButton,&QPushButton::clicked,this,&ModifyPersonDialog::onAddClicked);
    connect(cancelButton,&QPushButton::clicked,this,&ModifyPersonDialog::reject);
    connect(departmentEdit, &QLineEdit::textChanged, this, &ModifyPersonDialog::validateInput);
    validateInput();


}
ModifyPersonDialog::~ModifyPersonDialog() {}

int ModifyPersonDialog::getID() const {
    return idEdit->text().toInt();
}

QString ModifyPersonDialog::getName() const {
    return nameEdit->text().trimmed();
}

QString ModifyPersonDialog::getDepartment() const {
    return departmentEdit->text().trimmed();
}
void ModifyPersonDialog::onAddClicked() {
    if(getName().isEmpty()||getDepartment().isEmpty()){
        QMessageBox::warning(this, "输入错误", "请填写所有字段");
        return;
    }
    bool validId = false;
    //判断输入是否有效

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

void ModifyPersonDialog::validateInput() {
    bool isValid =
                  !nameEdit->text().isEmpty() &&
                  !departmentEdit->text().isEmpty();

    addButton->setEnabled(isValid);
}
