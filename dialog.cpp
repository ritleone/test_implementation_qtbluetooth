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

void Dialog::on_ScanButton_clicked()
{
    /*
    QString tab1 = this->bluetoothe.getTab().toUtf8().data();
    qWarning("%s",tab1.toLatin1().data());


    QBluetoothTransferManager mgr;
    QBluetoothTransferRequest req(this->bluetoothe.m_service.device().address());

    m_file = new QFile("/home/jupiter/document/Cours3_Qt_BdD.pdf");

    QBluetoothTransferReply *reply = mgr.put(req, m_file);
    reply->setParent(this);
    if (reply->error()){
        qDebug() << "Failed to send file";
        reply->deleteLater();
        return;
    }
*/
    connect(bluetoothe, SIGNAL(addressReceived(QString)), this, SLOT(scanButtonEnable(QString)));

        ClientSocket *CS = new ClientSocket(this);

        CS->startClient(bluetoothe->m_service);

        connect(CS, SIGNAL(messageReceived(QString,QString)), this, SLOT(showMessage(QString,QString)));




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
    bluetoothe->show();
    bluetoothe->startDiscovery(QBluetoothUuid(serviceUuid));
}

void Dialog::showMessage(const QString &sender, const QString &message)
{
    ui->chat->insertPlainText(QString::fromLatin1("%1: %2\n").arg(sender, message));
}

int Dialog::scanButtonEnable(QString &tab1)
{
    qWarning("%s",tab1.toLatin1().data());
    if(!tab1.isEmpty()){
        qWarning("Je suis pas connécté a un appareil");
        return 1;
    }
    return 0;
}
