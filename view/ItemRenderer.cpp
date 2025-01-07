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

QWidget* ItemRenderer::render(AbstractItem* item, ViewType viewType) {
    currentViewType = viewType; // Set the current view type
    item->accept(this);         // Use the visitor pattern
    return renderedWidget;
}


void ItemRenderer::visit(const Software* item) {
    QWidget* widget = new QWidget(this);
    if (currentViewType == ViewType::Grid) {
        QVBoxLayout* layout = new QVBoxLayout(widget);

        QLabel* imageLabel = new QLabel(widget);
        QPixmap pixmap(item->getImage());
        imageLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
        layout->addWidget(imageLabel);

        QLabel* nameLabel = new QLabel(item->getName(), widget);
        layout->addWidget(nameLabel);

        widget->setLayout(layout);
    } else if (currentViewType == ViewType::List) {
        QHBoxLayout* layout = new QHBoxLayout(widget);

        QLabel* imageLabel = new QLabel(widget);
        QPixmap pixmap(item->getImage());
        imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
        layout->addWidget(imageLabel);

        QVBoxLayout* textLayout = new QVBoxLayout();
        QLabel* nameLabel = new QLabel(item->getName(), widget);
        textLayout->addWidget(nameLabel);

        QLabel* descriptionLabel = new QLabel(item->getDescription().left(75) + "...", widget);
        textLayout->addWidget(descriptionLabel);

        QLabel* attributeLabel = new QLabel("Version: " + item->getCurrentVersion(), widget);
        textLayout->addWidget(attributeLabel);

        layout->addLayout(textLayout);
        widget->setLayout(layout);
    }
    setRenderedWidget(widget);
}

void ItemRenderer::visit(const Videogame* item) {
    QWidget* widget = new QWidget(this);
    if (currentViewType == ViewType::Grid) {
        QVBoxLayout* layout = new QVBoxLayout(widget);

        QLabel* imageLabel = new QLabel(widget);
        QPixmap pixmap(item->getImage());
        imageLabel->setPixmap(pixmap.scaled(200, 300, Qt::KeepAspectRatio));
        layout->addWidget(imageLabel);

        QLabel* nameLabel = new QLabel(item->getName(), widget);
        layout->addWidget(nameLabel);

        widget->setLayout(layout);
    } else if (currentViewType == ViewType::List) {
        QHBoxLayout* layout = new QHBoxLayout(widget);

        QLabel* imageLabel = new QLabel(widget);
        QPixmap pixmap(item->getImage());
        imageLabel->setPixmap(pixmap.scaled(100, 150, Qt::KeepAspectRatio));
        layout->addWidget(imageLabel);

        QVBoxLayout* textLayout = new QVBoxLayout();
        QLabel* nameLabel = new QLabel(item->getName(), widget);
        textLayout->addWidget(nameLabel);

        QLabel* descriptionLabel = new QLabel(item->getDescription().left(75) + "...", widget);
        textLayout->addWidget(descriptionLabel);

        QLabel* attributeLabel = new QLabel("Developer: " + item->getDeveloper(), widget);
        textLayout->addWidget(attributeLabel);

        layout->addLayout(textLayout);
        widget->setLayout(layout);
    }
    setRenderedWidget(widget);
}


void ItemRenderer::visit(const DLC* item) {
    QWidget* widget = new QWidget(this);
    if (currentViewType == ViewType::Grid) {
        QVBoxLayout* layout = new QVBoxLayout(widget);

        QLabel* imageLabel = new QLabel(widget);
        QPixmap pixmap(item->getImage());
        imageLabel->setPixmap(pixmap.scaled(200, 300, Qt::KeepAspectRatio));
        layout->addWidget(imageLabel);

        QLabel* nameLabel = new QLabel(item->getName(), widget);
        layout->addWidget(nameLabel);

        widget->setLayout(layout);
    } else if (currentViewType == ViewType::List) {
        QHBoxLayout* layout = new QHBoxLayout(widget);

        QLabel* imageLabel = new QLabel(widget);
        QPixmap pixmap(item->getImage());
        imageLabel->setPixmap(pixmap.scaled(100, 150, Qt::KeepAspectRatio));
        layout->addWidget(imageLabel);

        QVBoxLayout* textLayout = new QVBoxLayout();
        QLabel* nameLabel = new QLabel(item->getName(), widget);
        textLayout->addWidget(nameLabel);

        QLabel* descriptionLabel = new QLabel(item->getDescription().left(75) + "...", widget);
        textLayout->addWidget(descriptionLabel);

        QLabel* attributeLabel = new QLabel("DLC Type: " + item->getDlcType(), widget);
        textLayout->addWidget(attributeLabel);

        layout->addLayout(textLayout);
        widget->setLayout(layout);
    }
    setRenderedWidget(widget);
}

void ItemRenderer::visit(const Soundtrack* item) {
    QWidget* widget = new QWidget(this);
    if (currentViewType == ViewType::Grid) {
        QVBoxLayout* layout = new QVBoxLayout(widget);

        QLabel* imageLabel = new QLabel(widget);
        QPixmap pixmap(item->getImage());
        imageLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
        layout->addWidget(imageLabel);

        QLabel* nameLabel = new QLabel(item->getName(), widget);
        layout->addWidget(nameLabel);

        widget->setLayout(layout);
    } else if (currentViewType == ViewType::List) {
        QHBoxLayout* layout = new QHBoxLayout(widget);

        QLabel* imageLabel = new QLabel(widget);
        QPixmap pixmap(item->getImage());
        imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
        layout->addWidget(imageLabel);

        QVBoxLayout* textLayout = new QVBoxLayout();
        QLabel* nameLabel = new QLabel(item->getName(), widget);
        textLayout->addWidget(nameLabel);

        QLabel* descriptionLabel = new QLabel(item->getDescription().left(75) + "...", widget);
        textLayout->addWidget(descriptionLabel);

        QLabel* attributeLabel = new QLabel("Composer: " + item->getComposer(), widget);
        textLayout->addWidget(attributeLabel);

        layout->addLayout(textLayout);
        widget->setLayout(layout);
    }
    setRenderedWidget(widget);
}
