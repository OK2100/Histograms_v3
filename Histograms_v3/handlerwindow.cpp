#include "handlerwindow.h"
#include "ui_handlerwindow.h"


void DecodeChsRegExp(QString chIDs, QVector<quint8> &vec)
{
    QRegExp expr("([0-9]{1,2})-([0-9]{1,2})");
//    qDebug() << ( chIDs.contains(expr) ? "Contain" : "Don't contain" ) << ":" << chIDs;
    QRegExp expr2("[0-9]{1,2}");
//    qDebug() << ( chIDs.contains(expr2) ? "Contain" : "Don't contain" ) << ":" << chIDs;

    int lastPos = 0;
    while( ( lastPos = expr.indexIn( chIDs, lastPos ) ) != -1 ) {
        lastPos += expr.matchedLength();
//        qDebug() << expr.cap( 0 ) << ":" << expr.cap( 1 ) << expr.cap(2);
        quint8 first,last;
        first = expr.cap(1).toUShort(); last = expr.cap(2).toUShort();
        for(quint8 j=first;last>=j && j<=12;j++) {
            if(j==0) continue;
            if(!vec.contains(j)) vec.append(j);
        }
    }
    lastPos = 0;
    while( ( lastPos = expr2.indexIn( chIDs, lastPos ) ) != -1 ) {
        lastPos += expr2.matchedLength();
//        qDebug() << expr2.cap( 0 );
        quint8 num = expr2.cap(0).toUShort();
        if(!vec.contains(num) && num<=12 && num!=0) { vec.append(num); }
    }
    std::sort(vec.begin(),vec.end());

}

QString HexStrtoBinStr(QString inp){
    QString result;
    bool ok;
    for(int i=0;i<inp.size();i++){
        QString tmp = inp.mid(i,1);
        result.append(QString("%1").arg(tmp.toLong(&ok,16),4,2,QLatin1Char('0')));
    }
    return result;
};

HandlerWindow::HandlerWindow(HandlerWindow* prevWindow,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HandlerWindow)
{
    ui->setupUi(this);
    grid = ui->grid;
    prevWin=prevWindow;
    if(prevWindow!=nullptr) {
        connect(prevWindow,&HandlerWindow::showNewWindow,this,&HandlerWindow::startNewWindow);
    }

    connect(ui->b_1,&QPushButton::clicked,this,&HandlerWindow::addChannel);
    connect(ui->b_2,&QPushButton::clicked,this,&HandlerWindow::removeChannel);
    connect(ui->b_3,&QPushButton::clicked,this,&HandlerWindow::reset);
    connect(ui->b_4,&QPushButton::clicked,this,&HandlerWindow::hideZeroBars);
    connect(ui->b_6,&QPushButton::clicked,this,&HandlerWindow::readFile);


    LoadSettings("../default.ini");
    SetUp();
}

//      Functions

