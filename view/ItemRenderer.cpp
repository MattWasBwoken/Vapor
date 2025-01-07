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


QWidget* ItemRenderer::createGenericWidget(const QString& imagePath, const QString& name, const QString& description, const QString& attribute, ViewType viewType, int imageWidth, int imageHeight) {
    QWidget* widget = new QWidget(this);

    if (viewType == ViewType::Grid) {
        QVBoxLayout* layout = new QVBoxLayout(widget);
        QLabel* imageLabel = new QLabel(widget);
        QPixmap pixmap(imagePath);
        imageLabel->setPixmap(pixmap.scaled(imageWidth, imageHeight, Qt::KeepAspectRatio));
        layout->addWidget(imageLabel);

        QLabel* nameLabel = new QLabel("<b>"+name+"</b>", widget);
        layout->addWidget(nameLabel);
        widget->setLayout(layout);
    } else { // List
        QHBoxLayout* layout = new QHBoxLayout(widget);
        QLabel* imageLabel = new QLabel(widget);
        QPixmap pixmap(imagePath);
        imageLabel->setPixmap(pixmap.scaled(imageWidth / 2, imageHeight / 2, Qt::KeepAspectRatio));
        layout->addWidget(imageLabel, 0);
        layout->addSpacing(10);

        QVBoxLayout* textLayout = new QVBoxLayout();
        QLabel* nameLabel = new QLabel("<b>"+name+"</b>", widget);
        QFont nameFont = nameLabel->font();
        nameFont.setPointSize(12);
        nameLabel->setFont(nameFont);
        textLayout->addWidget(nameLabel);

        QLabel* descriptionLabel = new QLabel(description.left(150) + "...", widget);
        textLayout->addWidget(descriptionLabel);

        QLabel* attributeLabel = new QLabel(attribute, widget);
        textLayout->addWidget(attributeLabel);

        layout->addLayout(textLayout, 1);
        widget->setLayout(layout);
    }

    return widget;
}


// Visitor implementations using the helper function
void ItemRenderer::visit(const Software* item) {
    setRenderedWidget(createGenericWidget(item->getImage(), item->getName(), item->getDescription(), "Version: " + item->getCurrentVersion(), currentViewType, 200, 200));
}

void ItemRenderer::visit(const Videogame* item) {
    setRenderedWidget(createGenericWidget(item->getImage(), item->getName(), item->getDescription(), "Developer: " + item->getDeveloper(), currentViewType, 200, 300));
}

void ItemRenderer::visit(const DLC* item) {
    setRenderedWidget(createGenericWidget(item->getImage(), item->getName(), item->getDescription(), "DLC Type: " + item->getDlcType(), currentViewType, 200, 300));
}

void ItemRenderer::visit(const Soundtrack* item) {
    setRenderedWidget(createGenericWidget(item->getImage(), item->getName(), item->getDescription(), "Composer: " + item->getComposer(), currentViewType, 200, 200));
}
