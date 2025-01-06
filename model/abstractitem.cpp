#include "AbstractItem.h"
#include <QFile>
#include "view/DefaultImageVisitor.h"

AbstractItem::AbstractItem(unsigned int id, const QString& name, const QString& description)
    : id(id), name(name), description(description)
{}

unsigned int AbstractItem::getId() const {
    return this->id;
}

void AbstractItem::setId(unsigned int id) {
    this->id = id;
}

QString AbstractItem::getName() const {
    return this->name;
}

void AbstractItem::setName(const QString& name) {
    this->name = name;
}

QString AbstractItem::getDescription() const {
    return this->description;
}

void AbstractItem::setDescription(const QString& description) {
    this->description = description;
}

QString AbstractItem::getImage() const {
    return this->imagePath;
}

void AbstractItem::setImage(const QString& imagePath) {
    QFile file(imagePath);
    if (file.exists()) {
        this->imagePath = imagePath;
    } else {
        // Use the DefaultImageVisitor to determine the default image
        DefaultImageVisitor defaultVisitor;
        this->accept(&defaultVisitor);
        this->imagePath = defaultVisitor.getDefaultImagePath();
    }
}
