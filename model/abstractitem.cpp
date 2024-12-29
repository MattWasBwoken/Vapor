#include "AbstractItem.h"

AbstractItem::AbstractItem(unsigned int id, const QString& name, const QString& description)
    : m_id(id), m_name(name), m_description(description)
{}

unsigned int AbstractItem::getId() const {
    return m_id;
}

void AbstractItem::setId(unsigned int id) {
    m_id = id;
}

QString AbstractItem::getName() const {
    return m_name;
}

void AbstractItem::setName(const QString& name) {
    m_name = name;
}

QString AbstractItem::getDescription() const {
    return m_description;
}

void AbstractItem::setDescription(const QString& description) {
    m_description = description;
}

QString AbstractItem::getImage() const {
    return m_imagePath;
}

void AbstractItem::setImage(const QString& imagePath) {
    m_imagePath = imagePath;
}
