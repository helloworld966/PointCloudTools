/********************************************************************************
** Form generated from reading UI file 'KNearWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KNEARWIDGET_H
#define UI_KNEARWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KNearWidget
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_x;
    QLineEdit *lineEdit_X;
    QLabel *label_Y;
    QLineEdit *lineEdit_Y;
    QLabel *label_Z;
    QLineEdit *lineEdit_Z;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_voxelSearch;
    QPushButton *pushButton_kNearNodes;
    QPushButton *pushButton_NearRadiusSearch;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_result;
    QLineEdit *lineEdit_result;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_K;
    QLineEdit *lineEdit;

    void setupUi(QDialog *KNearWidget)
    {
        if (KNearWidget->objectName().isEmpty())
            KNearWidget->setObjectName(QString::fromUtf8("KNearWidget"));
        KNearWidget->resize(377, 190);
        layoutWidget = new QWidget(KNearWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 185, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_x = new QLabel(layoutWidget);
        label_x->setObjectName(QString::fromUtf8("label_x"));

        horizontalLayout->addWidget(label_x);

        lineEdit_X = new QLineEdit(layoutWidget);
        lineEdit_X->setObjectName(QString::fromUtf8("lineEdit_X"));

        horizontalLayout->addWidget(lineEdit_X);

        label_Y = new QLabel(layoutWidget);
        label_Y->setObjectName(QString::fromUtf8("label_Y"));

        horizontalLayout->addWidget(label_Y);

        lineEdit_Y = new QLineEdit(layoutWidget);
        lineEdit_Y->setObjectName(QString::fromUtf8("lineEdit_Y"));

        horizontalLayout->addWidget(lineEdit_Y);

        label_Z = new QLabel(layoutWidget);
        label_Z->setObjectName(QString::fromUtf8("label_Z"));

        horizontalLayout->addWidget(label_Z);

        lineEdit_Z = new QLineEdit(layoutWidget);
        lineEdit_Z->setObjectName(QString::fromUtf8("lineEdit_Z"));

        horizontalLayout->addWidget(lineEdit_Z);

        layoutWidget_2 = new QWidget(KNearWidget);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 100, 250, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_voxelSearch = new QPushButton(layoutWidget_2);
        pushButton_voxelSearch->setObjectName(QString::fromUtf8("pushButton_voxelSearch"));

        horizontalLayout_2->addWidget(pushButton_voxelSearch);

        pushButton_kNearNodes = new QPushButton(layoutWidget_2);
        pushButton_kNearNodes->setObjectName(QString::fromUtf8("pushButton_kNearNodes"));

        horizontalLayout_2->addWidget(pushButton_kNearNodes);

        pushButton_NearRadiusSearch = new QPushButton(layoutWidget_2);
        pushButton_NearRadiusSearch->setObjectName(QString::fromUtf8("pushButton_NearRadiusSearch"));

        horizontalLayout_2->addWidget(pushButton_NearRadiusSearch);

        layoutWidget_3 = new QWidget(KNearWidget);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 70, 213, 22));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_result = new QLabel(layoutWidget_3);
        label_result->setObjectName(QString::fromUtf8("label_result"));

        horizontalLayout_4->addWidget(label_result);

        lineEdit_result = new QLineEdit(layoutWidget_3);
        lineEdit_result->setObjectName(QString::fromUtf8("lineEdit_result"));
        lineEdit_result->setFocusPolicy(Qt::TabFocus);

        horizontalLayout_4->addWidget(lineEdit_result);

        layoutWidget_4 = new QWidget(KNearWidget);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(10, 40, 195, 22));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_K = new QLabel(layoutWidget_4);
        label_K->setObjectName(QString::fromUtf8("label_K"));

        horizontalLayout_3->addWidget(label_K);

        lineEdit = new QLineEdit(layoutWidget_4);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_3->addWidget(lineEdit);


        retranslateUi(KNearWidget);

        QMetaObject::connectSlotsByName(KNearWidget);
    } // setupUi

    void retranslateUi(QDialog *KNearWidget)
    {
        KNearWidget->setWindowTitle(QApplication::translate("KNearWidget", "KNearWidget", nullptr));
        label_x->setText(QApplication::translate("KNearWidget", "X:", nullptr));
        label_Y->setText(QApplication::translate("KNearWidget", "Y:", nullptr));
        label_Z->setText(QApplication::translate("KNearWidget", "Z:", nullptr));
        pushButton_voxelSearch->setText(QApplication::translate("KNearWidget", "\344\275\223\347\264\240\346\220\234\347\264\242", nullptr));
        pushButton_kNearNodes->setText(QApplication::translate("KNearWidget", "K\351\242\206\345\237\237\350\212\202\347\202\271\346\220\234\347\264\242", nullptr));
        pushButton_NearRadiusSearch->setText(QApplication::translate("KNearWidget", "\345\215\212\345\276\204\346\220\234\347\264\242", nullptr));
        label_result->setText(QApplication::translate("KNearWidget", "\351\202\273\345\237\237\347\273\223\347\202\271\346\225\260\357\274\232", nullptr));
        label_K->setText(QApplication::translate("KNearWidget", "K\351\230\266\351\242\206\345\237\237\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KNearWidget: public Ui_KNearWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KNEARWIDGET_H
