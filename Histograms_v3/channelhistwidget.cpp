#include "channelhistwidget.h"
#include "ui_channelhistwidget.h"
#include <QtGlobal>


void ChannelHistWidget::Experements()
{

}

ChannelHistWidget::ChannelHistWidget(QWidget *parent,QString _chID):
    QWidget(parent),
    ui(new Ui::ChannelHistWidget)
{
    ui->setupUi(this);

    QRect rec = QApplication::desktop()->screenGeometry();
//    this->setMinimumWidth(rec.width() / 4-18);

    chID = _chID;
    chargeHist = ui->chargeHist;
    timeHist = ui->timeHist;
    chargeTimeHist = ui->chargeTimeHist;

    channelIDButton = ui->channelIDButton;
    channelIDButton->setText("Setup Ch "+chID+":");

    connect(channelIDButton,SIGNAL(clicked()),this,SLOT(channelIDButton_clicked()));

    //---------------------------------------------


    InitHistograms();

    SetupView();

    //    Experements();

    //    LoadSettings("../../default.ini");


        setupWindow = new SetupChannelWindow;

        connect(setupWindow,
                reinterpret_cast<void (SetupChannelWindow::*)(Qt::CheckState)>(&SetupChannelWindow::check_status)
                ,ui->doFixRanges,&QCheckBox::setCheckState);
        connect(ui->doFixRanges,&QCheckBox::stateChanged,setupWindow,&SetupChannelWindow::set_fix_range_chaecked);

    connect(chargeHist,&QCustomPlot::mouseDoubleClick,this,&ChannelHistWidget::hist_double_clicked);
    connect(timeHist,  &QCustomPlot::mouseDoubleClick,this,&ChannelHistWidget::hist_double_clicked);

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
    chargeHist->clearPlottables();
    timeHist->clearPlottables();
    chargeTimeHist->clearPlottables();

    delete chargeHist;
    delete timeHist;
    delete chargeTimeHist;

//    delete setupWindow;

    delete ui;
}