void HandlerWindow::SetUp()
{

    for(quint16 i=0;i<12;i++) {
        channel[i]=nullptr;
    }
    this->statusBar()->addWidget(&label);

    QRect rec = QApplication::desktop()->screenGeometry();
    Height = rec.height() - rec.height() / 8;
    Width = rec.width() / 4;

    this->setMinimumSize(Width,Height);
    this->setGeometry(rec.x(),rec.y(),Width,Height);

//    ui->frame->setVisible(false);
    ui->b_1->setVisible(true);
    ui->b_2->setVisible(false);
    ui->b_3->setVisible(false);
    ui->b_4->setVisible(false);
    ui->b_5->setVisible(false);
    ui->b_6->setVisible(false);
    ui->b_7->setVisible(false);
    ui->b_8->setVisible(false);

    addedChannelsID.reserve(4);

//--------------------------- Appearance ---------------------------------

    fileBar=menuBar()->addMenu("&File");                    //  #File field

    openSourceFileAction=new QAction("&Open source file...",this);
    openSourceFileAction->setShortcut(tr("Ctrl+o"));
    fileBar->addAction(openSourceFileAction);
    connect(openSourceFileAction, SIGNAL(triggered()),this,SLOT(openSourceFile()));

    dataBar=menuBar()->addMenu("&Data");

    optionsBar=menuBar()->addMenu("&Options");              //  #Options field

    addChannelAction=new QAction("&Add channel...",this);
    addChannelAction->setShortcut(tr("Ctrl+a"));
    optionsBar->addAction(addChannelAction);
    connect(addChannelAction, SIGNAL(triggered()),this,SLOT(addChannel()));

    addChannelRangeAction=new QAction("&Add range of channels...",this);
    addChannelRangeAction->setShortcut(tr("Ctrl+Shift+a"));
    optionsBar->addAction(addChannelRangeAction);
    connect(addChannelRangeAction, SIGNAL(triggered()),this,SLOT(doAddChannelRange()));

    removeChannelAction=new QAction("&Remove channel...",this);
    removeChannelAction->setShortcut(tr("Ctrl+r"));
    optionsBar->addAction(removeChannelAction);
    connect(removeChannelAction, SIGNAL(triggered()),this,SLOT(removeChannel()));

    removeAllChannelAction=new QAction("&Remove all channel",this);
    removeAllChannelAction->setShortcut(tr("Ctrl+Shift+r"));
    optionsBar->addAction(removeAllChannelAction);
    connect(removeAllChannelAction, SIGNAL(triggered()),this,SLOT(removeAllChannel()));

    readFileAction=new QAction("&Read file",this);
    readFileAction->setShortcut(tr("Ctrl+f"));
    optionsBar->addAction(readFileAction);
    connect(readFileAction, SIGNAL(triggered()),this,SLOT(readFile()));

    resetAction=new QAction("&Reset channel...",this);
    resetAction->setShortcut(tr("Ctrl+e"));
    optionsBar->addAction(resetAction);
    connect(resetAction, SIGNAL(triggered()),this,SLOT(reset()));

    resetAllAction=new QAction("&Reset all channels",this);
    resetAllAction->setShortcut(tr("Ctrl+Shift+e"));
    optionsBar->addAction(resetAllAction);
    connect(resetAllAction, SIGNAL(triggered()),this,SLOT(resetAll()));

    hideZeroBarsAction=new QAction("&Hide empty bars",this);
    hideZeroBarsAction->setShortcut(tr("Ctrl+h"));
    optionsBar->addAction(hideZeroBarsAction);
    connect(hideZeroBarsAction, SIGNAL(triggered()),this,SLOT(hideZeroBars()));

    updateAction=new QAction("&Update screen",this);
    updateAction->setShortcut(tr("Ctrl+u"));
    optionsBar->addAction(updateAction);
    connect(updateAction, SIGNAL(triggered()),this,SLOT(updateScreen()));


    lbl.setText("\n"
                "\n"
                "\n"
                "Viewer\n"
                "See some shortcuts:\n"
                "\n"
                "Ctrl+A - add channel...   \n"
                "Ctrl+R - remove channel...\n"
                "Ctrl+F - plot from file   \n"
                "Ctrl+E - reset channel... \n"
                "Ctrl+H - on/off hiding empty bars\n"
                "Ctrl+U - update screen    \n"
                "\n"
                "For more details see 'Options'");

    lbl.setAlignment(Qt::AlignTop);
    QFont f("Times");
    lbl.setFont(f);
    grid->addWidget(&lbl);

//--------------------------------------------------------------------------
}

void HandlerWindow::LoadSettings(QString file_ini)
{
    QSettings sett(file_ini, QSettings::IniFormat);

    sett.beginGroup("HANDLER WINDOW");
    doHide = sett.value("DO_HIDE_ZEROS",1).toBool();
    sett.endGroup();

//    qDebug() << chargeHist->xAxis->range().lower;
//    qDebug() << chargeHist->xAxis->range().upper;

//    chargeTimeHist->xAxis->setRange(-3,3);
//    chargeTimeHist->yAxis->setRange(-3,3);

//    ui->rb_1->setChecked(1);
//    qDebug() << ui->rb_01->isChecked();


}


