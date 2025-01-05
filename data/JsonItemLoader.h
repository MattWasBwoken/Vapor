#ifndef JSONITEMLOADER_H
#define JSONITEMLOADER_H

#include <QVector>
#include "../model/AbstractItem.h"

class JsonItemLoader {
public:
    static QVector<AbstractItem*> loadItemsFromJson(const QString &filePath);
};

#endif
