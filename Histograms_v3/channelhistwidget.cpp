#include "channelhistwidget.h"
#include "ui_channelhistwidget.h"
#include <QtGlobal>

void ChannelHistWidget::add2data(qint16 _charge,qint16 _time,quint8 graph_id){

    bool makeHaos = true;
    if(makeHaos)
        chargeTimeHist->graph(graph_id)->addData(_charge+((1.0*(qrand()%101)/100)*hist0->getbinYWidth())-hist0->getbinYWidth()/2,
                                     _time+((1.0*(qrand()%101)/100)*hist0->getbinXWidth()-hist0->getbinXWidth()/2) );
    else chargeTimeHist->graph(graph_id)->addData(_charge,_time);

}

void ChannelHistWidget::Experements()
{
    qDebug() << (*hist0)(20,0) << (*hist1)(20,0);

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

void ChannelHistWidget::set2Data()
{
    Hist2Data* data = nullptr;
    Hist2Data* extra_data = nullptr;

    if(ADC_ID == 0) {
        data = hist0;
    }
    else if(ADC_ID == 1) {
        data = hist1;
    }
    else if(ADC_ID == 2) {
        data = hist0; extra_data = hist1;
    }

    quint8 graph_id=0;

    for(quint16 i=0;i<data->getnXBins();i++){
        for(quint16 j=0;j<data->getnYBins();j++){

            if(extra_data == nullptr){
                for(quint16 k=0;k<(*data)(i,j);k++){
                    if(     (*data)(i,j)*1.0/data->getTotalEvents()>0.04)   { graph_id=7;}
                    else if((*data)(i,j)*1.0/data->getTotalEvents()>0.03)   { graph_id=6;}
                    else if((*data)(i,j)*1.0/data->getTotalEvents()>0.02)   { graph_id=5;}
                    else if((*data)(i,j)*1.0/data->getTotalEvents()>0.01)   { graph_id=4;}
                    else if((*data)(i,j)*1.0/data->getTotalEvents()>0.008)  { graph_id=3;}
                    else if((*data)(i,j)*1.0/data->getTotalEvents()>0.004)  { graph_id=2;}
                    else if((*data)(i,j)*1.0/data->getTotalEvents()>0.001)  { graph_id=1;}
                    else                                                    { graph_id=0;}

                    add2data(data->getLeftXLimit() + (i*data->getbinXWidth()),data->getLeftYLimit() + (j*data->getbinYWidth()),graph_id);
//                    if(extra_data!=nullptr) add2data(extra_data->getLeftXLimit() + (i*extra_data->getbinXWidth()),extra_data->getLeftYLimit() + (j*extra_data->getbinYWidth()),graph_id);
                }

            }
            else{
                for(quint16 k=0;k<((*data)(i,j)+(*extra_data)(i,j));k++){
                    if(     ((*data)(i,j)+(*extra_data)(i,j))*1.0/(data->getTotalEvents()+extra_data->getTotalEvents())>0.04)   { graph_id=7;}
                    else if(((*data)(i,j)+(*extra_data)(i,j))*1.0/(data->getTotalEvents()+extra_data->getTotalEvents())>0.03)   { graph_id=6;}
                    else if(((*data)(i,j)+(*extra_data)(i,j))*1.0/(data->getTotalEvents()+extra_data->getTotalEvents())>0.02)   { graph_id=5;}
                    else if(((*data)(i,j)+(*extra_data)(i,j))*1.0/(data->getTotalEvents()+extra_data->getTotalEvents())>0.01)   { graph_id=4;}
                    else if(((*data)(i,j)+(*extra_data)(i,j))*1.0/(data->getTotalEvents()+extra_data->getTotalEvents())>0.008)  { graph_id=3;}
                    else if(((*data)(i,j)+(*extra_data)(i,j))*1.0/(data->getTotalEvents()+extra_data->getTotalEvents())>0.004)  { graph_id=2;}
                    else if(((*data)(i,j)+(*extra_data)(i,j))*1.0/(data->getTotalEvents()+extra_data->getTotalEvents())>0.001)  { graph_id=1;}
                    else                                                    { graph_id=0;}

                    add2data(data->getLeftXLimit() + (i*data->getbinXWidth()),data->getLeftYLimit() + (j*data->getbinYWidth()),graph_id);
//                    add2data(extra_data->getLeftXLimit() + (i*extra_data->getbinXWidth()),extra_data->getLeftYLimit() + (j*extra_data->getbinYWidth()),graph_id);
                }


            }

        }
    }


}

ChannelHistWidget::ChannelHistWidget(QWidget *parent,QString _chID):
    QWidget(parent),
    ui(new Ui::ChannelHistWidget)
{
    ui->setupUi(this);

    QRect rec = QApplication::desktop()->screenGeometry();
    this->setMaximumWidth(rec.width() / 4-18);

    chID = _chID;
    chargeHist = ui->chargeHist;
    timeHist = ui->timeHist;
    chargeTimeHist = ui->chargeTimeHist;

    channelIDButton = ui->channelIDButton;
    channelIDButton->setText("Setup channel "+chID+":");

    connect(channelIDButton,SIGNAL(clicked()),this,SLOT(channelIDButton_clicked()));

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

    connect(chargeTimeHist->xAxis,
            static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged),
            chargeHist->xAxis,
            static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::setRange));

    connect(chargeTimeHist->yAxis,
            static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged),
            timeHist->xAxis,
            static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::setRange));


    connect(chargeHist,&QCustomPlot::afterReplot,this,&ChannelHistWidget::replot_chargeTimeHist);
    connect(timeHist,&QCustomPlot::afterReplot,this,&ChannelHistWidget::replot_chargeTimeHist);

    connect(chargeTimeHist,&QCustomPlot::afterReplot,this,&ChannelHistWidget::replot_chargeHist);
    connect(chargeTimeHist,&QCustomPlot::afterReplot,this,&ChannelHistWidget::replot_timeHist);

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