void HandlerWindow::PlotHistograms()
{
    for (quint16 i=0;i<12;i++) {
        if(channel[i]!=nullptr){
            channel[i]->PlotHistograms();
            //            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
            if(doHide){ channel[i]->HideZeroBars();}
        }
    }
}


/*
void HandlerWindow::ReadBinaryFile()
{
    for(quint16 i=0;i<12;i++) {
        if(channel[i]!=nullptr){
            channel[i]->Clear();
        }
    }

    DataConversion convertor;
    EventHeader* pHeader;
    EventData* pData;

    DataBlockFT0 *dataBlock = new DataBlockFT0;
    DataBlockFileReaderFT0 *rawReader = new DataBlockFileReaderFT0(qPrintable(filePath),"",dataBlock);


    for(quint16 i=0;i<12;i++) {
        if(channel[i]!=nullptr) {
            channel[i]->Clear();
        }
    }
    rawReader->InitFile();

    while(rawReader->ReadNextEvent()) {

        pData  = dataBlock->GetEventDataPtr();
        pHeader = dataBlock->GetEventHeaderPtr();

        for(int iCh=0;iCh<2*(pHeader->Nwords);iCh++)
        {
            for (quint16 i=0;i<12;i++) {
                if(channel[i]!=nullptr){
                    if(pData[iCh].channelID == i) {
                        convertor.dataBlocks.charge=pData[iCh].charge;
                        convertor.dataBlocks.time=pData[iCh].time;
                        channel[i]->AddEvent(convertor.dataReal.charge,convertor.dataReal.time);
                    }
                }
            }
        }
    }

    delete rawReader;
    delete dataBlock;
    PlotHistograms();
}
*/


void HandlerWindow::ReadTxtFile()
{

    for(quint16 i=0;i<12;i++) {
        if(channel[i]!=nullptr){
            channel[i]->Clear();
        }
    }
    QFile file(filePath);
    QString gbtword;
    quint16 nWords;
    bool ok;

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream readStream(&file);

        while(!file.atEnd()) {
//        for (quint8 j=0;j<20;j++){
            gbtword = readStream.readLine();
//            qDebug() << gbtword;

            if (gbtword.left(1) == "E")    {continue;} //trigger
            if (gbtword.left(4) == "FFFF") {continue;} //trailer
            if (gbtword.left(1) == "0")    {continue;} //leftover
            if (gbtword.left(3) == "DAF")  {continue;}

            if(gbtword.left(1)=="F"){
                nWords = gbtword.mid(1,1).toUShort(&ok,16);
                for(quint16 i=0;i<nWords;i++) {
                    gbtword = readStream.readLine();
                    addEvent(gbtword);

                } // end of for
            }

        } // end of while
    }
    else {
        qDebug() << "File is not opened";
    }
    file.close();

    PlotHistograms();

}



void HandlerWindow::addEvent(QString gbtword,bool doPrint)
{
    QString halfgbt[2];
    quint16 channelID;
    DataConversion convertor;
    quint8 tADCNum;
    bool ok;

    if(doPrint) qDebug() << "\t" << gbtword;

    // divide GBT word to 2 channels
    halfgbt[0]=gbtword.left(10);
    halfgbt[1]=gbtword.right(10);

    for(quint8 j=0;j<2;j++){
        // convert hex to binary QString
        halfgbt[j]=HexStrtoBinStr(halfgbt[j]);

        if(doPrint) qDebug()<< "\t\t" << halfgbt[j];

        if(doCheckFlags){
            if(halfgbt[j].mid(13,1).toUShort()){ continue;}          // double event
            if(halfgbt[j].mid(12,1).toUShort()){ continue;}          // time not valid
            if(!halfgbt[j].mid(11,1).toUShort()){ continue;}         // ADC in gate
            if(halfgbt[j].mid(10,1).toUShort()){ continue;}          // time information too late
            if(halfgbt[j].mid( 9,1).toUShort()){ continue;}          // amplitude too high
            ////////if(halfgbt[j].mid( 8,1).toUShort()){ continue;}          // event included in TVDC trigger
            if(halfgbt[j].mid( 7,1).toUShort()){ continue;}          // time information lost
        }

        // get time, charge and channelID for first channel in gbt word
        convertor.dataBlocks.time = halfgbt[j].right(12).toULongLong(&ok,2);
        convertor.dataBlocks.charge = halfgbt[j].mid(15,13).toULongLong(&ok,2);
        channelID = halfgbt[j].left(4).toUShort(&ok,2);
        tADCNum = halfgbt[j].mid(14,1).toUShort();

        if(doPrint) qDebug() << "\tChannel ID:"<< channelID
                             << "\tADC ID:"<< tADCNum
                             << "\tTime:"<< convertor.dataReal.time
                             << "\tCharge:"<< convertor.dataReal.charge;

        sendEventToChannel(channelID,tADCNum,convertor.dataReal.charge,convertor.dataReal.time);


    } // end of for
    if(doPrint) qDebug() << endl;
}

