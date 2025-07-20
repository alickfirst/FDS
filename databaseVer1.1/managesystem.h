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
    bool modifyName(int id,QString& newName);
    bool modifyDepartment(int id,QString& newName);
    Person* queryById(int id);
    QVector<Person*> queryByName(const QString& name);

private:
    static ManageSystem* instance;
};

#endif // MANAGESYSTEM_H