ChannelHistWidget::~ChannelHistWidget()
{
    delete chargeData;
    delete chargeData1;
    delete timeData;
    delete timeData1;

    delete hist0;
    delete hist1;

    chargeHist->clearPlottables();
    timeHist->clearPlottables();
    chargeTimeHist->clearPlottables();

    delete chargeHist;
    delete timeHist;
    delete chargeTimeHist;

    delete ui;
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


//void ChannelHistWidget::hist_double_clicked( QCPAbstractPlottable *  	plottable, int  	dataIndex, QMouseEvent *  	event )
void ChannelHistWidget::hist_double_clicked( QMouseEvent * event )
{
    if(ui->doFixRanges->isChecked()) return;

    QCustomPlot* hist = static_cast<QCustomPlot*>( QObject::sender() );

    if(event->buttons() & Qt::RightButton){
        hist->xAxis->setRangeUpper(qFloor(hist->xAxis->pixelToCoord(event->x())));
        hist->replot();
    }
    else if(event->buttons() & Qt::LeftButton){
        hist->xAxis->setRangeLower(qFloor(hist->xAxis->pixelToCoord(event->x())));
        hist->replot();
    }

}

void ChannelHistWidget::InitHistograms()
{
    chargeData = new HistData(-100,4095,4196);
    chargeData->name = "Channel "+chID+" charge";
    timeData = new HistData(-2048,2047,4096);
    timeData->name = "Channel "+chID+" time";
    chargeBars = new QCPBars(chargeHist->xAxis,chargeHist->yAxis);
    timeBars = new QCPBars(timeHist->xAxis,timeHist->yAxis);

    chargeData1 = new HistData(-100,4095,4196);
    chargeData1->name = "Channel "+chID+" charge _ ADC1";
    timeData1 = new HistData(-2048,2047,4096);
    timeData1->name = "Channel "+chID+" time _ ADC1";

    chargeTimeHist->addGraph(chargeTimeHist->xAxis,chargeTimeHist->yAxis);
    chargeTimeHist->addGraph(chargeTimeHist->xAxis,chargeTimeHist->yAxis);
    chargeTimeHist->addGraph(chargeTimeHist->xAxis,chargeTimeHist->yAxis);
    chargeTimeHist->addGraph(chargeTimeHist->xAxis,chargeTimeHist->yAxis);
    chargeTimeHist->addGraph(chargeTimeHist->xAxis,chargeTimeHist->yAxis);
    chargeTimeHist->addGraph(chargeTimeHist->xAxis,chargeTimeHist->yAxis);
    chargeTimeHist->addGraph(chargeTimeHist->xAxis,chargeTimeHist->yAxis);
    chargeTimeHist->addGraph(chargeTimeHist->xAxis,chargeTimeHist->yAxis);

    hist0 = new Hist2Data(-2048,2047,4096,-100,4095,4196);
    hist1 = new Hist2Data(-2048,2047,4096,-100,4095,4196);
}

void ChannelHistWidget::setLabels()
{
    if(ADC_ID==0){
        ui->lbl_Nev->setText("Sum:"+QString::number(chargeData->getTotalEvents()));
        ui->lbl_Mean->setText("Mean:"+QString::number(chargeData->getSampleMean(),'g',5));
        ui->lbl_StdDev->setText("RMS:"+QString::number( sqrt(chargeData->getSampleVariance()),'g',4 ));
        ui->lbl_Nev1->setText("Sum:"+QString::number(timeData->getTotalEvents()));
        ui->lbl_Mean1->setText("Mean:"+QString::number(timeData->getSampleMean(),'g',5));
        ui->lbl_StdDev1->setText("RMS:"+QString::number( sqrt(timeData->getSampleVariance()),'g',4 ));
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }

    if(ADC_ID==1){
        ui->lbl_Nev->setText("Sum:"+QString::number(chargeData1->getTotalEvents()));
        ui->lbl_Mean->setText("Mean:"+QString::number(chargeData1->getSampleMean(),'g',5));
        ui->lbl_StdDev->setText("RMS:"+QString::number( sqrt(chargeData1->getSampleVariance()),'g',4 ));
        ui->lbl_Nev1->setText("Sum:"+QString::number(timeData1->getTotalEvents()));
        ui->lbl_Mean1->setText("Mean:"+QString::number(timeData1->getSampleMean(),'g',5));
        ui->lbl_StdDev1->setText("RMS:"+QString::number( sqrt(timeData1->getSampleVariance()),'g',4 ));
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }

    if(ADC_ID==2){
        ui->lbl_Nev->setText("Sum:"+QString::number(chargeData->getTotalEvents()+chargeData1->getTotalEvents()));
        if(chargeData->getTotalEvents()!=0 && chargeData1->getTotalEvents()!=0){
            ui->lbl_StdDev->setText("RMS:"+QString::number(sqrt(1000*(chargeData->getSumSquares()+chargeData1->getSumSquares())/(chargeData->getTotalEvents()+chargeData1->getTotalEvents())
                                                               - pow((chargeData->getSampleMean()+chargeData1->getSampleMean())/2,2)),'g',4));
            ui->lbl_Mean->setText("Mean:"+QString::number( (chargeData->getSampleMean()+chargeData1->getSampleMean())/2,'g',5 ));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        else if(chargeData->getTotalEvents()==0){
            ui->lbl_StdDev->setText("RMS:"+QString::number(sqrt(chargeData1->getSampleVariance()),'g',4));
            ui->lbl_Mean->setText("Mean:"+QString::number(chargeData1->getSampleMean(),'g',5));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        else{
            ui->lbl_StdDev->setText("RMS:"+QString::number(sqrt(chargeData->getSampleVariance()),'g',4));
            ui->lbl_Mean->setText("Mean:"+QString::number(chargeData->getSampleMean(),'g',5));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }

        ui->lbl_Nev1->setText("Sum:"+QString::number(timeData->getTotalEvents()+timeData1->getTotalEvents()));
        if(timeData->getTotalEvents()!=0 && timeData1->getTotalEvents()!=0){
            ui->lbl_StdDev1->setText("RMS:"+QString::number(sqrt(1000*(timeData->getSumSquares()+timeData1->getSumSquares())/(timeData->getTotalEvents()+timeData1->getTotalEvents())
                                                               - pow((timeData->getSampleMean()+timeData1->getSampleMean())/2,2)),'g',4));
            ui->lbl_Mean1->setText("Mean:"+QString::number( (timeData->getSampleMean()+timeData1->getSampleMean())/2,'g',5 ));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        else if(timeData->getTotalEvents()==0){
            ui->lbl_StdDev1->setText("RMS:"+QString::number(sqrt(timeData1->getSampleVariance()),'g',4));
            ui->lbl_Mean1->setText("Mean:"+QString::number(timeData1->getSampleMean(),'g',5));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        else{
            ui->lbl_StdDev1->setText("RMS:"+QString::number(sqrt(timeData->getSampleVariance()),'g',4));
            ui->lbl_Mean1->setText("Mean:"+QString::number(timeData->getSampleMean(),'g',5));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }

    }
}

void ChannelHistWidget::SetupView(){

    QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
    fixedTicker->setTickStep(1.0);
    fixedTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);

    QPen pen;
    pen.setColor(QColor(Qt::darkBlue));

    QCPItemText *chargeLabel = new QCPItemText(chargeHist);
    chargeLabel->setLayer("axes");
    chargeLabel->setPositionAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    chargeLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    chargeLabel->position->setCoords(1,1); // place position at center/top of axis rect
    chargeLabel->setRotation(270);
    chargeLabel->setClipToAxisRect(0);
    chargeLabel->setText("Charge");
    chargeLabel->setFont(QFont(font().family(),10)); // make font a bit larger
    chargeLabel->setBrush(Qt::white);

    QCPItemText *timeLabel = new QCPItemText(timeHist);
    timeLabel->setLayer("axes");
    timeLabel->setPositionAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    timeLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    timeLabel->position->setCoords(1,1); // place position at center/top of axis rect
    timeLabel->setRotation(270);
    timeLabel->setClipToAxisRect(0);
    timeLabel->setText("Time");
    timeLabel->setFont(QFont(font().family(),10)); // make font a bit larger
    timeLabel->setBrush(Qt::white);

    QCPItemText *chCountsLabel = new QCPItemText(chargeHist);
    chCountsLabel->setLayer("axes");
    chCountsLabel->setPositionAlignment(Qt::AlignBottom|Qt::AlignLeft);
    chCountsLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    chCountsLabel->position->setCoords(0,0); // place position at center/top of axis rect
    chCountsLabel->setRotation(0);
    chCountsLabel->setClipToAxisRect(0);
    chCountsLabel->setText("Counts");
    chCountsLabel->setFont(QFont(font().family(),10)); // make font a bit larger
    chCountsLabel->setBrush(Qt::white);

    QCPItemText *tCountsLabel = new QCPItemText(timeHist);
    tCountsLabel->setLayer("axes");
    tCountsLabel->setPositionAlignment(Qt::AlignBottom|Qt::AlignLeft);
    tCountsLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    tCountsLabel->position->setCoords(0,0); // place position at center/top of axis rect
    tCountsLabel->setRotation(0);
    tCountsLabel->setClipToAxisRect(0);
    tCountsLabel->setText("Counts");
    tCountsLabel->setFont(QFont(font().family(),10)); // make font a bit larger
    tCountsLabel->setBrush(Qt::white);

    chargeHist->yAxis->setTicker(fixedTicker);
    chargeHist->xAxis->setTicker(fixedTicker);
    chargeHist->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    chargeHist->axisRect()->setRangeDrag(Qt::Horizontal);
    chargeHist->axisRect()->setRangeZoom(Qt::Horizontal);
    chargeHist->axisRect()->setBackgroundScaled(false);
    chargeBars->setPen(pen);
    chargeBars->setBrush(QColor(Qt::darkBlue));

    timeHist->yAxis->setTicker(fixedTicker);
    timeHist->xAxis->setTicker(fixedTicker);
    timeHist->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    timeHist->axisRect()->setRangeDrag(Qt::Horizontal);
    timeHist->axisRect()->setRangeZoom(Qt::Horizontal);
    timeBars->setPen(pen);
    timeBars->setBrush(QColor(Qt::darkBlue));

    chargeTimeHist->xAxis->setTicker(fixedTicker);
    chargeTimeHist->yAxis->setTicker(fixedTicker);

    QCPItemText *chargeLabel1 = new QCPItemText(chargeTimeHist);
    chargeLabel1->setLayer("axes");
    chargeLabel1->setPositionAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    chargeLabel1->position->setType(QCPItemPosition::ptAxisRectRatio);
    chargeLabel1->position->setCoords(1,1); // place position at center/top of axis rect
    chargeLabel1->setRotation(270);
    chargeLabel1->setClipToAxisRect(0);
    chargeLabel1->setText("Charge");
    chargeLabel1->setFont(QFont(font().family(),10)); // make font a bit larger
    chargeLabel1->setBrush(Qt::white);

    QCPItemText *timeLabel1 = new QCPItemText(chargeTimeHist);
    timeLabel1->setLayer("axes");
    timeLabel1->setPositionAlignment(Qt::AlignBottom|Qt::AlignLeft);
    timeLabel1->position->setType(QCPItemPosition::ptAxisRectRatio);
    timeLabel1->position->setCoords(0,0); // place position at center/top of axis rect
    timeLabel1->setRotation(0);
    timeLabel1->setClipToAxisRect(0);
    timeLabel1->setText("Time");
    timeLabel1->setFont(QFont(font().family(),10)); // make font a bit larger
    timeLabel1->setBrush(Qt::white);

    chargeTimeHist->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    for(quint8 j=0;j<8;j++) chargeTimeHist->graph(j)->setLineStyle(QCPGraph::lsNone);

    chargeTimeHist->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare,QColor(0,0,0),QColor(0,0,0),3));
    chargeTimeHist->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare,QColor(0,0,100),QColor(0,0,100),3));
    chargeTimeHist->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare,QColor(0,0,255),QColor(0,0,255),3));
    chargeTimeHist->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare,QColor(0,240,240),QColor(0,240,240),3));
    chargeTimeHist->graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare,QColor(0,255,0),QColor(0,255,0),3));
    chargeTimeHist->graph(5)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare,QColor(255,255,0),QColor(255,255,0),3));
    chargeTimeHist->graph(6)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare,QColor(255,180,0),QColor(255,127,0),3));
    chargeTimeHist->graph(7)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare,QColor(255,0,0),QColor(255,0,0),3));

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

    qDebug() << chargeHist->xAxis->range().lower;
    qDebug() << chargeHist->xAxis->range().upper;

    chargeTimeHist->xAxis->setRange(-3,3);
    chargeTimeHist->yAxis->setRange(-3,3);

    ui->rb_1->setChecked(1);
    qDebug() << ui->rb_01->isChecked();


}

