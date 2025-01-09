// Updated ItemRenderer.cpp
#include "ItemRenderer.h"
#include "../model/Software.h"
#include "../model/Videogame.h"
#include "../model/DLC.h"
#include "../model/Soundtrack.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>

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

        QSpacerItem* spacer = new QSpacerItem(200, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addSpacerItem(spacer);

        QLabel* imageLabel = new QLabel(widget);
        QPixmap pixmap(imagePath);
        imageLabel->setPixmap(pixmap.scaled(imageWidth, imageHeight, Qt::KeepAspectRatioByExpanding , Qt::SmoothTransformation));
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->setFixedSize(imageWidth, imageHeight);
        layout->addWidget(imageLabel, 0, Qt::AlignCenter);

        QLabel* nameLabel = new QLabel("<b>"+name+"</b>", widget);
        nameLabel->setWordWrap(true);
        nameLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(nameLabel);

        widget->setLayout(layout);
    } else if (viewType == ViewType::List){
        QHBoxLayout* layout = new QHBoxLayout(widget);

        QLabel* imageLabel = new QLabel(widget);
        QPixmap pixmap(imagePath);
        imageLabel->setPixmap(pixmap.scaled(imageWidth, imageHeight, Qt::KeepAspectRatioByExpanding , Qt::SmoothTransformation));
        layout->addWidget(imageLabel, 0);
        layout->addSpacing(10);

        QVBoxLayout* textLayout = new QVBoxLayout();
        QLabel* nameLabel = new QLabel("<b>"+name+"</b>", widget);
        QFont nameFont = nameLabel->font();
        nameFont.setPointSize(12);
        nameLabel->setFont(nameFont);
        textLayout->addWidget(nameLabel);

        QLabel* descriptionLabel = new QLabel(description.left(250) + "...", widget);
        descriptionLabel->setWordWrap(true);
        textLayout->addWidget(descriptionLabel);

        QLabel* attributeLabel = new QLabel(attribute, widget);
        textLayout->addWidget(attributeLabel);

        layout->addLayout(textLayout, 1);
        widget->setLayout(layout);
    } else if (viewType == ViewType::Details){
        QVBoxLayout* layout = new QVBoxLayout(widget);

        // Add item image
        QLabel* imageLabel = new QLabel(widget);
        QPixmap pixmap(imagePath);
        imageLabel->setPixmap(pixmap.scaled(imageWidth*2, imageHeight*2, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        imageLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(imageLabel);

        // Add item name
        QLabel* nameLabel = new QLabel("<h2>" + name + "</h2>", widget);
        nameLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(nameLabel);

        // Add description
        QLabel* descriptionLabel = new QLabel(description, widget);
        descriptionLabel->setWordWrap(true);
        descriptionLabel->setAlignment(Qt::AlignLeft);
        layout->addWidget(descriptionLabel);

        // Add specific attributes (visited-specific attributes)
        QLabel* attributeLabel = new QLabel(attribute, widget);
        attributeLabel->setWordWrap(true);
        layout->addWidget(attributeLabel);

        // Additional buttons (Edit/Delete) could be added here if needed
        QPushButton* editButton = new QPushButton("Edit", widget);
        QPushButton* deleteButton = new QPushButton("Delete", widget);
        QHBoxLayout* buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(editButton);
        buttonLayout->addWidget(deleteButton);
        layout->addLayout(buttonLayout);

        // Configure layout
        widget->setLayout(layout);
    }

    return widget;
}


// Visitor implementations using the helper function
void ItemRenderer::visit(const Software* item) {
    int imageWidth = 200;
    int imageHeight = 94;
    setRenderedWidget(createGenericWidget(item->getImage(), item->getName(), item->getDescription(), "Version: " + item->getCurrentVersion(), currentViewType, imageWidth, imageHeight));
}

void ItemRenderer::visit(const Videogame* item) {
    int imageWidth = (currentViewType == ViewType::Grid) ? 200 : 100;
    int imageHeight = (currentViewType == ViewType::Grid) ? 300 : 150;
    setRenderedWidget(createGenericWidget(item->getImage(), item->getName(), item->getDescription(), "Developer: " + item->getDeveloper(), currentViewType, imageWidth, imageHeight));
}

void ItemRenderer::visit(const DLC* item) {
    // Determine sizes based on currentViewType
    int imageWidth = (currentViewType == ViewType::Grid) ? 200 : 100;
    int imageHeight = (currentViewType == ViewType::Grid) ? 300 : 150;

    QWidget* widget = createGenericWidget(item->getImage(), item->getName(), item->getDescription(), "DLC Type: " + item->getDlcType(), currentViewType, imageWidth, imageHeight);

    QLabel* imageLabel = widget->findChild<QLabel*>();
    if (imageLabel) {
        QPixmap pixmap(item->getImage());
        pixmap = pixmap.scaled(imageWidth, imageHeight, Qt::KeepAspectRatioByExpanding , Qt::SmoothTransformation);

        QPixmap overlayedPixmap = pixmap;
        QPainter painter(&overlayedPixmap);
        painter.setRenderHint(QPainter::Antialiasing);

        // Load the arrow icon
        QPixmap arrowPixmap(":/assets/dlc_icon.png");
        arrowPixmap = arrowPixmap.scaled(imageWidth/4, imageHeight/4, Qt::KeepAspectRatioByExpanding , Qt::SmoothTransformation);

        // Calculate position for overlay (bottom-right corner)
        int overlayX = overlayedPixmap.width()-arrowPixmap.width()-1;
        int overlayY = overlayedPixmap.height()-arrowPixmap.height()-1;

        // Draw the arrow icon on top of the DLC image
        painter.drawPixmap(overlayX, overlayY, arrowPixmap);
        painter.end();

        imageLabel->setPixmap(overlayedPixmap);
    }

    setRenderedWidget(widget);
}

void ItemRenderer::visit(const Soundtrack* item) {
    // Determine sizes based on currentViewType
    int imageWidth = (currentViewType == ViewType::Grid) ? 200 : 100;
    int imageHeight = (currentViewType == ViewType::Grid) ? 200 : 100;

    QWidget* widget = createGenericWidget(item->getImage(), item->getName(), item->getDescription(), "Composer: " + item->getComposer(), currentViewType, imageWidth, imageHeight);

    QLabel* imageLabel = widget->findChild<QLabel*>();
    if (imageLabel) {
        QPixmap pixmap(item->getImage());
        pixmap = pixmap.scaled(imageWidth, imageHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        QPixmap circularPixmap(pixmap.size());
        circularPixmap.fill(Qt::transparent);

        QPainter painter(&circularPixmap);
        painter.setRenderHint(QPainter::Antialiasing);

        // Create circular mask
        QPainterPath outerCircle;
        outerCircle.addEllipse(0, 0, pixmap.width(), pixmap.height());

        QPainterPath innerCircle;
        const int holeDiameter = pixmap.width() / 5; // Diameter of the hole
        const int holeX = (pixmap.width() - holeDiameter) / 2; // Centering the hole
        const int holeY = (pixmap.height() - holeDiameter) / 2;
        innerCircle.addEllipse(holeX, holeY, holeDiameter, holeDiameter);
        QPainterPath ringShape = outerCircle.subtracted(innerCircle);

        // Apply mask
        painter.setClipPath(ringShape);
        painter.drawPixmap(0, 0, pixmap);

        painter.end();
        imageLabel->setPixmap(circularPixmap);
    }

    setRenderedWidget(widget);
}





