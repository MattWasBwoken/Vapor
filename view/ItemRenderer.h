#ifndef ITEMRENDERER_H
#define ITEMRENDERER_H

#include <QWidget>
#include <QLabel>
#include "../model/IConstVisitor.h"
#include "../model/AbstractItem.h"


class ItemRenderer : public QWidget, public IConstVisitor {
    Q_OBJECT

public:
    explicit ItemRenderer(QWidget* parent = nullptr);

    enum class ViewType {
        Grid,
        List,
        Details
    };

    // Render methods
    QWidget* render(AbstractItem* item, ViewType viewType);

    // Visitor methods
    void visit(const Software* item) override;
    void visit(const Videogame* item) override;
    void visit(const DLC* item) override;
    void visit(const Soundtrack* item) override;

private:
    QWidget* renderedWidget;
    ViewType currentViewType;

    void setRenderedWidget(QWidget* widget);
    QWidget* createGenericWidget(const QString& imagePath, const QString& name, const QString& description, QLayout* attributeLayout, ViewType viewType, int imageWidth, int imageHeight);
};

#endif
