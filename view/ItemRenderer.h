#ifndef ITEMRENDERER_H
#define ITEMRENDERER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "../model/IConstVisitor.h"
#include "../model/AbstractItem.h"

class ItemRenderer : public QWidget, public IConstVisitor {
    Q_OBJECT

private:
    QWidget* renderedWidget;

    void setRenderedWidget(QWidget* widget);

public:
    explicit ItemRenderer(QWidget* parent = nullptr);

    // Render method
    QWidget* render(AbstractItem* item);

    // Visitor methods
    void visit(const Software* item) override;
    void visit(const Videogame* item) override;
    void visit(const DLC* item) override;
    void visit(const Soundtrack* item) override;
};

#endif