void ChannelHistWidget::AddEvent(quint8 adc_id, qint16 charge, qint16 time)
{
    if(adc_id == 0) { chargeData->addEvent(charge);     timeData->addEvent(time);   hist0->addEvent(charge,time);}
    if(adc_id == 1) { chargeData1->addEvent(charge);    timeData1->addEvent(time);  hist1->addEvent(charge,time);}
}

void ChannelHistWidget::Update()
{
    ClearScreen();
    PlotHistograms();
}

void ChannelHistWidget::ClearScreen()
{
    for(quint8 j=0;j<8;j++) chargeTimeHist->graph(j)->data().data()->clear();

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
        else { chargeHist->yAxis->rescale(); chargeHist->yAxis->setRange(0,chargeHist->yAxis->range().upper*1.1); }
        chargeBars->setWidth(chargeData->getbinWidth());

//----------------------- TIME --------------------------
        setData(timeBars);
        if(timeData->isEmpty() && timeData1->isEmpty() )     { timeHist->yAxis->setRange(0,5); }
        else { timeHist->yAxis->rescale(); timeHist->yAxis->setRange(0,timeHist->yAxis->range().upper*1.1);}
        timeBars->setWidth(timeData->getbinWidth());

//-------------------- CHARGE-TIME ----------------------

    set2Data();
//    chargeTimeHist->rescaleAxes();

//=======================================================

//    if(!chargeData->inputs.isEmpty()&&!timeData->inputs.isEmpty()) {
//        if(doHideZeroBars) HideZeroBars();
//    }


    chargeHist->replot();
    timeHist->replot();
    chargeTimeHist->replot();

    setLabels();
}

