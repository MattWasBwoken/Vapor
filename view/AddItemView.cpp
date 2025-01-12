#include "AddItemView.h"
#include "../model/Software.h"
#include "../model/DLC.h"
#include "../model/Videogame.h"
#include "../model/Soundtrack.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QImage>

void AddItemView::resetFields() {
    typeComboBox->setCurrentIndex(0);
    nameEdit->clear();
    descriptionEdit->clear();
    versionEdit->clear();
    winCompatibilityCheck->setChecked(false);
    developerEdit->clear();
    dlcdeveloperEdit->clear();
    soundtrackdeveloperEdit->clear();
    genreEdit->clear();
    dlcgenreEdit->clear();
    soundtrackgenreEdit->clear();
    releaseDateEdit->clear();
    dlcreleaseDateEdit->clear();
    soundtrackreleaseDateEdit->clear();
    dlcTypeEdit->clear();
    standaloneCheck->setChecked(false);
    composerEdit->clear();
    tracksNumberEdit->clear();
    imagePreviewLabel->clear();
    selectedImagePath.clear();
    updateFieldsVisibility(0);
}

AddItemView::AddItemView(QWidget *parent, QVector<AbstractItem*>* items) : QWidget(parent), items(items) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Type selection
    typeComboBox = new QComboBox(this);
    typeComboBox->addItems({tr("Software"), tr("Videogame"), tr("DLC"), tr("Soundtrack")});
    mainLayout->addWidget(new QLabel("Type:"));
    mainLayout->addWidget(typeComboBox);

    // Basic information
    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText(tr("Name"));
    mainLayout->addWidget(new QLabel("Name:"));
    mainLayout->addWidget(nameEdit);
    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setPlaceholderText(tr("Add a description here"));
    mainLayout->addWidget(new QLabel("Description:"));
    mainLayout->addWidget(descriptionEdit);

    selectImageButton = new QPushButton(tr("Select Image"), this);
    connect(selectImageButton, &QPushButton::clicked, this, &AddItemView::selectImage);
    mainLayout->addWidget(selectImageButton);
    imagePreviewLabel = new QLabel(this);
    imagePreviewLabel->setFixedSize(100, 100);
    mainLayout->addWidget(imagePreviewLabel);

    // Specific fields containers
    softwareFields = new QWidget(this);
    videogameFields = new QWidget(this);
    dlcFields = new QWidget(this);
    soundtrackFields = new QWidget(this);


    // Software specific fields
    QVBoxLayout* softwareLayout = new QVBoxLayout(softwareFields);
    versionEdit = new QLineEdit(this);
    versionEdit->setPlaceholderText("Current Version");
    softwareLayout->addWidget(new QLabel("Version:"));
    softwareLayout->addWidget(versionEdit);
    winCompatibilityCheck = new QCheckBox("Windows Compatible", this);
    softwareLayout->addWidget(winCompatibilityCheck);
    softwareFields->setLayout(softwareLayout);

    // Videogame specific fields
    QVBoxLayout* videogameLayout = new QVBoxLayout(videogameFields);
    developerEdit = new QLineEdit(this);
    developerEdit->setPlaceholderText(tr("Developer"));
    videogameLayout->addWidget(new QLabel("Developer:"));
    videogameLayout->addWidget(developerEdit);
    genreEdit = new QLineEdit(this);
    genreEdit->setPlaceholderText(tr("Genre"));
    videogameLayout->addWidget(new QLabel("Genre:"));
    videogameLayout->addWidget(genreEdit);
    releaseDateEdit = new QLineEdit(this);
    releaseDateEdit->setPlaceholderText(tr("Release Date"));
    videogameLayout->addWidget(new QLabel("Release Date:"));
    videogameLayout->addWidget(releaseDateEdit);
    videogameFields->setLayout(videogameLayout);

    // DLC specific fields
    QVBoxLayout* dlcLayout = new QVBoxLayout(dlcFields);
    dlcdeveloperEdit = new QLineEdit(this);
    dlcdeveloperEdit->setPlaceholderText(tr("Developer"));
    dlcLayout->addWidget(new QLabel("Developer:"));
    dlcLayout->addWidget(dlcdeveloperEdit);
    dlcgenreEdit = new QLineEdit(this);
    dlcgenreEdit->setPlaceholderText(tr("Genre"));
    dlcLayout->addWidget(new QLabel("Genre:"));
    dlcLayout->addWidget(dlcgenreEdit);
    dlcreleaseDateEdit = new QLineEdit(this);
    dlcreleaseDateEdit->setPlaceholderText(tr("Release Date"));
    dlcLayout->addWidget(new QLabel("Release Date:"));
    dlcLayout->addWidget(dlcreleaseDateEdit);
    dlcTypeEdit = new QLineEdit(this);
    dlcTypeEdit->setPlaceholderText(tr("(Expansion, Mod, Skin, etc.)"));
    dlcLayout->addWidget(new QLabel("DLC Type:"));
    dlcLayout->addWidget(dlcTypeEdit);
    standaloneCheck = new QCheckBox(tr("Standalone"), this);
    dlcLayout->addWidget(standaloneCheck);
    dlcFields->setLayout(dlcLayout);

    // Soundtrack specific fields
    QVBoxLayout* soundtrackLayout = new QVBoxLayout(soundtrackFields);
    soundtrackdeveloperEdit = new QLineEdit(this);
    soundtrackdeveloperEdit->setPlaceholderText(tr("Developer"));
    soundtrackLayout->addWidget(new QLabel("Developer:"));
    soundtrackLayout->addWidget(soundtrackdeveloperEdit);
    soundtrackgenreEdit = new QLineEdit(this);
    soundtrackgenreEdit->setPlaceholderText(tr("Genre"));
    soundtrackLayout->addWidget(new QLabel("Genre:"));
    soundtrackLayout->addWidget(soundtrackgenreEdit);
    soundtrackreleaseDateEdit = new QLineEdit(this);
    soundtrackreleaseDateEdit->setPlaceholderText(tr("Release Date"));
    soundtrackLayout->addWidget(new QLabel("Release Date:"));
    soundtrackLayout->addWidget(soundtrackreleaseDateEdit);
    composerEdit = new QLineEdit(this);
    composerEdit->setPlaceholderText(tr("Composer"));
    soundtrackLayout->addWidget(new QLabel("Composer:"));
    soundtrackLayout->addWidget(composerEdit);
    tracksNumberEdit = new QLineEdit(this);
    tracksNumberEdit->setPlaceholderText(tr("Tracks Number"));
    soundtrackLayout->addWidget(new QLabel("Tracks Number:"));
    soundtrackLayout->addWidget(tracksNumberEdit);
    soundtrackFields->setLayout(soundtrackLayout);

    // Add containers to main layout
    mainLayout->addWidget(softwareFields);
    mainLayout->addWidget(videogameFields);
    mainLayout->addWidget(dlcFields);
    mainLayout->addWidget(soundtrackFields);

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

    // Initially hide all specific fields and show fields based on initial selection
    softwareFields->setVisible(false);
    videogameFields->setVisible(false);
    dlcFields->setVisible(false);
    soundtrackFields->setVisible(false);


    connect(typeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index){
                updateFieldsVisibility(index);
            });
    updateFieldsVisibility(0); // Show fields for the initial selection

}

