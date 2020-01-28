#include "liaisonmeteo.h"

const int LiaisonMeteo::lgTrame[16] = {
  11, 16, 9, 9, 13, 7, 14, 0, 0, 0, 0, 0, 0, 0, 5, 9	};

LiaisonMeteo::LiaisonMeteo (int port) {
  qWarning("Constructeur liaisonMeteo");
  this->udpSocket= NULL;
  this->index = 0;
  this->initReseauMeteo(port);
  flagTrace= false;
  trace.setFileName("trace_meteo.dat");
}

LiaisonMeteo::~LiaisonMeteo () {
  qWarning("Destructeur LiaisonMeteo");
  if(flagTrace == true)
    trace.close();
  if(udpSocket){
    delete this->udpSocket;
    qWarning("delete udpSocket");
  }
}

QString LiaisonMeteo::getTrame(void) {
  return this->trame;
}

int LiaisonMeteo::getType(void) {
  return this->type;
}

void LiaisonMeteo::setFlagTrace(bool flag){
  if(flag == true){
    flagTrace= true;
    if (!trace.open(QIODevice::WriteOnly | QIODevice::Append))
      return;
  }
  else{
    flagTrace= false;
    trace.close();
  }
}

unsigned char* LiaisonMeteo::getDataComplete(void){
  return this->dataComplete;
}

void LiaisonMeteo::initReseauMeteo(int port) {
  qWarning("new udpSocket");
  this->udpSocket = new QUdpSocket(this);
  if( udpSocket->bind(QHostAddress::Any, port) == true)
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(readDatagram()));
  else
    qDebug() << "Erreur bind";
}

void LiaisonMeteo::readDatagram() {
  char buf[16];
  unsigned char car;
  int nb = this->udpSocket->readDatagram(buf,sizeof(buf));
  for(int i = 0; i < nb; i ++) {
    car = (unsigned char) buf[i];
    if(flagTrace == true){
      trace.write((const char*)&car, 1);
    }
    // qWarning("LiaisonMeteo : index  %d - valeur %x", index, car);
    this->dataEnCours[index] = car;
    switch(index) {
    case 0:
    case 1:
      if(car == 0xFF) {
        this->index ++;
      } else {
        this->index = 0;
      } break;
    case 2:
      if (car > 0xF) {
        this->index = 0;
      } else {
        this->index ++;
        this->type = (int)car;
        if(type>15) // type impossible
          index=0;
      } break;
    default:
      if (this->index >= this->lgTrame[type] -1) {
        this->index = 0;
        if(testChecksum()==true) {
          for(int j=0; j<this->lgTrame[type]; j++)
            this->dataComplete[j]=this->dataEnCours[j];
          emit (dataOK());
        }
      } else {
        index++;
      }
    }
  }
}

bool LiaisonMeteo::testChecksum() {
    int checksum = 0;
    bool ret= false;
    QString val;
    trame.clear();
    for(int i = 0; i < lgTrame[type] - 1; i ++) {
        val.sprintf("%02x",(unsigned char)dataEnCours[i]);
        trame.append(val);  // qWarning("%s", trame.toLatin1().data());
        checksum += dataEnCours[i];
    }
    checksum &= 0xFF;
    val.sprintf("%02x",checksum);
    trame.append(val);
    if ((unsigned char)checksum == dataEnCours[lgTrame[type] - 1]) {
        ret = true; // qDebug() << "cheksum ok";
    }
    else
        qDebug() << "cheksum faux";
    return ret;
}
