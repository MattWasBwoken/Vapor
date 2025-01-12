#ifndef EDITITEMVISITOR_H
#define EDITITEMVISITOR_H

#include "../model/IVisitor.h"
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>

class EditItemVisitor : public IVisitor {
public:
    EditItemVisitor(QLineEdit* nameEdit, QTextEdit* descriptionEdit,
                    QLineEdit* versionEdit, QCheckBox* winCompatibilityCheck,
                    QLineEdit* developerEdit, QLineEdit* dlcdeveloperEdit, QLineEdit* soundtrackdeveloperEdit,
                    QLineEdit* genreEdit, QLineEdit* dlcgenreEdit, QLineEdit* soundtrackgenreEdit,
                    QLineEdit* releaseDateEdit, QLineEdit* dlcreleaseDateEdit, QLineEdit* soundtrackreleaseDateEdit,
                    QLineEdit* dlcTypeEdit, QCheckBox* standaloneCheck,
                    QLineEdit* composerEdit, QLineEdit* tracksNumberEdit, QString selectedImagePath);

    void visit(Software* item) override;
    void visit(Videogame* item) override;
    void visit(DLC* item) override;
    void visit(Soundtrack* item) override;

private:
    QLineEdit* nameEdit;
    QTextEdit* descriptionEdit;
    QLineEdit* versionEdit;
    QCheckBox* winCompatibilityCheck;
    QLineEdit* developerEdit;
    QLineEdit* dlcdeveloperEdit;
    QLineEdit* soundtrackdeveloperEdit;
    QLineEdit* genreEdit;
    QLineEdit* dlcgenreEdit;
    QLineEdit* soundtrackgenreEdit;
    QLineEdit* releaseDateEdit;
    QLineEdit* dlcreleaseDateEdit;
    QLineEdit* soundtrackreleaseDateEdit;
    QLineEdit* dlcTypeEdit;
    QCheckBox* standaloneCheck;
    QLineEdit* composerEdit;
    QLineEdit* tracksNumberEdit;
    QString selectedImagePath;
};

#endif
