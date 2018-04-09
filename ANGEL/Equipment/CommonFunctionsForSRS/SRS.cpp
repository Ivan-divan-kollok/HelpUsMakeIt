#include "SRS.h"

SRS::SRS(QObject *parent) : QObject(parent)
{
    this->supportedList.push_back("DS335");
    this->supportedList.push_back("DS345");

    this->supportedList.push_back("SR830");
    this->supportedList.push_back("SR844");
    this->supportedList.push_back("SR865");

    this->supportedList.push_back("PTC10");

//    this->baudrateList.push_back(   "300");
//    this->baudrateList.push_back(   "600");
//    this->baudrateList.push_back(  "1200");
//    this->baudrateList.push_back(  "2400");
//    this->baudrateList.push_back(  "4800");
    this->baudrateList.push_back(  "9600");
    this->baudrateList.push_back( "19200");
    this->baudrateList.push_back( "38400");
//    this->baudrateList.push_back( "57600");
//    this->baudrateList.push_back("115200");
}

SRS::~SRS()
{
    this->supportedList.clear();
    this->baudrateList.clear();
}

QStringList SRS::getSupportedList() const
{
    return this->supportedList;
}

QStringList SRS::getBaudrateList() const
{
    return this->baudrateList;
}

void SRS::setWriteTimeout(const int &new_writeTimeout)
{
    this->writeTimeout = new_writeTimeout;

    return;
}

int SRS::getWriteTimeout() const
{
    return this->writeTimeout;
}

void SRS::setReadTimeout(const int &new_readTimeout)
{
    this->readTimeout = new_readTimeout;

    return;
}

int SRS::getReadTimeout() const
{
    return this->readTimeout;
}

void SRS::setReadWaitTimeout(const int &new_readWaitTimeout)
{
    this->readWaitTimeout = new_readWaitTimeout;

    return;
}

int SRS::getReadWaitTimeout() const
{
    return this->readWaitTimeout;
}

void SRS::setAttemptsToConnect(const int &new_attemptsToConnect)
{
    this->attemptsToConnect = new_attemptsToConnect;

    return;
}

int SRS::getAttemptsToConnect() const
{
    return this->attemptsToConnect;
}

QSerialPort* SRS::getSerial (QSerialPort*  const this_serial) const
{
    return this_serial;
}

void SRS::setSerial(QSerialPort* *this_serial, QSerialPort* const new_serial) const
{
    *this_serial = new_serial;
    return;
}

bool SRS::openSerial(QSerialPort* const this_serial) const
{
    if (!this_serial->open(QIODevice::ReadWrite)) {
        QSerialPort::SerialPortError error = QSerialPort::NoError;
        this_serial->error(error);

        emit this->errorSignal(tr("Can't open %1, error code %2").arg(this_serial->portName()).arg(this_serial->error()));

        return false;
    } else {
        return true;
    }
}

bool SRS::setConnection(QSerialPort* *this_serial, const QString &portName, const int &baudrate, const int &stopbit, const int &parity) const
{
    if (isActive(*this_serial))
        return true;

    if (*this_serial == nullptr)
        *this_serial = new QSerialPort();

    if (stopbit == 1)
        (*this_serial)->setStopBits(QSerialPort::OneStop);
    if (stopbit == 2)
        (*this_serial)->setStopBits(QSerialPort::TwoStop);
    if (stopbit == 3)
        (*this_serial)->setStopBits(QSerialPort::OneAndHalfStop);

    if (parity == 0)
        (*this_serial)->setParity(QSerialPort::NoParity);
    if (parity == 1)
        (*this_serial)->setParity(QSerialPort::OddParity);
    if (parity == 2)
        (*this_serial)->setParity(QSerialPort::EvenParity);

    (*this_serial)->setPortName(portName);
    (*this_serial)->setBaudRate((qint32) baudrate);

    (*this_serial)->setDataBits(QSerialPort::Data8);

    if (!(*this_serial)->open(QIODevice::ReadWrite)) {
        QSerialPort::SerialPortError error = QSerialPort::NoError;
        (*this_serial)->error(error);

        emit this->errorSignal(tr("Can't open %1, error code %2").arg(portName).arg((*this_serial)->error()));

        return false;
    } else {
        return isActive(*this_serial);
    }
}

void SRS::disconnect(QSerialPort* const this_serial) const
{
    if (this_serial != nullptr)
        if (this_serial->isOpen())
            this_serial->close();
    return;
}

