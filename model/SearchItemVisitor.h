#ifndef SEARCHITEMVISITOR_H
#define SEARCHITEMVISITOR_H

#include "IVisitor.h"
#include <QString>
#include <QVector>

class SearchItemVisitor : public IVisitor {
public:
    SearchItemVisitor(const QString& searchString, const QString& typeFilter = "");
    ~SearchItemVisitor() override = default;
    void visit(Software* item) override;
    void visit(Videogame* item) override;
    void visit(DLC* item) override;
    void visit(Soundtrack* item) override;
    const QVector<AbstractItem*>& getResults() const;
    void clearResults();
private:
    QString searchString;
    QString typeFilter;
    QVector<AbstractItem*> results;
};

#endif
