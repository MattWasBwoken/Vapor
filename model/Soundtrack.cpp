#include "Soundtrack.h"
#include "IVisitor.h"
#include "IConstVisitor.h"

Soundtrack::Soundtrack(unsigned int id, const QString& name, const QString& description, const QString& developer, const QString& genre, unsigned int releaseDate, const QString& composer, unsigned int tracksNumber, const QString& imagePath)
    : Videogame(id, name, description, developer, genre, releaseDate, imagePath), composer(composer), tracksNumber(tracksNumber)
{
    setImage(imagePath);
}

QString Soundtrack::getComposer() const {
    return this->composer;
}

void Soundtrack::setComposer(const QString& composer) {
    this->composer = composer;
}

unsigned int Soundtrack::getTracksNumber() const {
    return this->tracksNumber;
}

void Soundtrack::setTracksNumber(unsigned int tracksNumber) {
    this->tracksNumber = tracksNumber;
}

void Soundtrack::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void Soundtrack::accept(IConstVisitor* visitor) const {
    visitor->visit(this);
}
