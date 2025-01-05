#ifndef VIEWRENDERER_H
#define VIEWRENDERER_H

#include <QWidget>
#include <QVector>
#include "../model/AbstractItem.h"

class ItemRenderer;

class ViewRenderer : public QWidget {
    Q_OBJECT

private:
    enum ViewType { ListView, GridView };
    ViewType currentView;

    QWidget* createListView(const QVector<AbstractItem*>& items);
    QWidget* createGridView(const QVector<AbstractItem*>& items);

protected:
    void resizeEvent(QResizeEvent* event) override; // Handle resize events

public:
    explicit ViewRenderer(QWidget* parent = nullptr);

    void setViewType(bool isGridView);
    void render(const QVector<AbstractItem*>& items);

signals:
    void renderRequested(); // Signal to request rendering on resize
};

#endif
