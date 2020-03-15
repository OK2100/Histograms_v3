#ifndef HANDLERWINDOW_H
#define HANDLERWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QDebug>
#include <QInputDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
#include <QThread>
#include <QtGui>

#include "channelhistwidget.h"
//#include "../sources/DataBlockReaderFT0.h"
//#include "../sources/DataBlockFT0.h"
//#include "../sources/DataBlockFileReaderFT0.h"


struct EventData	{
    uint64_t time:12,
        charge:13,
        numberADC:1,
        isDoubleEvent:1,
        is1TimeLostEvent:1,
        is2TimeLostEvent:1,
        isADCinGate:1,
        isTimeInfoLate:1,
        isAmpHigh:1,
        isEventInTVDC:1,
        isTimeInfoLost:1,
        reservedField:2,
        channelID:4; /// equal to zero in case of half-word
//		ClassDefNV(EventData, 1);
};
struct EventDataReal {
        int time:12;
        int	charge:13;
        bool	numberADC:1,
            isDoubleEvent:1,
            is1TimeLostEvent:1,
            is2TimeLostEvent:1,
            isADCinGate:1,
            isTimeInfoLate:1,
            isAmpHigh:1,
            isEventInTVDC:1,
            isTimeInfoLost:1;
        unsigned short	reservedField:2,
            channelID:4;
//			ClassDefNV(EventData, 1);
};
union DataConversion {
    EventData dataBlocks;
    EventDataReal dataReal;
//		ClassDefNV(EventData, 1);
};


QT_BEGIN_NAMESPACE
namespace Ui { class HandlerWindow; }
QT_END_NAMESPACE

class HandlerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HandlerWindow(HandlerWindow* prevWindow = nullptr,QWidget *parent = nullptr);
    ~HandlerWindow();

private:
    Ui::HandlerWindow *ui;

public slots:                       //  Slots for connecting with other progs
    void updateScreen();
    void addEvent(quint8 chID,qint16 charge,qint16 time);
    void chooseADC();

signals:
    void showNewWindow(quint8 firstChannelID);

private:
    int Height;
    int Width;


//    QWidget* centralWidget = new QWidget;
//    QHBoxLayout* grid = new QHBoxLayout;
    QHBoxLayout* grid;

    ChannelHistWidget* channel[12];
//    const char* filePath;                 //  Path and name. It breaks somewhere in DataBlock lib
    QString filePath;
//    QString filePathSave;           //  Save of 'filePath'
    QString fileType;

    quint8 nAddedChannels = 0;
    quint8 nextChannelID = 1;
    quint8 ADCNumber = 2;       //  2 mean both ADC0 and ADC1

    HandlerWindow* secondWindow;

    void SetUp();
    void PlotHistograms();
//    void ReadBinaryFile();
    void ReadTxtFile();

//------------------------- Apearance --------------------------

    QMenu* fileBar;                 //  'File' field in menu
    QAction* openSourceFileAction;

    QMenu* editBar;                 //  'Edit' field in menu
    QAction* defaultSettingAction;

    QMenu* dataBar;
    QAction* showStatWindowAction;

    QMenu* optionsBar;              //  'Options' field in menu
    QAction* addChannelAction;
    QAction* removeChannelAction;
    QAction* removeAllChannelAction;
    QAction* updateAction;
    QAction* readFileAction;
    QAction* resetAction;
    QAction* resetAllAction;
    QAction* hideZeroBarsAction;
    QAction* chooseADCAction;

    QLabel lbl;                     //  Opening label
//----------------------------------------------------

private slots:
    void startNewWindow(quint8 firstChannelID);
    bool openSourceFile();
    void readFile();
    void addChannel();
    void removeChannel();
    void removeAllChannel();
    void reset();
    void resetAll();
    void hideZeroBars();
    void showStatWindow();
};
#endif // HANDLERWINDOW_H
