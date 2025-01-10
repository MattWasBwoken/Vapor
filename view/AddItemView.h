#ifndef ADDITEMVIEW_H
#define ADDITEMVIEW_H
#include "../model/AbstractItem.h"
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QTextEdit>

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
};
#endif
