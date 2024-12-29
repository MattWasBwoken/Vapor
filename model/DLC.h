#ifndef DLC_H
#define DLC_H

#include "Videogame.h"
#include <QString>

class DLC : public Videogame {
private:
    QString m_dlcType;
    bool m_standalone;
public:
    DLC(unsigned int id, const QString& name, const QString& description, const QString& developer, const QString& genre, unsigned int releaseDate, const QString& dlcType, bool standalone, const QString& imagePath = "");
    ~DLC() override = default;
    QString getDlcType() const;
    void setDlcType(const QString& dlcType);
    bool getStandalone() const;
    void setStandalone(bool standalone);

    // Implementazione metodi accept per il Visitor
    void accept(class IVisitor* visitor) override;
    void accept(class IConstVisitor* visitor) const override;
};

#endif