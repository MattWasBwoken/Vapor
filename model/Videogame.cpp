#include "Videogame.h"
#include "IVisitor.h"

Videogame::Videogame(unsigned int id, const QString& name, const QString& description, const QString& developer, const QString& genre, unsigned int releaseDate, const QString& imagePath)
    : AbstractItem(id, name, description), m_developer(developer), m_genre(genre), m_releaseDate(releaseDate)
{
    setImage(imagePath);
}

QString Videogame::getDeveloper() const {
    return m_developer;
}

void Videogame::setDeveloper(const QString& developer) {
    m_developer = developer;
}

QString Videogame::getGenre() const {
    return m_genre;
}

void Videogame::setGenre(const QString& genre) {
    m_genre = genre;
}

unsigned int Videogame::getReleaseDate() const {
    return m_releaseDate;
}

void Videogame::setReleaseDate(unsigned int releaseDate) {
    m_releaseDate = releaseDate;
}

void Videogame::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void Videogame::accept(IConstVisitor* visitor) const {
    visitor->visit(this);
}
