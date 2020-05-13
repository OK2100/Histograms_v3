#include "handlerwindow.h"
#include "histdata.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HandlerWindow w1;
    HandlerWindow w2;
    HandlerWindow w3;
    w1.show();
    w2.show();
    w3.show();

//    w1.addEvent("A0923BA05B90923C103E",1);
//    w1.addEvent(9,quint32(0x923C103E),1);       // part of right half 90923C103E
//    w1.addEvent(9,quint8(0x49),961,62);    // flags are 01001001 -> 0x49

//  ##  TEST of HistData class  ##
//  ##  uncomment "CONFIG += console" in .pro file  ##

//    Hist2Data h2(-1,1,3,-2,2,5);
//    h2.printInfo(1,1);

//    h2.addEvent(0,-2);
//    h2.addEvent(0,-1);
//    h2.addEvent(0,0);
//    h2.addEvent(0,1);
//    h2.addEvent(0,2);

//    h2.addEvent(-1,-2);
//    h2.addEvent(-1,-1);
//    h2.addEvent(-1,0);
//    h2.addEvent(-1,1);
//    h2.addEvent(-1,2);

//    h2.addEvent(1,-2);
//    h2.addEvent(1,-1);
//    h2.addEvent(1,0);
//    h2.addEvent(1,1);
//    h2.addEvent(1,2);

//    h2.printInfo(1,1);

//    HistData h1(-2,2,5);
//    h1.addEvent(-2);
//    h1.addEvent(-1);
//    h1.addEvent(0);
//    h1.addEvent(1);
//    h1.addEvent(2);
//    h1.printInfo(1,1);

//    hist.addEvent(-3);
//    hist.addEvent(-2);
//    hist.addEvent(-1);
//    hist.addEvent(0);
//    hist.addEvent(1);
//    hist.addEvent(2);
//    hist.addEvent(3);

//    hist.printInfo(1,1);

//    HistData hist2(-100,4095,1);
//    hist2.printInfo();
//    hist2.setbinWidth(2);   hist2.printInfo();
//    hist2.setbinWidth(1);   hist2.printInfo();

    return a.exec();
}
