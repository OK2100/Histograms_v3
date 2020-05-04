#include "handlerwindow.h"
#include "ui_handlerwindow.h"



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
    if(prevWindow!=nullptr) {
    connect(prevWindow,SIGNAL(showNewWindow(quint8)),this,SLOT(startNewWindow(quint8)));
    }

    connect(ui->b_1,&QPushButton::clicked,this,&HandlerWindow::addChannel);
    connect(ui->b_2,&QPushButton::clicked,this,&HandlerWindow::removeChannel);
    connect(ui->b_3,&QPushButton::clicked,this,&HandlerWindow::reset);
    connect(ui->b_4,&QPushButton::clicked,this,&HandlerWindow::hideZeroBars);
    connect(ui->b_6,&QPushButton::clicked,this,&HandlerWindow::readFile);




    SetUp();
}

//      Functions

void HandlerWindow::SetUp()
{

    for(quint16 i=0;i<12;i++) {
        channel[i]=nullptr;
    }

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


//--------------------------- Appearance ---------------------------------

    fileBar=menuBar()->addMenu("&File");                    //  #File field

    openSourceFileAction=new QAction("&Open source file...",this);
    openSourceFileAction->setShortcut(tr("Ctrl+o"));
    fileBar->addAction(openSourceFileAction);
    connect(openSourceFileAction, SIGNAL(triggered()),this,SLOT(openSourceFile()));

    dataBar=menuBar()->addMenu("&Data");

    showStatWindowAction=new QAction("&Show statistics (to console)",this);
    showStatWindowAction->setShortcut(tr("Ctrl+t"));
    dataBar->addAction(showStatWindowAction);
    connect(showStatWindowAction, SIGNAL(triggered()),this,SLOT(showStatWindow()));

    optionsBar=menuBar()->addMenu("&Options");              //  #Options field

    addChannelAction=new QAction("&Add channel...",this);
    addChannelAction->setShortcut(tr("Ctrl+a"));
    optionsBar->addAction(addChannelAction);
    connect(addChannelAction, SIGNAL(triggered()),this,SLOT(addChannel()));

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

    chooseADCAction=new QAction("&Choose ADC number",this);
    chooseADCAction->setShortcut(tr("Ctrl+d"));
    optionsBar->addAction(chooseADCAction);
    connect(chooseADCAction, SIGNAL(triggered()),this,SLOT(chooseADC()));


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

void HandlerWindow::PlotHistograms()
{
    for (quint16 i=0;i<12;i++) {
        if(channel[i]!=nullptr){
            channel[i]->PlotHistograms();
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
                    addEvent(gbtword,1);

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
    for(quint16 i=0;i<12;i++) {
        if(channel[i]!=nullptr){
            channel[i]->Update();
        }
    }
}

void HandlerWindow::startNewWindow(quint8 firstChannelID)
{
    this->show();
    nextChannelID = firstChannelID;
    addChannel();
}

bool HandlerWindow::openSourceFile()
{
    QString enteredFilePath = QFileDialog::getOpenFileName(this,
                                                    QString::fromUtf8("Open file"),
                                                    QDir::currentPath(),
                                                    "GBT files (*.GBT *.gbt);;/*Binary files (*.bin);;*/All files (*.*)",
                                                    &fileType);
    filePath = enteredFilePath;
//    filePathSave = enteredFilePath;
//    filePath = filePathSave.toUtf8().data();
//    if(filePathSave.isEmpty()) { return 0; }
    if(filePath.isEmpty()) { return 0; }
    else { return 1; }
}

void HandlerWindow::readFile()
{
//    if(filePathSave.isEmpty()) {
    if(filePath.isEmpty()) {
        if(!openSourceFile()) return;       // File is not choosen
    }

//    if(fileType == "Binary files (*.bin)"){ ReadBinaryFile();}
    if(fileType == "GBT files (*.GBT *.gbt)"){ ReadTxtFile();}
}

void HandlerWindow::addChannel()
{
    if(nAddedChannels == 4){
//        qDebug() <<"start new window" ;
        emit showNewWindow(nextChannelID);
        return;
    }


    bool bOk;
    QStringList listID = {"1","2","3","4","5","6","7","8","9","10","11","12"};
    QString chID=QInputDialog::getItem(this,tr("Input"),"Add channel:",listID,nextChannelID-1,0,&bOk);
    if(!bOk){
//        qDebug() << "Cancel";
        return;
    }

    if(channel[chID.toInt()-1]==nullptr) {
        channel[chID.toInt()-1] = new ChannelHistWidget(this,chID);
        if(!filePath.isEmpty()){ readFile(); }
        lbl.hide();
        grid->addWidget(channel[chID.toInt()-1]);
        this->resize(Width+Width*nAddedChannels,Height);
        nAddedChannels++;
        nextChannelID++;

//        connect(channel[chID.toInt()-1],&ChannelHistWidget::channelAdded,this,&HandlerWindow::readFile);
    }


    if(nAddedChannels == 1){
        ui->b_2->setVisible(true);
        ui->b_3->setVisible(true);
        ui->b_4->setVisible(true);
//        ui->b_5->setVisible(true);
        ui->b_6->setVisible(true);
    }
}

void HandlerWindow::removeChannel()
{
    bool bOk;
    QStringList listID = {"1","2","3","4","5","6","7","8","9","10","11","12"};
    QString chID=QInputDialog::getItem(this,"Delete","Remove channel:",listID,nextChannelID-2,0,&bOk);

    if(!bOk){
//        qDebug() << "Cancel";
        return;
    }

    if(channel[chID.toInt()-1] != nullptr){
        grid->removeWidget(channel[chID.toInt()-1]);
        delete channel[chID.toInt()-1];
        channel[chID.toInt()-1] = nullptr;
        this->resize(this->width() - Width,Height);
        nAddedChannels--;
        nextChannelID--;
    }
    if(nAddedChannels==0){
        lbl.show();
        ui->b_2->setVisible(false);
        ui->b_3->setVisible(false);
        ui->b_4->setVisible(false);
//        ui->b_5->setVisible(false);
        ui->b_6->setVisible(false);


    }
}

void HandlerWindow::removeAllChannel()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromUtf8("Message"),
                      QString::fromUtf8("Delete all channels?"),
                      QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        for(quint16 i=0;i<12;i++){
            if(channel[i]!=nullptr) {
                delete channel[i];
                channel[i] = nullptr;
                nextChannelID--;
            }
        }

        nAddedChannels=0;
        this->resize(0,0);
        lbl.show();
        ui->b_2->setVisible(false);
        ui->b_3->setVisible(false);
        ui->b_4->setVisible(false);
//        ui->b_5->setVisible(false);
        ui->b_6->setVisible(false);

    }
}

void HandlerWindow::reset()
{
    bool bOk;
    QStringList listID = {"1","2","3","4","5","6","7","8","9","10","11","12"};
    QString chID=QInputDialog::getItem(this,"Reset","Reset channel:",listID,0,0,&bOk);

    if(!bOk){
//        qDebug() << "Cancel";
        return;
    }

    if(channel[chID.toInt()-1]!=nullptr){
        channel[chID.toInt()-1]->Clear();
        channel[chID.toInt()-1]->PlotHistograms();
    }
}

void HandlerWindow::resetAll()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromUtf8("Message"),
                      QString::fromUtf8("Reset all channels?"),
                      QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        for(quint16 i=0;i<12;i++) {
            if(channel[i]!=nullptr){
                channel[i]->Clear();
            }
        }
        PlotHistograms();
    }
}

