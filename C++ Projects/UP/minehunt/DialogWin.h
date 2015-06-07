#ifndef DIALOGWIN_H
#define DIALOGWIN_H


#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QLabel>

QT_BEGIN_NAMESPACE

class Ui_DialogWin
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *DialogWin)
    {
        if (DialogWin->objectName().isEmpty())
            DialogWin->setObjectName(QString::fromUtf8("DialogWin"));
        DialogWin->resize(400, 165);
        buttonBox = new QDialogButtonBox(DialogWin);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(40, 110, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::No|QDialogButtonBox::Yes);
        label = new QLabel(DialogWin);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 371, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(18);
        font.setItalic(true);
        label->setFont(font);
        label->setTextFormat(Qt::AutoText);
        label_2 = new QLabel(DialogWin);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 70, 231, 16));

        retranslateUi(DialogWin);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogWin, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogWin, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogWin);
    } // setupUi

    void retranslateUi(QDialog *DialogWin)
    {
        DialogWin->setWindowTitle(QApplication::translate("DialogWin", "Congratulations!!", 0));
        label->setText(QApplication::translate("DialogWin", "Congratulations, You have Won!", 0));
        label_2->setText(QApplication::translate("DialogWin", "Would you like to play another game?", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogWin: public Ui_DialogWin {};
} // namespace Ui

QT_END_NAMESPACE


#endif // DIALOGWIN_H
