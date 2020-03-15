#ifndef CHANNELHISTWIDGET_H
#define CHANNELHISTWIDGET_H

#include "../sources/qcustomplot.h"
#include "histdata.h"
#include "setupchannelwindow.h"

#include <QFormLayout>
#include <QWidget>
#include <QHBoxLayout>
#include <QString>
#include <QLabel>
#include <QMouseEvent>
#include <QSettings>
#include <QVariant>

namespace Ui {
class ChannelHistWidget;
}

class ChannelHistWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelHistWidget(QWidget *parent = nullptr,QString _chID = "");
    ~ChannelHistWidget();

    bool doHideZeroBars=0;          // Flag
    void PlotHistograms();
    void Clear();
    void ClearScreen();
    void Update();
    void AddEvent(qint16 charge, quint8 ADCnum, qint16 time);
    void PrintInfo(bool onlyStat = false);
    QString GetStatInfo();

private slots:
    void channelIDButton_clicked();
    void binWidth_charge_was_changed(const QString&);
    void binWidth_time_was_changed(const QString&);
    void nBins_charge_was_changed(const QString&);
    void nBins_time_was_changed(const QString&);

    //    void hist_double_clicked( QCPAbstractPlottable *  	plottable, int  	dataIndex, QMouseEvent *  	event );
    void hist_double_clicked( QMouseEvent* event);
    void replot_chargeTimeHist(){ chargeTimeHist->replot(); }

private:
    Ui::ChannelHistWidget *ui;

    HistData* chargeData;
//    HistData* chargeData0;
//    HistData* chargeData1;
    HistData* timeData;

    SetupChannelWindow* setupWindow;
    QString chID;
    QPushButton* channelIDButton;

    QCustomPlot* chargeHist;            // First hist
    QCPBars* chargeBars;
    QVector<double> chargeKey;          // ADC channel -> x axis
    QVector<double> chargeValue;
//    QVector<double> chargeValue0;       // ADC0 counts -> y axis (depends on radioButton)
//    QVector<double> chargeValue1;       // ADC1 counts -> y axis (depends on radioButton)

    QCustomPlot* timeHist;              // Second hist
    QCPBars* timeBars;
    QVector<double> timeKey;
    QVector<double> timeValue;

    QCustomPlot* chargeTimeHist;        // Graph
    QCPGraph* chargeTimeGraph;

//    quint8 isLeftRangeSelected = 0;
//    quint8 isRightRangeSelected = 0;


    void InitHistograms();              // Create chargeData, chargeBars, timeData, timeBars, chargeTimeGraph
    void SetupView();
    void LoadSettings(QString file_ini);


    void HideZeroBars();
    void InitKeysAndValues();
};

#endif // CHANNELHISTWIDGET_H
