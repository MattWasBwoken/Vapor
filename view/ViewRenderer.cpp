#include "ViewRenderer.h"
#include "ItemRenderer.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QResizeEvent>

ViewRenderer::ViewRenderer(QWidget* parent) : QWidget(parent), currentView(ListView) {}

void ViewRenderer::setViewType(bool isGridView) {
    currentView = isGridView ? GridView : ListView;
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
    if (currentView == ListView) {
        this->setLayout(new QVBoxLayout);
        this->layout()->addWidget(createListView(items));
    } else {
        this->setLayout(new QVBoxLayout);
        this->layout()->addWidget(createGridView(items));
    }
}

QWidget* ViewRenderer::createListView(const QVector<AbstractItem*>& items) {
    // Create a vertical list view
    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(container);

    for (AbstractItem* item : items) {
        ItemRenderer* itemRenderer = new ItemRenderer(container);
        layout->addWidget(itemRenderer->render(item));
    }

    container->setLayout(layout);
    return container;
}

QWidget* ViewRenderer::createGridView(const QVector<AbstractItem*>& items) {
    // Calculate the number of columns dynamically
    const int itemWidth = 150; // Approximate width of an item in pixels
    int containerWidth = this->width(); // The width of the current ViewRenderer widget
    int columns = qMax(1, containerWidth / itemWidth); // Ensure at least 1 column

    QWidget* container = new QWidget(this);
    QGridLayout* layout = new QGridLayout(container);

    for (int i = 0; i < items.size(); ++i) {
        int row = i / columns;
        int col = i % columns;

        ItemRenderer* itemRenderer = new ItemRenderer(container);
        layout->addWidget(itemRenderer->render(items[i]), row, col);
    }

    container->setLayout(layout);
    return container;
}

void ViewRenderer::resizeEvent(QResizeEvent* event) {
    // Re-render on resize to adjust the grid dynamically
    if (currentView == GridView) {
        emit renderRequested(); // Custom signal to request a re-render
    }
    QWidget::resizeEvent(event);
}
