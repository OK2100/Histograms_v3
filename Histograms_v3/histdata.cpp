#include "histdata.h"

HistData::HistData(qint16 _leftLimit,qint16 _rightLimit,quint16 _nBins)
{
    leftLimit  = _leftLimit;
    rightLimit = _rightLimit;
    setnBins(_nBins);

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

    quint16 idx=(_event-leftLimit)/binWidth;
    if(idx<nBins) {
        nEvents[idx]++;
        sumValues+=_event;
        sumSquares+=(_event*_event*1.0)/1000;
        Nev++;
    }
    else {   nLosts++; return 0xffff;}

    return idx;
}


void HistData::printData(bool doPrintNumberEventsPerBin, bool doPrintAllInputs,QFile* pFileNev,QFile* pFileInp)
{
    QTextStream* out_Nev,*out_Inp;
    if(pFileNev==nullptr) out_Nev = new QTextStream(stdout);
    else out_Nev = new QTextStream(pFileNev);

    if(pFileInp==nullptr) out_Inp = new QTextStream(stdout);
    else out_Inp = new QTextStream(pFileInp);

    if(doPrintAllInputs) {
        *out_Inp<<"Hist \"" << name <<"\" inputs:" << endl;
        foreach(qint16 _inp,inputs){ *out_Inp << _inp << endl;}
        *out_Inp << endl;
    }
    if(doPrintNumberEventsPerBin) {
        *out_Nev << "Hist \"" << name << "\" number of events per bin: " << endl;
        *out_Nev << "index\tvalue" <<endl;
        for(quint16 i=0;i<nBins;i++) *out_Nev  << i << "\t" << nEvents[i] << endl;
        *out_Nev  << endl;
    }

    delete out_Inp;
    delete out_Nev;
}

void HistData::printInfo(bool doPrintStat,QFile* pFile){

    QTextStream* out;
    if(pFile==nullptr) out = new QTextStream(stdout);
    else out = new QTextStream(pFile);

    *out<<"#### INFO ####" << endl;
    *out<<"Histogram name: \""<<name << "\"" << endl;
    *out<<"From: "<<leftLimit<< " to "<<rightLimit << endl;
    *out<<"Bin width: "<<binWidth << endl;
    *out<<"Number of bins: "<<nBins<< endl;
    *out<<"Total events in range: " <<getTotalEvents()<< endl;
    *out<<"Events out of range: "<<nLosts<< endl;

    if(doPrintStat){
        *out<<"@@ "<<name<< endl;
        *out<<"Mean:"<<getMean()<< endl;
        *out<<"RMS:"<<getRMS()<< endl;
    }
    *out<<"##############" << endl<< endl;

    delete out;
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

    Nev=0;
    nLosts = 0;
    sumValues=0;
    sumSquares=0;
}

void HistData::setnBins(quint16 _nBins)
{
    if((rightLimit-leftLimit +1)%_nBins==0){
        binWidth=(rightLimit-leftLimit +1)/(_nBins);
        nBins=_nBins;
    }
    else {
        qDebug() << "Wrong number of bins";
        nBins=0;
        binWidth=0;
    }
}