void HandlerWindow::addEvent(quint8 channelID, quint32 bitset, bool doPrintDecoded)
{
    // in QBitArray order is from lower to higher bits
    QBitArray ar=QBitArray::fromBits(reinterpret_cast<const char*>(&bitset),32);

    if(doCheckFlags){
        if(ar[26]){ return;}          // double event
        if(ar[27]){ return;}          // time info not valid
        if(!ar[28]){ return;}         // ADC in gate
        if(ar[29]){ return;}          // time information too late
        if(ar[30]){ return;}          // amplitude too high
        ////////if(){ return;}          // event included in TVDC trigger
        /// time info lost
    }
    DataConversion convertor;
    convertor.dataBlocks.time = 0;
    for(quint8 j=0;j<12;j++){ convertor.dataBlocks.time += ar[j]*pow(2,j); }

    convertor.dataBlocks.charge = 0;
    for(quint8 j=0;j<13;j++){ convertor.dataBlocks.charge += ar[12+j]*pow(2,j); }

    if(doPrintDecoded){
        qDebug() << "\t" <<ar << "[inversed]";
        qDebug() << "\tChannel ID:" << channelID
                 << "\tADC ID:" << (quint8)ar[25]
                 << "\tTime:" << convertor.dataReal.time
                 << "\tCharge:"<< convertor.dataReal.charge;
        qDebug() << endl;
    }
    sendEventToChannel(channelID,ar[25],convertor.dataReal.charge,convertor.dataReal.time);

}

void HandlerWindow::addEvent(quint8 channelID, quint8 flags, qint16 charge, qint16 time)
{
    QBitArray ar=QBitArray::fromBits(reinterpret_cast<const char*>(&flags),8);

    if(doCheckFlags){
        ////  ADC ID bit here
        if(ar[1]){ return;}          // double event
        if(ar[2]){ return;}          // time info not valid
        if(!ar[3]){ return;}         // ADC in gate
        if(ar[4]){ return;}          // time information too late
        if(ar[5]){ return;}          // amplitude too high
        ////////if(ar[6]){ return;}          // event included in TVDC trigger
        if(ar[7]){ return;}           // time info lost
    }

//    qDebug() << "\t" <<ar << "[inversed]";
//    qDebug() << "\tChannel ID:" << channelID
//             << "\tADC ID:" << (quint8)ar[0]
//             << "\tTime:" << time
//             << "\tCharge:"<< charge;
//    qDebug() << endl;


    sendEventToChannel(channelID,ar[0],charge,time);
}







void HandlerWindow::sendEventToChannel(quint8 chID,bool adc_id,qint16 charge,qint16 time)
{
    if((chID<=12)&&(chID>=1)){
        if(channel[chID-1]!=nullptr){
            channel[chID-1]->AddEvent(adc_id,charge,time);
        }
    }
}

void HandlerWindow::updateScreen()
{
    this->statusBar()->showMessage("Updating screen...",500);
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);


    for(quint16 i=0;i<12;i++) {
        if(channel[i]!=nullptr){
            channel[i]->UpdateScreen();
        }
    }
}

