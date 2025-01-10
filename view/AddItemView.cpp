#include "AddItemView.h"
#include "../model/Software.h"
#include "../model/DLC.h"
#include "../model/Videogame.h"
#include "../model/Soundtrack.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>


AddItemView::AddItemView(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    // type selection
    typeComboBox = new QComboBox(this);
    typeComboBox->addItems({tr("Software"), tr("Videogame"), tr("DLC"), tr("Soundtrack")});
    mainLayout->addWidget(new QLabel("Type:"));
    mainLayout->addWidget(typeComboBox);
    // basic information
    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText(tr("Name"));
    mainLayout->addWidget(new QLabel("Name:"));
    mainLayout->addWidget(nameEdit);
    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setPlaceholderText(tr("Description"));
    mainLayout->addWidget(new QLabel("Description:"));
    mainLayout->addWidget(descriptionEdit);

    // Software specific
    versionEdit = new QLineEdit(this);
    versionEdit->setPlaceholderText("Current Version");
    mainLayout->addWidget(new QLabel("Version:"));
    mainLayout->addWidget(versionEdit);
    winCompatibilityCheck = new QCheckBox("Windows Compatible", this);
    mainLayout->addWidget(winCompatibilityCheck);

    // Videogame specific
    developerEdit = new QLineEdit(this);
    developerEdit->setPlaceholderText(tr("Developer"));
    mainLayout->addWidget(new QLabel("Developer:"));
    mainLayout->addWidget(developerEdit);
    genreEdit = new QLineEdit(this);
    genreEdit->setPlaceholderText(tr("Genre"));
    mainLayout->addWidget(new QLabel("Genre:"));
    mainLayout->addWidget(genreEdit);
    releaseDateEdit = new QLineEdit(this);
    releaseDateEdit->setPlaceholderText(tr("Release Date"));
    mainLayout->addWidget(new QLabel("Release Date:"));
    mainLayout->addWidget(releaseDateEdit);

    // DLC specific
    dlcTypeEdit = new QLineEdit(this);
    dlcTypeEdit->setPlaceholderText(tr("DLC Type"));
    mainLayout->addWidget(new QLabel("DLC Type:"));
    mainLayout->addWidget(dlcTypeEdit);
    standaloneCheck = new QCheckBox(tr("Standalone"), this);
    mainLayout->addWidget(standaloneCheck);

    //Soundtrack specific
    composerEdit = new QLineEdit(this);
    composerEdit->setPlaceholderText(tr("Composer"));
    mainLayout->addWidget(new QLabel("Composer:"));
    mainLayout->addWidget(composerEdit);
    tracksNumberEdit = new QLineEdit(this);
    tracksNumberEdit->setPlaceholderText(tr("Tracks Number"));
    mainLayout->addWidget(new QLabel("Tracks Number:"));
    mainLayout->addWidget(tracksNumberEdit);

    // Button layout
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* addButton = new QPushButton("Add", this);
    QPushButton* cancelButton = new QPushButton("Cancel", this);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);
    connect(addButton, &QPushButton::clicked, this, &AddItemView::addItem);
    connect(cancelButton, &QPushButton::clicked, this, &AddItemView::handleCancel);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}
void AddItemView::addItem() {
    QString type = typeComboBox->currentText();
    unsigned int id = 0; // da decidere come generare l'id, omettiamo per ora
    QString name = nameEdit->text();
    QString description = descriptionEdit->toPlainText();
    AbstractItem *newItem = nullptr;
    if (type == "Software") {
        newItem = new Software(id, name, description, versionEdit->text(), winCompatibilityCheck->isChecked());
    }
    else if (type == "Videogame") {
        bool ok;
        unsigned int releaseDate = releaseDateEdit->text().toUInt(&ok);
        if(!ok){
            releaseDate=0;
        }
        newItem = new Videogame(id, name, description, developerEdit->text(), genreEdit->text(),releaseDate );
    }
    else if (type == "DLC") {
        bool ok;
        unsigned int releaseDate = releaseDateEdit->text().toUInt(&ok);
        if(!ok){
            releaseDate=0;
        }
        newItem = new DLC(id, name, description, developerEdit->text(), genreEdit->text(),releaseDate, dlcTypeEdit->text(), standaloneCheck->isChecked());
    }
    else if (type == "Soundtrack") {
        bool ok;
        unsigned int releaseDate = releaseDateEdit->text().toUInt(&ok);
        if(!ok){
            releaseDate=0;
        }
        bool ok2;
        unsigned int tracksNumber = tracksNumberEdit->text().toUInt(&ok2);
        if(!ok2){
            tracksNumber = 0;
        }
        newItem = new Soundtrack(id, name, description, developerEdit->text(), genreEdit->text(), releaseDate, composerEdit->text(), tracksNumber);

    }
    if(newItem){
        emit itemAdded(newItem);
    }
    emit backToGridRequested();
}
void AddItemView::handleCancel() {
    emit backToGridRequested();
}
