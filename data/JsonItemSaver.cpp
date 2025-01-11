#include "JsonItemSaver.h"
#include "JsonVisitor.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


bool JsonItemSaver::saveItemsToJson(const QVector<AbstractItem*> &items, const QString &filePath) {
    QJsonArray itemsArray;
    for (const auto& item : items) {
        JsonVisitor visitor;
        item->accept(&visitor);
        itemsArray.append(visitor.getJsonObject());
    }
    QJsonObject rootObj;
    rootObj["items"] = itemsArray;
    QJsonDocument jsonDoc(rootObj);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open file for writing:" << filePath;
        return false;
    }
    file.write(jsonDoc.toJson());
    file.close();
    return true;
}
