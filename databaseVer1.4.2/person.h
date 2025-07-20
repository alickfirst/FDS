#ifndef PERSON_H
#define PERSON_H

#include <QString>

class Person {
public:
    Person(int id, const QString& name, const QString& department)
        : id(id), name(name), department(department) {}

    int getId() const { return id; }
    const QString& getName() const { return name; }
    const QString& getDepartment() const { return department; }

    void setName(QString& newName) {
        name = newName;  // 直接赋值QString
    }
    void setDepartment(QString& newdepartment){
        department = newdepartment;
    }

private:
    int id;                   // 唯一标识符
    QString name;             // 姓名（使用QString管理内存）
    QString department;       // 部门信息
};

#endif // PERSON_H
