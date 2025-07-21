#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>

class PersonItem : public QWidget {
    Q_OBJECT
public:
    explicit PersonItem(int id, const QString& name, const QString& department, QWidget *parent = nullptr)
        : QWidget(parent), m_id(id) {
        // 创建控件
        nameLabel = new QLabel(name, this);
        idLabel = new QLabel(QString("ID: %1").arg(id), this);
        deptLabel = new QLabel(department, this);

        modifyBtn = new QPushButton("修改", this);
        deleteBtn = new QPushButton("删除", this);

        // 设置样式
        setupStyles();

        // 布局
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->setContentsMargins(15, 10, 15, 10);
        layout->setSpacing(20);

        // 信息区域
        QVBoxLayout *infoLayout = new QVBoxLayout();
        infoLayout->addWidget(nameLabel);
        infoLayout->addWidget(idLabel);
        infoLayout->addWidget(deptLabel);

        // 按钮区域
        QVBoxLayout *btnLayout = new QVBoxLayout();
        btnLayout->addWidget(modifyBtn);
        btnLayout->addWidget(deleteBtn);
        btnLayout->setSpacing(5);

        layout->addLayout(infoLayout, 1);  // 伸缩因子为1，占据剩余空间
        layout->addLayout(btnLayout, 0);   // 不伸缩

        // 连接信号槽
        connect(modifyBtn, &QPushButton::clicked, this, &PersonItem::onModifyClicked);
        connect(deleteBtn, &QPushButton::clicked, this, &PersonItem::onDeleteClicked);
    }

signals:
    void modifyRequested(int id);  // 修改请求信号
    void deleteRequested(int id);  // 删除请求信号

private slots:
    void onModifyClicked() { emit modifyRequested(m_id); }
    void onDeleteClicked() { emit deleteRequested(m_id); }

private:
    void setupStyles() {
        // 基础样式
        this->setStyleSheet(R"(
            PersonItem {
                background-color: rgba(255, 255, 255, 220);
                border-radius: 10px;
                border: 1px solid rgba(0, 0, 0, 10%);
            }
            PersonItem:hover {
                background-color: rgba(255, 255, 255, 250);
                box-shadow: 0 4px 8px rgba(0, 0, 0, 10%);
            }
        )");

        // 标签样式
        nameLabel->setStyleSheet("font: bold 16px; color: #2C3E50;");
        idLabel->setStyleSheet("font: 12px; color: #7F8C8D;");
        deptLabel->setStyleSheet("font: 14px; color: #3498DB;");

        // 按钮样式
        QString btnStyle = R"(
            QPushButton {
                min-width: 60px;
                padding: 5px;
                border-radius: 5px;
                font-size: 12px;
            }
            QPushButton:hover {
                transform: translateY(-1px);
            }
        )";
        modifyBtn->setStyleSheet(btnStyle + "background-color: #F1C40F; color: #2C3E50;");
        deleteBtn->setStyleSheet(btnStyle + "background-color: #E74C3C; color: white;");
    }

    int m_id;
    QLabel *nameLabel, *idLabel, *deptLabel;
    QPushButton *modifyBtn, *deleteBtn;
};
