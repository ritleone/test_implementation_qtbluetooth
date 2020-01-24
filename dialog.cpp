#include "dialog.h"
#include "ui_dialog.h"
#include "time.h"
#include "bluetoothe.h"


#include <qbluetoothtransferrequest.h>
#include <qbluetoothtransferreply.h>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_ScanButton_clicked()
{
    QString tab1 = this->bluetoothe.getTab().toUtf8().data();
    qWarning("%s",tab1.toLatin1().data());

    /*
    //Debut Pression
    double Pression = 1007;
    ui->lcdPression->display(Pression);
    //Fin Pression

    //Debut Heure
    QTime t = QTime::currentTime();
    ui->timeEdit->setTime(t);
    //Fin Heure

    //Debut TempInt
    double TempInt = 24;
    ui->lcdTempInt->display(TempInt);
    //Fin TempInt
    //Debut TempExt
    double TempExt = 11;
    ui->lcdTempExt->display(TempExt);
    //Fin TempExt

    //Debut HRI
    int HRI = 50;
    ui->progressBarHRI->setValue(HRI);
    //Fin HRI
    //Debut HRE
    int HRE = 83;
    ui->progressBarHRE->setValue(HRE);
    //Fin HRE

    //Debut Pluie
    double Pluie = 0;
    ui->lcdPluie->display(Pluie);
    //Fin Pluie

    //Debut Vent
    double Vent = 12.6;
    ui->lcdVent->display(Vent);
    //Fin Vent

    //Debut Boussole
    QString n;

    position = 300;

    if(position == 0 || position == 360){
        n = "Nord";
        ui->dial->setValue(position);
    }

    if(position == 90){
        n = "Est";
        ui->dial->setValue(position);
    }

    if(position == 270){
        n = "Ouest";
        ui->dial->setValue(position);
    }

    if(position == 180){
        n = "Sud";
        ui->dial->setValue(position);
    }


    if(position < 90 && position > 0){
        n = "Nord-Est";
        ui->dial->setValue(position);
    }

    if(position < 180 && position > 90){
        n = "Sud-Est";
        ui->dial->setValue(position);
    }

    if(position < 360 && position > 270){
        n = "Nord-Ouest";
        ui->dial->setValue(position);
    }

    if(position < 270 && position > 180){
        n = "Sud-Ouest";
        ui->dial->setValue(position);
    }

    QString a = QString::number(position);

    ui->textEdit->setText(n + '\t' + a + "°");
    //Fin Boussole
    */
}


void Dialog::on_BluetoothButton_clicked()
{
    this->bluetoothe.show();
}
