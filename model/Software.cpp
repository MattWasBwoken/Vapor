#include "Software.h"
#include "IVisitor.h"
#include "IConstVisitor.h"

Software::Software(unsigned int id, const QString& name, const QString& description, const QString& currentVersion, bool winCompatibility, const QString& imagePath)
    : AbstractItem(id, name, description), currentVersion(currentVersion), winCompatibility(winCompatibility) {
    setImage(imagePath);
}

QString Software::getCurrentVersion() const {
    return this->currentVersion;
}

void Software::setCurrentVersion(const QString& currentVersion) {
    this->currentVersion = currentVersion;
}

bool Software::getWinCompatibility() const {
    return this->winCompatibility;
}

void Software::setWinCompatibility(bool winCompatibility) {
    this->winCompatibility = winCompatibility;
}

void Software::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void Software::accept(IConstVisitor* visitor) const {
    visitor->visit(this);
}
