#include "EditItemVisitor.h"
#include "model/Software.h"
#include "model/Videogame.h"
#include "model/DLC.h"
#include "model/Soundtrack.h"

EditItemVisitor::EditItemVisitor(QLineEdit* nameEdit, QTextEdit* descriptionEdit, QLineEdit* versionEdit, QCheckBox* winCompatibilityCheck,
                    QLineEdit* developerEdit, QLineEdit* dlcdeveloperEdit, QLineEdit* soundtrackdeveloperEdit, QLineEdit* genreEdit, QLineEdit* dlcgenreEdit,
                    QLineEdit* soundtrackgenreEdit, QLineEdit* releaseDateEdit, QLineEdit* dlcreleaseDateEdit, QLineEdit* soundtrackreleaseDateEdit,
                    QLineEdit* dlcTypeEdit, QCheckBox* standaloneCheck, QLineEdit* composerEdit, QLineEdit* tracksNumberEdit, QString selectedImagePath)
    : nameEdit(nameEdit), descriptionEdit(descriptionEdit), versionEdit(versionEdit), winCompatibilityCheck(winCompatibilityCheck),
    developerEdit(developerEdit), dlcdeveloperEdit(dlcdeveloperEdit), soundtrackdeveloperEdit(soundtrackdeveloperEdit), genreEdit(genreEdit), dlcgenreEdit(dlcgenreEdit),
    soundtrackgenreEdit(soundtrackgenreEdit), releaseDateEdit(releaseDateEdit), dlcreleaseDateEdit(dlcreleaseDateEdit), soundtrackreleaseDateEdit(soundtrackreleaseDateEdit),
    dlcTypeEdit(dlcTypeEdit), standaloneCheck(standaloneCheck), composerEdit(composerEdit), tracksNumberEdit(tracksNumberEdit), selectedImagePath(selectedImagePath) {}

void EditItemVisitor::visit(Software* item) {
    item->setName(nameEdit->text());
    item->setDescription(descriptionEdit->toPlainText());
    item->setImage(selectedImagePath);
    item->setCurrentVersion(versionEdit->text());
    item->setWinCompatibility(winCompatibilityCheck->isChecked());
}

void EditItemVisitor::visit(Videogame* item) {
    item->setName(nameEdit->text());
    item->setDescription(descriptionEdit->toPlainText());
    item->setImage(selectedImagePath);
    bool ok;
    unsigned int releaseDate = releaseDateEdit->text().toUInt(&ok);
    if(!ok){
        releaseDate=0;
    }
    item->setDeveloper(developerEdit->text());
    item->setGenre(genreEdit->text());
    item->setReleaseDate(releaseDate);
}

void EditItemVisitor::visit(DLC* item) {
    item->setName(nameEdit->text());
    item->setDescription(descriptionEdit->toPlainText());
    item->setImage(selectedImagePath);
    bool ok;
    unsigned int releaseDate = dlcreleaseDateEdit->text().toUInt(&ok);
    if(!ok){
        releaseDate=0;
    }
    item->setDeveloper(dlcdeveloperEdit->text());
    item->setGenre(dlcgenreEdit->text());
    item->setReleaseDate(releaseDate);
    item->setDlcType(dlcTypeEdit->text());
    item->setStandalone(standaloneCheck->isChecked());
}

void EditItemVisitor::visit(Soundtrack* item) {
    item->setName(nameEdit->text());
    item->setDescription(descriptionEdit->toPlainText());
    item->setImage(selectedImagePath);
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
    item->setDeveloper(soundtrackdeveloperEdit->text());
    item->setGenre(soundtrackgenreEdit->text());
    item->setReleaseDate(releaseDate);
    item->setComposer(composerEdit->text());
    item->setTracksNumber(tracksNumber);
}
