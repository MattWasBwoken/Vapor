#include "ItemFactory.h"
#include <QInputDialog>
#include <QMessageBox>
#include "Software.h"
#include "Videogame.h"
#include "DLC.h"
#include "Soundtrack.h"

bool getBool(QWidget *parent, const QString &title, const QString &label, bool defaultValue = false) {
    QMessageBox msgBox(parent);
    msgBox.setWindowTitle(title);
    msgBox.setText(label);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(defaultValue ? QMessageBox::Yes : QMessageBox::No);

    return msgBox.exec() == QMessageBox::Yes;
}

AbstractItem* ItemFactory::createItem(QWidget *parent) {
    // Step 1: Prompt for item type
    QStringList itemTypes = { "Software", "Videogame", "DLC", "Soundtrack" };
    bool ok;
    QString selectedType = QInputDialog::getItem(parent, QObject::tr("Select Item Type"), QObject::tr("Item Type:"), itemTypes, 0, false, &ok);

    if (!ok || selectedType.isEmpty()) {
        return nullptr; // User canceled
    }

    // Step 2: Prompt for item attributes
    unsigned int id = QInputDialog::getInt(parent, QObject::tr("Enter ID"), QObject::tr("ID:"), 0, 0, 100000, 1, &ok);
    if (!ok) return nullptr;

    QString name = QInputDialog::getText(parent, QObject::tr("Enter Name"), QObject::tr("Name:"), QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return nullptr;

    QString description = QInputDialog::getText(parent, QObject::tr("Enter Description"), QObject::tr("Description:"), QLineEdit::Normal, "", &ok);
    if (!ok) return nullptr;

    QString imagePath = QInputDialog::getText(parent, QObject::tr("Enter Image Path"), QObject::tr("Image Path:"), QLineEdit::Normal, "", &ok);
    if (!ok) return nullptr;

    AbstractItem *newItem = nullptr;

    if (selectedType == "Software") {
        QString currentVersion = QInputDialog::getText(parent, QObject::tr("Enter Current Version"), QObject::tr("Current Version:"), QLineEdit::Normal, "", &ok);
        if (!ok) return nullptr;

        bool winCompatibility = getBool(parent, QObject::tr("Windows Compatibility"), QObject::tr("Is it compatible with Windows?"), false);
        if (!ok) return nullptr;

        newItem = new Software(id, name, description, currentVersion, winCompatibility, imagePath);
    } else if (selectedType == "Videogame") {
        QString developer = QInputDialog::getText(parent, QObject::tr("Enter Developer"), QObject::tr("Developer:"), QLineEdit::Normal, "", &ok);
        if (!ok) return nullptr;

        QString genre = QInputDialog::getText(parent, QObject::tr("Enter Genre"), QObject::tr("Genre:"), QLineEdit::Normal, "", &ok);
        if (!ok) return nullptr;

        unsigned int releaseDate = QInputDialog::getInt(parent, QObject::tr("Enter Release Date"), QObject::tr("Release Date:"), 2022, 1970, 2100, 1, &ok);
        if (!ok) return nullptr;

        newItem = new Videogame(id, name, description, developer, genre, releaseDate, imagePath);
    } else if (selectedType == "DLC") {
        QString developer = QInputDialog::getText(parent, QObject::tr("Enter Developer"), QObject::tr("Developer:"), QLineEdit::Normal, "", &ok);
        if (!ok) return nullptr;

        QString genre = QInputDialog::getText(parent, QObject::tr("Enter Genre"), QObject::tr("Genre:"), QLineEdit::Normal, "", &ok);
        if (!ok) return nullptr;

        unsigned int releaseDate = QInputDialog::getInt(parent, QObject::tr("Enter Release Date"), QObject::tr("Release Date:"), 2022, 1970, 2100, 1, &ok);
        if (!ok) return nullptr;

        QString dlcType = QInputDialog::getText(parent, QObject::tr("Enter DLC Type"), QObject::tr("DLC Type:"), QLineEdit::Normal, "", &ok);
        if (!ok) return nullptr;

        bool standalone = getBool(parent, QObject::tr("Standalone"), QObject::tr("Is it standalone?"), false);
        if (!ok) return nullptr;

        newItem = new DLC(id, name, description, developer, genre, releaseDate, dlcType, standalone, imagePath);
    } else if (selectedType == "Soundtrack") {
        QString developer = QInputDialog::getText(parent, QObject::tr("Enter Developer"), QObject::tr("Developer:"), QLineEdit::Normal, "", &ok);
        if (!ok) return nullptr;

        QString genre = QInputDialog::getText(parent, QObject::tr("Enter Genre"), QObject::tr("Genre:"), QLineEdit::Normal, "", &ok);
        if (!ok) return nullptr;

        unsigned int releaseDate = QInputDialog::getInt(parent, QObject::tr("Enter Release Date"), QObject::tr("Release Date:"), 2022, 1970, 2100, 1, &ok);
        if (!ok) return nullptr;

        QString composer = QInputDialog::getText(parent, QObject::tr("Enter Composer"), QObject::tr("Composer:"), QLineEdit::Normal, "", &ok);
        if (!ok) return nullptr;

        unsigned int tracksNumber = QInputDialog::getInt(parent, QObject::tr("Enter Number of Tracks"), QObject::tr("Tracks Number:"), 1, 1, 100, 1, &ok);
        if (!ok) return nullptr;

        newItem = new Soundtrack(id, name, description, developer, genre, releaseDate, composer, tracksNumber, imagePath);
    }

    return newItem;
}
