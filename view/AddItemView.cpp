#include "AddItemView.h"
#include "model/Software.h"
#include "model/DLC.h"
#include "model/Videogame.h"
#include "model/Soundtrack.h"
#include <QVBoxLayout>
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
    QWidget* container = new QWidget(this);
    QGridLayout* mainLayout = new QGridLayout(container);

    mainLayout->addWidget(new QLabel("Type:"),0,0);
    typeComboBox = new QComboBox(this);
    typeComboBox->addItems({tr("Software"), tr("Videogame"), tr("DLC"), tr("Soundtrack")});
    mainLayout->addWidget(typeComboBox,0,1);

    mainLayout->addWidget(new QLabel("Name:"), 1, 0);
    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText(tr("Name"));
    mainLayout->addWidget(nameEdit, 1, 1);

    mainLayout->addWidget(new QLabel("Description:"), 2, 0);
    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setPlaceholderText(tr("Add a description here"));
    mainLayout->addWidget(descriptionEdit, 2, 1);

    selectImageButton = new QPushButton(tr("Select Image"), this);
    connect(selectImageButton, &QPushButton::clicked, this, &AddItemView::selectImage);
    mainLayout->addWidget(selectImageButton, 3, 0);

    imagePreviewLabel = new QLabel(this);
    imagePreviewLabel->setFixedSize(100, 100);
    mainLayout->addWidget(imagePreviewLabel, 3, 1);

    softwareFields = new QWidget(this);
    videogameFields = new QWidget(this);
    dlcFields = new QWidget(this);
    soundtrackFields = new QWidget(this);

    QVBoxLayout* softwareLayout = new QVBoxLayout(softwareFields);
    versionEdit = new QLineEdit(this);
    versionEdit->setPlaceholderText("Current Version");
    softwareLayout->addWidget(new QLabel("Version:"));
    softwareLayout->addWidget(versionEdit);
    winCompatibilityCheck = new QCheckBox("Windows Compatible", this);
    softwareLayout->addWidget(winCompatibilityCheck);
    softwareFields->setLayout(softwareLayout);
    mainLayout->addWidget(softwareFields, 4, 0, 1, 2);

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
    mainLayout->addWidget(videogameFields, 4, 0, 1, 2);

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
    mainLayout->addWidget(dlcFields, 4, 0, 1, 2);

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
    mainLayout->addWidget(soundtrackFields, 4, 0, 1, 2);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* addButton = new QPushButton("Add", this);
    QPushButton* cancelButton = new QPushButton("Cancel", this);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);
    connect(addButton, &QPushButton::clicked, this, &AddItemView::addItem);
    connect(cancelButton, &QPushButton::clicked, this, &AddItemView::handleCancel);
    mainLayout->addLayout(buttonLayout, 6, 0, 1, 2, Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(container);
    setLayout(layout);

    softwareFields->setVisible(false);
    videogameFields->setVisible(false);
    dlcFields->setVisible(false);
    soundtrackFields->setVisible(false);

    connect(typeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index){
                updateFieldsVisibility(index);
            });
    updateFieldsVisibility(0);

    addButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; border: none; padding: 10px 20px; border-radius: 5px; } QPushButton:hover { background-color: #367c39; }");
    cancelButton->setStyleSheet("QPushButton { background-color: #f44336; color: white; border: none; padding: 10px 20px; border-radius: 5px; } QPushButton:hover { background-color: #b00a02; }");
    selectImageButton->setStyleSheet("QPushButton { background-color: #2196F3; color: white; border: none; padding: 10px 20px; border-radius: 5px; } QPushButton:hover { background-color: #1868a3; }");
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
    emit backToGridRequested(false);
}

void AddItemView::handleCancel() {
    emit backToGridRequested(true);
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
