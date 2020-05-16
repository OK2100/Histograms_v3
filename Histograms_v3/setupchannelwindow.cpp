#include "setupchannelwindow.h"
#include "ui_setupchannelwindow.h"

SetupChannelWindow::SetupChannelWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupChannelWindow)
{
    ui->setupUi(this);

    ui->boxCharge->insertItem(0,"1");
    ui->boxCharge->insertItem(1,"2");
    ui->boxCharge->insertItem(2,"4");
    ui->boxCharge->insertItem(3,"1049");
    ui->boxCharge->insertItem(4,"2098");
    ui->boxCharge->insertItem(5,"4196");

    ui->boxTime->insertItem(0,"1");
    ui->boxTime->insertItem(1,"2");
    ui->boxTime->insertItem(2,"4");
    ui->boxTime->insertItem(3,"8");
    ui->boxTime->insertItem(4,"16");
    ui->boxTime->insertItem(5,"32");
    ui->boxTime->insertItem(6,"64");
    ui->boxTime->insertItem(7,"128");
    ui->boxTime->insertItem(8,"256");
    ui->boxTime->insertItem(9,"512");
    ui->boxTime->insertItem(10,"1024");
    ui->boxTime->insertItem(11,"2048");
    ui->boxTime->insertItem(12,"4096");

    connect( ui->btnApply, SIGNAL( clicked() ), SLOT( apply_clicked() ) );
    connect( ui->btnCancel, SIGNAL( clicked() ), SLOT( reject() ) );
    connect( ui->btnOK, SIGNAL( clicked()), SLOT( apply_clicked() ));
    connect( ui->btnOK, SIGNAL( clicked() ), SLOT( accept() ) );
    connect(ui->checkFixRanges,&QCheckBox::stateChanged,this,&SetupChannelWindow::check_status);
}

void SetupChannelWindow::set_chID(QString _chID){
    ui->lblChID->setText("Channel: " + _chID);
}

void SetupChannelWindow::set_binWidth_charge(quint16 _binWidth)
{
    ui->boxCharge->setCurrentText(QString::number(_binWidth));
    binWidth_charge=_binWidth;
}

void SetupChannelWindow::set_binWidth_time(quint16 _binWidth)
{
    ui->boxTime->setCurrentText(QString::number(_binWidth));
    binWidth_time=_binWidth;
}

void SetupChannelWindow::set_nBins_charge(QString _nBins)
{
    ui->lblChargeNBins->setText(_nBins);
    nBins_charge=_nBins;
}

void SetupChannelWindow::set_nBins_time(QString _nBins)
{
    ui->lblTimeNBins->setText(_nBins);
    nBins_time=_nBins;
}

void SetupChannelWindow::set_charge_range(qint16 left, qint16 right)
{
    ui->minCharge->setValue(left);
    ui->maxCharge->setValue(right);
}

void SetupChannelWindow::set_fix_range_chaecked(int state)
{
    ui->checkFixRanges->setCheckState((Qt::CheckState)state);
}

void SetupChannelWindow::set_time_range(qint16 left, qint16 right){
    ui->minTime->setValue(left);
    ui->maxTime->setValue(right);
}

void SetupChannelWindow::apply_clicked()
{

    if(ui->boxCharge->currentText().toUShort()!=binWidth_charge){
        emit binWidth_charge_changed(ui->boxCharge->currentText().toUShort());
    }

    set_nBins_charge(nBins_charge);

    if(ui->boxTime->currentText().toUShort()!=binWidth_time){
        emit binWidth_time_changed(ui->boxTime->currentText().toUShort());
    }
    set_nBins_time(nBins_time);

    emit end_of_apply();
}

SetupChannelWindow::~SetupChannelWindow()
{
    delete ui;
}
