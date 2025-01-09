#include "ViewRenderer.h"
#include "ItemRenderer.h"
#include <QLayout>
#include <QPushButton>
#include <QFrame>
#include <QDebug>
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
    if (currentView == ViewType::Grid) {
        this->setLayout(new QVBoxLayout);
        this->layout()->addWidget(createGridView(items));
    } else if (currentView == ViewType::List) {
        this->setLayout(new QVBoxLayout);
        this->layout()->addWidget(createListView(items));
    } else if (currentView == ViewType::Details && items.size() == 1) { //mostra i dettagli solo se c'è un singolo elemento selezionato
        this->setLayout(new QVBoxLayout);
        this->layout()->addWidget(createDetailsView(items.first())); // Passa l'oggetto selezionato
    }
}


QWidget* ViewRenderer::createGridView(const QVector<AbstractItem*>& items) {
    const int itemWidth = 200;
    int containerWidth = this->width();
    if (containerWidth < itemWidth) {
        containerWidth = 1200;
    }
    int columns = qMax(1, containerWidth / (itemWidth+20));

    QWidget* container = new QWidget(this);
    QGridLayout* layout = new QGridLayout(container);

    for (int i = 0; i < items.size(); ++i) {
        AbstractItem* item = items[i];
        int row = i / columns;
        int col = i % columns;

        ItemRenderer* itemRenderer = new ItemRenderer(container);
        QWidget* renderedItem = itemRenderer->render(item, ItemRenderer::ViewType::Grid);
        QPushButton* button = new QPushButton(container);
        button->setLayout(renderedItem->layout()); // Use the rendered item's layout
        button->setFixedSize(220,350);

        connect(button, &QPushButton::clicked, [this, item]() {
            emit itemSelected(item); // Emit signal on click
        });
        layout->addWidget(button, row, col);
    }

    container->setLayout(layout);
    return container;
}

QWidget* ViewRenderer::createListView(const QVector<AbstractItem*>& items) {
    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(container);

    for (AbstractItem* item : items) {
        ItemRenderer* itemRenderer = new ItemRenderer(container);

        QWidget* renderedItem = itemRenderer->render(item, ItemRenderer::ViewType::List);
        QPushButton* button = new QPushButton(container);
        button->setLayout(renderedItem->layout());
        button->setFixedSize(this->width(),150);

        connect(button, &QPushButton::clicked, [this, item]() {
            emit itemSelected(item); // Emit signal on click
        });

        layout->addWidget(button);

        QFrame* separator = new QFrame(container);
        separator->setFrameShape(QFrame::HLine);
        separator->setFrameShadow(QFrame::Sunken);
        layout->addWidget(separator);
    }

    container->setLayout(layout);
    return container;
}


QWidget* ViewRenderer::createDetailsView(AbstractItem* item) {
    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(container);

    ItemRenderer* itemRenderer = new ItemRenderer(container);
    layout->addWidget(itemRenderer->render(item, ItemRenderer::ViewType::Details));

    // Aggiungi un pulsante "Back"
    QPushButton* backButton = new QPushButton("Back to grid", container);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, [this]() {
        currentView = ViewType::Grid;
        //render(items); // Torna alla vista lista
    });
    container->setLayout(layout);
    return container;
}