void AddItemView::selectImage() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Image"), "", tr("Images (*.png *.jpg *.jpeg)"));
    if (!filePath.isEmpty()) {
        selectedImagePath = filePath;
        QPixmap image(selectedImagePath);
        if(!image.isNull()){
            imagePreviewLabel->setPixmap(image.scaled(imagePreviewLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        }
        else{
            QMessageBox::warning(this, tr("Error"), tr("Can't load the chosen image."));
            selectedImagePath.clear();
            imagePreviewLabel->clear();
        }
    }
}

void AddItemView::updateFieldsVisibility(int index) {
    softwareFields->setVisible(false);
    videogameFields->setVisible(false);
    dlcFields->setVisible(false);
    soundtrackFields->setVisible(false);

    if (index == 0) {
        softwareFields->setVisible(true);
    } else if (index == 1) {
        videogameFields->setVisible(true);
    } else if (index == 2) {
        dlcFields->setVisible(true);
    } else if (index == 3) {
        soundtrackFields->setVisible(true);
    }
}

void AddItemView::addItem() {
    QString type = typeComboBox->currentText();
    unsigned int id =  getMaxId() + 1;
    QString name = nameEdit->text();
    QString description = descriptionEdit->toPlainText();

    AbstractItem *newItem = nullptr;

    if (type == "Software") {
        newItem = new Software(id, name, description, versionEdit->text(), winCompatibilityCheck->isChecked(), selectedImagePath);
    }
    else if (type == "Videogame") {
        bool ok;
        unsigned int releaseDate = releaseDateEdit->text().toUInt(&ok);
        if(!ok){
            releaseDate=0;
        }
        newItem = new Videogame(id, name, description, developerEdit->text(), genreEdit->text(),releaseDate, selectedImagePath);
    }
    else if (type == "DLC") {
        bool ok;
        unsigned int releaseDate = dlcreleaseDateEdit->text().toUInt(&ok);
        if(!ok){
            releaseDate=0;
        }
        newItem = new DLC(id, name, description, dlcdeveloperEdit->text(), dlcgenreEdit->text(),releaseDate, dlcTypeEdit->text(), standaloneCheck->isChecked(), selectedImagePath);
    }
    else if (type == "Soundtrack") {
        bool ok;
        unsigned int releaseDate = soundtrackreleaseDateEdit->text().toUInt(&ok);
        if(!ok){
            releaseDate=0;
        }
        bool ok2;
        unsigned int tracksNumber = tracksNumberEdit->text().toUInt(&ok2);
        if(!ok2){
            tracksNumber = 0;
        }
        newItem = new Soundtrack(id, name, description, soundtrackdeveloperEdit->text(), soundtrackgenreEdit->text(), releaseDate, composerEdit->text(), tracksNumber, selectedImagePath);
    }

    if(newItem){
        emit itemAdded(newItem);
    }

    emit backToGridRequested();
}

void AddItemView::handleCancel() {
    emit backToGridRequested();
}

unsigned int AddItemView::getMaxId() const{
    unsigned int maxId = 0;
    if(items){
        for(const auto& item: *items){
            maxId = std::max(maxId, item->getId());
        }
    }
    return maxId;
}
