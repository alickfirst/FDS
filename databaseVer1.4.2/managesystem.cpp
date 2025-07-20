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

// 修改 modify
bool ManageSystem::modifyPerson(int id, QString& newName,QString& newDepartment) {

    if (!idTable.contains(id)) return false;

    Person* p = idTable[id];

    // 处理姓名修改
    if (newName != p->getName()) {
        if (nameTable.contains(newName)) return false;
        nameTable.remove(p->getName(), p);
        p->setName(newName);
        nameTable.insert(newName, p);
    }

    p->setDepartment(newDepartment);

    return true;
}
Person* ManageSystem::queryById(int id){
    auto it = idTable.find(id); // 返回迭代器
    //如果迭代器不为空，我们就返回it.value(迭代器对应的指针)
        if (it != idTable.end()) {
            return it.value();
        }
        return nullptr;
}
