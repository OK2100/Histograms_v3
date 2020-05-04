//===========================================================================
//                           Histogram's data class
//===========================================================================
#ifndef HISTDATA_H
#define HISTDATA_H
#include <stdint.h>
#include <QVector>
#include <QDebug>
#include <QtMath>

class HistData
{
public:
    HistData(qint16 _leftLimit,qint16 _rightLimit,quint16 _nBins);

    QVector <double> inputs;                      //    All input values

    void printInfo(bool doPrintAllInputs=0,bool doPrintNumberEventsPerBin=0, bool doPrintOnlyStat = 0);
    quint16 addEvent(qint16 _event);
    void clear();

    void setnBins(quint16 _nBins);
    quint16 getnBins();
    void setbinWidth(qreal _binWidth);
    qreal getbinWidth();
    void setHistName(QString _name);
    QString getHistName();
    quint32 getTotalEvents();
    qint16 getLeftLimit(){ return leftLimit;}
    qint16 getRightLimit(){ return rightLimit;}

    bool isEmpty(){return bEmpty;}

    double getSampleMean();
    double getSampleVariance();
    double getSigma();
    double getFWHM();
    double getSumSquares(){ return sampleVariance; }

    quint32& operator[] (const quint16 index);      //  return nEvents per bin

    QString name;

private:
    qint16 leftLimit;
    qint16 rightLimit;
    quint16 nBins;
    qreal binWidth;
    qint32 sampleMean=0;
    double sampleVariance=0;
    quint32 nLosts=0;

    bool bEmpty = 1;

    QVector<quint32> nEvents;       // Number of events per bin

    void calcbinWidth();
    void calcnBins();
};

class Hist2Data
{
public:
    Hist2Data(qint16 _leftXLimit,qint16 _rightXLimit,quint16 _nXBins,
              qint16 _leftYLimit,qint16 _rightYLimit,quint16 _nYBins);


    QVector <double> inputs;                      //    All input values


    void printInfo(bool doPrintAllInputs=0,bool doPrintNumberEventsPerCell=0, bool doPrintOnlyStat = 0);
    quint16 addEvent(qint16 _valX,qint16 _valY);
    void clear();

    void setHistName(QString _name);
    void setnXBins(quint16 _nXBins);
    quint16 getnXBins();
    void setbinXWidth(qreal _binXWidth);
    qreal getbinXWidth();
    QString getHistName();
    quint32 getTotalEvents();
    qint16 getLeftXLimit(){ return leftLimit;}
    qint16 getRightXLimit(){ return rightLimit;}

    bool isEmpty(){return bEmpty;}

//    double getSampleMean();
//    double getSampleVariance();
//    double getSigma();
//    double getFWHM();

    quint32& operator() (const quint16 indexX,const quint16 indexY);      //  return nEvents per cell

    QString name;

private:
    qint16 leftLimit;
    qint16 rightLimit;
    quint16 nBins;
    qreal binWidth;

    qint16 leftYLimit;
    qint16 rightYLimit;
    quint16 nYBins;
    qreal binYWidth;

//    double sampleMean;
//    double sampleVariance;

    quint32 nLosts=0;

    bool bEmpty = 1;

    QVector<QVector<quint32>> nEvents;       // Number of events per cell

    void calcbinWidth();            // ??
    void calcnBins();

    void fillNevents(quint32 val=0);
    void initNevents();
    void clearNevents();
};


#endif // HISTDATA_H
