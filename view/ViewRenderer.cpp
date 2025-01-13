#include "ViewRenderer.h"
#include "ItemRenderer.h"
#include <QLayout>
#include <QPushButton>
#include <QFrame>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QResizeEvent>

ViewRenderer::ViewRenderer(QWidget* parent) : QWidget(parent), currentView(ViewType::Grid) {}

void ViewRenderer::setViewType(ViewType viewType) {
    currentView = viewType;
}

ViewType ViewRenderer::getViewType() const {
    return currentView;
}

void ViewRenderer::render(const QVector<AbstractItem*>& items) {
    QLayout* layout = this->layout();
    if (layout) {
        QLayoutItem* child;
        while ((child = layout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
        delete layout;
    }

    if (currentView == ViewType::Grid) {
        this->setLayout(new QVBoxLayout);
        this->layout()->addWidget(createGridView(items));
    } else if (currentView == ViewType::List) {
        this->setLayout(new QVBoxLayout);
        this->layout()->addWidget(createListView(items));
    } else if (currentView == ViewType::Details && items.size() == 1) {
        this->setLayout(new QVBoxLayout);
        this->layout()->addWidget(createDetailsView(items.first())); // pass selected object
    }
}

QWidget* ViewRenderer::createGridView(const QVector<AbstractItem*>& items) {
    int containerWidth = this->width();
    if (containerWidth < itemWidth) {
        containerWidth = 1200;
    }
    int columns = qMax(1, containerWidth / (itemWidth));

    QWidget* container = new QWidget(this);
    QGridLayout* layout = new QGridLayout(container);

    for (int i = 0; i < items.size(); ++i) {
        AbstractItem* item = items[i];
        int row = i / columns;
        int col = i % columns;

        ItemRenderer* itemRenderer = new ItemRenderer(container);
        QWidget* renderedItem = itemRenderer->render(item, ViewType::Grid);
        QPushButton* button = new QPushButton(container);
        button->setLayout(renderedItem->layout());
        button->setFixedSize(itemWidth,350); // 350 or more for Linux?

        connect(button, &QPushButton::clicked, [this, item]() {
            emit itemSelected(item);
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

        QWidget* renderedItem = itemRenderer->render(item, ViewType::List);
        QPushButton* button = new QPushButton(container);
        button->setLayout(renderedItem->layout());
        button->setFixedSize(this->width(),170);

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
    layout->addWidget(itemRenderer->render(item, ViewType::Details));

    QPushButton* editButton = new QPushButton("Edit", container);
    connect(editButton, &QPushButton::clicked, [this, item]() {
        emit editItemRequested(item);
    });

    QPushButton* deleteButton = new QPushButton("Delete", container);
    connect(deleteButton, &QPushButton::clicked, [this, item]() {
        emit deleteItemRequested(item);
    });

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    layout->addLayout(buttonLayout);
    container->setLayout(layout);

    QPushButton* backButton = new QPushButton("Back to grid", container);
    layout->addWidget(backButton);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        emit backToGridRequested(true);
    });

    container->setLayout(layout);
    return container;
}
