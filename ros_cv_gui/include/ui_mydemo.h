/********************************************************************************
** Form generated from reading UI file 'mydemo.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDEMO_H
#define UI_MYDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mydemo
{
public:
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_txt;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_open;
    QPushButton *pushButton_quit;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QSlider *verticalSlider;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lineEdit;
    QPushButton *pushButton_save;
    QLabel *label;

    void setupUi(QWidget *mydemo)
    {
        if (mydemo->objectName().isEmpty())
            mydemo->setObjectName(QString::fromUtf8("mydemo"));
        mydemo->resize(784, 540);
        horizontalLayout_4 = new QHBoxLayout(mydemo);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_txt = new QLabel(mydemo);
        label_txt->setObjectName(QString::fromUtf8("label_txt"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_txt->sizePolicy().hasHeightForWidth());
        label_txt->setSizePolicy(sizePolicy);
        label_txt->setMinimumSize(QSize(640, 0));
        label_txt->setMaximumSize(QSize(640, 16777215));
        label_txt->setSizeIncrement(QSize(480, 0));
        QFont font;
        font.setPointSize(15);
        label_txt->setFont(font);
        label_txt->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_txt);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton_open = new QPushButton(mydemo);
        pushButton_open->setObjectName(QString::fromUtf8("pushButton_open"));

        verticalLayout_2->addWidget(pushButton_open);

        pushButton_quit = new QPushButton(mydemo);
        pushButton_quit->setObjectName(QString::fromUtf8("pushButton_quit"));

        verticalLayout_2->addWidget(pushButton_quit);

        frame = new QFrame(mydemo);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radioButton = new QRadioButton(frame);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setCheckable(true);
        radioButton->setChecked(false);

        verticalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(frame);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(frame);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        verticalLayout->addWidget(radioButton_3);


        verticalLayout_2->addWidget(frame);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalSlider = new QSlider(mydemo);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setMaximum(40);
        verticalSlider->setPageStep(2);
        verticalSlider->setValue(0);
        verticalSlider->setSliderPosition(0);
        verticalSlider->setOrientation(Qt::Vertical);

        horizontalLayout_2->addWidget(verticalSlider);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_2);

        lineEdit = new QLineEdit(mydemo);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lineEdit);

        pushButton_save = new QPushButton(mydemo);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));

        verticalLayout_2->addWidget(pushButton_save);


        horizontalLayout_3->addLayout(verticalLayout_2);

        label = new QLabel(mydemo);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(640, 480));
        label->setMaximumSize(QSize(640, 480));
        label->setSizeIncrement(QSize(640, 480));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8(""));
        label->setFrameShape(QFrame::Box);
        label->setFrameShadow(QFrame::Plain);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout_3);


        retranslateUi(mydemo);

        QMetaObject::connectSlotsByName(mydemo);
    } // setupUi

    void retranslateUi(QWidget *mydemo)
    {
        mydemo->setWindowTitle(QApplication::translate("mydemo", "Form", nullptr));
        label_txt->setText(QApplication::translate("mydemo", "TextLabel", nullptr));
        pushButton_open->setText(QApplication::translate("mydemo", "Open..", nullptr));
        pushButton_quit->setText(QApplication::translate("mydemo", "Quit", nullptr));
        radioButton->setText(QApplication::translate("mydemo", "BoxFilter", nullptr));
        radioButton_2->setText(QApplication::translate("mydemo", "MeanBlur", nullptr));
        radioButton_3->setText(QApplication::translate("mydemo", "Gaussian", nullptr));
        lineEdit->setText(QString());
        pushButton_save->setText(QApplication::translate("mydemo", "Save", nullptr));
        label->setText(QApplication::translate("mydemo", "Display Image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mydemo: public Ui_mydemo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDEMO_H
