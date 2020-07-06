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
#include <QDir>

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

    void UpdateScreen();
    void HideZeroBars();                                        // hide empty bars from left and right
    void ShowFullRange();
    void SaveHistograms(QString dest_dir);

    quint8 ADC_ID = 2;                                          // 0 -> ADC0; 1->ADC1; 2->ADC0+ADC1

private slots:
    void channelIDButton_clicked();

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
    dataContainer* data;

    void InitHistograms();              // Create chargeData, chargeBars, timeData, timeBars, chargeTimeGraph
    void SetupView();
    void LoadSettings(QString file_ini);

    void Experements();                 //  function to do some tests

    QString chID;

    quint16 nXBins,nYBins,Xwidth,Ywidth;

    QCustomPlot* chargeHist;            // First hist
    QCPBars* chargeBars;
    QCPBars* chargeBars1;

    QCustomPlot* timeHist;              // Second hist
    QCPBars* timeBars;
    QCPBars* timeBars1;

    QCustomPlot* chargeTimeHist;        // 2dim hist

    SetupChannelWindow* setupWindow;
    QPushButton* channelIDButton;

    friend dataContainer;
};



class dataContainer :public QObject
{
    Q_OBJECT
public:
    dataContainer(ChannelHistWidget *);
    ~dataContainer();

    ChannelHistWidget *ui=nullptr;

    void AddEvent(quint8 adc_id,qint16 charge, qint16 time);    // add data to data containers


    void add2data(double _charge,double _time,quint8 graph_id);
    void setData(bool);
    void set2Data();
    void Clear();                                               // Clear all data containers
    void setLabels();

    void saveHistogramsData(QString dest_dir);

    static const quint16 Ncols=256;
    double threshold[Ncols];              // for color map

    void fillColorMap();
    //    void PrintInfo(bool onlyStat = false);                      // Print info about data containers to console

    HistData* chargeData;
    HistData* chargeData1;
    HistData* timeData;
    HistData* timeData1;

    Hist2Data* hist0;
    Hist2Data* hist1;

    void updateUiScreen(){set2Data();ui->UpdateScreen();}

private:
    QTimer chargeTimer;
    QTimer timeTimer;

public slots:
    void rebinX(quint16);
    void rebinY(quint16);

};





#endif // CHANNELHISTWIDGET_H
