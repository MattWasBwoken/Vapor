#include "EditItemView.h"
#include "../model/Software.h"
#include "../model/DLC.h"
#include "../model/Videogame.h"
#include "../model/Soundtrack.h"


void EditItemView::resetFields() {
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

EditItemView::EditItemView(QWidget *parent, QVector<AbstractItem*>* items) : QWidget(parent), items(items), currentItem(nullptr) {
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
    connect(selectImageButton, &QPushButton::clicked, this, &EditItemView::selectImage);
    mainLayout->addWidget(selectImageButton);

    imagePreviewLabel = new QLabel(this);
    imagePreviewLabel->setFixedSize(100, 100);
    imagePreviewLabel->setScaledContents(true);
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
    QPushButton* editButton = new QPushButton("Edit", this);
    QPushButton* cancelButton = new QPushButton("Cancel", this);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(cancelButton);
    connect(editButton, &QPushButton::clicked, this, &EditItemView::editItem);
    connect(cancelButton, &QPushButton::clicked, this, &EditItemView::handleCancel);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    // Initially hide all specific fields
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

void EditItemView::setItem(AbstractItem* item) {
    currentItem = item;
    if (!currentItem) {
        resetFields();
        return;
    }
    nameEdit->setText(currentItem->getName());
    descriptionEdit->setText(currentItem->getDescription());
    selectedImagePath = currentItem->getImage();
    QPixmap image(selectedImagePath);
    if(!image.isNull()){
        imagePreviewLabel->setPixmap(image.scaled(imagePreviewLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else{
        imagePreviewLabel->clear();
        selectedImagePath.clear();
    }

    if (Software* software = dynamic_cast<Software*>(currentItem)) {
        typeComboBox->setCurrentIndex(0);
        versionEdit->setText(software->getCurrentVersion());
        winCompatibilityCheck->setChecked(software->getWinCompatibility());
        updateFieldsVisibility(0);
    } else if (DLC* dlc = dynamic_cast<DLC*>(currentItem)) {
        typeComboBox->setCurrentIndex(2);
        dlcdeveloperEdit->setText(dlc->getDeveloper());
        dlcgenreEdit->setText(dlc->getGenre());
        dlcreleaseDateEdit->setText(QString::number(dlc->getReleaseDate()));
        dlcTypeEdit->setText(dlc->getDlcType());
        standaloneCheck->setChecked(dlc->getStandalone());
        updateFieldsVisibility(2);
    } else if (Soundtrack* soundtrack = dynamic_cast<Soundtrack*>(currentItem)) {
        typeComboBox->setCurrentIndex(3);
        soundtrackdeveloperEdit->setText(soundtrack->getDeveloper());
        soundtrackgenreEdit->setText(soundtrack->getGenre());
        soundtrackreleaseDateEdit->setText(QString::number(soundtrack->getReleaseDate()));
        composerEdit->setText(soundtrack->getComposer());
        tracksNumberEdit->setText(QString::number(soundtrack->getTracksNumber()));
        updateFieldsVisibility(3);
    } else if (Videogame* videogame = dynamic_cast<Videogame*>(currentItem)) {
        typeComboBox->setCurrentIndex(1);
        developerEdit->setText(videogame->getDeveloper());
        genreEdit->setText(videogame->getGenre());
        releaseDateEdit->setText(QString::number(videogame->getReleaseDate()));
        updateFieldsVisibility(1);
    }
}


void EditItemView::selectImage() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Image"), "", tr("Images (*.png *.jpg *.jpeg)"));
    if (!filePath.isEmpty()) {
        selectedImagePath = filePath;
        QPixmap image(selectedImagePath);
        if(!image.isNull()){
            imagePreviewLabel->setPixmap(image.scaled(imagePreviewLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        else{
            QMessageBox::warning(this, tr("Error"), tr("Can't load the chosen image."));
            selectedImagePath.clear();
            imagePreviewLabel->clear();
        }
    }
}


void EditItemView::updateFieldsVisibility(int index) {
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


void EditItemView::editItem() {
    if (!currentItem) return;

    QString type = typeComboBox->currentText();
    currentItem->setName(nameEdit->text());
    currentItem->setDescription(descriptionEdit->toPlainText());
    currentItem->setImage(selectedImagePath);

    if (type == "Software") {
        Software* software = dynamic_cast<Software*>(currentItem);
        if(software){
            software->setCurrentVersion(versionEdit->text());
            software->setWinCompatibility(winCompatibilityCheck->isChecked());
        }
    } else if (type == "DLC") {
        DLC* dlc = dynamic_cast<DLC*>(currentItem);
        if(dlc){
            bool ok;
            unsigned int releaseDate = dlcreleaseDateEdit->text().toUInt(&ok);
            if(!ok){
                releaseDate=0;
            }
            dlc->setDeveloper(dlcdeveloperEdit->text());
            dlc->setGenre(dlcgenreEdit->text());
            dlc->setReleaseDate(releaseDate);
            dlc->setDlcType(dlcTypeEdit->text());
            dlc->setStandalone(standaloneCheck->isChecked());
        }
    } else if (type == "Soundtrack") {
        Soundtrack* soundtrack = dynamic_cast<Soundtrack*>(currentItem);
        if(soundtrack){
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
            soundtrack->setDeveloper(soundtrackdeveloperEdit->text());
            soundtrack->setGenre(soundtrackgenreEdit->text());
            soundtrack->setReleaseDate(releaseDate);
            soundtrack->setComposer(composerEdit->text());
            soundtrack->setTracksNumber(tracksNumber);
        }
    } else if (type == "Videogame") {
        Videogame* videogame = dynamic_cast<Videogame*>(currentItem);
        if(videogame){
            bool ok;
            unsigned int releaseDate = releaseDateEdit->text().toUInt(&ok);
            if(!ok){
                releaseDate=0;
            }
            videogame->setDeveloper(developerEdit->text());
            videogame->setGenre(genreEdit->text());
            videogame->setReleaseDate(releaseDate);
        }
    }

    emit itemModified(currentItem);
    emit backToGridRequested();
}


void EditItemView::handleCancel() {
    emit backToGridRequested();
}
