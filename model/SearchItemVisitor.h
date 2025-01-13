#ifndef SEARCHITEMVISITOR_H
#define SEARCHITEMVISITOR_H

#include "IConstVisitor.h"
#include <QString>
#include <QVector>

class SearchItemVisitor : public IConstVisitor {
private:
    QString searchString;
    QString typeFilter;
    QVector<const AbstractItem*> results;
public:
    SearchItemVisitor(const QString& searchString, const QString& typeFilter = "");
    ~SearchItemVisitor() override = default;
    void visit(const Software* item) override;
    void visit(const Videogame* item) override;
    void visit(const DLC* item) override;
    void visit(const Soundtrack* item) override;
    const QVector<const AbstractItem*>& getResults() const;
    void clearResults();
};

#endif
