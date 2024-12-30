#ifndef SEARCHITEMVISITOR_H
#define SEARCHITEMVISITOR_H

#include "IConstVisitor.h"
#include <QString>
#include <QVector>

class SearchItemVisitor : public IConstVisitor {
private:
    QString searchString;
    QString typeFilter;
    QString genreFilter;
    bool winCompatibilityFilter;
    QVector<const AbstractItem*> results; // salva i risultati della ricerca
public:
    SearchItemVisitor(const QString& searchString, const QString& typeFilter = "", const QString& genreFilter = "", bool winCompatibilityFilter = false);
    ~SearchItemVisitor() override = default;
    void visit(const Software* item) override;
    void visit(const Videogame* item) override;
    void visit(const DLC* item) override;
    void visit(const Soundtrack* item) override;
    const QVector<const AbstractItem*>& getResults() const; // recupera i risultati
    void clearResults();
};

#endif
