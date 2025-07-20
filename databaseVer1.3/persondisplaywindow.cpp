// PersonDisplayWindow.cpp
#include "AddPersonDialog.h"
#include <persondisplaywindow.h>

PersonDisplayWindow::PersonDisplayWindow(QWidget *parent)
    : QWidget(parent), system(ManageSystem::getInstance()) {

    // 初始化界面
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 搜索框
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchEdit = new QLineEdit();
    searchEdit->setPlaceholderText("输入姓名或部门搜索...");
    QPushButton *searchBtn = new QPushButton("搜索");
    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(searchBtn);

    // 表格
    table = new QTableWidget();
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"ID", "姓名", "部门"});
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSortingEnabled(true);

    // 操作按钮
    QPushButton *addBtn = new QPushButton("添加人员");
    QPushButton *deleteBtn = new QPushButton("删除选中");

    // 布局组合
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(table);
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(addBtn);
    btnLayout->addWidget(deleteBtn);
    mainLayout->addLayout(btnLayout);

    // 信号连接
    connect(searchBtn, &QPushButton::clicked, this, &PersonDisplayWindow::refreshTable);
    connect(deleteBtn, &QPushButton::clicked, this, &PersonDisplayWindow::onDeleteClicked);
    connect(addBtn, &QPushButton::clicked, this, &PersonDisplayWindow::onAddClicked);
    connect(table, &QTableWidget::cellDoubleClicked, this, &PersonDisplayWindow::onCellDoubleClicked);

    // 初始化显示
    refreshTable();
}

void PersonDisplayWindow::refreshTable() {
    table->setRowCount(0);
    QString keyword = searchEdit->text().trimmed();

    // 遍历哈希表填充数据
    for (auto it = system->getIdTable().begin(); it != system->getIdTable().end(); ++it) {
        Person *p = it.value();

        // 执行搜索过滤
        if (!keyword.isEmpty() &&
            !p->getName().contains(keyword, Qt::CaseInsensitive) &&
            !p->getDepartment().contains(keyword, Qt::CaseInsensitive)) {
            continue;
        }

        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(p->getId())));
        table->setItem(row, 1, new QTableWidgetItem(p->getName()));
        table->setItem(row, 2, new QTableWidgetItem(p->getDepartment()));
    }

    // 自适应列宽
    table->resizeColumnsToContents();
}

void PersonDisplayWindow::onDeleteClicked() {
    int selectedRow = table->currentRow();
    if (selectedRow < 0) return;

    int id = table->item(selectedRow, 0)->text().toInt();
    if (system->deletePerson(id)) {
        refreshTable();
    }
}

void PersonDisplayWindow::onAddClicked() {
    AddPersonDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        refreshTable();
    }
}

void PersonDisplayWindow::onCellDoubleClicked(int row, int column) {
    if (column == 1) { // 双击姓名列进入编辑
        int id = table->item(row, 0)->text().toInt();
        QString oldName = table->item(row, 1)->text();

        bool ok;
        QString newName = QInputDialog::getText(this, "修改姓名",
            "新姓名:", QLineEdit::Normal, oldName, &ok);

        if (ok && !newName.isEmpty()) {
            system->modifyName(id, newName);
            refreshTable();
        }
    }
}
