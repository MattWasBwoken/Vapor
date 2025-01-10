#include "JsonItemSaver.h"
#include "../model/Software.h"
#include "../model/Videogame.h"
#include "../model/DLC.h"
#include "../model/Soundtrack.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

bool JsonItemSaver::saveItemsToJson(const QVector<AbstractItem*> &items, const QString &filePath) {
    QJsonArray itemsArray;
    for (const auto& item : items) {
        QJsonObject itemObj;
        itemObj["id"] = (int)item->getId();
        itemObj["name"] = item->getName();
        itemObj["description"] = item->getDescription();
        itemObj["imagePath"] = item->getImage();


        if (const Software* software = dynamic_cast<const Software*>(item)) {
            itemObj["type"] = "Software";
            itemObj["currentVersion"] = software->getCurrentVersion();
            itemObj["winCompatibility"] = software->getWinCompatibility();
        } else if (const Videogame* videogame = dynamic_cast<const Videogame*>(item)) {
            itemObj["type"] = "Videogame";
            itemObj["developer"] = videogame->getDeveloper();
            itemObj["genre"] = videogame->getGenre();
            itemObj["releaseDate"] = (int)videogame->getReleaseDate();
        } else if (const DLC* dlc = dynamic_cast<const DLC*>(item)) {
            itemObj["type"] = "DLC";
            itemObj["developer"] = dlc->getDeveloper();
            itemObj["genre"] = dlc->getGenre();
            itemObj["releaseDate"] = (int)dlc->getReleaseDate();
            itemObj["dlcType"] = dlc->getDlcType();
            itemObj["standalone"] = dlc->getStandalone();
        } else if (const Soundtrack* soundtrack = dynamic_cast<const Soundtrack*>(item)) {
            itemObj["type"] = "Soundtrack";
            itemObj["developer"] = soundtrack->getDeveloper();
            itemObj["genre"] = soundtrack->getGenre();
            itemObj["releaseDate"] = (int)soundtrack->getReleaseDate();
            itemObj["composer"] = soundtrack->getComposer();
            itemObj["tracksNumber"] = (int)soundtrack->getTracksNumber();
        }
        itemsArray.append(itemObj);
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
