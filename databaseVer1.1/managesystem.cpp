// ManageSystem.cpp
#include "ManageSystem.h"


ManageSystem* ManageSystem::instance = nullptr;
//初始化懒汉式单例
ManageSystem::ManageSystem(QObject *parent) : QObject(parent) {}

ManageSystem* ManageSystem::getInstance() {
    if (!instance) {
        instance = new ManageSystem();
    }
    return instance;
}
//维护一张哈希表，实现id的快速查询
//再维护一张哈希表实现name的快速查询
bool ManageSystem::addPerson(int id, QString& name,QString& department) {
    if (idTable.contains(id)) return false;
    Person* p = new Person(id, name,department);
    idTable.insert(id, p);
    nameTable.insert(name, p); // 同步插入nameTable
    return true;
}

// 修改 deletePerson
bool ManageSystem::deletePerson(int id) {
    if (!idTable.contains(id)) return false;
    Person* p = idTable.take(id);
    nameTable.remove(p->getName(), p); // 同步删除nameTable条目
    delete p;
    return true;
}

// 修改 modifyName
bool ManageSystem::modifyName(int id,QString& newName) {
    if (!idTable.contains(id)) return false;
    Person* p = idTable[id];
    nameTable.remove(p->getName(), p); // 先删除旧名字记录
    p->setName(newName);
    nameTable.insert(newName, p); // 插入新名字记录
    return true;
}
