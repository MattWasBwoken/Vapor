#include "SetItemVisitor.h"
#include "model/Software.h"
#include "model/Videogame.h"
#include "model/DLC.h"
#include "model/Soundtrack.h"
#include <QPixmap>

SetItemVisitor::SetItemVisitor(QLineEdit* nameEdit, QTextEdit* descriptionEdit, QLineEdit* versionEdit, QCheckBox* winCompatibilityCheck,
                    QLineEdit* developerEdit, QLineEdit* dlcdeveloperEdit, QLineEdit* soundtrackdeveloperEdit, QLineEdit* genreEdit, QLineEdit* dlcgenreEdit,
                    QLineEdit* soundtrackgenreEdit, QLineEdit* releaseDateEdit, QLineEdit* dlcreleaseDateEdit, QLineEdit* soundtrackreleaseDateEdit,
                    QLineEdit* dlcTypeEdit, QCheckBox* standaloneCheck, QLineEdit* composerEdit, QLineEdit* tracksNumberEdit, QLabel *imagePreviewLabel, QString &selectedImagePath)
    : nameEdit(nameEdit), descriptionEdit(descriptionEdit), versionEdit(versionEdit), winCompatibilityCheck(winCompatibilityCheck),
    developerEdit(developerEdit), dlcdeveloperEdit(dlcdeveloperEdit), soundtrackdeveloperEdit(soundtrackdeveloperEdit), genreEdit(genreEdit), dlcgenreEdit(dlcgenreEdit),
    soundtrackgenreEdit(soundtrackgenreEdit), releaseDateEdit(releaseDateEdit), dlcreleaseDateEdit(dlcreleaseDateEdit), soundtrackreleaseDateEdit(soundtrackreleaseDateEdit),
    dlcTypeEdit(dlcTypeEdit), standaloneCheck(standaloneCheck), composerEdit(composerEdit), tracksNumberEdit(tracksNumberEdit), imagePreviewLabel(imagePreviewLabel),
    selectedImagePath(selectedImagePath) {}

void SetItemVisitor::visit(const Software* item) {
    nameEdit->setText(item->getName());
    descriptionEdit->setText(item->getDescription());
    versionEdit->setText(item->getCurrentVersion());
    winCompatibilityCheck->setChecked(item->getWinCompatibility());
    QPixmap image(item->getImage());
    if(!image.isNull()){
        imagePreviewLabel->setPixmap(image.scaled(imagePreviewLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    }
    else{
        imagePreviewLabel->clear();
    }
    selectedImagePath = item->getImage();

}

void SetItemVisitor::visit(const Videogame* item) {
    nameEdit->setText(item->getName());
    descriptionEdit->setText(item->getDescription());
    developerEdit->setText(item->getDeveloper());
    genreEdit->setText(item->getGenre());
    releaseDateEdit->setText(QString::number(item->getReleaseDate()));
    QPixmap image(item->getImage());
    if(!image.isNull()){
        imagePreviewLabel->setPixmap(image.scaled(imagePreviewLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    }
    else{
        imagePreviewLabel->clear();
    }
    selectedImagePath = item->getImage();
}

void SetItemVisitor::visit(const DLC* item) {
    nameEdit->setText(item->getName());
    descriptionEdit->setText(item->getDescription());
    dlcdeveloperEdit->setText(item->getDeveloper());
    dlcgenreEdit->setText(item->getGenre());
    dlcreleaseDateEdit->setText(QString::number(item->getReleaseDate()));
    dlcTypeEdit->setText(item->getDlcType());
    standaloneCheck->setChecked(item->getStandalone());
    QPixmap image(item->getImage());
    if(!image.isNull()){
        imagePreviewLabel->setPixmap(image.scaled(imagePreviewLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    }
    else{
        imagePreviewLabel->clear();
    }
    selectedImagePath = item->getImage();
}

void SetItemVisitor::visit(const Soundtrack* item) {
    nameEdit->setText(item->getName());
    descriptionEdit->setText(item->getDescription());
    soundtrackdeveloperEdit->setText(item->getDeveloper());
    soundtrackgenreEdit->setText(item->getGenre());
    soundtrackreleaseDateEdit->setText(QString::number(item->getReleaseDate()));
    composerEdit->setText(item->getComposer());
    tracksNumberEdit->setText(QString::number(item->getTracksNumber()));
    QPixmap image(item->getImage());
    if(!image.isNull()){
        imagePreviewLabel->setPixmap(image.scaled(imagePreviewLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    }
    else{
        imagePreviewLabel->clear();
    }
    selectedImagePath = item->getImage();
}
