#include "DefaultImageVisitor.h"

DefaultImageVisitor::DefaultImageVisitor() : defaultImagePath("") {}

void DefaultImageVisitor::visit(const Software*) {
    defaultImagePath = ":/assets/defaults/default_software.png";
}

void DefaultImageVisitor::visit(const Videogame*) {
    defaultImagePath = ":/assets/defaults/default_videogame.png";
}

void DefaultImageVisitor::visit(const DLC*) {
    defaultImagePath = ":/assets/defaults/default_dlc.png";
}

void DefaultImageVisitor::visit(const Soundtrack*) {
    defaultImagePath = ":/assets/defaults/default_soundtrack.png";
}

QString DefaultImageVisitor::getDefaultImagePath() const {
    return defaultImagePath.isEmpty() ? ":/assets/defaults/default_unknown.png" : defaultImagePath;
}