QString SRS::autoDetect(QSerialPort* const this_serial) const
{
    QString idn;

    if (!this_serial->isOpen()) {
        if (!this->openSerial(this_serial))
            return "";
    }

    if (!this->getIDN(this_serial, idn)) {
        return "";
    }

//    this_serial->close(); // ЗАЧЕМ? И ПОЧЕМУ ТАК РАБОТАЕТ?!?!?!
    foreach (QString equipment, this->supportedList) {
        if (idn.contains(equipment))
            return equipment;
    }

    return "";
}

QString SRS::autoDetect(const QString &portName, const int &baudrate, const int &stopbit, const int &parity) const
{
    QSerialPort *serial = new QSerialPort();

    serial->setPortName(portName);
    serial->setBaudRate(baudrate);

    if (stopbit == 1)
        serial->setStopBits(QSerialPort::OneStop);
    if (stopbit == 2)
        serial->setStopBits(QSerialPort::TwoStop);
    if (stopbit == 3)
        serial->setStopBits(QSerialPort::OneAndHalfStop);

    if (parity == 0)
        serial->setParity(QSerialPort::NoParity);
    if (parity == 1)
        serial->setParity(QSerialPort::OddParity);
    if (parity == 2)
        serial->setParity(QSerialPort::EvenParity);

    return autoDetect(serial);
}

QString SRS::autoDetect(const QString &portName) const
{
    for (int stopbit = 1; stopbit <= 3; stopbit++)
        for (int parity = 0; parity <= 2; parity++)
            for (int baud = 0; baud < this->baudrateList.length(); baud++) {
                QString response = autoDetect(portName, this->baudrateList[baud].toInt(), stopbit, parity);
                if (!response.trimmed().isEmpty())
                    return response;
                QTest::qWait(20*this->readTimeout);
            }
    return "";
}

bool SRS::send(QSerialPort* const this_serial, const QString &command, QString &response, const bool &wait_for_response) const
{
    emit this->commandSignal(command);
    response.clear();

    if (this_serial == nullptr || !this_serial->isOpen())
        return false;

    QString modyfiedCommand = command.trimmed() + "\n";

    this_serial->write(modyfiedCommand.toLocal8Bit());
    if (this_serial->waitForBytesWritten(writeTimeout)) {
        if (wait_for_response) {
            if (this_serial->waitForReadyRead(readTimeout)) {
                QByteArray responseData = this_serial->readAll();
                while (this_serial->waitForReadyRead(readWaitTimeout))
                    responseData += this_serial->readAll();
                response = QString(responseData).trimmed();

                emit this->responseSignal(response);
                return true;
            } else {
                emit this->timeoutSignal(tr("Wait write request timeout %1").arg(QTime::currentTime().toString()));
                return false;
            }
        } else {
            return true;
        }
    } else {
        emit this->timeoutSignal(tr("Wait write request timeout %1").arg(QTime::currentTime().toString()));
        return false;
    }
}

bool SRS::sendCommand(QSerialPort* const this_serial, const QString &command) const
{
    QString response;

    return send(this_serial, command, response, false);
}

bool SRS::sendQuery(QSerialPort* const this_serial, const QString &command, QString &response) const
{
    return send(this_serial, command, response, true);
}

QString SRS::ask(QSerialPort* const this_serial, const QString &command) const
{
    QString response;
    sendQuery(this_serial, command, response);

    return response;
}

bool SRS::isActive(QSerialPort* const this_serial) const
{
    QString idn;

    return getIDN(this_serial, idn);
}

bool SRS::getIDN(QSerialPort* const this_serial, QString &idn) const
{
    for (int attempt = 0; attempt < this->attemptsToConnect; attempt++) {
        sendQuery(this_serial, "*IDN?", idn);
        if (!idn.trimmed().isEmpty())
            return true;
    }
    return false;
}

void SRS::initQStringList(QStringList &target, const QStringList &source) const
{
    target.clear();
    target = source;

    return;
}

int SRS::numberFromString(const QStringList &list, const QString &string) const
{
    return list.indexOf(string);
}

QString SRS::stringFromNumber(const QStringList &list, const int &number) const
{
    if (isValidNumber(list, number))
        return list.at(number);
    return "";
}

bool SRS::isValidString(const QStringList &list, const QString &string) const
{
    return(numberFromString(list, string) != -1);
}

bool SRS::isValidNumber(const QStringList &list, const int &number) const
{
    return (number >= 0 && number < list.size());
}
