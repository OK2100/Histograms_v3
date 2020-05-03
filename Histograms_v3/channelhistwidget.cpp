#include "channelhistwidget.h"
#include "ui_channelhistwidget.h"
#include <QtGlobal>

void ChannelHistWidget::Experements()
{
//    colorMap->data()->setSize(50, 50);
//    colorMap->data()->setRange(QCPRange(0, 2), QCPRange(0, 2));
    
//    for (int x=0; x<50; ++x)
//      for (int y=0; y<50; ++y)
//        colorMap->data()->setCell(x, y, qCos(x/10.0)+qSin(y/10.0));
    
//    colorMap->setGradient(QCPColorGradient::gpCold);
//    colorMap->setInterpolate(false);
//    colorMap->rescaleDataRange(true);
//    chargeTimeHist->rescaleAxes();
//    chargeTimeHist->replot();
}

void ChannelHistWidget::setData(QCPBars* bars)
{
    HistData* data = nullptr;
    HistData* extra_data = nullptr;

    if(ADC_ID == 0) {
        if(bars == chargeBars) data = chargeData;
        else if(bars == timeBars) data = timeData;
        else   { qDebug() << "ERROR: setData empty pointer"; return;}
    }
    else if(ADC_ID == 1) {
        if(bars == chargeBars) data = chargeData1;
        else if(bars == timeBars) data = timeData1;
        else   { qDebug() << "ERROR: setData empty pointer"; return;}
    }
    else if(ADC_ID == 2) {
        if(bars == chargeBars){ data = chargeData;   extra_data = chargeData1;}
        else if(bars == timeBars){ data = timeData;   extra_data = timeData1;}
        else   { qDebug() << "ERROR: setData empty pointer"; return;}
    }

    for(quint16 i=0;i<data->getnBins();i++){
        if(extra_data==nullptr) bars->addData(data->getLeftLimit() + (i*data->getbinWidth()),(*data)[i]) ;
        else bars->addData(data->getLeftLimit() + (i*data->getbinWidth()),(*data)[i]+(*extra_data)[i]) ;
    }
}

ChannelHistWidget::ChannelHistWidget(QWidget *parent,QString _chID):
    QWidget(parent),
    ui(new Ui::ChannelHistWidget)
{
    ui->setupUi(this);

    chID = _chID;
    chargeHist = ui->chargeHist;
    timeHist = ui->timeHist;
    chargeTimeHist = ui->chargeTimeHist;

    channelIDButton = ui->channelIDButton;
    channelIDButton->setText("Setup channel "+chID+":");
//    channelIDButton->setFixedWidth(150);

    connect(channelIDButton,SIGNAL(clicked()),this,SLOT(channelIDButton_clicked()));

    connect(this,SIGNAL(channelAdded()),parent,SLOT(readFile()));

    //---------------------------------------------

    InitHistograms();

    SetupView();

//    HideZeroBars();

//    Experements();

    setupWindow = new SetupChannelWindow;

    connect(setupWindow,SIGNAL(binWidth_charge_changed(const QString&)),this,SLOT(binWidth_charge_was_changed(const QString&)));
    connect(setupWindow,SIGNAL(binWidth_time_changed(const QString&)),this,SLOT(binWidth_time_was_changed(const QString&)));
    connect(setupWindow,SIGNAL(nBins_charge_changed(const QString&)),this,SLOT(nBins_charge_was_changed(const QString&)));
    connect(setupWindow,SIGNAL(nBins_time_changed(const QString&)),this,SLOT(nBins_time_was_changed(const QString&)));


//    connect(chargeHist,&QCustomPlot::plottableDoubleClick,this,&ChannelHistWidget::hist_double_clicked);
    connect(chargeHist,&QCustomPlot::mouseDoubleClick,this,&ChannelHistWidget::hist_double_clicked);
    connect(timeHist,  &QCustomPlot::mouseDoubleClick,this,&ChannelHistWidget::hist_double_clicked);
//    LoadSettings("../../default.ini");

    connect(chargeHist->xAxis,
            static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged),
            chargeTimeHist->xAxis,
            static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::setRange));

    connect(timeHist->xAxis,
            static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged),
            chargeTimeHist->yAxis,
            static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::setRange));

    connect(chargeHist,&QCustomPlot::afterReplot,this,&ChannelHistWidget::replot_chargeTimeHist);
    connect(timeHist,&QCustomPlot::afterReplot,this,&ChannelHistWidget::replot_chargeTimeHist);

    connect(ui->rb_0,&QRadioButton::clicked,this,&ChannelHistWidget::ADC0_choosed);
    connect(ui->rb_1,&QRadioButton::clicked,this,&ChannelHistWidget::ADC1_choosed);
    connect(ui->rb_01,&QRadioButton::clicked,this,&ChannelHistWidget::ADC01_choosed);

    connect(chargeHist->xAxis,
            static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged),
            this,&ChannelHistWidget::auto_rescale);

    connect(timeHist->xAxis,
            static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged),
            this,&ChannelHistWidget::auto_rescale);
}

