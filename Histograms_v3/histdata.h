//===========================================================================
//                           Integer Histogram's data classes
//===========================================================================
#ifndef HISTDATA_H
#define HISTDATA_H
#include <stdint.h>
#include <QVector>
#include <QDebug>
#include <QtMath>
#include <iostream>
#include <QFile>


class HistData
{
public:
    HistData(qint16 _leftLimit,qint16 _rightLimit,quint16 _nBins);
    ~HistData();

    quint16 addEvent(qint16 _event);
    quint16& operator[] (const quint16 index);      //  return nEvents per bin
    bool isEmpty(){return Nev>0?0:1 ;}
    void clear();

    quint16 getnBins(){return nBins;}
    quint16 getbinWidth(){return binWidth;}
    QString getHistName();
    qint16  getLeftLimit(){ return leftLimit;}
    qint16  getRightLimit(){ return rightLimit;}

    void    setHistName(QString _name);
    bool    rebin(quint16 newBinWidth);

    quint32 getTotalEvents();
    double getMean();
    double getVariance();
    double getRMS();
    double getSumSquares(){ return sumSquares; }

    void printInfo( bool doPrintStat = 0, QFile* pFile=nullptr);
    void printData(bool doPrintNumberEventsPerBin=0, bool doPrintAllInputs=0,
                   QFile* pFileNev=nullptr,QFile* pFileInp=nullptr );

private:
    QString name;

    qint16  leftLimit;
    qint16  rightLimit;
    quint16 nBins;
    quint16 binWidth;
    qint32  sumValues=0;
    double  sumSquares=0;
    quint16 nLosts=0;
    quint32 Nev=0;

    std::vector<qint16> inputs;                      //    All input values
    quint16* nEvents=nullptr;       // Number of events per bin

    void initNevents();
    void fillNevents(quint16 val=0);
    void clearNevents();
    void setnBins(quint16 _nBins);


};



class Hist2Data
{
public:
    Hist2Data(qint16 _leftXLimit,qint16 _rightXLimit,quint16 _nXBins,
              qint16 _leftYLimit,qint16 _rightYLimit,quint16 _nYBins);
    ~Hist2Data();

    std::vector <qint16> inputs;                                            //    All input values

    void addEvent(qint16 _valX,qint16 _valY);
    quint16& operator() (const quint16 indexX,const quint16 indexY);        //  return nEvents per cell
    bool isEmpty(){return inputs.empty();}
    void clear();

    quint16 getnXBins()     {return nXBins;}
    quint16 getnYBins()     {return nYBins;}
    quint16 getbinXWidth()  {return binXWidth;}
    quint16 getbinYWidth()  {return binYWidth;}
    QString getHistName()   {return name;}
    qint16  getLeftXLimit() {return leftXLimit;}
    qint16  getRightXLimit(){return rightXLimit;}
    qint16  getLeftYLimit() {return leftYLimit;}
    qint16  getRightYLimit(){return rightYLimit;}

    quint32 getTotalEvents(){return Nev;}

    void setHistName(QString _name){name=_name;}
    bool rebinX(quint16 _newBinXWidth);
    bool rebinY(quint16 _newBinYWidth);

    void setbinXWidth(qreal _binXWidth);

    void printInfo(QFile* pFile=nullptr);
    void printData(bool doPrintNumberEventsPerBin=0, bool doPrintAllInputs=0,
                   QFile* pFileNev=nullptr,QFile* pFileInp=nullptr );


private:

    QString name;
    qint16  leftXLimit;
    qint16  rightXLimit;
    quint16 nXBins;
    quint16 binXWidth;

    qint16  leftYLimit;
    qint16  rightYLimit;
    quint16 nYBins;
    quint16 binYWidth;

    quint16* nEvents;       // Number of events per cell

    quint32 Nev=0;
    quint32 nLosts=0;

    void setnXBins(quint16 _nXBins);
    void setnYBins(quint16 _nYBins);

    void fillNevents(quint16 val=0);
    void initNevents();
    void clearNevents();
};


#endif // HISTDATA_H
