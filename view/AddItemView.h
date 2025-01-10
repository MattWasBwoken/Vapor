#ifndef ADDITEMVIEW_H
#define ADDITEMVIEW_H

#include "../model/AbstractItem.h"
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>

class AddItemView : public QWidget {
    Q_OBJECT

public:
    explicit AddItemView(QWidget* parent = nullptr);

signals:
    void itemAdded(AbstractItem* item);
    void backToGridRequested();

private slots:
    void addItem();
    void handleCancel();
    void updateFieldsVisibility(int index);

private:
    QComboBox *typeComboBox;
    QLineEdit *nameEdit;
    QTextEdit *descriptionEdit;
    QLineEdit *versionEdit;
    QCheckBox *winCompatibilityCheck;
    QLineEdit *developerEdit;
    QLineEdit *genreEdit;
    QLineEdit *releaseDateEdit;
    QLineEdit *dlcTypeEdit;
    QCheckBox *standaloneCheck;
    QLineEdit *composerEdit;
    QLineEdit *tracksNumberEdit;

    // **Dichiarazione dei QWidget per i campi specifici**
    QWidget *softwareFields;
    QWidget *videogameFields;
    QWidget *dlcFields;
    QWidget *soundtrackFields;
};

#endif
