#ifndef JSONITEMSAVER_H
#define JSONITEMSAVER_H

#include <QVector>
#include <QString>
#include "model/AbstractItem.h"

class JsonItemSaver {
public:
    static bool saveItemsToJson(const QVector<AbstractItem*> &items, const QString &filePath);
};

#endif
