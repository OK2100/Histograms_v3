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
#include <QLabel>
#include <QtGui>
#include <QRegExp>
#include <QStringList>

#include "channelhistwidget.h"


struct EventData	{
    quint16 time:12;
    quint16 charge:13;
};
struct EventDataReal {
    qint16 time:12;
    qint16	charge:13;
};

union DataConversion {
    EventData dataBlocks;
    EventDataReal dataReal;
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

public slots:

    void addEvent(quint8 chID, quint8 flags, qint16 charge, qint16 time);
    void addEvent(QString gbtword,bool doPrintDecoded=false);
    void addEvent(quint8 chID, quint32 bitset, bool doPrintDecoded=false); // without "time info lost"

    bool addSingleChannel(quint8 chID);
    void addChannelRange(QString chIDs);

    void removeSingleChannel(quint8 chID);
    void removeChannelRange(QString chIDs);

    void resetSingleChannel(quint8 chID);
    void resetChannelRange(QString chIDs);

    QString getFilePath(){return filePath;}
    QString getFileType(){return fileType;}
    void setFilePath(QString path){filePath = path;}

    bool isEmptyBarsHidden(){return doHide;}
    void hideZeroBars();        // works as switch

    void readFile();
    void updateScreen();

    void chooseADC(quint8 chID,quint8 adcID);           // [0,1,2]  2 mean both ADC0 and ADC1


private slots:
    void startNewWindow(QVector<quint8>& channelsToAdd);
    bool openSourceFile();
    void addChannel();              // with input
    void removeChannel();           // with input
    void removeAllChannel();        // with input
    void reset();                   // with input
    void resetAll();                // with input
    void doAddChannelRange();

signals:
    void showNewWindow(QVector<quint8>& channelsToAdd);


private:
    Ui::HandlerWindow *ui;
    QLabel label;
    HandlerWindow* prevWin=nullptr;

    int Height;
    int Width;
    bool doHide=1;
    bool doCheckFlags=0;

    QHBoxLayout* grid;
    ChannelHistWidget* channel[4];
    QString filePath;
    QString fileType;

    QStack<quint8> addedChannelsID;
    quint8 nAddedChannels = 0;
    quint8 nextChannelID = 1;
    quint8 ADCNumber = 2;       //  2 mean both ADC0 and ADC1

    HandlerWindow* secondWindow;

    void closeEvent(QCloseEvent *event) override;

    void SetUp();
    void PlotHistograms();
//    void ReadBinaryFile();
    void ReadTxtFile();
    void sendEventToChannel(quint8 chID,bool adc_id,qint16 charge,qint16 time);

    void LoadSettings(QString file_ini);
//    void SaveSettings();

//------------------------- Apearance --------------------------

    QMenu* fileBar;                 //  'File' field in menu
    QAction* openSourceFileAction;

    QMenu* editBar;                 //  'Edit' field in menu
    QAction* defaultSettingAction;

    QMenu* dataBar;
    QAction* showStatWindowAction;

    QMenu* optionsBar;              //  'Options' field in menu
    QAction* addChannelAction;
    QAction* addChannelRangeAction;
    QAction* removeChannelAction;
    QAction* removeAllChannelAction;
    QAction* updateAction;
    QAction* readFileAction;
    QAction* resetAction;
    QAction* resetAllAction;
    QAction* hideZeroBarsAction;

    QLabel lbl;                     //  Opening label
//----------------------------------------------------

};
#endif // HANDLERWINDOW_H
