#include "Videogame.h"
#include "IVisitor.h"
#include "IConstVisitor.h"

Videogame::Videogame(unsigned int id, const QString& name, const QString& description, const QString& developer, const QString& genre, unsigned int releaseDate, const QString& imagePath)
    : AbstractItem(id, name, description), developer(developer), genre(genre), releaseDate(releaseDate)
{
    setImage(imagePath);
}

QString Videogame::getDeveloper() const {
    return this->developer;
}

void Videogame::setDeveloper(const QString& developer) {
    this->developer = developer;
}

QString Videogame::getGenre() const {
    return this->genre;
}

void Videogame::setGenre(const QString& genre) {
    this->genre = genre;
}

unsigned int Videogame::getReleaseDate() const {
    return this->releaseDate;
}

void Videogame::setReleaseDate(unsigned int releaseDate) {
    this->releaseDate = releaseDate;
}

void Videogame::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void Videogame::accept(IConstVisitor* visitor) const {
    visitor->visit(this);
}