void HandlerWindow::startNewWindow(QVector<quint8>& channelsToAdd)
{
    this->show();
    this->activateWindow();
    filePath=prevWin->getFilePath();
    doHide=prevWin->isEmptyBarsHidden();

    quint8 j=0;
    do{
        if(addSingleChannel(channelsToAdd.at(j))) j++;
        else{
            QVector<quint8> vec1=channelsToAdd.mid(j);
            emit showNewWindow(vec1);
            return;
        }
    }while(j<channelsToAdd.size());


}

void HandlerWindow::doAddChannelRange()
{
    bool ok;
    QString chIDs = QInputDialog::getText(this,
                                 QString::fromUtf8("Input"),
                                 QString::fromUtf8("Input range of channels \n(f.e. \"2,3,10\" or \"1-12\" ):"),
                                 QLineEdit::Normal,
                                 "", &ok);
    if (!ok || chIDs.isEmpty()){ return; }

    addChannelRange(chIDs);

}

void HandlerWindow::closeEvent(QCloseEvent *event)
{
    removeChannelRange("1-12");
    event->accept();
}

void HandlerWindow::addChannelRange(QString chIDs)
{
    QVector<quint8> vec;
    vec.reserve(12);
    DecodeChsRegExp(chIDs,vec);

    quint8 j=0;
    do{
        if(addSingleChannel(vec.at(j))) j++;
        else{
            QVector<quint8> vec1=vec.mid(j);
            emit showNewWindow(vec1);
            return;
        }
    }while(j<vec.size());
}

bool HandlerWindow::addSingleChannel(quint8 chID)
{
    if(addedChannelsID.size() == 4){
        this->statusBar()->clearMessage();
        return 0;
    }

    if(channel[chID-1]==nullptr) {
        channel[chID-1] = new ChannelHistWidget(this,QString::number(chID));
        lbl.hide();
//        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        grid->addWidget(channel[chID-1]);
//        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        this->resize(Width+Width*addedChannelsID.size(),Height);
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

        addedChannelsID.push(chID);

        if(!filePath.isEmpty()){ readFile(); }

    }

    if(addedChannelsID.size() == 1){
        ui->b_2->setVisible(true);
        ui->b_3->setVisible(true);
        ui->b_4->setVisible(true);
//        ui->b_5->setVisible(true);
        ui->b_6->setVisible(true);
    }

    return 1;
}

bool HandlerWindow::openSourceFile()
{
    this->statusBar()->showMessage("Opening file...");

    QString enteredFilePath = QFileDialog::getOpenFileName(this,
                                                    QString::fromUtf8("Open file"),
                                                    QDir::currentPath(),
                                                    "GBT files (*.GBT *.gbt);;/*Binary files (*.bin);;*/All files (*.*)",
                                                    &fileType);
    filePath = enteredFilePath;

    this->statusBar()->clearMessage();
    label.setText("Reading File...");
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

//    if(fileType == "Binary files (*.bin)"){ ReadBinaryFile();}
    if(fileType == "GBT files (*.GBT *.gbt)"){ ReadTxtFile();}
    label.clear();

    if(filePath.isEmpty()) { return 0; }
    else { return 1; }
}

void HandlerWindow::readFile()
{
    qDebug() << "Read file" << filePath;

    label.clear();
    label.setText("Reading File...");
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    if(filePath.isEmpty()){ openSourceFile(); label.clear(); return; }
//    if(fileType == "Binary files (*.bin)"){ ReadBinaryFile();}
    if(fileType == "GBT files (*.GBT *.gbt)"){ ReadTxtFile();}
        label.clear();
}

void HandlerWindow::addChannel()
{
    this->statusBar()->showMessage("Adding channel...");
    bool bOk;
    QStringList listID = {"1","2","3","4","5","6","7","8","9","10","11","12"};
    QString chID=QInputDialog::getItem(this,tr("Input"),"Add channel:",listID,
                                       addedChannelsID.empty()?0:addedChannelsID.back(),0,&bOk);
    if(!bOk){
//        qDebug() << "Cancel";
        return;
    }

    quint8 choosed_cannel = chID.toUShort();

    this->statusBar()->clearMessage();

    if( addSingleChannel(choosed_cannel) ){}
    else{
        QVector<quint8> v={choosed_cannel};
        emit showNewWindow(v);
    }
}