void ChannelHistWidget::auto_rescale(const QCPRange &newRange){
    bool fr=false;
    quint16 upper = 0;
    if(sender() == chargeHist->xAxis){
        upper=chargeBars->data().data()->valueRange(fr,QCP::sdBoth,newRange).upper;
        chargeHist->yAxis->setRange(0,upper*1.1);
    }
    else if(sender() == timeHist->xAxis){
        upper=timeBars->data().data()->valueRange(fr,QCP::sdBoth,newRange).upper;
        timeHist->yAxis->setRange(0,upper*1.1);
    }
}



ChannelHistWidget::~ChannelHistWidget()
{
    delete chargeData;
    delete chargeData1;
    delete timeData;
    delete timeData1;

    chargeHist->clearPlottables();
    timeHist->clearPlottables();
    chargeTimeHist->clearPlottables();

    delete chargeHist;
    delete timeHist;
    delete chargeTimeHist;

    delete ui;
}

//void ChannelHistWidget::hist_double_clicked( QCPAbstractPlottable *  	plottable, int  	dataIndex, QMouseEvent *  	event )
void ChannelHistWidget::hist_double_clicked( QMouseEvent * event )
{
    QCustomPlot* hist = static_cast<QCustomPlot*>( QObject::sender() );

    if(event->buttons() & Qt::RightButton){
        hist->xAxis->setRangeUpper(qFloor(hist->xAxis->pixelToCoord(event->x())));
        hist->replot();
//        if(hist == chargeHist) isRightRangeSelected = 1;
//        if(hist == timeHist)   isLeftRangeSelected = 2;
    }
    else if(event->buttons() & Qt::LeftButton){
        hist->xAxis->setRangeLower(qFloor(hist->xAxis->pixelToCoord(event->x())));
        hist->replot();
//        if(hist == chargeHist) isLeftRangeSelected = 1;
//        if(hist == timeHist) isLeftRangeSelected = 2;
    }

//    if( (isRightRangeSelected == isLeftRangeSelected != 0) ){
//        hist->replot();
//        isRightRangeSelected = isLeftRangeSelected = 0;
//    }


}

void ChannelHistWidget::InitHistograms()
{

    chargeData = new HistData(-100,4095,4196);
    chargeData->name = "Channel "+chID+" charge";
    timeData = new HistData(-2048,2047,4096);
    timeData->name = "Channel "+chID+" time";
    chargeBars = new QCPBars(chargeHist->xAxis,chargeHist->yAxis);
    timeBars = new QCPBars(timeHist->xAxis,timeHist->yAxis);
    chargeTimeGraph = new QCPGraph(chargeTimeHist->xAxis,chargeTimeHist->yAxis);

    chargeData1 = new HistData(-100,4095,4196);
    chargeData1->name = "Channel "+chID+" charge _ ADC1";
    timeData1 = new HistData(-2048,2047,4096);
    timeData1->name = "Channel "+chID+" time _ ADC1";

//    hist0 = new Hist2Data(-2048,2047,4096,-100,4095,4196);
//    hist1 = new Hist2Data(-2048,2047,4096,-100,4095,4196);
}

