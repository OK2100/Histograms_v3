#include "channelhistwidget.h"
#include "ui_channelhistwidget.h"
#include <QtGlobal>

void ChannelHistWidget::add2data(qint16 _charge,qint16 _time,quint8 graph_id){


    bool makeHaos = true;
    quint8 step = 20;


    if(!makeHaos)
        for(quint8 i=0;i<=step+1;i++){
            for(quint8 j=0;j<=step+1;j++) {
                chargeTimeHist->graph(graph_id)->addData(_charge+((1.0*(i%(step+1))/step)*hist0->getbinYWidth())-hist0->getbinYWidth()*0.5,
                                             _time+((1.0*(j%(step+1))/step)*hist0->getbinXWidth()-hist0->getbinXWidth()*0.5) );

            }
        }
    else
        for(quint8 i=0;i<=step+1;i++){
            for(quint8 j=0;j<=step+1;j++) {
                chargeTimeHist->graph(graph_id)->addData(_charge+((1.0*(qrand()%(step+1))/step)*hist0->getbinYWidth())-hist0->getbinYWidth()*0.5,
                                             _time+((1.0*(qrand()%(step+1))/step)*hist0->getbinXWidth()-hist0->getbinXWidth()*0.5) );

            }
        }

}



void ChannelHistWidget::fillColorMap()
{
//    QFile file("../sources/black-body-table-byte-0256.csv");
    QFile file("../sources/colormap.csv");
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "File not exists";
    }
    else {
        QStringList wordList;
        quint8 r,g,b;
        quint16 counter=0;

        while (!file.atEnd()) {
            QString line = file.readLine();
            wordList = line.split(",");
            double x=wordList[0].toDouble();
            threshold[counter] = (1.0/50) * (x/(1.01-pow(x,2)));
//            threshold[counter] = wordList[0].toDouble();                      // linear
//            threshold[counter] = 1-sqrt(1-pow(wordList[0].toDouble(),4));     // pseudo circle
//            threshold[counter] = -qLn(1-wordList[0].toDouble())/(8*qLn(2));
//            threshold[counter] = pow(wordList[0].toDouble(),8);               // poly
            r = wordList[1].toUShort();
            g = wordList[2].toUShort();
            b = wordList[3].toUShort();
            chargeTimeHist->graph(counter)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare,QColor(r,g,b),QColor(r,g,b),5));
//            qDebug() <<counter << threshold[counter] << r << g << b;
            counter++;
        }
        file.close();
    }

}



void ChannelHistWidget::Experements()
{
    for(quint16 j=0;j<1000;j++) AddEvent(0,1001,100);
    for(quint16 j=0;j<1000;j++) AddEvent(0,1003,102);
    for(quint16 j=0;j<1000;j++) AddEvent(0,1010,100);

    for(quint16 j=0;j<1000;j++) AddEvent(1,1008,97);
    for(quint16 j=0;j<1000;j++) AddEvent(1,998,95);
    for(quint16 j=0;j<1000;j++) AddEvent(1,1000,99);

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
                if((*data)(i,j)==0){continue;}
                    double tr=(*data)(i,j)*1.0/data->getTotalEvents();
                    for(quint16 c=0;c<256;c++){
                        if(tr>=threshold[255-c]){ graph_id = 255-c;break; }
                        else {continue;}
                    }

                    add2data(data->getLeftXLimit() + (i*data->getbinXWidth()),data->getLeftYLimit() + (j*data->getbinYWidth()),graph_id);

            }
            else{
                if(((*data)(i,j)+(*extra_data)(i,j))==0){continue;}
                    double tr=((*data)(i,j)+(*extra_data)(i,j))*1.0/(data->getTotalEvents()+extra_data->getTotalEvents());
                    for(quint16 c=0;c<256;c++){
                        if(tr>=threshold[255-c]){ graph_id = 255-c;break; }
                        else {continue;}
                    }
                    add2data(data->getLeftXLimit() + (i*data->getbinXWidth()),data->getLeftYLimit() + (j*data->getbinYWidth()),graph_id);


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

    for(quint16 j=0;j<256;j++){    chargeTimeHist->addGraph(chargeTimeHist->xAxis,chargeTimeHist->yAxis);}
    chargeTimeHist->graph(15)->isWidgetType();

    hist0 = new Hist2Data(-2048,2047,4096,-100,4095,4196);
    hist1 = new Hist2Data(-2048,2047,4096,-100,4095,4196);
}

