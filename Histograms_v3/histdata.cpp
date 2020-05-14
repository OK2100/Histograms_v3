#include "histdata.h"

HistData::HistData(qint16 _leftLimit,qint16 _rightLimit,quint16 _nBins)
{
    leftLimit  = _leftLimit;
    rightLimit = _rightLimit;
    nBins = _nBins;
    calcbinWidth();

    inputs.reserve(50000);
    initNevents();
    fillNevents(0);
}

HistData::~HistData()
{
 clearNevents();
}

void HistData::initNevents()
{
    nEvents = new quint16[nBins];
}

void HistData::fillNevents(quint16 val)
{
    if(nEvents!=nullptr){
        for(quint16 i=0;i<nBins;i++){
            nEvents[i]=val;
        }
    }
    else return;
}

quint16 HistData::addEvent(qint16 _event)
{
    inputs.push_back(_event);
    qreal leftborder=leftLimit - binWidth/2;
    qreal rightborder=leftborder+binWidth;

    for(quint16 i=0;i<nBins;i++) {
        if((leftborder<=_event)&&(_event<=rightborder)) {
            nEvents[i]++;
            bEmpty = 0;
            sampleMean+=_event;
            sampleVariance+=(_event*_event*1.0)/1000;
            return i;
        }
        leftborder+=binWidth;
        rightborder+=binWidth;
    }
    nLosts++;
    return nBins;
}

void HistData::printInfo(bool doPrintAllInputs,bool doPrintNumberEventsPerBin, bool doPrintOnlyStat){
    if(doPrintOnlyStat){
        qDebug()<<"@@ "<<name;
        qDebug()<<"Sample mean:"<<getSampleMean();
        qDebug()<<"Sample variance:"<<getSampleVariance();
        return;
    }
    qDebug()<<"#### INFO ####";
    qDebug()<<"Histogram name"<<name;
    qDebug()<<"From:"<<leftLimit<< "to:"<<rightLimit;
    qDebug()<<"Bin width:"<<binWidth;
    qDebug()<<"Number of bins:"<<nBins;
    qDebug()<<"Total events in range:" <<getTotalEvents();
    qDebug()<<"Events out of range:"<<nLosts;
    if(doPrintAllInputs) {qDebug()<<"Inputs:"<<inputs;}
    if(doPrintNumberEventsPerBin) {qDebug()<<"Number of events per bin:"<<nEvents;}
    qDebug()<<"##############";
    qDebug()<<"";
}

void HistData::clearNevents()
{
    if(nEvents!=nullptr){
        delete[] nEvents;
        nEvents=nullptr;
    }
    else return;
}

void HistData::clear()
{
    inputs.clear();
    clearNevents();
    initNevents();
    fillNevents(0);
    nLosts = 0;
    bEmpty = 1;
    sampleMean=0;
    sampleVariance=0;
}

void HistData::setnBins(quint16 _nBins)
{
    nBins=_nBins;
    calcbinWidth();

    clearNevents();
    initNevents();

    std::vector<quint16> _inputs(inputs);
    inputs.clear();
    foreach(double _inp,_inputs) {
        addEvent(_inp);
    }
}

quint16 HistData::getnBins()
{
    return nBins;
}

void HistData::setbinWidth(qreal _binWidth)
{
    quint16 _nBins=qCeil((rightLimit-leftLimit+1)/_binWidth);            //convert _binWidth to nearest
    setnBins(_nBins);
}

qreal HistData::getbinWidth()
{
    return binWidth;
}

void HistData::setHistName(QString _name)
{
    name=_name;
}

QString HistData::getHistName()
{
    if (name.isEmpty()) {return "";}
    else { return name;}
}

quint32 HistData::getTotalEvents()
{
    if(nEvents != nullptr){
        quint32 sum=0;
        for(quint16 i=0;i<nBins;i++){ sum+=nEvents[i]; }
        return sum;
    }
    else return 0;
}

quint16& HistData::operator[] (const quint16 index)
{
    return nEvents[index];
};

