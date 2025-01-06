// Updated ItemRenderer.cpp
#include "ItemRenderer.h"
#include "../model/Software.h"
#include "../model/Videogame.h"
#include "../model/DLC.h"
#include "../model/Soundtrack.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>

ItemRenderer::ItemRenderer(QWidget* parent) : QWidget(parent), renderedWidget(nullptr) {}

void ItemRenderer::setRenderedWidget(QWidget* widget) {
    if (renderedWidget) {
        delete renderedWidget;
    }
    renderedWidget = widget;
}

QWidget* ItemRenderer::render(AbstractItem* item) {
    item->accept(this); // Delegate to visitor methods
    return renderedWidget;
}

void ItemRenderer::visit(const Software* item) {
    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(widget);

    QLabel* imageLabel = new QLabel(widget);
    QPixmap pixmap(item->getImage());
    imageLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
    layout->addWidget(imageLabel);

    QLabel* nameLabel = new QLabel(item->getName(), widget);
    layout->addWidget(nameLabel);

    widget->setLayout(layout);
    setRenderedWidget(widget);
}

void ItemRenderer::visit(const Videogame* item) {
    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(widget);

    QLabel* imageLabel = new QLabel(widget);
    QPixmap pixmap(item->getImage());
    imageLabel->setPixmap(pixmap.scaled(200, 300, Qt::KeepAspectRatio));
    layout->addWidget(imageLabel);

    QLabel* nameLabel = new QLabel(item->getName(), widget);
    layout->addWidget(nameLabel);

    widget->setLayout(layout);
    setRenderedWidget(widget);
}

void ItemRenderer::visit(const DLC* item) {
    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(widget);

    QLabel* imageLabel = new QLabel(widget);
    QPixmap pixmap(item->getImage());
    imageLabel->setPixmap(pixmap.scaled(200, 300, Qt::KeepAspectRatio));
    layout->addWidget(imageLabel);

    QLabel* nameLabel = new QLabel(item->getName(), widget);
    layout->addWidget(nameLabel);

    widget->setLayout(layout);
    setRenderedWidget(widget);
}

void ItemRenderer::visit(const Soundtrack* item) {
    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(widget);

    QLabel* imageLabel = new QLabel(widget);
    QPixmap pixmap(item->getImage());
    imageLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
    layout->addWidget(imageLabel);

    QLabel* nameLabel = new QLabel(item->getName(), widget);
    layout->addWidget(nameLabel);

    widget->setLayout(layout);
    setRenderedWidget(widget);
}
