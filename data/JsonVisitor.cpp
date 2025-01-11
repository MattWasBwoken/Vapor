#include "JsonVisitor.h"
#include "model/Software.h"
#include "model/Videogame.h"
#include "model/DLC.h"
#include "model/Soundtrack.h"

void JsonVisitor::visit(Software* item){
    QJsonObject itemObj;
    itemObj["id"] = (int)item->getId();
    itemObj["name"] = item->getName();
    itemObj["description"] = item->getDescription();
    itemObj["imagePath"] = item->getImage();
    itemObj["type"] = "Software";
    itemObj["currentVersion"] = item->getCurrentVersion();
    itemObj["winCompatibility"] = item->getWinCompatibility();
    currentObject = itemObj;
}

void JsonVisitor::visit(Videogame* item){
    QJsonObject itemObj;
    itemObj["id"] = (int)item->getId();
    itemObj["name"] = item->getName();
    itemObj["description"] = item->getDescription();
    itemObj["imagePath"] = item->getImage();
    itemObj["type"] = "Videogame";
    itemObj["developer"] = item->getDeveloper();
    itemObj["genre"] = item->getGenre();
    itemObj["releaseDate"] = (int)item->getReleaseDate();
    currentObject = itemObj;
}

void JsonVisitor::visit(DLC* item){
    QJsonObject itemObj;
    itemObj["id"] = (int)item->getId();
    itemObj["name"] = item->getName();
    itemObj["description"] = item->getDescription();
    itemObj["imagePath"] = item->getImage();
    itemObj["type"] = "DLC";
    itemObj["developer"] = item->getDeveloper();
    itemObj["genre"] = item->getGenre();
    itemObj["releaseDate"] = (int)item->getReleaseDate();
    itemObj["dlcType"] = item->getDlcType();
    itemObj["standalone"] = item->getStandalone();
    currentObject = itemObj;
}

void JsonVisitor::visit(Soundtrack* item){
    QJsonObject itemObj;
    itemObj["id"] = (int)item->getId();
    itemObj["name"] = item->getName();
    itemObj["description"] = item->getDescription();
    itemObj["imagePath"] = item->getImage();
    itemObj["type"] = "Soundtrack";
    itemObj["developer"] = item->getDeveloper();
    itemObj["genre"] = item->getGenre();
    itemObj["releaseDate"] = (int)item->getReleaseDate();
    itemObj["composer"] = item->getComposer();
    itemObj["tracksNumber"] = (int)item->getTracksNumber();
    currentObject = itemObj;
}

QJsonObject JsonVisitor::getJsonObject() const{
    return currentObject;
}
