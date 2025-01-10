#include "SearchItemVisitor.h"
#include "Software.h"
#include "Videogame.h"
#include "DLC.h"
#include "Soundtrack.h"
#include <QString>

SearchItemVisitor::SearchItemVisitor(const QString& searchString, const QString& typeFilter, const QString& genreFilter, bool winCompatibilityFilter)
    : searchString(searchString), typeFilter(typeFilter), genreFilter(genreFilter), winCompatibilityFilter(winCompatibilityFilter) {}

void SearchItemVisitor::visit(const Software* item) {
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
    if (this->winCompatibilityFilter && !item->getWinCompatibility()) {
        matches = false;
    }
    if (matches) {
        this->results.push_back(item);
    }
}

void SearchItemVisitor::visit(const Videogame* item) {
    bool matches = true;
    if (!this->searchString.isEmpty()) {
        QString lowerSearchString = this->searchString.toLower();
        QString lowerName = item->getName().toLower();
        QString lowerDescription = item->getDescription().toLower();
        QString lowerDeveloper = item->getDeveloper().toLower();
        if (!(lowerName.contains(lowerSearchString) || lowerDescription.contains(lowerSearchString) || lowerDeveloper.contains(lowerSearchString))) {
            matches = false;
        }
    }
    if (!this->typeFilter.isEmpty() && this->typeFilter != "All" && this->typeFilter != "Videogame") {
        matches = false;
    }
    if(!this->genreFilter.isEmpty() && item->getGenre() != this->genreFilter) {
        matches = false;
    }
    if (matches) {
        this->results.push_back(item);
    }
}

void SearchItemVisitor::visit(const DLC* item) {
    bool matches = true;
    if (!this->searchString.isEmpty()) {
        QString lowerSearchString = this->searchString.toLower();
        QString lowerName = item->getName().toLower();
        QString lowerDescription = item->getDescription().toLower();
        QString lowerDeveloper = item->getDeveloper().toLower();
        if (!(lowerName.contains(lowerSearchString) || lowerDescription.contains(lowerSearchString) || lowerDeveloper.contains(lowerSearchString))) {
            matches = false;
        }
    }
    if (!this->typeFilter.isEmpty() && this->typeFilter != "All" && this->typeFilter != "DLC") {
        matches = false;
    }
    if(!this->genreFilter.isEmpty() && item->getGenre() != this->genreFilter) {
        matches = false;
    }
    if (matches) {
        this->results.push_back(item);
    }
}

void SearchItemVisitor::visit(const Soundtrack* item) {
    bool matches = true;
    if (!this->searchString.isEmpty()) {
        QString lowerSearchString = this->searchString.toLower();
        QString lowerName = item->getName().toLower();
        QString lowerDescription = item->getDescription().toLower();
        QString lowerDeveloper = item->getDeveloper().toLower();
        QString lowerComposer = item->getComposer().toLower();
        if (!(lowerName.contains(lowerSearchString) || lowerDescription.contains(lowerSearchString) || lowerDeveloper.contains(lowerSearchString) || lowerComposer.contains(lowerSearchString))) {
            matches = false;
        }
    }
    if (!this->typeFilter.isEmpty() && this->typeFilter != "All" && this->typeFilter != "Soundtrack") {
        matches = false;
    }
    if(!this->genreFilter.isEmpty() && item->getGenre() != this->genreFilter) {
        matches = false;
    }
    if (matches) {
        this->results.push_back(item);
    }
}

const QVector<const AbstractItem*>& SearchItemVisitor::getResults() const {
    return this->results;
}

void SearchItemVisitor::clearResults() {
    this->results.clear();
}
