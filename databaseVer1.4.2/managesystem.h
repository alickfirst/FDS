// ManageSystem.h
#ifndef MANAGESYSTEM_H
#define MANAGESYSTEM_H
#include <QObject>
#include <QMap>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QVector>
#include <person.h>
#include <QMultiHash>

class ManageSystem : public QObject {
    Q_OBJECT

private:
    explicit ManageSystem(QObject *parent = nullptr);
    QMap<int, Person*> idTable;
    QMultiHash<QString,Person*> nameTable;

public:
    static ManageSystem* getInstance();

    // 增删改查接口
    bool addPerson(int id,QString& name,QString& department);
    bool deletePerson(int id);
    Person* queryById(int id);
    QVector<Person*> queryByName(const QString& name);
    QMap<int, Person*> getIdTable(){return idTable;}
    QMultiHash<QString,Person*> getNameTable(){return nameTable;}
    bool modifyPerson(int id, QString& newName, QString& newDepartment);
public:
    // 添加迭代器访问接口

    auto begin() const -> decltype(idTable.constBegin()) {
            return idTable.constBegin();
    }

    auto end() const -> decltype(idTable.constEnd()) {
            return idTable.constEnd();
    }




private:
    static ManageSystem* instance;
};

#endif // MANAGESYSTEM_H