void HandlerWindow::removeChannel()
{
    bool bOk;
    QStringList listID = {"1","2","3","4","5","6","7","8","9","10","11","12"};
    QString chID=QInputDialog::getItem(this,"Delete","Remove channel:",listID,addedChannelsID.back()-1,0,&bOk);

    if(!bOk){
//        qDebug() << "Cancel";
        return;
    }
    removeSingleChannel(chID.toUShort());
}

void HandlerWindow::removeSingleChannel(quint8 chID)
{
    if(channel[chID-1] != nullptr){
        grid->removeWidget(channel[chID-1]);
        delete channel[chID-1];
        channel[chID-1] = nullptr;
        this->resize(this->width() - Width,Height);
        addedChannelsID.pop();
    }
    if(addedChannelsID.size()==0){
        lbl.show();
        ui->b_2->setVisible(false);
        ui->b_3->setVisible(false);
        ui->b_4->setVisible(false);
//        ui->b_5->setVisible(false);
        ui->b_6->setVisible(false);
    }
}

void HandlerWindow::removeChannelRange(QString chIDs)
{
    QVector<quint8> vec;
    DecodeChsRegExp(chIDs,vec);
//    qDebug() << vec;

    quint8 j=0;
    do{
        removeSingleChannel(vec.at(j));
        j++;
    }while(j<vec.size() );
}

void HandlerWindow::removeAllChannel()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromUtf8("Message"),
                      QString::fromUtf8("Delete all channels?"),
                      QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
//        for(quint16 i=1;i<=12;i++){
//            removeSingleChannel(i);
//        }
        removeChannelRange("1-12");
    }
}

void HandlerWindow::reset()
{
    this->statusBar()->showMessage("Channel resetting...");

    bool bOk;
    QStringList listID = {"1","2","3","4","5","6","7","8","9","10","11","12"};
    QString chID=QInputDialog::getItem(this,"Reset","Reset channel:",listID,0,0,&bOk);

    if(!bOk){
//        qDebug() << "Cancel";
        return;
    }
    resetSingleChannel(chID.toUShort());
}

void HandlerWindow::resetSingleChannel(quint8 chID)
{
    this->statusBar()->showMessage("Clearing data...");

    if(channel[chID-1]!=nullptr){
        channel[chID-1]->Clear();
        channel[chID-1]->PlotHistograms();
    }

    this->statusBar()->clearMessage();
}

void HandlerWindow::resetChannelRange(QString chIDs)
{
    QVector<quint8> vec;
    DecodeChsRegExp(chIDs,vec);
//    qDebug() << vec;

    quint8 j=0;
    do{
        resetSingleChannel(vec.at(j));
        j++;
    }while(j<vec.size() );
}

void HandlerWindow::resetAll()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromUtf8("Message"),
                      QString::fromUtf8("Reset all channels?"),
                      QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        resetChannelRange("1-12");
    }
}

void HandlerWindow::hideZeroBars()
{
    if(doHide) doHide=0;
    else doHide=1;

    for(quint16 i=0;i<12;i++) {
        if(channel[i]!=nullptr){
            if(doHide) {
                this->statusBar()->showMessage("Hiding emty bars...",500);
                channel[i]->HideZeroBars();
            }
            else {
                this->statusBar()->showMessage("Unhiding emty bars...",500);
                channel[i]->ShowFullRange();
            }
        }
    }
}

void HandlerWindow::chooseADC(quint8 chID,quint8 adcID)
{
    if(chID>=1 && chID<=12){
        if(channel[chID-1]!=nullptr){
            channel[chID-1]->ADC_ID=adcID;
        }
    }
}


HandlerWindow::~HandlerWindow()
{
    delete ui;
}