void ChannelHistWidget::SetupView(){

    QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
    fixedTicker->setTickStep(2.0);
    fixedTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);

    QPen pen;
    pen.setColor(QColor(Qt::darkBlue));

    chargeHist->xAxis->setLabel("Charge");
    chargeHist->xAxis->setTicker(fixedTicker);
    chargeHist->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    chargeHist->axisRect()->setRangeDrag(Qt::Horizontal);
    chargeHist->axisRect()->setRangeZoom(Qt::Horizontal);
    chargeHist->axisRect()->setBackgroundScaled(false);
    chargeHist->yAxis->setLabel("N_inputs");
    chargeBars->setPen(pen);
    chargeBars->setBrush(QColor(Qt::darkBlue));

    timeHist->xAxis->setLabel("Time");
    timeHist->xAxis->setTicker(fixedTicker);
    timeHist->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    timeHist->axisRect()->setRangeDrag(Qt::Horizontal);
    timeHist->axisRect()->setRangeZoom(Qt::Horizontal);
    timeHist->yAxis->setLabel("N_inputs");
    timeBars->setPen(pen);
    timeBars->setBrush(QColor(Qt::darkBlue));

    chargeTimeHist->xAxis->setLabel("Charge");
    chargeTimeHist->yAxis->setLabel("Time");
    chargeTimeHist->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    chargeHist->xAxis->setRange(chargeData->getLeftLimit(),chargeData->getRightLimit());
    timeHist->xAxis->setRange(timeData->getLeftLimit(),timeData->getRightLimit());

    chargeTimeHist->xAxis->setRange(-100,4095);
    chargeTimeHist->yAxis->setRange(-2048,2047);
}


void ChannelHistWidget::LoadSettings(QString file_ini)
{
    QSettings sett(file_ini, QSettings::IniFormat);
    sett.beginGroup("CHANNEL "+QString("%1").arg(chID));
    qDebug() << sett.value("TEST","ini doesn't work").toString() ;
    sett.endGroup();

//    chargeHist->xAxis->setRange(-2,2);
//    chargeHist->xAxis->setRangeLower(0);
    qDebug() << chargeHist->xAxis->range().lower;
    qDebug() << chargeHist->xAxis->range().upper;

    chargeTimeHist->xAxis->setRange(-3,3);
    chargeTimeHist->yAxis->setRange(-3,3);

    ui->rb_1->setChecked(1);
    qDebug() << ui->rb_01->isChecked();


}

void ChannelHistWidget::AddEvent(quint8 adc_id, qint16 charge, qint16 time)
{
    if(adc_id == 0) { chargeData->addEvent(charge);     timeData->addEvent(time); }
    if(adc_id == 1) { chargeData1->addEvent(charge);    timeData1->addEvent(time); }
}

void ChannelHistWidget::Update()
{
    ClearScreen();
    PlotHistograms();
}

void ChannelHistWidget::ClearScreen()
{
    chargeTimeHist->graph()->data().data()->clear();
    chargeBars->data().data()->clear();
    timeBars->data().data()->clear();
    chargeHist->yAxis->setRange(0,5);
    timeHist->yAxis->setRange(0,5);
    chargeHist->replot();
    timeHist->replot();
    chargeTimeHist->replot();
}

void ChannelHistWidget::PlotHistograms()
{


//---------------------- CHARGE ------------------------
        setData(chargeBars);
        if(chargeData->isEmpty() && chargeData1->isEmpty() )   { chargeHist->yAxis->setRange(0,5); }
        else                        { chargeHist->yAxis->rescale(); }
        chargeBars->setWidth(chargeData->getbinWidth());

//----------------------- TIME --------------------------
        setData(timeBars);
        if(timeData->isEmpty() && timeData1->isEmpty() )     { timeHist->yAxis->setRange(0,5); }
        else                        { timeHist->yAxis->rescale(); }
        timeBars->setWidth(timeData->getbinWidth());

//-------------------- CHARGE-TIME ----------------------
    chargeTimeHist->addGraph();
    chargeTimeHist->graph()->setLineStyle(QCPGraph::lsNone);
    chargeTimeHist->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare,2));

    chargeTimeHist->graph()->setData(chargeData->inputs,timeData->inputs);

    chargeTimeHist->rescaleAxes();

