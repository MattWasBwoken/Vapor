#ifndef ICONSTVISITOR_H
#define ICONSTVISITOR_H

#include "AbstractItem.h"

class Software;
class Videogame;
class DLC;
class Soundtrack;

class IConstVisitor {
public:
    virtual ~IConstVisitor() = default;
    virtual void visit(const Software* item) = 0;
    virtual void visit(const Videogame* item) = 0;
    virtual void visit(const DLC* item) = 0;
    virtual void visit(const Soundtrack* item) = 0;
};

#endif
