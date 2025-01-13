#include "JsonItemLoader.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include "model/Software.h"
#include "model/Videogame.h"
#include "model/DLC.h"
#include "model/Soundtrack.h"

QVector<AbstractItem*> JsonItemLoader::loadItemsFromJson(const QString &filePath) {
    QVector<AbstractItem*> items;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file:" << filePath;
        return items;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    if (!jsonDoc.isObject()) {
        qWarning() << "Invalid JSON format in file:" << filePath;
        return items;
    }

    QJsonObject rootObj = jsonDoc.object();
    QJsonArray itemsArray = rootObj["items"].toArray();

    for (const QJsonValue &value : itemsArray) {
        if (!value.isObject()) continue;
        QJsonObject itemObj = value.toObject();
        QString type = itemObj["type"].toString();
        AbstractItem *item = nullptr;
        if (type == "Software") {
            item = new Software(
                itemObj["id"].toInt(),
                itemObj["name"].toString(),
                itemObj["description"].toString(),
                itemObj["currentVersion"].toString(),
                itemObj["winCompatibility"].toBool(),
                itemObj["imagePath"].toString()
                );
        } else if (type == "Videogame") {
            item = new Videogame(
                itemObj["id"].toInt(),
                itemObj["name"].toString(),
                itemObj["description"].toString(),
                itemObj["developer"].toString(),
                itemObj["genre"].toString(),
                itemObj["releaseDate"].toInt(),
                itemObj["imagePath"].toString()
                );
        } else if (type == "DLC") {
            item = new DLC(
                itemObj["id"].toInt(),
                itemObj["name"].toString(),
                itemObj["description"].toString(),
                itemObj["developer"].toString(),
                itemObj["genre"].toString(),
                itemObj["releaseDate"].toInt(),
                itemObj["dlcType"].toString(),
                itemObj["standalone"].toBool(),
                itemObj["imagePath"].toString()
                );
        } else if (type == "Soundtrack") {
            item = new Soundtrack(
                itemObj["id"].toInt(),
                itemObj["name"].toString(),
                itemObj["description"].toString(),
                itemObj["developer"].toString(),
                itemObj["genre"].toString(),
                itemObj["releaseDate"].toInt(),
                itemObj["composer"].toString(),
                itemObj["tracksNumber"].toInt(),
                itemObj["imagePath"].toString()
                );
        }
        if (item) {
            items.append(item);
        }
    }
    return items;
}