void ChannelHistWidget::auto_rescale(const QCPRange &newRange){
    bool fr=false;
    quint16 upper = 0;
    quint16 upper1 = 0;
    if(sender() == chargeHist->xAxis){
        if(newRange.upper > 4095) chargeHist->xAxis->setRangeUpper(4095);
        if(newRange.lower < -100) chargeHist->xAxis->setRangeLower(-100);

        upper=chargeBars->data().data()->valueRange(fr,QCP::sdBoth,newRange).upper;
        upper1=chargeBars1->data().data()->valueRange(fr,QCP::sdBoth,newRange).upper;
        if(ADC_ID==2){
            if((upper+upper1) > chargeHist->yAxis->range().upper){
                chargeHist->yAxis->rescale();
                chargeHist->yAxis->setRange(0,chargeHist->yAxis->range().upper*1.1);
            } else chargeHist->yAxis->setRange(0,(upper+upper1)*1.1);
        }
        else if(ADC_ID==1)  chargeHist->yAxis->setRange(0,upper1*1.1);
        else if(ADC_ID==0)  chargeHist->yAxis->setRange(0,upper*1.1);
    }
    else if(sender() == timeHist->xAxis){
        if(newRange.upper > 2047) timeHist->xAxis->setRangeUpper(2047);
        if(newRange.lower < -2048) timeHist->xAxis->setRangeLower(-2048);

        upper=timeBars->data().data()->valueRange(fr,QCP::sdBoth,newRange).upper;
        upper1=timeBars1->data().data()->valueRange(fr,QCP::sdBoth,newRange).upper;
        if(ADC_ID==2)
            if((upper+upper1) > timeHist->yAxis->range().upper){
                timeHist->yAxis->rescale();
                timeHist->yAxis->setRange(0,timeHist->yAxis->range().upper*1.1);
            } else timeHist->yAxis->setRange(0,(upper+upper1)*1.1);
        else if(ADC_ID==1)  timeHist->yAxis->setRange(0,upper1*1.1);
        else if(ADC_ID==0)  timeHist->yAxis->setRange(0,upper*1.1);
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
    chargeBars = new QCPBars(chargeHist->xAxis,chargeHist->yAxis);
    timeBars = new QCPBars(timeHist->xAxis,timeHist->yAxis);

    chargeBars1 = new QCPBars(chargeHist->xAxis,chargeHist->yAxis);
    timeBars1 = new QCPBars(timeHist->xAxis,timeHist->yAxis);

    chargeBars1->moveAbove(chargeBars);
    timeBars1->moveAbove(timeBars);

    for(quint16 j=0;j<256;j++){    chargeTimeHist->addGraph(chargeTimeHist->xAxis,chargeTimeHist->yAxis);}
}


void ChannelHistWidget::SetupView(){

    ui->frame_3->setStyleSheet("background-color: rgba(255, 255, 255,150);");
    ui->frame_4->setStyleSheet("background-color: rgba(255, 255, 255,150);");
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
    chargeBars->setBrush(QColor(QColor(100,0,0)));
    chargeBars1->setPen(pen);
    chargeBars1->setBrush(QColor(QColor(200,0,0)));
    chargeBars->setWidth(1);
    chargeBars1->setWidth(1);

    chargeBars->setStackingGap(0);
    chargeBars1->setStackingGap(0);
    timeBars->setStackingGap(0);
    timeBars1->setStackingGap(0);

    timeHist->yAxis->setTicker(fixedTicker);
    timeHist->xAxis->setTicker(fixedTicker);
    timeHist->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    timeHist->axisRect()->setRangeDrag(Qt::Horizontal);
    timeHist->axisRect()->setRangeZoom(Qt::Horizontal);

    timeBars->setPen(pen);
    timeBars->setBrush(QColor(QColor(100,0,0)));
    timeBars1->setPen(pen);
    timeBars1->setBrush(QColor(QColor(200,0,0)));
    timeBars->setWidth(1);
    timeBars1->setWidth(1);

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

    chargeHist->xAxis->setRange(-100,4095);
    timeHist->xAxis->setRange(-2048,2047);

    chargeTimeHist->xAxis->setRange(-100,4095);
    chargeTimeHist->yAxis->setRange(-2048,2047);
}

void ChannelHistWidget::SaveHistograms(QString dest_dir)
{
    QPixmap chargePix(chargeHist->size()); chargeHist->render(&chargePix); chargePix.save(dest_dir+"/Ch"+chID+"_charge.png","PNG");
    QPixmap timePix(timeHist->size()); timeHist->render(&timePix); timePix.save(dest_dir+"/Ch"+chID+"_time.png","PNG");
    QPixmap chargeTimePix(chargeTimeHist->size()); chargeTimeHist->render(&chargeTimePix); chargeTimePix.save(dest_dir+"/Ch"+chID+"_charge_time.png","PNG");
}


void ChannelHistWidget::ADC0_choosed()
{
    ADC_ID = 0;
    chargeBars->setVisible(1);
    chargeBars1->setVisible(0);
    timeBars->setVisible(1);
    timeBars1->setVisible(0);
//    UpdateScreen();
}
void ChannelHistWidget::ADC1_choosed()
{
    ADC_ID = 1;
    chargeBars1->moveAbove(0);

    chargeBars->setVisible(0);
    chargeBars1->setVisible(1);

    timeBars1->moveAbove(0);
    timeBars->setVisible(0);
    timeBars1->setVisible(1);
//    UpdateScreen();
}
void ChannelHistWidget::ADC01_choosed()
{
    ADC_ID = 2;
    chargeBars->setVisible(1);
    chargeBars1->setVisible(1);
    chargeBars1->moveAbove(chargeBars);

    timeBars->setVisible(1);
    timeBars1->setVisible(1);
    timeBars1->moveAbove(timeBars);
//    UpdateScreen();
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

void ChannelHistWidget::UpdateScreen()
{
    chargeHist->yAxis->rescale(1);  chargeHist->yAxis->setRange(0,chargeHist->yAxis->range().upper*1.1);
    timeHist->yAxis->rescale(1);    timeHist->yAxis->setRange(0,timeHist->yAxis->range().upper*1.1);
    chargeHist->replot();
    timeHist->replot();
    chargeTimeHist->replot();
}

void ChannelHistWidget::channelIDButton_clicked()
{
//    qDebug()<<"Clicked";
    if(setupWindow->isHidden()){
        setupWindow->set_charge_range(chargeHist->xAxis->range().lower,chargeHist->xAxis->range().upper);
        setupWindow->set_time_range(timeHist->xAxis->range().lower,timeHist->xAxis->range().upper);
        setupWindow->set_chID(chID);
        setupWindow->set_binWidth_charge(Ywidth);
        setupWindow->set_binWidth_time(Xwidth);
        setupWindow->set_nBins_charge(QString::number(nXBins));
        setupWindow->set_nBins_time(QString::number(nYBins));
        setupWindow->set_fix_range_chaecked(ui->doFixRanges->checkState());
        setupWindow->show();
    }
    else {
        setupWindow->activateWindow();
    }
}

void ChannelHistWidget::HideZeroBars()
{
    if(ui->doFixRanges->isChecked()) return;

    if(ADC_ID==2){
        qint16 left,right,left1,right1;
        left=right=left1=right1=0;
        if(!chargeBars->data()->isEmpty()){
            left = chargeBars->data()->at(0)->key;
            right = chargeBars->data()->at(chargeBars->data()->size()-1)->key;
        }
        if(!chargeBars1->data()->isEmpty()){
            left1 = chargeBars1->data()->at(0)->key;
            right1 = chargeBars1->data()->at(chargeBars1->data()->size()-1)->key;
        }
//        qDebug() << left << right << left1 << right1 << timeBars1->data()->isEmpty();

        if(left != right && left1!= right1) chargeHist->xAxis->setRange(qMin(left,left1)-chargeBars->width(),qMax(right,right1)+chargeBars->width());
        else if(left==right) chargeHist->xAxis->setRange(left1-chargeBars->width(),right1+chargeBars->width());
        else chargeHist->xAxis->setRange(left-chargeBars->width(),right+chargeBars->width());

        left=right=left1=right1=0;

        if(!timeBars->data()->isEmpty()){
            left = timeBars->data()->at(0)->key;
            right = timeBars->data()->at(timeBars->data()->size()-1)->key;
        }
        if(!timeBars1->data()->isEmpty()){
            left1 = timeBars1->data()->at(0)->key;
            right1 = timeBars1->data()->at(timeBars1->data()->size()-1)->key;
        }
        if(left != right && left1!= right1) timeHist->xAxis->setRange(qMin(left,left1)-timeBars->width(),qMax(right,right1)+timeBars->width());
        else if(left==right) timeHist->xAxis->setRange(left1-timeBars->width(),right1+timeBars->width());
        else timeHist->xAxis->setRange(left-timeBars->width(),right+timeBars->width());
    }
    else if(ADC_ID==0){
        qint16 left,right;
        left=right=0;
        if(!chargeBars->data()->isEmpty()){
            left = chargeBars->data()->at(0)->key;
            right = chargeBars->data()->at(chargeBars->data()->size()-1)->key;
        }
        chargeHist->xAxis->setRange(left-chargeBars->width(),right+chargeBars->width());
        left=right=0;
        if(!timeBars->data()->isEmpty()){
            left = timeBars->data()->at(0)->key;
            right = timeBars->data()->at(timeBars->data()->size()-1)->key;
        }
        timeHist->xAxis->setRange(left-timeBars->width(),right+timeBars->width());

    }
    else if(ADC_ID==1){
        qint16 left,right;
        left=right=0;
        if(!chargeBars1->data()->isEmpty()){
            left = chargeBars1->data()->at(0)->key;
            right = chargeBars1->data()->at(chargeBars1->data()->size()-1)->key;
        }
        chargeHist->xAxis->setRange(left-chargeBars1->width(),right+chargeBars1->width());
        left=right=0;
        if(!timeBars1->data()->isEmpty()){
            left = timeBars1->data()->at(0)->key;
            right = timeBars1->data()->at(timeBars1->data()->size()-1)->key;
        }
        timeHist->xAxis->setRange(left-timeBars1->width(),right+timeBars1->width());
    }

    chargeHist->replot();
    timeHist->replot();
    chargeTimeHist->replot();
}

void ChannelHistWidget::ShowFullRange(){
    if(ui->doFixRanges->isChecked()) return;
    chargeHist->xAxis->setRange(-100,4095);
    chargeHist->replot();
    timeHist->xAxis->setRange(-2048,2047);
    timeHist->replot();
}






// ########################################################################################################################
// ########################################################################################################################



// ########################################################################################################################
// ########################################################################################################################


dataContainer::dataContainer(ChannelHistWidget * _ui):
    QObject(nullptr)
{
    chargeData = new HistData(-100,4095,4196);
    timeData = new HistData(-2048,2047,4096);

    chargeData1 = new HistData(-100,4095,4196);
    timeData1 = new HistData(-2048,2047,4096);

    hist0 = new Hist2Data(-100,4095,4196,-2048,2047,4096);
    hist1 = new Hist2Data(-100,4095,4196,-2048,2047,4096);

    ui=_ui;

    chargeData->setHistName(qPrintable("Channel "+ui->chID+" ADC_0 charge data"));
    chargeData1->setHistName(qPrintable("Channel "+ui->chID+" ADC_1 charge data"));
    timeData->setHistName(qPrintable("Channel "+ui->chID+" ADC_0 time data"));
    timeData1->setHistName(qPrintable("Channel "+ui->chID+" ADC_1 time data"));

    hist0->setHistName(qPrintable("Channel "+ui->chID+" ADC_0 data"));
    hist1->setHistName(qPrintable("Channel "+ui->chID+" ADC_1 data"));

    fillColorMap();

    ui->data = this;
    ui->nXBins = chargeData->getnBins();
    ui->nYBins = timeData->getnBins();
    ui->Xwidth = chargeData->getbinWidth();
    ui->Ywidth = timeData->getbinWidth();

    connect(ui->setupWindow,&SetupChannelWindow::binWidth_charge_changed,this,&dataContainer::rebinX);
    connect(ui->setupWindow,&SetupChannelWindow::binWidth_time_changed,this,&dataContainer::rebinY);
    connect(ui->setupWindow,&SetupChannelWindow::end_of_apply,this,&dataContainer::updateUiScreen);

    connect(ui->ui->rb_0,&QRadioButton::clicked,this,&dataContainer::updateUiScreen);
    connect(ui->ui->rb_1,&QRadioButton::clicked,this,&dataContainer::updateUiScreen);
    connect(ui->ui->rb_01,&QRadioButton::clicked,this,&dataContainer::updateUiScreen);

//    connect(ui->ui->rb_0,&QRadioButton::clicked,this,&dataContainer::set2Data);
//    connect(ui->ui->rb_1,&QRadioButton::clicked,this,&dataContainer::set2Data);
//    connect(ui->ui->rb_01,&QRadioButton::clicked,this,&dataContainer::set2Data);

//    connect(ui->ui->rb_0,&QRadioButton::clicked,this,&dataContainer::setLabels);
//    connect(ui->ui->rb_1,&QRadioButton::clicked,this,&dataContainer::setLabels);
//    connect(ui->ui->rb_01,&QRadioButton::clicked,this,&dataContainer::setLabels);


    chargeTimer.setSingleShot(1);
    chargeTimer.setInterval(1000);
    chargeTimer.callOnTimeout([=](){
        qint16 leftCh = qCeil(ui->chargeHist->xAxis->range().lower);
        qint16 rightCh = qFloor(ui->chargeHist->xAxis->range().upper);

        if(ui->ADC_ID==0){
           ui->ui->lbl_Nev->setText("Sum:  "+QString::number(chargeData->getTotalEvents(leftCh,rightCh)));
           ui->ui->lbl_Mean->setText("Mean: "+QString::number(chargeData->getMean(leftCh,rightCh),'g',5));
           ui->ui->lbl_StdDev->setText("RMS:  "+QString::number( chargeData->getRMS(leftCh,rightCh),'g',4 ));
       }

       if(ui->ADC_ID==1){
           ui->ui->lbl_Nev->setText("Sum:  "+QString::number(chargeData1->getTotalEvents(leftCh,rightCh)));
           ui->ui->lbl_Mean->setText("Mean: "+QString::number(chargeData1->getMean(leftCh,rightCh),'g',5));
           ui->ui->lbl_StdDev->setText("RMS:  "+QString::number( chargeData1->getRMS(leftCh,rightCh),'g',4 ));
       }

       if(ui->ADC_ID==2){
            quint32 N = chargeData->getTotalEvents(leftCh,rightCh)+ chargeData1->getTotalEvents(leftCh,rightCh);

            double mean2=0;
            double mean = (N!=0)?
                        (chargeData->getMean(leftCh,rightCh)*chargeData->getTotalEvents(leftCh,rightCh)+
                        chargeData1->getMean(leftCh,rightCh)*chargeData1->getTotalEvents(leftCh,rightCh))*1.0/N
                                                             :0;
            ui->ui->lbl_Nev->setText(QString::asprintf("Sum:  %d",N));
            ui->ui->lbl_Mean->setText(QString::asprintf("Mean: %.3f",mean));

            if(N!=0){
                quint16 il=(leftCh < chargeData->getLeftLimit())?0:(leftCh-chargeData->getLeftLimit())/chargeData->getbinWidth();
                quint16 ir=(rightCh > chargeData->getRightLimit())?chargeData->getnBins()-1:(rightCh-chargeData->getLeftLimit())/chargeData->getbinWidth();
                quint16 il1=(leftCh < chargeData1->getLeftLimit())?0:(leftCh-chargeData1->getLeftLimit())/chargeData1->getbinWidth();
                quint16 ir1=(rightCh > chargeData1->getRightLimit())?chargeData1->getnBins()-1:(rightCh-chargeData1->getLeftLimit())/chargeData1->getbinWidth();

                quint16 min_idx = (il<il1)?il:il1;
                quint16 max_idx = (ir>ir1)?ir:ir1;


                for(quint16 i=min_idx;i<=max_idx;i++){
                    mean2+=( ((*chargeData)[i]+(*chargeData1)[i])*(leftCh+chargeData->getbinWidth()*(i-min_idx)-mean)*(leftCh+chargeData->getbinWidth()*(i-min_idx)-mean)*1.0)/N;
                }
                ui->ui->lbl_StdDev->setText(QString::asprintf("RMS:  %.3f", pow(mean2,0.5)));

            }
            else ui->ui->lbl_StdDev->setText(QString::asprintf("RMS:  %.3f", double(0) ));



       }

    });

    timeTimer.setSingleShot(1);
    timeTimer.setInterval(1000);
    timeTimer.callOnTimeout([=](){
        qint16 leftT = qCeil(ui->timeHist->xAxis->range().lower);
        qint16 rightT = qFloor(ui->timeHist->xAxis->range().upper);
        if(ui->ADC_ID==0){
            ui->ui->lbl_Nev1->setText("Sum: "+QString::number(timeData->getTotalEvents(leftT,rightT)));
            ui->ui->lbl_Mean1->setText("Mean: "+QString::number(timeData->getMean(leftT,rightT),'g',5));
            ui->ui->lbl_StdDev1->setText("RMS: "+QString::number( timeData->getRMS(leftT,rightT),'g',4 ));
        }

        if(ui->ADC_ID==1){
            ui->ui->lbl_Nev1->setText("Sum:  "+QString::number(timeData1->getTotalEvents(leftT,rightT)));
            ui->ui->lbl_Mean1->setText("Mean: "+QString::number(timeData1->getMean(leftT,rightT),'g',5));
            ui->ui->lbl_StdDev1->setText("RMS:  "+QString::number( timeData1->getRMS(leftT,rightT),'g',4 ));
        }

        if(ui->ADC_ID==2){
             quint32 N = timeData->getTotalEvents(leftT,rightT)+ timeData1->getTotalEvents(leftT,rightT);

             double mean2=0;
             double mean = (N!=0)?
                         (timeData->getMean(leftT,rightT)*timeData->getTotalEvents(leftT,rightT)+
                         timeData1->getMean(leftT,rightT)*timeData1->getTotalEvents(leftT,rightT))*1.0/N
                                                              :0;
             ui->ui->lbl_Nev1->setText(QString::asprintf("Sum:  %d",N));
             ui->ui->lbl_Mean1->setText(QString::asprintf("Mean: %.3f",mean));

             if(N!=0){
                 quint16 il=(leftT < timeData->getLeftLimit())?0:(leftT-timeData->getLeftLimit())/timeData->getbinWidth();
                 quint16 ir=(rightT > timeData->getRightLimit())?timeData->getnBins()-1:(rightT-timeData->getLeftLimit())/timeData->getbinWidth();
                 quint16 il1=(leftT < timeData1->getLeftLimit())?0:(leftT-timeData1->getLeftLimit())/timeData1->getbinWidth();
                 quint16 ir1=(rightT > timeData1->getRightLimit())?timeData1->getnBins()-1:(rightT-timeData1->getLeftLimit())/timeData1->getbinWidth();

                 quint16 min_idx = (il<il1)?il:il1;
                 quint16 max_idx = (ir>ir1)?ir:ir1;


                 for(quint16 i=min_idx;i<=max_idx;i++){
                     mean2+=( ((*timeData)[i]+(*timeData1)[i])*(leftT+timeData->getbinWidth()*(i-min_idx)-mean)*(leftT+timeData->getbinWidth()*(i-min_idx)-mean)*1.0)/N;
                 }
                 ui->ui->lbl_StdDev1->setText(QString::asprintf("RMS:  %.3f", pow(mean2,0.5)));

             }
             else ui->ui->lbl_StdDev1->setText(QString::asprintf("RMS:  %.3f", double(0) ));

        }
    });

    connect(ui->chargeHist,&QCustomPlot::afterReplot,this,[=](){
        chargeTimer.start();
    });

    connect(ui->timeHist,&QCustomPlot::afterReplot,this,[=](){
        timeTimer.start();
    });


}


dataContainer::~dataContainer()
{
    delete chargeData;
    delete chargeData1;
    delete timeData;
    delete timeData1;

    delete hist0;
    delete hist1;
}


void dataContainer::saveHistogramsData(QString dest_dir)
{
}

void dataContainer::Clear()
{
    chargeData->clear();
    timeData->clear();

    chargeData1->clear();
    timeData1->clear();

    ui->chargeBars->data().data()->clear();
    ui->chargeBars1->data().data()->clear();
    ui->timeBars->data().data()->clear();
    ui->timeBars1->data().data()->clear();

    hist0->clear();
    hist1->clear();
    for(quint16 j=0;j<Ncols;j++) ui->chargeTimeHist->graph(j)->data().data()->clear();
}


void dataContainer::AddEvent(quint8 adc_id, qint16 charge, qint16 time)
{
    quint16 idx;
    quint16 idy;
    double left;

    if(adc_id == 0) {
        idx=chargeData->addEvent(charge);
        idy=timeData->addEvent(time);
        hist0->addEvent(charge,time);

        left=chargeData->getLeftLimit()-0.5 + chargeData->getbinWidth()/2.0;
        ui->chargeBars->data().data()->remove(left + (idx*chargeData->getbinWidth()));
        ui->chargeBars->addData(left + (idx*chargeData->getbinWidth()),(*chargeData)[idx]);

        left=timeData->getLeftLimit()-0.5 + timeData->getbinWidth()/2.0;
        ui->timeBars->data().data()->remove(left + (idy*timeData->getbinWidth()));
        ui->timeBars->addData(left + (idy*timeData->getbinWidth()),(*timeData)[idy]);
    }
    else if(adc_id == 1) {
        idx=chargeData1->addEvent(charge);
        idy=timeData1->addEvent(time);
        hist1->addEvent(charge,time);

        left=chargeData1->getLeftLimit()-0.5 + chargeData1->getbinWidth()/2.0;
        ui->chargeBars1->data().data()->remove(left + (idx*chargeData1->getbinWidth()));
        ui->chargeBars1->addData(left + (idx*chargeData1->getbinWidth()),(*chargeData1)[idx]);

        left=timeData1->getLeftLimit()-0.5 + timeData1->getbinWidth()/2.0;
        ui->timeBars1->data().data()->remove(left + (idy*timeData1->getbinWidth()));
        ui->timeBars1->addData(left + (idy*timeData1->getbinWidth()),(*timeData1)[idy]);
    }

}



void dataContainer::add2data(double _charge,double _time,quint8 graph_id)
{
    bool makeHaos = true;
    quint8 step = 20;


    if(!makeHaos)
        for(quint8 i=0;i<step+1;i++){
            for(quint8 j=0;j<step+1;j++) {
                ui->chargeTimeHist->graph(graph_id)->addData(
                            _charge+((1.0*(i%(step+1))/step)*hist0->getbinXWidth())-hist0->getbinXWidth()*0.5,
                            _time  +((1.0*(j%(step+1))/step)*hist0->getbinYWidth()-hist0->getbinYWidth()*0.5)
                            );

            }
        }
    else
        for(quint8 i=0;i<step+1;i++){
            for(quint8 j=0;j<step+1;j++) {
                ui->chargeTimeHist->graph(graph_id)->addData(
                            _charge+((1.0*(qrand()%(step))/step)*hist0->getbinXWidth())-hist0->getbinXWidth()*0.5,
                            _time  +((1.0*(qrand()%(step))/step)*hist0->getbinYWidth()-hist0->getbinYWidth()*0.5)
                            );
            }
        }

}



void dataContainer::fillColorMap()
{
//    QFile file("../sources/black-body-table-byte-0256.csv");
    QFile file("./sources/colormap.csv");
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
            ui->chargeTimeHist->graph(counter)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare,QColor(r,g,b),QColor(r,g,b),5));
//            qDebug() <<counter << threshold[counter] << r << g << b;
            counter++;
        }
        file.close();
    }

}