bool HistData::rebin(quint16 newBinWidth)
{
    if((rightLimit-leftLimit+1)%newBinWidth==0){
        setnBins((rightLimit-leftLimit+1)/newBinWidth);
        clearNevents();
        initNevents();
        fillNevents(0);
        sumValues=0;
        sumSquares=0;
        Nev=0;
        nLosts=0;

        quint32 size=inputs.size();
        for(quint32 i=0;i<size;i++) { addEvent(inputs[i]); inputs.pop_back(); }
        return 1;
    }
    else {
        qDebug() << "Can't set" <<newBinWidth << "as bin width";
        return 0;
    }
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

quint32 HistData::getTotalEvents(qint16 left, qint16 right)
{
    if(left==right && left==0){
        return Nev;
    }
    else{
        if(nEvents != nullptr){
            quint32 sum=0;
            quint16 il=(left < leftLimit)?0:(left-leftLimit)/binWidth;
            quint16 ir=(right > rightLimit)?nBins-1:(right-leftLimit)/binWidth;

            for(quint16 i=il;i<=ir;i++){
                sum+=nEvents[i];
            }
            return sum;
        }
        else return 0;

    }
}

double HistData::getMean(qint16 left, qint16 right)
{
    quint32 N = getTotalEvents(left,right);
    if(left==right && left==0){
        if(N!=0) return sumValues*1.0/getTotalEvents();
        else return 0;
    }
    else{
//        qDebug() << "Start calculating mean value" << N << nBins;
        double mean=0;
        if(N!=0){
            quint16 il=(left < leftLimit)?0:(left-leftLimit)/binWidth;
            quint16 ir=(right > rightLimit)?nBins-1:(right-leftLimit)/binWidth;

            for(quint16 i=il;i<=ir;i++){
                mean+=(nEvents[i]*(left+binWidth*(i-il))*1.0)/N;
//                qDebug() << i << mean;
            }
            return mean;
        }
        else return 0;
    }
}

double HistData::getVariance(qint16 left, qint16 right)
{
    quint32 N = getTotalEvents(left,right);
    if(left==right && left==0){
        if(N!=0) {return (1000*sumSquares)/getTotalEvents()-pow(getMean(),2);}
        else {return 0;}
    }
    else{
        double mean2=0;
        double mean = getMean(left,right);
        if(N!=0){
            quint16 il=(left < leftLimit)?0:(left-leftLimit)/binWidth;
            quint16 ir=(right > rightLimit)?nBins-1:(right-leftLimit)/binWidth;

            for(quint16 i=il;i<=ir;i++){
                mean2+=(nEvents[i]*(left+binWidth*(i-il)-mean)*(left+binWidth*(i-il)-mean)*1.0)/N;
            }
            return mean2;
        }
        else return 0;
    }
}

double HistData::getRMS(qint16 left, qint16 right)
{
    return pow(getVariance(left,right),0.5);
}


quint16& HistData::operator[] (const quint16 index)
{
    if(index<nBins) return nEvents[index];
    else {qDebug() << "Index out of range"; exit(1);}
};


// ################################################################################
// ################################################################################
// ################################################################################



Hist2Data::Hist2Data(qint16 _leftXLimit,qint16 _rightXLimit,quint16 _nXBins,
                     qint16 _leftYLimit,qint16 _rightYLimit,quint16 _nYBins)
{       
    leftXLimit  = _leftXLimit;
    rightXLimit = _rightXLimit;

    leftYLimit  = _leftYLimit;
    rightYLimit = _rightYLimit;

    setnXBins(_nXBins);
    setnYBins(_nYBins);

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
    nEvents = new quint16[nXBins*nYBins];
}

void Hist2Data::fillNevents(quint16 val)
{
    for(quint32 i=0;i<nXBins*nYBins;i++) {
            nEvents[i] = val;
    }
}


void Hist2Data::clearNevents()
{
    delete [] nEvents;
}

void Hist2Data::addEvent(qint16 _valX,qint16 _valY)
{
    inputs.push_back(_valX);
    inputs.push_back(_valY);

    quint16 idX=(_valX-leftXLimit)/binXWidth;
    quint16 idY=(_valY-leftYLimit)/binYWidth;

    if(idX<nXBins && idY<nYBins) {
        nEvents[idX*nYBins+idY]++;
        Nev++;
    }
    else    nLosts++;

}

void Hist2Data::printData(bool doPrintNumberEventsPerBin, bool doPrintAllInputs, QFile *pFileNev, QFile *pFileInp)
{
    QTextStream* out_Nev,*out_Inp;

    if(pFileNev==nullptr) out_Nev = new QTextStream(stdout);
    else out_Nev = new QTextStream(pFileNev);

    if(pFileInp==nullptr) out_Inp = new QTextStream(stdout);
    else out_Inp = new QTextStream(pFileInp);

    if(doPrintAllInputs) {
        *out_Inp<<"Hist \"" << name <<"\" inputs:" << endl;
        *out_Inp<<"XVal\tYVal" << endl;
        for(quint32 i=0;i<inputs.size();i+=2){ *out_Inp << inputs[i] << "\t" << inputs[i+1] << endl;}
        *out_Inp << endl;
    }

    if(doPrintNumberEventsPerBin) {
        *out_Nev<<"Number of events per cell:" << endl;
        *out_Nev<<"idX\tidY\tValue" << endl;

        for(quint16 i=0;i<nXBins;i++){
            for(quint16 j=0;j<nYBins;j++){
                *out_Nev << i << "\t" << j << "\t" << nEvents[i*nYBins+j] << endl;
            }
        *out_Nev << endl;
        }
    }

    delete out_Inp;
    delete out_Nev;
}


void Hist2Data::printInfo(QFile *pFile)
{
    QTextStream* out;
    if(pFile==nullptr) out = new QTextStream(stdout);
    else out = new QTextStream(pFile);

    *out<<"#### INFO ####" << endl;
    *out<<"Histogram name: \""<<name <<"\"" << endl;

    *out<<"X From: "<<leftXLimit<< " to "<<rightXLimit << endl;
    *out<<"X Bin width: "<<binXWidth << endl;
    *out<<"X Number of bins: "<<nXBins << endl;

    *out<<"Y From: "<<leftYLimit<< " to "<<rightYLimit << endl;
    *out<<"Y Bin width: "<<binYWidth << endl;
    *out<<"Y Number of bins: "<<nYBins << endl;

    *out<<"Total events: " << Nev << endl;
    *out<<"Events out of range:"<<nLosts << endl;
    *out<<"##############" << endl;
    *out<< endl;

    delete out;
}

void Hist2Data::clear()
{
    inputs.clear();
    clearNevents();
    nLosts = 0;
    initNevents();
    fillNevents(0);
    Nev=0;
}

bool Hist2Data::rebinX(quint16 _newBinXWidth)
{
    if((rightXLimit-leftXLimit+1)%_newBinXWidth==0){
        setnXBins((rightXLimit-leftXLimit+1)/_newBinXWidth);
        clearNevents();
        initNevents();
        fillNevents(0);
        Nev=0;
        nLosts=0;

        quint32 size=inputs.size();
        for(quint32 i=0;i<size;i+=2) { addEvent(inputs[i],inputs[i+1]); inputs.pop_back();inputs.pop_back(); }
        return 1;
    }
    else {
        qDebug() << "Can't set" <<_newBinXWidth << "as X bin width";
        return 0;
    }
}


bool Hist2Data::rebinY(quint16 _newBinYWidth)
{
    if((rightYLimit-leftYLimit+1)%_newBinYWidth==0){
        setnYBins((rightYLimit-leftYLimit+1)/_newBinYWidth);
        clearNevents();
        initNevents();
        fillNevents(0);
        Nev=0;
        nLosts=0;

        quint32 size=inputs.size();
        for(quint32 i=0;i<size;i+=2) { addEvent(inputs[i],inputs[i+1]); inputs.pop_back();inputs.pop_back(); }
        return 1;
    }
    else {
        qDebug() << "Can't set" <<_newBinYWidth << "as Y bin width";
        return 0;
    }
}



void Hist2Data::setnXBins(quint16 _nXBins)
{
    if((rightXLimit-leftXLimit +1)%_nXBins==0){
        binXWidth=(rightXLimit-leftXLimit +1)/(_nXBins);
        nXBins=_nXBins;
    }
    else {
        qDebug() << "Wrong number of X bins";
        nXBins=0;
        binXWidth=0;
    }
}

void Hist2Data::setnYBins(quint16 _nYBins)
{
    if((rightYLimit-leftYLimit +1)%_nYBins==0){
        binYWidth=(rightYLimit-leftYLimit +1)/(_nYBins);
        nYBins=_nYBins;
    }
    else {
        qDebug() << "Wrong number of Y bins";
        nYBins=0;
        binYWidth=0;
    }
}

void Hist2Data::setbinXWidth(qreal _binWidth)
{
    quint16 _nXBins=qCeil((rightXLimit-leftXLimit+1)/_binWidth);            //convert _binWidth to nearest
    setnXBins(_nXBins);
}

quint16& Hist2Data::operator() (const quint16 indexX,const quint16 indexY)
{
    return nEvents[indexX*nYBins+indexY];
};

