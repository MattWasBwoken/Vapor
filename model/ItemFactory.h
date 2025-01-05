#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <QObject>
#include "AbstractItem.h"

class ItemFactory : public QObject {
    Q_OBJECT
public:
    static AbstractItem* createItem(QWidget *parent = nullptr);
};

#endif
