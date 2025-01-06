#include "DefaultImageVisitor.h"

DefaultImageVisitor::DefaultImageVisitor() : defaultImagePath("") {}

void DefaultImageVisitor::visit(const Software*) {
    defaultImagePath = ":/assets/default_software.png";
}

void DefaultImageVisitor::visit(const Videogame*) {
    defaultImagePath = ":/assets/default_videogame.png";
}

void DefaultImageVisitor::visit(const DLC*) {
    defaultImagePath = ":/assets/default_dlc.png";
}

void DefaultImageVisitor::visit(const Soundtrack*) {
    defaultImagePath = ":/assets/default_soundtrack.png";
}

QString DefaultImageVisitor::getDefaultImagePath() const {
    return defaultImagePath.isEmpty() ? ":/assets/default_unknown.png" : defaultImagePath;
}
