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


class dataContainer;

namespace Ui {
class ChannelHistWidget;
}

class ChannelHistWidget : public QWidget
{
    Q_OBJECT

public:

    explicit ChannelHistWidget(QWidget *parent = nullptr,QString _chID = "");
    ~ChannelHistWidget();

//    void AddEvent(quint8 adc_id,qint16 charge, qint16 time);    // add data to data containers

    void PlotHistograms();                                      // Draw current data
//    void Clear();                                               // Clear all data containers
    void ClearScreen();
    void UpdateScreen();
//    void HideZeroBars();                                        // hide empty bars from left and right
    void ShowFullRange();

//    void PrintInfo(bool onlyStat = false);                      // Print info about data containers to console

    quint8 ADC_ID = 2;                                          // 0 -> ADC0; 1->ADC1; 2->ADC0+ADC1

private slots:
//    void channelIDButton_clicked();
//    void binWidth_charge_was_changed(quint16);
//    void binWidth_time_was_changed(quint16);

    void hist_double_clicked( QMouseEvent* event);
    void replot_chargeTimeHist(){ chargeTimeHist->replot(); }
    void replot_chargeHist(){chargeHist->replot();}
    void replot_timeHist(){timeHist->replot();}

    void ADC0_choosed();
    void ADC1_choosed();
    void ADC01_choosed();

    void auto_rescale(const QCPRange &newRange);

private:
    Ui::ChannelHistWidget *ui;

    void InitHistograms();              // Create chargeData, chargeBars, timeData, timeBars, chargeTimeGraph
    void SetupView();
    void LoadSettings(QString file_ini);

//    void add2data(qint16 _charge,qint16 _time,quint8 graph_id);
//    void setData(QCPBars*);
//    void set2Data();
//    void setLabels();
//    void fillColorMap();

    void Experements();                 //  function to do some tests


    QString chID;

    //  ----Data containers---
//    HistData* chargeData;
//    HistData* chargeData1;
//    HistData* timeData;
//    HistData* timeData1;

//    Hist2Data* hist0;
//    Hist2Data* hist1;
    // -----------------------

    QCustomPlot* chargeHist;            // First hist
    QCPBars* chargeBars;
    QCPBars* chargeBars1;

    QCustomPlot* timeHist;              // Second hist
    QCPBars* timeBars;
    QCPBars* timeBars1;

    QCustomPlot* chargeTimeHist;        // 2dim hist

//    SetupChannelWindow* setupWindow;
    QPushButton* channelIDButton;

    double threshold[256];              // for color map

    friend dataContainer;
};



class dataContainer
{
public:
    dataContainer(ChannelHistWidget *);
    ~dataContainer();

    const ChannelHistWidget *ui;

    void AddEvent(quint8 adc_id,qint16 charge, qint16 time);    // add data to data containers

    void add2data(qint16 _charge,qint16 _time,quint8 graph_id);
    void setData(QCPBars*);
    void set2Data();
    void Clear();                                               // Clear all data containers

    double threshold[256];              // for color map

    void fillColorMap();

    HistData* chargeData;
    HistData* chargeData1;
    HistData* timeData;
    HistData* timeData1;

    Hist2Data* hist0;
    Hist2Data* hist1;

};





#endif // CHANNELHISTWIDGET_H
