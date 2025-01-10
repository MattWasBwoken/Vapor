#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <QString>

class AbstractItem {
private:
    unsigned int id;
    QString name;
    QString description;
    QString imagePath;

public:
    AbstractItem(unsigned int id, const QString& name, const QString& description);
    virtual ~AbstractItem() = default;
    unsigned int getId() const;
    void setId(unsigned int id);
    QString getName() const;
    void setName(const QString& name);
    QString getDescription() const;
    void setDescription(const QString& description);
    virtual QString getImage() const;
    virtual void setImage(const QString& imagePath);

    // Visitor Pattern
    virtual void accept(class IVisitor* visitor) = 0;
    virtual void accept(class IConstVisitor* visitor) const = 0;

signals:
    void attributeChanged();
};

#endif
