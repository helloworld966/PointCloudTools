/********************************************************************************
** Form generated from reading UI file 'Registration_function.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_FUNCTION_H
#define UI_REGISTRATION_FUNCTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Registration_function
{
public:
    QWidget *widget;

    void setupUi(QDockWidget *Registration_function)
    {
        if (Registration_function->objectName().isEmpty())
            Registration_function->setObjectName(QString::fromUtf8("Registration_function"));
        Registration_function->resize(400, 300);
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        Registration_function->setWidget(widget);

        retranslateUi(Registration_function);

        QMetaObject::connectSlotsByName(Registration_function);
    } // setupUi

    void retranslateUi(QDockWidget *Registration_function)
    {
        Registration_function->setWindowTitle(QApplication::translate("Registration_function", "Registration_function", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registration_function: public Ui_Registration_function {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_FUNCTION_H
