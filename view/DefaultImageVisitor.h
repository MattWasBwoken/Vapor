#ifndef DEFAULTIMAGEVISITOR_H
#define DEFAULTIMAGEVISITOR_H

#include "model/IConstVisitor.h"
#include <QString>

class DefaultImageVisitor : public IConstVisitor {
public:
    DefaultImageVisitor();

    void visit(const Software* item) override;
    void visit(const Videogame* item) override;
    void visit(const DLC* item) override;
    void visit(const Soundtrack* item) override;

    QString getDefaultImagePath() const;
private:
    QString defaultImagePath;
};

#endif
