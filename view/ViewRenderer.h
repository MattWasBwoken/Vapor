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
        List
    };

    explicit ViewRenderer(QWidget* parent = nullptr);

    void setViewType(ViewType viewType);
    void render(const QVector<AbstractItem*>& items);

private:
    ViewType currentView;

    QWidget* createListView(const QVector<AbstractItem*>& items);
    QWidget* createGridView(const QVector<AbstractItem*>& items);
};

#endif
