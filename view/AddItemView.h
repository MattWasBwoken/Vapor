#ifndef ADDITEMVIEW_H
#define ADDITEMVIEW_H

#include "../model/AbstractItem.h"
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QVector>

class AddItemView : public QWidget {
    Q_OBJECT

public:
    explicit AddItemView(QWidget* parent = nullptr, QVector<AbstractItem*>* items = nullptr);
    void resetFields();

signals:
    void itemAdded(AbstractItem* item);
    void backToGridRequested();

private slots:
    void addItem();
    void handleCancel();
    void updateFieldsVisibility(int index);
    void selectImage();

private:
    QComboBox *typeComboBox;
    QLineEdit *nameEdit;
    QTextEdit *descriptionEdit;
    QLineEdit *versionEdit;
    QCheckBox *winCompatibilityCheck;
    QLineEdit *developerEdit;
    QLineEdit *dlcdeveloperEdit;
    QLineEdit *soundtrackdeveloperEdit;
    QLineEdit *genreEdit;
    QLineEdit *dlcgenreEdit;
    QLineEdit *soundtrackgenreEdit;
    QLineEdit *releaseDateEdit;
    QLineEdit *dlcreleaseDateEdit;
    QLineEdit *soundtrackreleaseDateEdit;
    QLineEdit *dlcTypeEdit;
    QCheckBox *standaloneCheck;
    QLineEdit *composerEdit;
    QLineEdit *tracksNumberEdit;

    QPushButton *selectImageButton;
    QLabel *imagePreviewLabel;
    QString selectedImagePath;
    QVector<AbstractItem*>* items;
    unsigned int getMaxId() const;

    // **Dichiarazione dei QWidget per i campi specifici**
    QWidget *softwareFields;
    QWidget *videogameFields;
    QWidget *dlcFields;
    QWidget *soundtrackFields;
};

#endif
