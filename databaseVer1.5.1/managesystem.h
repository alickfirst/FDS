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
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class ManageSystem : public QObject {
    Q_OBJECT

private:
    //内含有两张哈希表
    explicit ManageSystem(QObject *parent = nullptr);
    QMap<int, Person*> idTable;
    QMultiHash<QString,Person*> nameTable;

    //文件io


public:
    //单例
    static ManageSystem* getInstance();
    // 增删改查接口
    bool addPerson(int id,QString& name,QString& department);
    bool deletePerson(int id);
    Person* queryById(int id);
    QVector<Person*> queryByName(const QString& name);
    QMap<int, Person*> getIdTable(){return idTable;}
    QMultiHash<QString,Person*> getNameTable(){return nameTable;}
    bool modifyPerson(int id, QString& newName, QString& newDepartment);
    QList<Person*> getAllPersons () const;

    const QString DEFAULT_FILENAME;

    //文件io操作
    bool saveToFile(const QString& filename);
    bool loadFromFile(const QString& filename);

public:

    // 添加迭代器访问接口
    auto begin() const -> decltype(idTable.constBegin()) {
            return idTable.constBegin();
    }
    auto end() const -> decltype(idTable.constEnd()) {
            return idTable.constEnd();
    }

    //单例模式
private:
    static ManageSystem* instance;
};

#endif // MANAGESYSTEM_H
