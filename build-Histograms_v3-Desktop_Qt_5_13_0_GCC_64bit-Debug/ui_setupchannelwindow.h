/********************************************************************************
** Form generated from reading UI file 'setupchannelwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUPCHANNELWINDOW_H
#define UI_SETUPCHANNELWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SetupChannelWindow
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *lbl_channelID;
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QGridLayout *gridLayout_8;
    QRadioButton *rb_binW_charge;
    QRadioButton *rb_nBins_charge;
    QLabel *label_5;
    QLineEdit *le_chargeRange_left;
    QLineEdit *le_chargeRange_right;
    QLineEdit *le_binWidth_charge;
    QLineEdit *le_nBins_charge;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QGridLayout *gridLayout_5;
    QRadioButton *rb_binW_time;
    QLineEdit *le_binWidth_time;
    QLabel *label_4;
    QRadioButton *rb_nBins_time;
    QLineEdit *le_timeRange_left;
    QLineEdit *le_nBins_time;
    QLineEdit *le_timeRange_right;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_7;
    QLabel *label_12;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_13;
    QLabel *label_10;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_10;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *ApplyButton;
    QPushButton *CancelButton;
    QPushButton *OkButton;

    void setupUi(QDialog *SetupChannelWindow)
    {
        if (SetupChannelWindow->objectName().isEmpty())
            SetupChannelWindow->setObjectName(QString::fromUtf8("SetupChannelWindow"));
        SetupChannelWindow->resize(462, 402);
        verticalLayout_2 = new QVBoxLayout(SetupChannelWindow);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        lbl_channelID = new QLabel(SetupChannelWindow);
        lbl_channelID->setObjectName(QString::fromUtf8("lbl_channelID"));

        horizontalLayout_10->addWidget(lbl_channelID);


        verticalLayout_2->addLayout(horizontalLayout_10);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        frame_2 = new QFrame(SetupChannelWindow);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_7 = new QHBoxLayout(frame_2);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(135, 0));
        label->setMaximumSize(QSize(135, 16777215));

        horizontalLayout_2->addWidget(label);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        rb_binW_charge = new QRadioButton(frame_2);
        rb_binW_charge->setObjectName(QString::fromUtf8("rb_binW_charge"));
        rb_binW_charge->setEnabled(true);
        rb_binW_charge->setChecked(true);

        gridLayout_8->addWidget(rb_binW_charge, 1, 0, 1, 1);

        rb_nBins_charge = new QRadioButton(frame_2);
        rb_nBins_charge->setObjectName(QString::fromUtf8("rb_nBins_charge"));

        gridLayout_8->addWidget(rb_nBins_charge, 2, 0, 1, 1);

        label_5 = new QLabel(frame_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_8->addWidget(label_5, 0, 0, 1, 1);

        le_chargeRange_left = new QLineEdit(frame_2);
        le_chargeRange_left->setObjectName(QString::fromUtf8("le_chargeRange_left"));
        le_chargeRange_left->setDragEnabled(true);
        le_chargeRange_left->setReadOnly(true);

        gridLayout_8->addWidget(le_chargeRange_left, 0, 1, 1, 1);

        le_chargeRange_right = new QLineEdit(frame_2);
        le_chargeRange_right->setObjectName(QString::fromUtf8("le_chargeRange_right"));
        le_chargeRange_right->setMouseTracking(true);
        le_chargeRange_right->setEchoMode(QLineEdit::Normal);
        le_chargeRange_right->setReadOnly(true);

        gridLayout_8->addWidget(le_chargeRange_right, 0, 2, 1, 1);

        le_binWidth_charge = new QLineEdit(frame_2);
        le_binWidth_charge->setObjectName(QString::fromUtf8("le_binWidth_charge"));

        gridLayout_8->addWidget(le_binWidth_charge, 1, 1, 1, 2);

        le_nBins_charge = new QLineEdit(frame_2);
        le_nBins_charge->setObjectName(QString::fromUtf8("le_nBins_charge"));

        gridLayout_8->addWidget(le_nBins_charge, 2, 1, 1, 2);


        horizontalLayout_2->addLayout(gridLayout_8);


        horizontalLayout_7->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(frame_2);

        frame_3 = new QFrame(SetupChannelWindow);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_3);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(frame_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(135, 0));
        label_2->setMaximumSize(QSize(135, 16777215));

        horizontalLayout_3->addWidget(label_2);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        rb_binW_time = new QRadioButton(frame_3);
        rb_binW_time->setObjectName(QString::fromUtf8("rb_binW_time"));
        rb_binW_time->setChecked(true);

        gridLayout_5->addWidget(rb_binW_time, 1, 0, 1, 1);

        le_binWidth_time = new QLineEdit(frame_3);
        le_binWidth_time->setObjectName(QString::fromUtf8("le_binWidth_time"));

        gridLayout_5->addWidget(le_binWidth_time, 1, 1, 1, 2);

        label_4 = new QLabel(frame_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_5->addWidget(label_4, 0, 0, 1, 1);

        rb_nBins_time = new QRadioButton(frame_3);
        rb_nBins_time->setObjectName(QString::fromUtf8("rb_nBins_time"));

        gridLayout_5->addWidget(rb_nBins_time, 2, 0, 1, 1);

        le_timeRange_left = new QLineEdit(frame_3);
        le_timeRange_left->setObjectName(QString::fromUtf8("le_timeRange_left"));
        le_timeRange_left->setReadOnly(true);

        gridLayout_5->addWidget(le_timeRange_left, 0, 1, 1, 1);

        le_nBins_time = new QLineEdit(frame_3);
        le_nBins_time->setObjectName(QString::fromUtf8("le_nBins_time"));

        gridLayout_5->addWidget(le_nBins_time, 2, 1, 1, 2);

        le_timeRange_right = new QLineEdit(frame_3);
        le_timeRange_right->setObjectName(QString::fromUtf8("le_timeRange_right"));
        le_timeRange_right->setDragEnabled(false);
        le_timeRange_right->setReadOnly(true);

        gridLayout_5->addWidget(le_timeRange_right, 0, 2, 1, 1);


        horizontalLayout_3->addLayout(gridLayout_5);


        horizontalLayout_6->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(frame_3);

        frame = new QFrame(SetupChannelWindow);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(135);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setMaximumSize(QSize(135, 16777215));

        horizontalLayout_4->addWidget(label_3);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_12 = new QLabel(frame);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_7->addWidget(label_12, 1, 0, 1, 1);

        lineEdit_9 = new QLineEdit(frame);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));

        gridLayout_7->addWidget(lineEdit_9, 0, 2, 1, 1);

        lineEdit_13 = new QLineEdit(frame);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));

        gridLayout_7->addWidget(lineEdit_13, 1, 2, 1, 1);

        label_10 = new QLabel(frame);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_7->addWidget(label_10, 0, 0, 1, 1);

        lineEdit_11 = new QLineEdit(frame);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));

        gridLayout_7->addWidget(lineEdit_11, 1, 1, 1, 1);

        lineEdit_10 = new QLineEdit(frame);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));

        gridLayout_7->addWidget(lineEdit_10, 0, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_7, 0, 0, 1, 1);


        horizontalLayout_4->addLayout(gridLayout_6);

        horizontalLayout_4->setStretch(1, 1);

        horizontalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ApplyButton = new QPushButton(SetupChannelWindow);
        ApplyButton->setObjectName(QString::fromUtf8("ApplyButton"));

        horizontalLayout->addWidget(ApplyButton);

        CancelButton = new QPushButton(SetupChannelWindow);
        CancelButton->setObjectName(QString::fromUtf8("CancelButton"));

        horizontalLayout->addWidget(CancelButton);

        OkButton = new QPushButton(SetupChannelWindow);
        OkButton->setObjectName(QString::fromUtf8("OkButton"));

        horizontalLayout->addWidget(OkButton);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);

        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(SetupChannelWindow);

        QMetaObject::connectSlotsByName(SetupChannelWindow);
    } // setupUi

    void retranslateUi(QDialog *SetupChannelWindow)
    {
        SetupChannelWindow->setWindowTitle(QCoreApplication::translate("SetupChannelWindow", "Dialog", nullptr));
        lbl_channelID->setText(QString());
        label->setText(QCoreApplication::translate("SetupChannelWindow", "Charge histogram:", nullptr));
        rb_binW_charge->setText(QCoreApplication::translate("SetupChannelWindow", "Bin width", nullptr));
        rb_nBins_charge->setText(QCoreApplication::translate("SetupChannelWindow", "Number of bins", nullptr));
        label_5->setText(QCoreApplication::translate("SetupChannelWindow", "Data range:", nullptr));
        le_chargeRange_left->setText(QString());
        le_chargeRange_right->setText(QString());
        le_chargeRange_right->setPlaceholderText(QString());
        label_2->setText(QCoreApplication::translate("SetupChannelWindow", "Time histogram:", nullptr));
        rb_binW_time->setText(QCoreApplication::translate("SetupChannelWindow", "Bin width", nullptr));
        label_4->setText(QCoreApplication::translate("SetupChannelWindow", "Data range:", nullptr));
        rb_nBins_time->setText(QCoreApplication::translate("SetupChannelWindow", "Number of bins", nullptr));
        le_timeRange_left->setText(QString());
        le_timeRange_right->setText(QString());
        label_3->setText(QCoreApplication::translate("SetupChannelWindow", "Charge/time graph:", nullptr));
        label_12->setText(QCoreApplication::translate("SetupChannelWindow", "Range time axis:", nullptr));
        label_10->setText(QCoreApplication::translate("SetupChannelWindow", "Range charge axis:", nullptr));
        ApplyButton->setText(QCoreApplication::translate("SetupChannelWindow", "Apply", nullptr));
        CancelButton->setText(QCoreApplication::translate("SetupChannelWindow", "Cancel", nullptr));
        OkButton->setText(QCoreApplication::translate("SetupChannelWindow", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetupChannelWindow: public Ui_SetupChannelWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUPCHANNELWINDOW_H
