#include "SearchItemVisitor.h"
#include "Software.h"
#include "Videogame.h"
#include "DLC.h"
#include "Soundtrack.h"

SearchItemVisitor::SearchItemVisitor(const QString& searchString, const QString& typeFilter): searchString(searchString), typeFilter(typeFilter) {}

void SearchItemVisitor::visit(Software* item) {
    bool matches = true;
    if (!this->searchString.isEmpty()) {
        QString lowerSearchString = this->searchString.toLower();
        QString lowerName = item->getName().toLower();
        QString lowerDescription = item->getDescription().toLower();
        if (!(lowerName.contains(lowerSearchString) || lowerDescription.contains(lowerSearchString))) {
            matches = false;
        }
    }
    if (!this->typeFilter.isEmpty() && this->typeFilter != "All" && this->typeFilter != "Software") {
        matches = false;
    }
    if (matches) {
        results.push_back(item);
    }
}

void SearchItemVisitor::visit(Videogame* item) {
    bool matches = true;
    if (!this->searchString.isEmpty()) {
        QString lowerSearchString = this->searchString.toLower();
        QString lowerName = item->getName().toLower();
        QString lowerDescription = item->getDescription().toLower();
        QString lowerDeveloper = item->getDeveloper().toLower();
        QString lowerGenre = item->getGenre().toLower();
        if (!(lowerName.contains(lowerSearchString) || lowerDescription.contains(lowerSearchString) || lowerDeveloper.contains(lowerSearchString) || lowerGenre.contains(lowerSearchString))) {
            matches = false;
        }
    }
    if (!this->typeFilter.isEmpty() && this->typeFilter != "All" && this->typeFilter != "Videogame") {
        matches = false;
    }
    if (matches) {
        results.push_back(item);
    }
}

void SearchItemVisitor::visit(DLC* item) {
    bool matches = true;
    if (!this->searchString.isEmpty()) {
        QString lowerSearchString = this->searchString.toLower();
        QString lowerName = item->getName().toLower();
        QString lowerDescription = item->getDescription().toLower();
        QString lowerDeveloper = item->getDeveloper().toLower();
        QString lowerGenre = item->getGenre().toLower();
        if (!(lowerName.contains(lowerSearchString) || lowerDescription.contains(lowerSearchString) || lowerDeveloper.contains(lowerSearchString) || lowerGenre.contains(lowerSearchString))) {
            matches = false;
        }
    }
    if (!this->typeFilter.isEmpty() && this->typeFilter != "All" && this->typeFilter != "DLC") {
        matches = false;
    }
    if (matches) {
        results.push_back(item);
    }
}

void SearchItemVisitor::visit(Soundtrack* item) {
    bool matches = true;
    if (!this->searchString.isEmpty()) {
        QString lowerSearchString = this->searchString.toLower();
        QString lowerName = item->getName().toLower();
        QString lowerDescription = item->getDescription().toLower();
        QString lowerDeveloper = item->getDeveloper().toLower();
        QString lowerGenre = item->getGenre().toLower();
        QString lowerComposer = item->getComposer().toLower();
        if (!(lowerName.contains(lowerSearchString) || lowerDescription.contains(lowerSearchString) || lowerDeveloper.contains(lowerSearchString) || lowerGenre.contains(lowerSearchString) || lowerComposer.contains(lowerSearchString))) {
            matches = false;
        }
    }
    if (!this->typeFilter.isEmpty() && this->typeFilter != "All" && this->typeFilter != "Soundtrack") {
        matches = false;
    }
    if (matches) {
        results.push_back(item);
    }
}

const QVector<AbstractItem*>& SearchItemVisitor::getResults() const {
    return this->results;
}

void SearchItemVisitor::clearResults() {
    this->results.clear();
}
