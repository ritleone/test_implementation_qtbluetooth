#include "dialog.h"
#include "ui_dialog.h"
#include "time.h"
#include "bluetoothe.h"
#include "stdio.h"
#include <unistd.h>

#include <QTextStream>
#include <QFile>
#include <QDataStream>


#include <qbluetoothtransferrequest.h>
#include <qbluetoothtransferreply.h>
#include <qbluetoothuuid.h>
#include <qbluetoothserver.h>
#include <qbluetoothservicediscoveryagent.h>
#include <qbluetoothdeviceinfo.h>
#include <qbluetoothlocaldevice.h>

static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8"); //Mettre le uuid dans un fichier

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    qWarning("Dialog construit");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_BluetoothButton_clicked()
{
    this->bluetoothe.show();
    this->bluetoothe.startDiscovery(QBluetoothUuid(serviceUuid));
}

void Dialog::showMessage(const QString &sender, const QString &message)
{
    ui->chat->insertPlainText(QString::fromLatin1("%1: %2\n").arg(sender, message));
}

void Dialog::on_ScanButton_clicked()
{
    qWarning("test");
        ClientSocket *CS = new ClientSocket(this);

        if(this->bluetoothe.ScanEnable == 0 || ui->ScanButton->text() == "Arreter le scan"){
            qWarning("Choisi un appareil");
            if(CS->CSCreate == 1){
                CS->stopClient();
            }
            ui->ScanButton->setText("Lancer le scan");
        }
            else {
            ui->ScanButton->setText("Arreter le scan");

            qWarning("Creation du socket client");
            CS->startClient(this->bluetoothe.m_service);
        }



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

