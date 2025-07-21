#include "addpersondialog.h"
#include <QIntValidator>








/*********************************重要********************************/
/*本类用于设计添加人员时的弹窗界面以及读取数据功能*/








AddPersonDialog::AddPersonDialog(QWidget *parent)
    :QDialog(parent)
{setWindowTitle("添加该人员");
    setFixedSize(800, 600);
    mainLayout = new QVBoxLayout(this);

    formLayout = new QFormLayout();

    // 新增ID输入框
    idEdit = new QLineEdit(this);
    idEdit->setPlaceholderText("请输入ID");
    idEdit->setValidator(new QIntValidator(1, INT_MAX, this)); // 限制只能输入正整数
    formLayout->addRow("ID:", idEdit);

    // 原有姓名和部门输入框
    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("请输入姓名");
    departmentEdit = new QLineEdit(this);
    departmentEdit->setPlaceholderText("请输入部门");

    // 样式设置保持不变...
    QString inputStyle = "..."; // 原有样式代码
    idEdit->setStyleSheet(inputStyle); // 应用相同样式
    nameEdit->setStyleSheet(inputStyle);
    departmentEdit->setStyleSheet(inputStyle);

    // 布局设置保持不变...
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
     return idEdit->text().toInt(); // 因为已经校验过，所以可以直接转换
 }

QString AddPersonDialog::getName() const {
    return nameEdit->text().trimmed();
}

QString AddPersonDialog::getDepartment() const {
    return departmentEdit->text().trimmed();
}
void AddPersonDialog::onAddClicked() {
    // ID校验
    QString idText = idEdit->text().trimmed();
    if (idText.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "ID不能为空");
        idEdit->setFocus();
        return;
    }

    bool ok;
    int id = idText.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "输入错误", "ID必须为有效整数");
        idEdit->setFocus();
        return;
    }

    if (id <= 0) {
        QMessageBox::warning(this, "输入错误", "ID必须为正整数");
        idEdit->setFocus();
        return;
    }

    // 原有姓名校验
    QString name = getName();
    for (const QChar &ch : name) {
        if (ch.unicode() < 0x4E00 || ch.unicode() > 0x9FA5) {
            QMessageBox::warning(this, "输入错误", "名字含非中文字符");
            nameEdit->setFocus();
            return;
        }
    }

    // 原有部门校验
    QString department = getDepartment();
    for (const QChar &ch : department) {
        if (ch.unicode() < 0x4E00 || ch.unicode() > 0x9FA5) {
            QMessageBox::warning(this, "输入错误", "部门名称含非中文字符");
            departmentEdit->setFocus();
            return;
        }
    }

    accept();
}

void AddPersonDialog::validateInput() {
    bool isValid = !nameEdit->text().isEmpty() &&
                  !departmentEdit->text().isEmpty();

    addButton->setEnabled(isValid);
}
