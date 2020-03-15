/********************************************************************************
** Form generated from reading UI file 'handlerwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HANDLERWINDOW_H
#define UI_HANDLERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HandlerWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *mainVLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *b_1;
    QPushButton *b_2;
    QPushButton *b_3;
    QPushButton *b_4;
    QPushButton *b_5;
    QPushButton *b_6;
    QPushButton *b_7;
    QPushButton *b_8;
    QHBoxLayout *grid;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HandlerWindow)
    {
        if (HandlerWindow->objectName().isEmpty())
            HandlerWindow->setObjectName(QString::fromUtf8("HandlerWindow"));
        HandlerWindow->resize(229, 467);
        centralwidget = new QWidget(HandlerWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        mainVLayout = new QVBoxLayout();
        mainVLayout->setSpacing(1);
        mainVLayout->setObjectName(QString::fromUtf8("mainVLayout"));
        mainVLayout->setContentsMargins(-1, 0, -1, -1);
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Plain);
        frame->setLineWidth(10);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        b_1 = new QPushButton(frame);
        b_1->setObjectName(QString::fromUtf8("b_1"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(b_1->sizePolicy().hasHeightForWidth());
        b_1->setSizePolicy(sizePolicy);
        b_1->setMinimumSize(QSize(25, 25));
        b_1->setMaximumSize(QSize(16777215, 50));
        QFont font;
        font.setPointSize(8);
        b_1->setFont(font);

        horizontalLayout->addWidget(b_1);

        b_2 = new QPushButton(frame);
        b_2->setObjectName(QString::fromUtf8("b_2"));
        sizePolicy.setHeightForWidth(b_2->sizePolicy().hasHeightForWidth());
        b_2->setSizePolicy(sizePolicy);
        b_2->setMinimumSize(QSize(25, 25));
        b_2->setMaximumSize(QSize(16777215, 50));
        b_2->setFont(font);

        horizontalLayout->addWidget(b_2);

        b_3 = new QPushButton(frame);
        b_3->setObjectName(QString::fromUtf8("b_3"));
        sizePolicy.setHeightForWidth(b_3->sizePolicy().hasHeightForWidth());
        b_3->setSizePolicy(sizePolicy);
        b_3->setMinimumSize(QSize(25, 25));
        b_3->setMaximumSize(QSize(16777215, 50));
        b_3->setFont(font);

        horizontalLayout->addWidget(b_3);

        b_4 = new QPushButton(frame);
        b_4->setObjectName(QString::fromUtf8("b_4"));
        sizePolicy.setHeightForWidth(b_4->sizePolicy().hasHeightForWidth());
        b_4->setSizePolicy(sizePolicy);
        b_4->setMinimumSize(QSize(25, 25));
        b_4->setMaximumSize(QSize(16777215, 50));
        b_4->setFont(font);

        horizontalLayout->addWidget(b_4);

        b_5 = new QPushButton(frame);
        b_5->setObjectName(QString::fromUtf8("b_5"));
        sizePolicy.setHeightForWidth(b_5->sizePolicy().hasHeightForWidth());
        b_5->setSizePolicy(sizePolicy);
        b_5->setMinimumSize(QSize(25, 25));
        b_5->setMaximumSize(QSize(16777215, 50));
        b_5->setFont(font);

        horizontalLayout->addWidget(b_5);

        b_6 = new QPushButton(frame);
        b_6->setObjectName(QString::fromUtf8("b_6"));
        sizePolicy.setHeightForWidth(b_6->sizePolicy().hasHeightForWidth());
        b_6->setSizePolicy(sizePolicy);
        b_6->setMinimumSize(QSize(25, 25));
        b_6->setMaximumSize(QSize(16777215, 50));
        b_6->setFont(font);

        horizontalLayout->addWidget(b_6);

        b_7 = new QPushButton(frame);
        b_7->setObjectName(QString::fromUtf8("b_7"));
        sizePolicy.setHeightForWidth(b_7->sizePolicy().hasHeightForWidth());
        b_7->setSizePolicy(sizePolicy);
        b_7->setMinimumSize(QSize(25, 25));
        b_7->setMaximumSize(QSize(16777215, 50));
        b_7->setFont(font);

        horizontalLayout->addWidget(b_7);

        b_8 = new QPushButton(frame);
        b_8->setObjectName(QString::fromUtf8("b_8"));
        sizePolicy.setHeightForWidth(b_8->sizePolicy().hasHeightForWidth());
        b_8->setSizePolicy(sizePolicy);
        b_8->setMinimumSize(QSize(25, 25));
        b_8->setMaximumSize(QSize(16777215, 50));
        b_8->setFont(font);

        horizontalLayout->addWidget(b_8);


        mainVLayout->addWidget(frame);

        grid = new QHBoxLayout();
        grid->setSpacing(2);
        grid->setObjectName(QString::fromUtf8("grid"));

        mainVLayout->addLayout(grid);

        mainVLayout->setStretch(0, 1);
        mainVLayout->setStretch(1, 15);

        verticalLayout_2->addLayout(mainVLayout);

        HandlerWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(HandlerWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 229, 22));
        HandlerWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(HandlerWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        HandlerWindow->setStatusBar(statusbar);

        retranslateUi(HandlerWindow);

        QMetaObject::connectSlotsByName(HandlerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *HandlerWindow)
    {
        HandlerWindow->setWindowTitle(QCoreApplication::translate("HandlerWindow", "HandlerWindow", nullptr));
        b_1->setText(QCoreApplication::translate("HandlerWindow", "Add\n"
"chanel", nullptr));
        b_2->setText(QCoreApplication::translate("HandlerWindow", "Remove\n"
"channel", nullptr));
        b_3->setText(QCoreApplication::translate("HandlerWindow", "Reset\n"
"channel", nullptr));
        b_4->setText(QCoreApplication::translate("HandlerWindow", "Hide/show \n"
"zeros", nullptr));
        b_5->setText(QCoreApplication::translate("HandlerWindow", "Update\n"
"screen", nullptr));
        b_6->setText(QCoreApplication::translate("HandlerWindow", "Read\n"
"file", nullptr));
        b_7->setText(QString());
        b_8->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class HandlerWindow: public Ui_HandlerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HANDLERWINDOW_H