//=======================================================

//    if(!chargeData->inputs.isEmpty()&&!timeData->inputs.isEmpty()) {
        if(doHideZeroBars) HideZeroBars();
//    }

    chargeHist->replot();
    timeHist->replot();
    chargeTimeHist->replot();
}

void ChannelHistWidget::Clear()
{
    chargeData->clear();
    timeData->clear();

    chargeData1->clear();
    timeData1->clear();

    chargeBars->data().data()->clear();
    timeBars->data().data()->clear();
    chargeTimeHist->clearGraphs();
}

void ChannelHistWidget::PrintInfo(bool onlyStat)
{
        chargeData->printInfo(0,0,onlyStat);
        timeData->printInfo(0,0,onlyStat);

        chargeData1->printInfo(0,0,onlyStat);
        timeData1->printInfo(0,0,onlyStat);
}

QString ChannelHistWidget::GetStatInfo()
{
    QString statStr;
    statStr.append("@ "+chargeData->name+"\n");
    statStr.append("Sample mean "+QString::number(chargeData->getSampleMean())+"\n");
    statStr.append("Sample variance "+QString::number(chargeData->getSampleVariance())+"\n");
    statStr.append("Sigma "+QString::number(chargeData->getSigma())+"\n");
    statStr.append("FWHM "+QString::number(chargeData->getFWHM())+"\n");
    statStr.append("\n");

    return statStr;
}

void ChannelHistWidget::channelIDButton_clicked()
{
//    qDebug()<<"Clicked";
    if(setupWindow->isHidden()){
        setupWindow->set_charge_hist_range(QString::number(chargeHist->xAxis->range().lower),
                                           QString::number(chargeHist->xAxis->range().upper));
        setupWindow->set_time_hist_range(QString::number(timeHist->xAxis->range().lower),
                                           QString::number(timeHist->xAxis->range().upper));
        setupWindow->set_chID(chID);
        setupWindow->set_binWidth_charge(QString::number(chargeData->getbinWidth()));
        setupWindow->set_binWidth_time(QString::number(timeData->getbinWidth()));
        setupWindow->set_nBins_charge(QString::number(chargeData->getnBins()));
        setupWindow->set_nBins_time(QString::number(timeData->getnBins()));

        setupWindow->show();
    }
    else {
        setupWindow->activateWindow();
    }
}

void ChannelHistWidget::HideZeroBars()
{
    double leftBorder,rightBorder,binWidth;
    quint16 i,nBins;
    i=0;
    HistData* cdata = nullptr;
    HistData* ex_cdata = nullptr;
    HistData* ex_tdata = nullptr;
    HistData* tdata = nullptr;

    if(ADC_ID ==0)          { cdata = chargeData;   tdata = timeData; }
    else if(ADC_ID ==1)     { cdata = chargeData1;  tdata = timeData1; }
    else if(ADC_ID ==2)     { cdata = chargeData;  ex_cdata = chargeData1;
                              tdata = timeData;   ex_tdata = timeData1; }

    if(ex_cdata==nullptr && ex_tdata==nullptr) {
        leftBorder = cdata->getLeftLimit();
        binWidth = cdata->getbinWidth();
        while((*cdata)[i]==0){
            i++;
            leftBorder+=binWidth;
        }
        i=0;
        rightBorder = cdata->getRightLimit();
        nBins = cdata->getnBins();
        while((*cdata)[nBins-1-i]==0){
            i++;
            rightBorder-=binWidth;
        }
        chargeHist->xAxis->setRange(leftBorder,rightBorder);
        chargeHist->replot();

        i=0;
        leftBorder = tdata->getLeftLimit();
        binWidth = tdata->getbinWidth();
        while((*tdata)[i]==0){
            i++;
            leftBorder+=binWidth;
        }

        i=0;
        rightBorder = tdata->getRightLimit();
        nBins = tdata->getnBins();
        while((*tdata)[nBins-1-i]==0){
            i++;
            rightBorder-=binWidth;
        }
        timeHist->xAxis->setRange(leftBorder,rightBorder);
        timeHist->replot();
    }
    else{
        leftBorder = cdata->getLeftLimit();
        binWidth = cdata->getbinWidth();
        while((*cdata)[i]==0 && (*ex_cdata)[i]==0){
            i++;
            leftBorder+=binWidth;
        }
        i=0;
        rightBorder = cdata->getRightLimit();
        nBins = cdata->getnBins();
        while((*cdata)[nBins-1-i]==0 && (*ex_cdata)[nBins-1-i]==0){
            i++;
            rightBorder-=binWidth;
        }
        chargeHist->xAxis->setRange(leftBorder,rightBorder);
        chargeHist->replot();

        i=0;
        leftBorder = tdata->getLeftLimit();
        binWidth = tdata->getbinWidth();
        while((*tdata)[i]==0 && (*ex_tdata)[i]==0){
            i++;
            leftBorder+=binWidth;
        }

        i=0;
        rightBorder = tdata->getRightLimit();
        nBins = tdata->getnBins();
        while((*tdata)[nBins-1-i]==0 && (*ex_tdata)[nBins-1-i]==0){
            i++;
            rightBorder-=binWidth;
        }
        timeHist->xAxis->setRange(leftBorder,rightBorder);
        timeHist->replot();
    }



    doHideZeroBars = 1;
}

