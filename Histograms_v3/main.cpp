#include "handlerwindow.h"

#include "histdata.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HandlerWindow w1;
//    HandlerWindow w2(&w1);
//    HandlerWindow w3(&w2);
    w1.show();


//  ##  TEST of HistData class  ##
//  ##  uncomment "CONFIG += console" in .pro file  ##

//    HistData hist(-2,2,5);

//    hist.printInfo(1,1);

//    hist.addEvent(-3);
//    hist.addEvent(-2);
//    hist.addEvent(-1);
//    hist.addEvent(0);
//    hist.addEvent(1);
//    hist.addEvent(2);
//    hist.addEvent(3);

//    hist.printInfo(1,1);


    HistData hist2(-100,4095,1);
    hist2.printInfo();
    hist2.setbinWidth(2);   hist2.printInfo();
    hist2.setbinWidth(1);   hist2.printInfo();




    return a.exec();
}
