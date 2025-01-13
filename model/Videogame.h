#ifndef VIDEOGAME_H
#define VIDEOGAME_H

#include "AbstractItem.h"
#include <QString>

class Videogame : public AbstractItem {
public:
    Videogame(unsigned int id, const QString& name, const QString& description, const QString& developer, const QString& genre, unsigned int releaseDate, const QString& imagePath = "");
    ~Videogame() override = default;
    QString getDeveloper() const;
    void setDeveloper(const QString& developer);
    QString getGenre() const;
    void setGenre(const QString& genre);
    unsigned int getReleaseDate() const;
    void setReleaseDate(unsigned int releaseDate);

    void accept(class IVisitor* visitor) override;
    void accept(class IConstVisitor* visitor) const override;
private:
    QString developer;
    QString genre;
    unsigned int releaseDate;
};

#endif
