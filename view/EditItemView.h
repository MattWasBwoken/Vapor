#ifndef EDITITEMVIEW_H
#define EDITITEMVIEW_H

#include "../model/AbstractItem.h"
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>

class EditItemView : public QWidget {
    Q_OBJECT

public:
    explicit EditItemView(QWidget* parent = nullptr, QVector<AbstractItem*>* items = nullptr);
    void setItem(AbstractItem* item); // Method to set the item to edit
    void resetFields();

signals:
    void itemModified(AbstractItem* item);
    void backToGridRequested(bool showMessage);

private slots:
    void editItem();
    void handleCancel();
    void updateFieldsVisibility(int index);
    void selectImage();

private:
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
    AbstractItem* currentItem;
    QWidget *softwareFields;
    QWidget *videogameFields;
    QWidget *dlcFields;
    QWidget *soundtrackFields;
};

#endif