void ChannelHistWidget::ShowFullRange(){
    chargeHist->xAxis->setRange(chargeData->getLeftLimit(),chargeData->getRightLimit());
    chargeHist->replot();
    timeHist->xAxis->setRange(timeData->getLeftLimit(),timeData->getRightLimit());
    timeHist->replot();
}


void ChannelHistWidget::binWidth_charge_was_changed(const QString& _binWidth)
{
    chargeData->setbinWidth(_binWidth.toDouble());
    chargeData1->setbinWidth(_binWidth.toDouble());
    setupWindow->set_binWidth_charge(QString::number(chargeData->getbinWidth()));
//    setupWindow->set_binWidth_time(QString::number(timeData->getbinWidth()));
    setupWindow->set_nBins_charge(QString::number(chargeData->getnBins()));
//    setupWindow->set_nBins_time(QString::number(timeData->getnBins()));
    Update();
//    chargeData->printInfo();
}

void ChannelHistWidget::binWidth_time_was_changed(const QString& _binWidth)
{
    timeData->setbinWidth(_binWidth.toDouble());
    timeData1->setbinWidth(_binWidth.toDouble());
//    setupWindow->set_binWidth_charge(QString::number(chargeData->getbinWidth()));
    setupWindow->set_binWidth_time(QString::number(timeData->getbinWidth()));
//    setupWindow->set_nBins_charge(QString::number(chargeData->getnBins()));
    setupWindow->set_nBins_time(QString::number(timeData->getnBins()));
    Update();
//    timeData->printInfo();
}

void ChannelHistWidget::nBins_charge_was_changed(const QString& _nBins)
{
    chargeData->setnBins(_nBins.toUInt());
    chargeData1->setnBins(_nBins.toUInt());
    setupWindow->set_binWidth_charge(QString::number(chargeData->getbinWidth()));
    setupWindow->set_binWidth_time(QString::number(timeData->getbinWidth()));
    setupWindow->set_nBins_charge(QString::number(chargeData->getnBins()));
    setupWindow->set_nBins_time(QString::number(timeData->getnBins()));
    Update();
//    chargeData->printInfo(0,1);
}

void ChannelHistWidget::nBins_time_was_changed(const QString& _nBins)
{
    timeData->setnBins(_nBins.toUInt());
    timeData1->setnBins(_nBins.toUInt());
    setupWindow->set_binWidth_charge(QString::number(chargeData->getbinWidth()));
    setupWindow->set_binWidth_time(QString::number(timeData->getbinWidth()));
    setupWindow->set_nBins_charge(QString::number(chargeData->getnBins()));
    setupWindow->set_nBins_time(QString::number(timeData->getnBins()));
    Update();
//    timeData->printInfo();
}
