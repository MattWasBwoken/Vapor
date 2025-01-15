#include "DLC.h"
#include "IVisitor.h"
#include "IConstVisitor.h"

DLC::DLC(unsigned int id, const QString& name, const QString& description, const QString& developer, const QString& genre, unsigned int releaseDate, const QString& dlcType, bool standalone, const QString& imagePath)
    : Videogame(id, name, description, developer, genre, releaseDate, imagePath), dlcType(dlcType), standalone(standalone) {
    setImage(imagePath);
}

QString DLC::getDlcType() const {
    return this->dlcType;
}

void DLC::setDlcType(const QString& dlcType) {
    this->dlcType = dlcType;
}

bool DLC::getStandalone() const {
    return this->standalone;
}

void DLC::setStandalone(bool standalone) {
    this->standalone = standalone;
}

void DLC::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void DLC::accept(IConstVisitor* visitor) const {
    visitor->visit(this);
}
