#ifndef SETUPCHANNELWINDOW_H
#define SETUPCHANNELWINDOW_H

#include <QDialog>
#include <QString>
#include <QDebug>

namespace Ui {
class SetupChannelWindow;
}

class SetupChannelWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SetupChannelWindow(QWidget *parent = nullptr);
    ~SetupChannelWindow();

    void set_chID(QString _chID);
    void set_binWidth_charge(quint16);
    void set_binWidth_time(quint16);
    void set_nBins_charge(QString);
    void set_nBins_time(QString);
    void set_charge_range(qint16 left,qint16 right);
    void set_time_range(qint16 left,qint16 right);
    void set_fix_range_chaecked(int state);

private:
    Ui::SetupChannelWindow *ui;

signals:
    void binWidth_charge_changed(quint16 );
    void binWidth_time_changed(quint16);
    void check_status(int);
    void end_of_apply();

private:

    QString leftLimit_charge;
    QString rightLimit_charge;
    QString nBins_charge;
    quint16 binWidth_charge;

    QString leftLimit_time;
    QString rightLimit_time;
    QString nBins_time;
    quint16 binWidth_time;

private slots:
    void apply_clicked();
};

#endif // SETUPCHANNELWINDOW_H
