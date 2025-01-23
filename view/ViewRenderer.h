#ifndef VIEWRENDERER_H
#define VIEWRENDERER_H

#include <QWidget>
#include <QVector>
#include "model/AbstractItem.h"
#include "ViewType.h"

class ViewRenderer : public QWidget {
    Q_OBJECT
public:
    explicit ViewRenderer(QWidget* parent = nullptr);
    void setViewType(ViewType viewType);
    ViewType getViewType() const;
    void render(QVector<AbstractItem*> &items);
signals:
    void itemSelected(AbstractItem *item);
    void backToGridRequested(bool showMessage);
    void editItemRequested(AbstractItem* item);
    void deleteItemRequested(AbstractItem* item);
private:
    const int itemWidth = 220;
    ViewType currentView;
    QWidget* createListView(const QVector<AbstractItem*> &items);
    QWidget* createGridView(const QVector<AbstractItem*> &items);
    QWidget* createDetailsView(AbstractItem* item);
};

#endif
