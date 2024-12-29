#include "Soundtrack.h"
#include "IVisitor.h"

Soundtrack::Soundtrack(unsigned int id, const QString& name, const QString& description, const QString& developer, const QString& genre, unsigned int releaseDate, const QString& composer, unsigned int tracksNumber, const QString& imagePath)
    : Videogame(id, name, description, developer, genre, releaseDate, imagePath), m_composer(composer), m_tracksNumber(tracksNumber)
{
    setImage(imagePath);
}

QString Soundtrack::getComposer() const {
    return m_composer;
}

void Soundtrack::setComposer(const QString& composer) {
    m_composer = composer;
}

unsigned int Soundtrack::getTracksNumber() const {
    return m_tracksNumber;
}

void Soundtrack::setTracksNumber(unsigned int tracksNumber) {
    m_tracksNumber = tracksNumber;
}

void Soundtrack::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void Soundtrack::accept(IConstVisitor* visitor) const {
    visitor->visit(this);
}
