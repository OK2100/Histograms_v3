/********************************************************************************
** Form generated from reading UI file 'channelhistwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANNELHISTWIDGET_H
#define UI_CHANNELHISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../sources/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_ChannelHistWidget
{
public:
    QGridLayout *gridLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_5;
    QCustomPlot *chargeTimeHist;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_2;
    QCustomPlot *chargeHist;
    QGridLayout *gridLayout_4;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_5;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer_3;
    QCustomPlot *timeHist;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *channelIDButton;
    QSpacerItem *horizontalSpacer;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QRadioButton *rb_0;
    QRadioButton *rb_1;
    QRadioButton *rb_01;

    void setupUi(QWidget *ChannelHistWidget)
    {
        if (ChannelHistWidget->objectName().isEmpty())
            ChannelHistWidget->setObjectName(QString::fromUtf8("ChannelHistWidget"));
        ChannelHistWidget->resize(197, 432);
        gridLayout_2 = new QGridLayout(ChannelHistWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_2->setHorizontalSpacing(0);
        gridLayout_2->setVerticalSpacing(1);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(ChannelHistWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Plain);
        frame->setLineWidth(10);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_3->addItem(verticalSpacer_5);


        horizontalLayout_2->addLayout(verticalLayout_3);

        chargeTimeHist = new QCustomPlot(frame);
        chargeTimeHist->setObjectName(QString::fromUtf8("chargeTimeHist"));

        horizontalLayout_2->addWidget(chargeTimeHist);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 10);

        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMinimumSize(QSize(10, 10));
        pushButton_2->setMaximumSize(QSize(20, 20));

        verticalLayout->addWidget(pushButton_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setMinimumSize(QSize(10, 10));
        pushButton_3->setMaximumSize(QSize(20, 20));

        verticalLayout->addWidget(pushButton_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout);

        chargeHist = new QCustomPlot(frame);
        chargeHist->setObjectName(QString::fromUtf8("chargeHist"));
        gridLayout_4 = new QGridLayout(chargeHist);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 2, 2, 0);
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_6, 2, 1, 1, 1);

        label_2 = new QLabel(chargeHist);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setPointSize(8);
        label_2->setFont(font);

        gridLayout_4->addWidget(label_2, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        label_3 = new QLabel(chargeHist);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        gridLayout_4->addWidget(label_3, 1, 1, 1, 1);


        horizontalLayout->addWidget(chargeHist);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 10);

        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton_5 = new QPushButton(frame);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy1);
        pushButton_5->setMinimumSize(QSize(15, 15));
        pushButton_5->setMaximumSize(QSize(20, 20));

        verticalLayout_2->addWidget(pushButton_5);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_4);

        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
        pushButton_4->setMinimumSize(QSize(10, 10));
        pushButton_4->setMaximumSize(QSize(20, 20));

        verticalLayout_2->addWidget(pushButton_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_3);


        horizontalLayout_3->addLayout(verticalLayout_2);

        timeHist = new QCustomPlot(frame);
        timeHist->setObjectName(QString::fromUtf8("timeHist"));

        horizontalLayout_3->addWidget(timeHist);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 10);

        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        channelIDButton = new QPushButton(frame);
        channelIDButton->setObjectName(QString::fromUtf8("channelIDButton"));

        horizontalLayout_5->addWidget(channelIDButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMaximumSize(QSize(16777215, 25));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_2);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFont(font);

        horizontalLayout_6->addWidget(label);

        rb_0 = new QRadioButton(frame_2);
        rb_0->setObjectName(QString::fromUtf8("rb_0"));
        rb_0->setMinimumSize(QSize(10, 0));
        rb_0->setFont(font);

        horizontalLayout_6->addWidget(rb_0);

        rb_1 = new QRadioButton(frame_2);
        rb_1->setObjectName(QString::fromUtf8("rb_1"));
        rb_1->setMinimumSize(QSize(10, 0));
        rb_1->setFont(font);

        horizontalLayout_6->addWidget(rb_1);

        rb_01 = new QRadioButton(frame_2);
        rb_01->setObjectName(QString::fromUtf8("rb_01"));
        rb_01->setMinimumSize(QSize(10, 0));
        rb_01->setFont(font);
        rb_01->setChecked(true);

        horizontalLayout_6->addWidget(rb_01);


        horizontalLayout_5->addWidget(frame_2);


        gridLayout->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 5);
        gridLayout->setRowStretch(2, 5);
        gridLayout->setRowStretch(3, 5);

        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);


        gridLayout_2->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(ChannelHistWidget);

        QMetaObject::connectSlotsByName(ChannelHistWidget);
    } // setupUi

    void retranslateUi(QWidget *ChannelHistWidget)
    {
        ChannelHistWidget->setWindowTitle(QCoreApplication::translate("ChannelHistWidget", "Form", nullptr));
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        label_2->setText(QCoreApplication::translate("ChannelHistWidget", "Bin w: 1", nullptr));
        label_3->setText(QCoreApplication::translate("ChannelHistWidget", "N ev:10101541", nullptr));
        pushButton_5->setText(QString());
        pushButton_4->setText(QString());
        channelIDButton->setText(QCoreApplication::translate("ChannelHistWidget", "Setup Channel", nullptr));
        label->setText(QCoreApplication::translate("ChannelHistWidget", "ADC:", nullptr));
        rb_0->setText(QCoreApplication::translate("ChannelHistWidget", "0", nullptr));
        rb_1->setText(QCoreApplication::translate("ChannelHistWidget", "1", nullptr));
        rb_01->setText(QCoreApplication::translate("ChannelHistWidget", "0+1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChannelHistWidget: public Ui_ChannelHistWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANNELHISTWIDGET_H