void dataContainer::setData(bool f) // 0-time , 1-charge
{
    if(f){
        ui->chargeBars->data().data()->clear();
        ui->chargeBars1->data().data()->clear();
        double left=chargeData->getLeftLimit()-0.5 + chargeData->getbinWidth()/2.0;

        for(quint16 i=0;i<chargeData->getnBins();i++){
            if((*chargeData)[i])ui->chargeBars->addData(left + (i*chargeData->getbinWidth()),(*chargeData)[i]) ;
            if((*chargeData1)[i])ui->chargeBars1->addData(left + (i*chargeData1->getbinWidth()),(*chargeData1)[i]) ;
        }
    }
    else{
        ui->timeBars->data().data()->clear();
        ui->timeBars1->data().data()->clear();

        double left=timeData->getLeftLimit()-0.5 + timeData->getbinWidth()/2.0;

        for(quint16 i=0;i<timeData->getnBins();i++){
            if((*timeData)[i])ui->timeBars->addData(left + (i*timeData->getbinWidth()),(*timeData)[i]) ;
            if((*timeData1)[i])ui->timeBars1->addData(left + (i*timeData1->getbinWidth()),(*timeData1)[i]) ;
        }
    }
}

void dataContainer::set2Data()
{
    for(quint16 i=0;i<Ncols;i++) ui->chargeTimeHist->graph(i)->data().data()->clear();
    Hist2Data* data = nullptr;
    Hist2Data* extra_data = nullptr;

    if(ui->ADC_ID == 0) {
        data = hist0;
    }
    else if(ui->ADC_ID == 1) {
        data = hist1;
    }
    else if(ui->ADC_ID == 2) {
        data = hist0; extra_data = hist1;
    }

    quint8 graph_id=0;
    double leftX,leftY;

    leftX=data->getLeftXLimit()-0.5+data->getbinXWidth()/2.0;
    leftY=data->getLeftYLimit()-0.5+data->getbinYWidth()/2.0;

    for(quint16 i=0;i<data->getnXBins();i++){
        for(quint16 j=0;j<data->getnYBins();j++){

            if(extra_data == nullptr){
                if((*data)(i,j)==0){continue;}
                    double tr=(*data)(i,j)*1.0/data->getTotalEvents();
                    for(quint16 c=0;c<Ncols;c++){
                        if(tr>=threshold[Ncols-1-c]){ graph_id = Ncols-1-c;break; }
                        else {continue;}
                    }
                    add2data(leftX + (i*data->getbinXWidth()),leftY + (j*data->getbinYWidth()),graph_id);
            }
            else{
                if(((*data)(i,j)+(*extra_data)(i,j))==0){continue;}
                    double tr=((*data)(i,j)+(*extra_data)(i,j))*1.0/(data->getTotalEvents()+extra_data->getTotalEvents());
                    for(quint16 c=0;c<Ncols;c++){
                        if(tr>=threshold[Ncols-1-c]){ graph_id = Ncols-1-c;break; }
                        else {continue;}
                    }
                    add2data(leftX + (i*data->getbinXWidth()),leftY + (j*data->getbinYWidth()),graph_id);
            }
        }
    }
}

