#ifndef DIALOGLOSE_H
#define DIALOGLOSE_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QLabel>

QT_BEGIN_NAMESPACE

class Ui_DialogLose
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *DialogLose)
    {
        if (DialogLose->objectName().isEmpty())
            DialogLose->setObjectName(QString::fromUtf8("DialogLose"));
        DialogLose->resize(400, 165);
        buttonBox = new QDialogButtonBox(DialogLose);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(40, 110, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::No|QDialogButtonBox::Yes);
        label = new QLabel(DialogLose);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 371, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(18);
        font.setItalic(true);
        label->setFont(font);
        label->setTextFormat(Qt::AutoText);
        label_2 = new QLabel(DialogLose);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 70, 231, 16));

        retranslateUi(DialogLose);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogLose, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogLose, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogLose);
    } // setupUi

    void retranslateUi(QDialog *DialogLose)
    {
        DialogLose->setWindowTitle(QApplication::translate("DialogLose", "You Lose!!", 0));
        label->setText(QApplication::translate("DialogLose", "Sorry, You have hit a mine!", 0));
        label_2->setText(QApplication::translate("DialogLose", "Would you like to play another game?", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogLose: public Ui_DialogLose {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DIALOGLOSE_H
