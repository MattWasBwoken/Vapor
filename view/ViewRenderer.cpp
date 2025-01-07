#include "ViewRenderer.h"
#include "ItemRenderer.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QResizeEvent>

ViewRenderer::ViewRenderer(QWidget* parent) : QWidget(parent), currentView(ViewType::Grid) {}

void ViewRenderer::setViewType(ViewType viewType) {
    currentView = viewType;
}

void ViewRenderer::render(const QVector<AbstractItem*>& items) {
    // Clear existing layout
    QLayout* layout = this->layout();
    if (layout) {
        QLayoutItem* child;
        while ((child = layout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
        delete layout;
    }

    // Render items based on the current view type
    if (currentView == ViewType::List) {
        this->setLayout(new QVBoxLayout);
        this->layout()->addWidget(createListView(items));
    } else {
        this->setLayout(new QVBoxLayout);
        this->layout()->addWidget(createGridView(items));
    }
}

QWidget* ViewRenderer::createGridView(const QVector<AbstractItem*>& items) {
    const int itemWidth = 250;
    int containerWidth = this->width();
    if (containerWidth < itemWidth) {
        containerWidth = 1100;
    }
    int columns = qMax(1, containerWidth / itemWidth);

    QWidget* container = new QWidget(this);
    QGridLayout* layout = new QGridLayout(container);

    for (int i = 0; i < items.size(); ++i) {
        AbstractItem* item = items[i];
        int row = i / columns;
        int col = i % columns;

        ItemRenderer* itemRenderer = new ItemRenderer(container);
        layout->addWidget(itemRenderer->render(item, ItemRenderer::ViewType::Grid), row, col);
    }

    container->setLayout(layout);
    return container;
}

QWidget* ViewRenderer::createListView(const QVector<AbstractItem*>& items) {
    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(container);

    for (AbstractItem* item : items) {
        ItemRenderer* itemRenderer = new ItemRenderer(container);
        layout->addWidget(itemRenderer->render(item, ItemRenderer::ViewType::List));

        QFrame* separator = new QFrame(container);
        separator->setFrameShape(QFrame::HLine);
        separator->setFrameShadow(QFrame::Sunken);
        layout->addWidget(separator);
    }

    container->setLayout(layout);
    return container;
}





