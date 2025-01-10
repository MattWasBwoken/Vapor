#ifndef VIEWRENDERER_H
#define VIEWRENDERER_H

#include <QWidget>
#include <QVector>
#include "../model/AbstractItem.h"

class ItemRenderer;

class ViewRenderer : public QWidget {
    Q_OBJECT

public:
    // Make the enum public for external access
    enum class ViewType {
        Grid,
        List,
        Details
    };

    explicit ViewRenderer(QWidget* parent = nullptr);
    void setViewType(ViewType viewType);
    ViewType getViewType() const;
    void render(const QVector<AbstractItem*> &items);

signals:
    void itemSelected(AbstractItem *item);
    void backToGridRequested();

private:
    ViewType currentView;
    QWidget* createListView(const QVector<AbstractItem*> &items);
    QWidget* createGridView(const QVector<AbstractItem*> &items);
    QWidget* createDetailsView(AbstractItem* item);
};

#endif
