#ifndef JSONVISITOR
#define JSONVISITOR

#include "model/IVisitor.h"
#include <QJsonObject>

class JsonVisitor;

class JsonVisitor : public IVisitor {
    QJsonObject currentObject;
public:
    void visit(Software* item) override;
    void visit(Videogame* item) override;
    void visit(DLC* item) override;
    void visit(Soundtrack* item) override;
    QJsonObject getJsonObject() const;
};

#endif
