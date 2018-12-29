/********************************************************************************
** Form generated from reading UI file 'findtext.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDTEXT_H
#define UI_FINDTEXT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FindText
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;

    void setupUi(QDialog *FindText)
    {
        if (FindText->objectName().isEmpty())
            FindText->setObjectName(QString::fromUtf8("FindText"));
        FindText->setEnabled(true);
        FindText->resize(300, 150);
        FindText->setMinimumSize(QSize(300, 150));
        FindText->setMaximumSize(QSize(300, 150));
        verticalLayout_2 = new QVBoxLayout(FindText);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(FindText);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(FindText);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(FindText);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(FindText);

        QMetaObject::connectSlotsByName(FindText);
    } // setupUi

    void retranslateUi(QDialog *FindText)
    {
        FindText->setWindowTitle(QApplication::translate("FindText", "Find", nullptr));
        pushButton->setText(QApplication::translate("FindText", "Find", nullptr));
        pushButton_2->setText(QApplication::translate("FindText", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindText: public Ui_FindText {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDTEXT_H
