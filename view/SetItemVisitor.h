#ifndef SETITEMVISITOR_H
#define SETITEMVISITOR_H

#include "../model/IConstVisitor.h"
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QLabel>


class SetItemVisitor : public IConstVisitor {
public:
    SetItemVisitor(QLineEdit* nameEdit, QTextEdit* descriptionEdit,
                   QLineEdit* versionEdit, QCheckBox* winCompatibilityCheck,
                   QLineEdit* developerEdit, QLineEdit* dlcdeveloperEdit, QLineEdit* soundtrackdeveloperEdit,
                   QLineEdit* genreEdit, QLineEdit* dlcgenreEdit, QLineEdit* soundtrackgenreEdit,
                   QLineEdit* releaseDateEdit, QLineEdit* dlcreleaseDateEdit, QLineEdit* soundtrackreleaseDateEdit,
                   QLineEdit* dlcTypeEdit, QCheckBox* standaloneCheck,
                   QLineEdit* composerEdit, QLineEdit* tracksNumberEdit, QLabel *imagePreviewLabel, QString &selectedImagePath);


    void visit(const Software* item) override;
    void visit(const Videogame* item) override;
    void visit(const DLC* item) override;
    void visit(const Soundtrack* item) override;

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
    QLabel *imagePreviewLabel;
    QString &selectedImagePath;

};

#endif