double HistData::getSampleMean()
{
//    double sum_elems(0);
//    foreach(double _elem,inputs){
//        sum_elems += _elem;
//    }
//    sampleMean = sum_elems/(getTotalEvents());
    if(getTotalEvents()!=0) return sampleMean*1.0/getTotalEvents();
    else return 0;
}

double HistData::getSampleVariance()
{
//    double sum_sqs(0);
//    foreach(double _elem,inputs){
//        sum_sqs += (_elem-getSampleMean())*(_elem-getSampleMean());
//    }
//    sampleVariance = sum_sqs/(getTotalEvents()-1);
    if(getTotalEvents()!=0) {return (1000*sampleVariance)/getTotalEvents()-pow(getSampleMean(),2);}
    else {return 0;}
}

double HistData::getSigma()
{
    return pow(getSampleVariance(),0.5);
}

double HistData::getFWHM()
{
    return 2.355*getSigma();
}

void HistData::calcbinWidth()
{
    binWidth=(rightLimit-leftLimit +1)/(1.0*nBins);
}

void HistData::calcnBins()
{
    nBins=(rightLimit-leftLimit)/binWidth + 1;
}


// ################################################################################
// ################################################################################
// ################################################################################



Hist2Data::Hist2Data(qint16 _leftXLimit,qint16 _rightXLimit,quint16 _nXBins,
                     qint16 _leftYLimit,qint16 _rightYLimit,quint16 _nYBins)
{
    leftLimit  = _leftXLimit;
    rightLimit = _rightXLimit;
    nBins = _nXBins;

    leftYLimit  = _leftYLimit;
    rightYLimit = _rightYLimit;
    nYBins = _nYBins;

    calcbinWidth();

    inputs.reserve(100000);

    initNevents();
    fillNevents(0);
}

Hist2Data::~Hist2Data()
{
    clearNevents();
}

void Hist2Data::initNevents()
{
    nEvents = new quint16[nBins*nYBins];
}

void Hist2Data::fillNevents(quint16 val)
{
    for(quint32 i=0;i<nBins*nYBins;i++) {
            nEvents[i] = val;
    }
}


void Hist2Data::clearNevents()
{
    delete [] nEvents;
}

quint16 Hist2Data::addEvent(qint16 _valX,qint16 _valY)
{
    inputs<<_valX << _valY;

    qreal leftXborder=leftLimit - binWidth/2;
    qreal rightXborder=leftXborder+binWidth;

    qreal leftYborder=leftYLimit - binYWidth/2;
    qreal rightYborder=leftYborder+binYWidth;

    for(quint16 i=0;i<nBins;i++) {
        if((leftXborder<=_valX)&&(_valX<=rightXborder)) {
            for(quint16 j=0;j<nYBins;j++) {
                if((leftYborder<=_valY)&&(_valY<=rightYborder)) {
                    nEvents[i*nBins+j]++;
                    Nev++;
                    bEmpty = 0;
                    return i;
                }
                leftYborder+=binYWidth;
                rightYborder+=binYWidth;
            }
        }
        leftXborder+=binWidth;
        rightXborder+=binWidth;
    }
    nLosts++;
    return nBins;
}

void Hist2Data::printInfo(bool doPrintAllInputs,bool doPrintNumberEventsPerBin, bool doPrintOnlyStat){
    if(doPrintOnlyStat){
        qDebug()<<"@@ "<<name;
//        qDebug()<<"Sample mean:"<<getSampleMean();
//        qDebug()<<"Sample variance:"<<getSampleVariance();
        return;
    }
    qDebug()<<"#### INFO ####";
    qDebug()<<"Histogram name"<<name;

    qDebug()<<"X From:"<<leftLimit<< "to:"<<rightLimit;
    qDebug()<<"X Bin width:"<<binWidth;
    qDebug()<<"X Number of bins:"<<nBins;

    qDebug()<<"Y From:"<<leftYLimit<< "to:"<<rightYLimit;
    qDebug()<<"Y Bin width:"<<binYWidth;
    qDebug()<<"Y Number of bins:"<<nYBins;

    qDebug()<<"Total events in range:" <<getTotalEvents();
    qDebug()<<"Events out of range:"<<nLosts;
    if(doPrintAllInputs) {qDebug()<<"Inputs:"<<inputs;}
    if(doPrintNumberEventsPerBin) {
        qDebug()<<"Number of events per bin:";
//        foreach(QVector<quint16> v, nEvents)
//            qDebug()<<v;
    }
    qDebug()<<"##############";
    qDebug()<<"";
}