void HandlerWindow::hideZeroBars()
{
    if(doHide) doHide=0;
    else doHide=1;

    for(quint16 i=0;i<12;i++) {
        if(channel[i]!=nullptr){
            if(doHide) {
                channel[i]->HideZeroBars();
            }
            else {
                channel[i]->ShowFullRange();
            }
        }
    }
}

void HandlerWindow::chooseADC()
{

    bool bOk;
    QStringList listID = {"0","1","2"};
    QString adcNum=QInputDialog::getItem(this,"ADC","Choose ADC number:",listID,0,0,&bOk);

    if(!bOk){
//        qDebug() << "Cancel";
        return;
    }

    quint8 adc = adcNum.toUShort();
//    qDebug() << adc;
    ADCNumber = adc;

}

void HandlerWindow::showStatWindow()
{
    QString text;
    QMessageBox msgBox;
    msgBox.setWindowTitle("Stat");
    msgBox.show();
    for(quint16 i=0;i<12;i++) {
        if(channel[i]!=nullptr){
            text.append(channel[i]->GetStatInfo());
//            qDebug()<<"";
//            channel[i]->PrintInfo(1);
        }
    }
    msgBox.setText(text);
    msgBox.exec();

}


HandlerWindow::~HandlerWindow()
{
    delete ui;
}

