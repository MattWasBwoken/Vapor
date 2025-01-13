#ifndef SOUNDTRACK_H
#define SOUNDTRACK_H

#include "Videogame.h"
#include <QString>

class Soundtrack : public Videogame {
public:
    Soundtrack(unsigned int id, const QString& name, const QString& description, const QString& developer, const QString& genre, unsigned int releaseDate, const QString& composer, unsigned int tracksNumber, const QString& imagePath = "");
    ~Soundtrack() override = default;
    QString getComposer() const;
    void setComposer(const QString& composer);
    unsigned int getTracksNumber() const;
    void setTracksNumber(unsigned int tracksNumber);

    void accept(class IVisitor* visitor) override;
    void accept(class IConstVisitor* visitor) const override;
private:
    QString composer;
    unsigned int tracksNumber;
};

#endif