void ChannelHistWidget::Clear()
{
    chargeData->clear();
    timeData->clear();

    chargeData1->clear();
    timeData1->clear();

    chargeBars->data().data()->clear();
    timeBars->data().data()->clear();

    hist0->clear();
    hist1->clear();
    for(quint8 j=0;j<8;j++) chargeTimeHist->graph(j)->data().data()->clear();
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
    if(ui->doFixRanges->isChecked()) return;

    HistData* cdata[2];
    HistData* tdata[2];
    bool ADC_empty[2];
    double chMinBorder[2], chMaxBorder[2], tMinBorder[2], tMaxBorder[2];
    ADC_empty[0]=ADC_empty[1]=0;

    for(quint8 j=0;j<2;j++){ cdata[j]=tdata[j]=nullptr; ADC_empty[j]=1;}

    if(ADC_ID ==0){
        cdata[0] = chargeData;   tdata[0] = timeData;
        if(!(cdata[0]->isEmpty() && tdata[0]->isEmpty())){ADC_empty[0]=0;}
    }
    else if(ADC_ID ==1){
        cdata[1] = chargeData1;  tdata[1] = timeData1;
        if(!(cdata[1]->isEmpty() && tdata[1]->isEmpty())){ADC_empty[1]=0;}
    }
    else if(ADC_ID ==2){
        cdata[0] = chargeData;   tdata[0] = timeData;   if(!(cdata[0]->isEmpty() && tdata[0]->isEmpty())){ADC_empty[0]=0;}
        cdata[1] = chargeData1;  tdata[1] = timeData1;  if(!(cdata[1]->isEmpty() && tdata[1]->isEmpty())){ADC_empty[1]=0;}
    }

    if(ADC_empty[0] && ADC_empty[1]) return;
    else{
        for(quint8 j=0;j<2;j++) {
             if(cdata[j]==nullptr || ADC_empty[j]){ continue; }
             else{
                 double leftBorder,rightBorder,binWidth;
                 quint16 nBins;
                 quint16 i=0;

                 leftBorder = cdata[j]->getLeftLimit();
                 binWidth = cdata[j]->getbinWidth();
                 while((*cdata[j])[i]==0){
                     i++;
                     leftBorder+=binWidth;
                 }
//                 qDebug() << "Charge" << j << "left" << leftBorder;

                 i=0;
                 rightBorder = cdata[j]->getRightLimit();
                 nBins = cdata[j]->getnBins();
                 while((*cdata[j])[nBins-1-i]==0){
                     i++;
                     rightBorder-=binWidth;
                 }
//                 qDebug() << "Charge" << j << "right" << rightBorder;

                 chMinBorder[j]=leftBorder-binWidth; chMaxBorder[j]=rightBorder+binWidth;

                 i=0;
                 leftBorder = tdata[j]->getLeftLimit();
                 binWidth = tdata[j]->getbinWidth();
                 while((*tdata[j])[i]==0){
                     i++;
                     leftBorder+=binWidth;
                 }
//                 qDebug() << "Time" << j << "left" << leftBorder;

                 i=0;
                 rightBorder = tdata[j]->getRightLimit();
                 nBins = tdata[j]->getnBins();
                 while((*tdata[j])[nBins-1-i]==0){
                     i++;
                     rightBorder-=binWidth;
                 }
//                 qDebug() << "Time" << j << "right" << rightBorder;

                 tMinBorder[j]=leftBorder-binWidth; tMaxBorder[j]=rightBorder+binWidth;
             }
         } // end of for
    }
    if(ADC_ID==2){
        if(ADC_empty[0]){
            chargeHist->xAxis->setRange(chMinBorder[1],chMaxBorder[1]);
            timeHist->xAxis->setRange(tMinBorder[1],tMaxBorder[1]);
        }
        else if(ADC_empty[1]){
            chargeHist->xAxis->setRange(chMinBorder[0],chMaxBorder[0]);
            timeHist->xAxis->setRange(tMinBorder[0],tMaxBorder[0]);
        }
        else {
            chargeHist->xAxis->setRange(fmin(chMinBorder[0],chMinBorder[1]),fmax(chMaxBorder[0],chMaxBorder[1]));
            timeHist->xAxis->setRange(fmin(tMinBorder[0],tMinBorder[1]),fmax(tMaxBorder[0],tMaxBorder[1]));
        }
    }
    else {
        for(quint8 j=0;j<2;j++){
            if(ADC_ID==j && !ADC_empty[j]){
                chargeHist->xAxis->setRange(chMinBorder[j],chMaxBorder[j]);
                timeHist->xAxis->setRange(tMinBorder[j],tMaxBorder[j]);}
             else continue;
        }
    }
    chargeHist->replot();
    timeHist->replot();

}

void ChannelHistWidget::ShowFullRange(){
    if(ui->doFixRanges->isChecked()) return;
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
