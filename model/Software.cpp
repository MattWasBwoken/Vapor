#include "Software.h"
#include "IVisitor.h"

Software::Software(unsigned int id, const QString& name, const QString& description, const QString& currentVersion, bool winCompatibility, const QString& imagePath)
    : AbstractItem(id, name, description), m_currentVersion(currentVersion), m_winCompatibility(winCompatibility)
{
    setImage(imagePath);
}

QString Software::getCurrentVersion() const {
    return m_currentVersion;
}

void Software::setCurrentVersion(const QString& currentVersion) {
    m_currentVersion = currentVersion;
}

bool Software::getWinCompatibility() const {
    return m_winCompatibility;
}

void Software::setWinCompatibility(bool winCompatibility) {
    m_winCompatibility = winCompatibility;
}

void Software::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void Software::accept(IConstVisitor* visitor) const {
    visitor->visit(this);
}