void dataContainer::setLabels()
{
    if(ui->ADC_ID==0){
        ui->ui->lbl_Nev->setText("Sum: "+QString::number(chargeData->getTotalEvents(
                                                             ui->chargeHist->xAxis->range().lower
                                                             ,ui->chargeHist->xAxis->range().upper
                                                             )));
        ui->ui->lbl_Mean->setText("Mean: "+QString::number(chargeData->getMean(
                                                               ui->chargeHist->xAxis->range().lower
                                                               ,ui->chargeHist->xAxis->range().upper
                                                               ),'g',5));
        ui->ui->lbl_StdDev->setText("RMS: "+QString::number( chargeData->getRMS(
                                                                 ui->chargeHist->xAxis->range().lower
                                                                 ,ui->chargeHist->xAxis->range().upper
                                                                 ),'g',4 ));
        ui->ui->lbl_Nev1->setText("Sum: "+QString::number(timeData->getTotalEvents(
                                                              ui->timeHist->xAxis->range().lower
                                                              ,ui->timeHist->xAxis->range().upper
                                                              )));
        ui->ui->lbl_Mean1->setText("Mean: "+QString::number(timeData->getMean(
                                                                ui->timeHist->xAxis->range().lower
                                                                ,ui->timeHist->xAxis->range().upper
                                                                ),'g',5));
        ui->ui->lbl_StdDev1->setText("RMS: "+QString::number( timeData->getRMS(
                                                                  ui->timeHist->xAxis->range().lower
                                                                  ,ui->timeHist->xAxis->range().upper
                                                                  ),'g',4 ));
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }

    if(ui->ADC_ID==1){
        ui->ui->lbl_Nev->setText("Sum: "+QString::number(chargeData1->getTotalEvents(
                                                             ui->chargeHist->xAxis->range().lower
                                                             ,ui->chargeHist->xAxis->range().upper
                                                             )));
        ui->ui->lbl_Mean->setText("Mean: "+QString::number(chargeData1->getMean(
                                                               ui->chargeHist->xAxis->range().lower
                                                               ,ui->chargeHist->xAxis->range().upper
                                                               ),'g',5));
        ui->ui->lbl_StdDev->setText("RMS: "+QString::number( chargeData1->getRMS(
                                                                 ui->chargeHist->xAxis->range().lower
                                                                 ,ui->chargeHist->xAxis->range().upper
                                                                 ),'g',4 ));
        ui->ui->lbl_Nev1->setText("Sum: "+QString::number(timeData1->getTotalEvents(
                                                              ui->timeHist->xAxis->range().lower
                                                              ,ui->timeHist->xAxis->range().upper
                                                              )));
        ui->ui->lbl_Mean1->setText("Mean: "+QString::number(timeData1->getMean(
                                                                ui->timeHist->xAxis->range().lower
                                                                ,ui->timeHist->xAxis->range().upper
                                                                ),'g',5));
        ui->ui->lbl_StdDev1->setText("RMS: "+QString::number( timeData1->getRMS(
                                                                  ui->timeHist->xAxis->range().lower
                                                                  ,ui->timeHist->xAxis->range().upper
                                                                  ),'g',4 ));
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }

    if(ui->ADC_ID==2){
        ui->ui->lbl_Nev->setText("Sum: "+QString::number(chargeData->getTotalEvents()+chargeData1->getTotalEvents()));
        if(chargeData->getTotalEvents()!=0 && chargeData1->getTotalEvents()!=0){
            ui->ui->lbl_StdDev->setText("RMS: "+QString::number(sqrt(1000*(chargeData->getSumSquares()+chargeData1->getSumSquares())/(chargeData->getTotalEvents()+chargeData1->getTotalEvents())
                                                               - pow((chargeData->getMean()+chargeData1->getMean())/2,2)),'g',4));
            ui->ui->lbl_Mean->setText("Mean: "+QString::number( (chargeData->getMean()+chargeData1->getMean())/2,'g',5 ));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        else if(chargeData->getTotalEvents()==0){
            ui->ui->lbl_StdDev->setText("RMS: "+QString::number(chargeData1->getRMS(),'g',4));
            ui->ui->lbl_Mean->setText("Mean: "+QString::number(chargeData1->getMean(),'g',5));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        else{
            ui->ui->lbl_StdDev->setText("RMS: "+QString::number(chargeData->getRMS(),'g',4));
            ui->ui->lbl_Mean->setText("Mean: "+QString::number(chargeData->getMean(),'g',5));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }

        ui->ui->lbl_Nev1->setText("Sum: "+QString::number(timeData->getTotalEvents()+timeData1->getTotalEvents()));
        if(timeData->getTotalEvents()!=0 && timeData1->getTotalEvents()!=0){
            ui->ui->lbl_StdDev1->setText("RMS: "+QString::number(sqrt(1000*(timeData->getSumSquares()+timeData1->getSumSquares())/(timeData->getTotalEvents()+timeData1->getTotalEvents())
                                                               - pow((timeData->getMean()+timeData1->getMean())/2,2)),'g',4));
            ui->ui->lbl_Mean1->setText("Mean: "+QString::number( (timeData->getMean()+timeData1->getMean())/2,'g',5 ));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        else if(timeData->getTotalEvents()==0){
            ui->ui->lbl_StdDev1->setText("RMS: "+QString::number(timeData1->getRMS(),'g',4));
            ui->ui->lbl_Mean1->setText("Mean: "+QString::number(timeData1->getMean(),'g',5));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        else{
            ui->ui->lbl_StdDev1->setText("RMS: "+QString::number(timeData->getRMS(),'g',4));
            ui->ui->lbl_Mean1->setText("Mean: "+QString::number(timeData->getMean(),'g',5));
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }

    }
}

void dataContainer::rebinX(quint16 _binWidth)
{
    chargeData->rebin(_binWidth);
    chargeData1->rebin(_binWidth);
    hist0->rebinX(_binWidth);
    hist1->rebinX(_binWidth);
    ui->chargeBars->setWidth(chargeData->getbinWidth());
    ui->chargeBars1->setWidth(chargeData1->getbinWidth());
    setData(1);
    ui->HideZeroBars();
    ui->setupWindow->set_binWidth_charge(chargeData->getbinWidth());
    ui->setupWindow->set_nBins_charge(QString::number(chargeData->getnBins()));
    ui->setupWindow->set_charge_range(ui->chargeHist->xAxis->range().lower,ui->chargeHist->xAxis->range().upper);
}

void dataContainer::rebinY(quint16 _binWidth)
{
    timeData->rebin(_binWidth);
    timeData1->rebin(_binWidth);
    hist0->rebinY(_binWidth);
    hist1->rebinY(_binWidth);
    ui->timeBars->setWidth(timeData->getbinWidth());
    ui->timeBars1->setWidth(timeData1->getbinWidth());
    setData(0);
    ui->HideZeroBars();
    ui->setupWindow->set_binWidth_time(timeData->getbinWidth());
    ui->setupWindow->set_nBins_time(QString::number(timeData->getnBins()));
    ui->setupWindow->set_time_range(ui->timeHist->xAxis->range().lower,ui->timeHist->xAxis->range().upper);
}

