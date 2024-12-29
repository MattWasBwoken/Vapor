#include "DLC.h"
#include "IVisitor.h"

DLC::DLC(unsigned int id, const QString& name, const QString& description, const QString& developer, const QString& genre, unsigned int releaseDate, const QString& dlcType, bool standalone, const QString& imagePath)
    : Videogame(id, name, description, developer, genre, releaseDate, imagePath), m_dlcType(dlcType), m_standalone(standalone)
{
    setImage(imagePath);
}

QString DLC::getDlcType() const {
    return m_dlcType;
}

void DLC::setDlcType(const QString& dlcType) {
    m_dlcType = dlcType;
}

bool DLC::getStandalone() const {
    return m_standalone;
}

void DLC::setStandalone(bool standalone) {
    m_standalone = standalone;
}

void DLC::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void DLC::accept(IConstVisitor* visitor) const {
    visitor->visit(this);
}
