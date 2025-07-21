// ManageSystem.cpp
#include "ManageSystem.h"








/*********************************重要********************************/
/*手动实现数据库的功能，选用了单例的设计模式*/
/*内含增删改查等功能，可以实现文件io*/
/*本页面会在每次关闭后计入数据，每次打开后读取数据，实现存储功能*/
/*数据结构选用了哈希表，实现按id快速查询
 * 其实在思考后，我觉得直接用一个vector<int>甚至int[]都可以
 * 此处仅做探讨*/







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

QList<Person*> ManageSystem::getAllPersons() const {
    QList<Person*> persons;

    // 遍历idTable获取所有人员指针
    for (auto it = idTable.begin(); it != idTable.end(); ++it) {
        persons.append(it.value());
    }

    return persons;
}

//保存记录
bool ManageSystem::saveToFile(const QString& filename) {
    QFile file(filename.isEmpty() ? DEFAULT_FILENAME : filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "无法打开文件进行写入:" << file.fileName();
        return false;
    }

    // 创建JSON数组
    QJsonArray jsonArray;
    for (auto it = idTable.begin(); it != idTable.end(); ++it) {
        Person* person = it.value();
        QJsonObject jsonObj;
        jsonObj["id"] = person->getId();
        jsonObj["name"] = person->getName();
        jsonObj["department"] = person->getDepartment();
        jsonArray.append(jsonObj);
    }

    // 写入文件
    QJsonDocument doc(jsonArray);
    file.write(doc.toJson());
    file.close();

    return true;
}

//读取记录
bool ManageSystem::loadFromFile(const QString& filename) {
    QFile file(filename.isEmpty() ? DEFAULT_FILENAME : filename);
    if (!file.exists()) {
        qInfo() << "数据文件不存在，将创建新文件";
        return true; // 文件不存在不是错误
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "无法打开文件进行读取:" << file.fileName();
        return false;
    }

    // 读取并解析JSON
    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        qWarning() << "文件格式错误: 不是JSON数组";
        return false;
    }

    // 清空现有数据
    qDeleteAll(idTable);
    idTable.clear();
    nameTable.clear();

    // 加载新数据
    QJsonArray jsonArray = doc.array();
    for (const QJsonValue& value : jsonArray) {
        QJsonObject obj = value.toObject();
        int id = obj["id"].toInt();
        QString name = obj["name"].toString();
        QString department = obj["department"].toString();

        // 添加人员
        if (!idTable.contains(id)) {
            Person* p = new Person(id, name, department);
            idTable.insert(id, p);
            nameTable.insert(name, p);
        } else {
            qWarning() << "加载时发现重复ID:" << id << "，跳过";
        }
    }

    return true;
}
