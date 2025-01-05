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
    imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
    layout->addWidget(imageLabel);

    QLabel* nameLabel = new QLabel(item->getName(), widget);
    layout->addWidget(nameLabel);

    QLabel* versionLabel = new QLabel("Version: " + item->getCurrentVersion(), widget);
    layout->addWidget(versionLabel);

    QLabel* compatibilityLabel = new QLabel(item->getWinCompatibility() ? "Windows Compatible" : "Not Windows Compatible", widget);
    layout->addWidget(compatibilityLabel);

    widget->setLayout(layout);
    setRenderedWidget(widget);
}

void ItemRenderer::visit(const Videogame* item) {
    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(widget);

    QLabel* imageLabel = new QLabel(widget);
    QPixmap pixmap(item->getImage());
    imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
    layout->addWidget(imageLabel);

    QLabel* nameLabel = new QLabel(item->getName(), widget);
    layout->addWidget(nameLabel);

    QLabel* developerLabel = new QLabel("Developer: " + item->getDeveloper(), widget);
    layout->addWidget(developerLabel);

    QLabel* genreLabel = new QLabel("Genre: " + item->getGenre(), widget);
    layout->addWidget(genreLabel);

    QLabel* releaseDateLabel = new QLabel("Release Date: " + QString::number(item->getReleaseDate()), widget);
    layout->addWidget(releaseDateLabel);

    widget->setLayout(layout);
    setRenderedWidget(widget);
}

void ItemRenderer::visit(const DLC* item) {
    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(widget);

    QLabel* imageLabel = new QLabel(widget);
    QPixmap pixmap(item->getImage());
    imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
    layout->addWidget(imageLabel);

    QLabel* nameLabel = new QLabel(item->getName(), widget);
    layout->addWidget(nameLabel);

    QLabel* dlcTypeLabel = new QLabel("DLC Type: " + item->getDlcType(), widget);
    layout->addWidget(dlcTypeLabel);

    QLabel* standaloneLabel = new QLabel(item->getStandalone() ? "Standalone" : "Requires Base Game", widget);
    layout->addWidget(standaloneLabel);

    widget->setLayout(layout);
    setRenderedWidget(widget);
}

void ItemRenderer::visit(const Soundtrack* item) {
    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(widget);

    QLabel* imageLabel = new QLabel(widget);
    QPixmap pixmap(item->getImage());
    imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
    layout->addWidget(imageLabel);

    QLabel* nameLabel = new QLabel(item->getName(), widget);
    layout->addWidget(nameLabel);

    QLabel* composerLabel = new QLabel("Composer: " + item->getComposer(), widget);
    layout->addWidget(composerLabel);

    QLabel* tracksLabel = new QLabel("Tracks: " + QString::number(item->getTracksNumber()), widget);
    layout->addWidget(tracksLabel);

    widget->setLayout(layout);
    setRenderedWidget(widget);
}