void ChannelHistWidget::setLabels()
{
    if(ADC_ID==0){
        ui->lbl_Nev->setText("Sum: "+QString::number(chargeData->getTotalEvents()));
        ui->lbl_Mean->setText("Mean: "+QString::number(chargeData->getSampleMean(),'g',5));
        ui->lbl_StdDev->setText("RMS: "+QString::number( sqrt(chargeData->getSampleVariance()),'g',4 ));
        ui->lbl_Nev1->setText("Sum: "+QString::number(timeData->getTotalEvents()));
        ui->lbl_Mean1->setText("Mean: "+QString::number(timeData->getSampleMean(),'g',5));
        ui->lbl_StdDev1->setText("RMS: "+QString::number( sqrt(timeData->getSampleVariance()),'g',4 ));
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }

    if(ADC_ID==1){
        ui->lbl_Nev->setText("Sum: "+QString::number(chargeData1->getTotalEvents()));
        ui->lbl_Mean->setText("Mean: "+QString::number(chargeData1->getSampleMean(),'g',5));
        ui->lbl_StdDev->setText("RMS: "+QString::number( sqrt(chargeData1->getSampleVariance()),'g',4 ));
        ui->lbl_Nev1->setText("Sum: "+QString::number(timeData1->getTotalEvents()));
        ui->lbl_Mean1->setText("Mean: "+QString::number(timeData1->getSampleMean(),'g',5));
        ui->lbl_StdDev1->setText("RMS: "+QString::number( sqrt(timeData1->getSampleVariance()),'g',4 ));
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }

    if(ADC_ID==2){
        ui->lbl_Nev->setText("Sum: "+QString::number(chargeData->getTotalEvents()+chargeData1->getTotalEvents()));
        if(chargeData->getTotalEvents()!=0 && chargeData1->getTotalEvents()!=0){
            ui->lbl_StdDev->setText("RMS: "+QString::number(sqrt(1000*(chargeData->getSumSquares()+chargeData1->getSumSquares())/(chargeData->getTotalEvents()+chargeData1->getTotalEvents())
                                                               - pow((chargeData->getSampleMean()+chargeData1->getSampleMean())/2,2)),'g',4));
            ui->lbl_Mean->setText("Mean: "+QString::number( (chargeData->getSampleMean()+chargeData1->getSampleMean())/2,'g',5 ));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        else if(chargeData->getTotalEvents()==0){
            ui->lbl_StdDev->setText("RMS: "+QString::number(sqrt(chargeData1->getSampleVariance()),'g',4));
            ui->lbl_Mean->setText("Mean: "+QString::number(chargeData1->getSampleMean(),'g',5));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        else{
            ui->lbl_StdDev->setText("RMS: "+QString::number(sqrt(chargeData->getSampleVariance()),'g',4));
            ui->lbl_Mean->setText("Mean: "+QString::number(chargeData->getSampleMean(),'g',5));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }

        ui->lbl_Nev1->setText("Sum: "+QString::number(timeData->getTotalEvents()+timeData1->getTotalEvents()));
        if(timeData->getTotalEvents()!=0 && timeData1->getTotalEvents()!=0){
            ui->lbl_StdDev1->setText("RMS: "+QString::number(sqrt(1000*(timeData->getSumSquares()+timeData1->getSumSquares())/(timeData->getTotalEvents()+timeData1->getTotalEvents())
                                                               - pow((timeData->getSampleMean()+timeData1->getSampleMean())/2,2)),'g',4));
            ui->lbl_Mean1->setText("Mean: "+QString::number( (timeData->getSampleMean()+timeData1->getSampleMean())/2,'g',5 ));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        else if(timeData->getTotalEvents()==0){
            ui->lbl_StdDev1->setText("RMS: "+QString::number(sqrt(timeData1->getSampleVariance()),'g',4));
            ui->lbl_Mean1->setText("Mean: "+QString::number(timeData1->getSampleMean(),'g',5));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        else{
            ui->lbl_StdDev1->setText("RMS: "+QString::number(sqrt(timeData->getSampleVariance()),'g',4));
            ui->lbl_Mean1->setText("Mean: "+QString::number(timeData->getSampleMean(),'g',5));
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
    pen.setColor(QColor(QColor(50,0,0)));

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
    chargeBars->setBrush(QColor(QColor(100,0,0)));

    timeHist->yAxis->setTicker(fixedTicker);
    timeHist->xAxis->setTicker(fixedTicker);
    timeHist->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    timeHist->axisRect()->setRangeDrag(Qt::Horizontal);
    timeHist->axisRect()->setRangeZoom(Qt::Horizontal);
    timeBars->setPen(pen);
    timeBars->setBrush(QColor(Qt::darkBlue));
    timeBars->setBrush(QColor(QColor(100,0,0)));

    chargeHist->axisRect()->setBackground(QBrush(QColor(0,0,0,30)));
    timeHist->axisRect()->setBackground(QBrush(QColor(0,0,0,30)));
    chargeTimeHist->axisRect()->setBackground(QBrush(QColor(0,0,0,30)));

    chargeHist->xAxis->grid()->setPen(QPen(QColor(140, 140, 140,80), 1));
    chargeHist->yAxis->grid()->setPen(QPen(QColor(140, 140, 140,80), 1));
    chargeHist->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    chargeHist->yAxis->grid()->setZeroLinePen(Qt::NoPen);

    timeHist->xAxis->grid()->setPen(QPen(QColor(140, 140, 140,80), 1));
    timeHist->yAxis->grid()->setPen(QPen(QColor(140, 140, 140,80), 1));
    timeHist->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    timeHist->yAxis->grid()->setZeroLinePen(Qt::NoPen);

    chargeTimeHist->xAxis->grid()->setPen(QPen(QColor(140, 140, 140,80), 1));
    chargeTimeHist->yAxis->grid()->setPen(QPen(QColor(140, 140, 140,80), 1));
    chargeTimeHist->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    chargeTimeHist->yAxis->grid()->setZeroLinePen(Qt::NoPen);


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

    for(quint16 j=0;j<256;j++) {
        chargeTimeHist->graph(j)->setLineStyle(QCPGraph::lsNone);
    }

    fillColorMap();

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
    for(quint16 j=0;j<256;j++) chargeTimeHist->graph(j)->data().data()->clear();

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
    for(quint16 j=0;j<256;j++) chargeTimeHist->graph(j)->data().data()->clear();
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

                 chMinBorder[j]=leftBorder-2*binWidth; chMaxBorder[j]=rightBorder+2*binWidth;

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

                 tMinBorder[j]=leftBorder-2*binWidth; tMaxBorder[j]=rightBorder+2*binWidth;
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
