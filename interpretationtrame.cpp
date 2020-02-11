#include "interpretationtrame.h"

interpretationtrame::interpretationtrame()
{

    connect(&CS, SIGNAL(messageReceived(QString,QString)), this, SLOT(showMessage(QString,QString)));
}

void interpretationtrame::showMessage(const QString &sender, const QString &message)
{
    char messageR[33];
    int i=0;
    if(sender == Ble.m_service.device().name()){
        messageR[i] = message.data()->toLatin1();
        if(messageR[0] == 'F' && messageR[1] == 'F' && messageR[2] == 'F' && messageR[3] == 'F'){
            switch (messageR[5]) {
            case 0:
                qWarning("Wind");
                wind();
                break;
            case 1:
                qWarning("Rain");
                rain();
                break;
            case 2:
                qWarning("thermo hygro");
                th();
                break;
            case 3:
                qWarning("mushroom");
                mushroom();
                break;
            case 4:
                qWarning("thermo only");
                t();
                break;
            case 5:
                qWarning("thermo hygro baro");
                bth();
                break;
            case 'E':
                qWarning("minute");
                minute();
                break;
            case 'F':
                qWarning("clock");
                clock();
                break;
            case 6:
                qWarning("thermo hygro baro");
                extbth();
                break;
            }
        }
    }
}

void interpretationtrame::wind()
{

}

void interpretationtrame::rain()
{

}

void interpretationtrame::th()
{

}

void interpretationtrame::mushroom()
{

}

void interpretationtrame::t()
{

}

void interpretationtrame::bth()
{

}

void interpretationtrame::extbth()
{

}

void interpretationtrame::minute()
{

}

void interpretationtrame::clock()
{

}
