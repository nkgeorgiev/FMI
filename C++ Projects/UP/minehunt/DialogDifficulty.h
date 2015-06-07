#ifndef DIALOGDIFFICULTY_H
#define DIALOGDIFFICULTY_H


#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(385, 132);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(270, 30, 81, 111));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        radioButton = new QRadioButton(Dialog);
        buttonGroup = new QButtonGroup(Dialog);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButton,1);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(30, 20, 161, 20));
        radioButton_2 = new QRadioButton(Dialog);
        buttonGroup->addButton(radioButton_2,2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(30, 60, 191, 20));
        radioButton_3 = new QRadioButton(Dialog);
        buttonGroup->addButton(radioButton_3,3);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(30, 100, 181, 20));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Choose Difficulty", 0));
        radioButton->setText(QApplication::translate("Dialog", "Easy (8x8, 10 mines)", 0));
        radioButton_2->setText(QApplication::translate("Dialog", "Medium(16x16, 40 mines)", 0));
        radioButton_3->setText(QApplication::translate("Dialog", "Hard(16x30, 99 mines)", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE


#endif // DIALOGDIFFICULTY_H
