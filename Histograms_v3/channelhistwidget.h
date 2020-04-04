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

    quint8 ADC_ID = 2;              // 0 -> ADC0; 1->ADC1; 2->ADC0+ADC1
    bool doHideZeroBars=0;          // Flag
    void PlotHistograms();
    void Clear();
    void ClearScreen();
    void Update();
    void AddEvent(quint8 adc_id,qint16 charge, qint16 time);
    void PrintInfo(bool onlyStat = false);
    QString GetStatInfo();
    void HideZeroBars();
    void ShowFullRange();

private slots:
    void channelIDButton_clicked();
    void binWidth_charge_was_changed(const QString&);
    void binWidth_time_was_changed(const QString&);
    void nBins_charge_was_changed(const QString&);
    void nBins_time_was_changed(const QString&);

    //    void hist_double_clicked( QCPAbstractPlottable *  	plottable, int  	dataIndex, QMouseEvent *  	event );
    void hist_double_clicked( QMouseEvent* event);
    void replot_chargeTimeHist(){ chargeTimeHist->replot(); }

    void ADC0_choosed(){ ADC_ID = 0;}
    void ADC1_choosed(){ ADC_ID = 1;}
    void ADC01_choosed(){ADC_ID = 2;}

private:

    QCPColorMap *colorMap;
    void Experements();

    void setData(QCPBars*);

    Ui::ChannelHistWidget *ui;

    HistData* chargeData;
    HistData* chargeData1;
    HistData* timeData;
    HistData* timeData1;

    Hist2Data* hist0;
    Hist2Data* hist1;


    SetupChannelWindow* setupWindow;
    QString chID;
    QPushButton* channelIDButton;

    QCustomPlot* chargeHist;            // First hist
    QCPBars* chargeBars;

    QCustomPlot* timeHist;              // Second hist
    QCPBars* timeBars;

    QCustomPlot* chargeTimeHist;        // Graph
    QCPGraph* chargeTimeGraph;

//    quint8 isLeftRangeSelected = 0;
//    quint8 isRightRangeSelected = 0;


    void InitHistograms();              // Create chargeData, chargeBars, timeData, timeBars, chargeTimeGraph
    void SetupView();
    void LoadSettings(QString file_ini);

};

#endif // CHANNELHISTWIDGET_H