void Hist2Data::clear()
{
    inputs.clear();
    clearNevents();
    nLosts = 0;
    initNevents();
    fillNevents(0);
    Nev=0;
    bEmpty = 1;
}

void Hist2Data::setnXBins(quint16 _nBins)
{
    clearNevents();
    nBins=_nBins;
    calcbinWidth();
    initNevents();

    QVector<quint16> _inputs(inputs);
    inputs.clear();
    foreach(double _inp,_inputs) {
//        addEvent(_inp);
    }
}

//void Hist2Data::setnYBins(quint16 _nYBins)
//{
//    clearNevents();
//    nYBins=_nYBins;
//    calcbinWidth();
//    initNevents();

//    QVector<double> _inputs(inputs);
//    inputs.clear();
//    foreach(double _inp,_inputs) {
//        addEvent(_inp);
//    }
//}

quint16 Hist2Data::getnXBins() { return nBins; }

quint16 Hist2Data::getnYBins() { return nYBins; }

void Hist2Data::setbinXWidth(qreal _binWidth)
{
    quint16 _nBins=qCeil((rightLimit-leftLimit+1)/_binWidth);            //convert _binWidth to nearest
    setnXBins(_nBins);
}

//void Hist2Data::setbinYWidth(qreal _binYWidth)
//{
//    quint16 _nYBins=qCeil((rightYLimit-leftYLimit+1)/_binYWidth);            //convert _binWidth to nearest
//    setnYBins(_nYBins);
//}

qreal Hist2Data::getbinXWidth() { return binWidth; }

qreal Hist2Data::getbinYWidth() { return binYWidth; }

void Hist2Data::setHistName(QString _name) { name=_name; }

QString Hist2Data::getHistName()
{
    if (name.isEmpty()) {return "";}
    else { return name;}
}

quint32 Hist2Data::getTotalEvents()
{
    return Nev;
//    quint32 sum=0;
//    foreach(QVector<quint32> v,nEvents){
//        foreach(quint32 elem,v){
//            sum += elem;
//        }
//    }
//    return sum;
}

quint16& Hist2Data::operator() (const quint16 indexX,const quint16 indexY)
{
    return nEvents[indexX*nBins+indexY];
};

//double Hist2Data::getSampleMean()
//{
//    double sum_elems(0);
//    foreach(double _elem,inputs){
//        sum_elems += _elem;
//    }
//    sampleMean = sum_elems/(getTotalEvents());

//    return sampleMean;
//}

//double Hist2Data::getSampleVariance()
//{
//    double sum_sqs(0);
//    foreach(double _elem,inputs){
//        sum_sqs += (_elem-getSampleMean())*(_elem-getSampleMean());
//    }
//    sampleVariance = sum_sqs/(getTotalEvents()-1);
//    return sampleVariance;
//}

//double Hist2Data::getSigma()
//{
//    return pow(getSampleVariance(),0.5);
//}

//double Hist2Data::getFWHM()
//{
//    return 2.355*getSigma();
//}

void Hist2Data::calcbinWidth()
{
    binWidth=(rightLimit-leftLimit +1)/(1.0*nBins);
    binYWidth=(rightYLimit-leftYLimit +1)/(1.0*nYBins);
}

void Hist2Data::calcnBins()
{
    nBins=(rightLimit-leftLimit)/binWidth + 1;
    nYBins=(rightYLimit-leftYLimit)/binYWidth + 1;
}

