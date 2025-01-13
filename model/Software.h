#ifndef SOFTWARE_H
#define SOFTWARE_H

#include "AbstractItem.h"
#include <QString>

class Software : public AbstractItem {
public:
    Software(unsigned int id, const QString& name, const QString& description, const QString& currentVersion, bool winCompatibility, const QString& imagePath = "");
    ~Software() override = default;
    QString getCurrentVersion() const;
    void setCurrentVersion(const QString& currentVersion);
    bool getWinCompatibility() const;
    void setWinCompatibility(bool winCompatibility);

    void accept(class IVisitor* visitor) override;
    void accept(class IConstVisitor* visitor) const override;
private:
    QString currentVersion;
    bool winCompatibility;
};

#endif
