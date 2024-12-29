#ifndef IVISITOR_H
#define IVISITOR_H

#include "AbstractItem.h"

class Software;
class Videogame;
class DLC;
class Soundtrack;

class IVisitor {
public:
    virtual ~IVisitor() = default;
    virtual void visit(Software* item) = 0;
    virtual void visit(Videogame* item) = 0;
    virtual void visit(DLC* item) = 0;
    virtual void visit(Soundtrack* item) = 0;
};

#endif
