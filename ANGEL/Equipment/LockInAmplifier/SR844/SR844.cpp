#include "SR844.h"

SR844::SR844(QObject *parent) : QObject(parent)
{
    this->serial = nullptr;
    this->srs = nullptr;
    init();
}

SR844::SR844(const QString &portName, const int &baudrate, const int &stopBit, const int &parity)
{
    this->serial = nullptr;
    this->srs = nullptr;
    init();

    setConnection(portName, baudrate, stopBit, parity);
}

SR844::~SR844()
{
    if (this->serial->isOpen())
        this->serial->close();
    this->serial->~QSerialPort();
    delete this->serial;
    this->serial = nullptr;

    this->srs->~SRS();
    delete this->srs;
    this->srs = nullptr;

    baudrateList.clear();
    referenceSourceList.clear();
    referenceTriggerOutputZList.clear();
    wideReserveModeList.clear();
    signalInputZList.clear();
    sensivityList.clear();
    closeReserveModeList.clear();
    timeConstantList.clear();
    filterList.clear();
    sampleRateList.clear();
    outputNumberList.clear();
    bufferModeList.clear();
}

void SR844::init()
{
    if (this->srs == nullptr)
        this->srs = new SRS();

    initBaudrateList();
    initReferenceSourceList();
    initReferenceTriggerOutputZList();
    initWideReserveModeList();
    initSignalInputZList();
    initSensivityList();
    initCloseReserveModeList();
    initTimeConstantList();
    initFilterList();
    initSampleRateList();
    initBufferModeList();

    connect(this->srs, SIGNAL(errorSignal(QString)),    this, SLOT(catchErrorSignal(QString))   , Qt::DirectConnection);
    connect(this->srs, SIGNAL(responseSignal(QString)), this, SLOT(catchResponseSignal(QString)), Qt::DirectConnection);
    connect(this->srs, SIGNAL(commandSignal(QString)),  this, SLOT(catchCommandSignal(QString)) , Qt::DirectConnection);
    connect(this->srs, SIGNAL(timeoutSignal(QString)),  this, SLOT(catchTimeoutSignal(QString)) , Qt::DirectConnection);
}

void SR844::setSerial(QSerialPort* new_serial)
{
    return this->srs->setSerial(&this->serial, new_serial);
}

QSerialPort* SR844::getSerial() const
{
    return this->srs->getSerial(this->serial);
}

bool SR844::setConnection(const QString &portName, const int &baudrate, const int &stopBit, const int &parity)
{
    return this->srs->setConnection(&this->serial, portName, baudrate, stopBit, parity);
}

bool SR844::setConnectionBrute(const QString &portName)
{
    QStringList baudRates = this->srs->getBaudrateList();
    
    for (int i = 0;i < baudRates.size();i++) {
        if(this->srs->setConnection(&this->serial, portName, baudRates[i].toInt(), 1, 0))
            return true;
        if(this->srs->setConnection(&this->serial, portName, baudRates[i].toInt(), 1, 1))
            return true;
        if(this->srs->setConnection(&this->serial, portName, baudRates[i].toInt(), 1, 2))
            return true;
        // Just in case
        /*
        if(this->srs->setConnection(&this->serial, portName, baudRates[i].toInt(), 2, 0))
            return true;
        if(this->srs->setConnection(&this->serial, portName, baudRates[i].toInt(), 2, 1))
            return true;
        if(this->srs->setConnection(&this->serial, portName, baudRates[i].toInt(), 2, 2))
            return true;
        //*/
    }
    
    return false;
}

void SR844::disconnect() const
{
    return this->srs->disconnect(this->serial);
}

void SR844::initBaudrateList()
{
    this->baudrateList.clear();

    this->baudrateList.push_back( "1200");
    this->baudrateList.push_back( "2400");
    this->baudrateList.push_back( "4800");
    this->baudrateList.push_back( "9600");
    this->baudrateList.push_back("19200");

    return;
}

QStringList SR844::getBaudrateList() const
{
    return this->baudrateList;
}

bool SR844::isValidBaudrate(const int &baudrate) const
{
    return (baudrateList.indexOf(QString::number(baudrate)) != -1);
}

bool SR844::changeBaudrate(const int &baudrate)
{
    if (!isValidBaudrate(baudrate))
        return false;

    if (!this->serial->isOpen()) {
        this->serial->setBaudRate((qint32) baudrate);
        return true;
    } else {
        this->serial->close();
        return setConnection(this->serial->portName(), baudrate);
    }
}

void SR844::setWriteTimeout(const int &new_writeTimeout)
{
    return this->srs->setWriteTimeout(new_writeTimeout);
}

int SR844::getWriteTimeout() const
{
    return this->srs->getWriteTimeout();
}

void SR844::setReadTimeout(const int &new_readTimeout)
{
    return this->srs->setReadTimeout(new_readTimeout);
}

int SR844::getReadTimeout() const
{
    return this->srs->getReadTimeout();
}

void SR844::setReadWaitTimeout(const int &new_readWaitTimeout)
{
    return this->srs->setReadWaitTimeout(new_readWaitTimeout);
}

int SR844::getReadWaitTimeout() const
{
    return this->srs->getReadWaitTimeout();
}

void SR844::setAttemptsToConnect(const int &new_attemptsToConnect)
{
    return this->setAttemptsToConnect(new_attemptsToConnect);
}

int SR844::getAttemptsToConnect() const
{
    return this->getAttemptsToConnect();
}

bool SR844::isActive() const
{
    return this->srs->isActive(this->serial);
}

bool SR844::send(const QString &command, QString &response, const bool &wait_for_response) const
{
    return this->srs->send(this->serial, command, response, wait_for_response);
}

bool SR844::sendCommand(const QString &command) const
{
    return this->srs->sendCommand(this->serial, command);
}

bool SR844::sendQuery(const QString &command, QString &response) const
{
    return this->srs->sendQuery(this->serial, command, response);
}

QString SR844::ask(const QString &command) const
{
    return this->srs->ask(this->serial, command);
}

bool SR844::getIDN(QString &idn) const
{
    return this->srs->getIDN(this->serial, idn);
}

int SR844::numberFromString(const QStringList &list, const QString &string) const
{
    return this->srs->numberFromString(list, string);
}

QString SR844::stringFromNumber(const QStringList &list, const int &number) const
{
    return this->srs->stringFromNumber(list, number);
}

bool SR844::isValidString(const QStringList &list, const QString &string) const
{
    return this->srs->isValidString(list, string);
}

bool SR844::isValidNumber(const QStringList &list, const int &number) const
{
    return this->srs->isValidNumber(list, number);
}

double SR844::getMinInternalFrequency() const
{
    return this->minInternalFrequency;
}

double SR844::getMaxInternalFrequency() const
{
    return this->maxInternalFrequency;
}

bool SR844::isValidInternalFrequency(const double &frequency) const
{
    return (frequency >= this->minInternalFrequency &&
            frequency <= this->maxInternalFrequency);
}

bool SR844::setInternalFrequency(const double &frequency) const
{
    QString command = "FREQ " + QString::number(frequency);
    if (isValidInternalFrequency(frequency))
        return sendCommand(command);
    else
        return false;
}

double SR844::getFrequency() const
{
    return ask("FREQ?").toDouble();
}

double SR844::getFrequencyDetect() const
{
    return ask("FRAQ?").toDouble();
}

int SR844::getMinHarmonic() const
{
    return this->minHarmonic;
}

int SR844::getMaxHarmonic() const
{
    return this->maxHarmonic;
}

bool SR844::isValidHarmonic(const int &i) const
{
    return (i >= this->minHarmonic &&
            i <= this->maxHarmonic);
}

bool SR844::setHarmonic(const int &i) const
{
    QString command = "HARM " + QString::number(i-1);
    if (isValidHarmonic(i))
        return sendCommand(command);
    else
        return false;
}

int SR844::getHarmonic() const
{
    return ask("HARM?").toInt() + 1;
}

void SR844::initReferenceSourceList()
{
    this->referenceSourceList.clear();

    this->referenceSourceList.push_back("EXT");
    this->referenceSourceList.push_back("INT");

    return;
}

QStringList SR844::getReferenceSourceList() const
{
    return this->referenceSourceList;
}

int SR844::refSourceNumberFromString(const QString &ref_string) const
{
    return numberFromString(this->referenceSourceList, ref_string);
}

QString SR844::refSourceStringFromNumber(const int &ref_number) const
{
    return stringFromNumber(this->referenceSourceList, ref_number);
}

bool SR844::setReferenceSource(const int &source) const
{
    if (!isValidNumber(this->referenceSourceList, source))
        return false;

    QString command = "FMOD " + QString::number(source);
    return sendCommand(command);
}

bool SR844::setReferenceSource(const QString &source) const
{
    return setReferenceSource(refSourceNumberFromString(source));
}

QString SR844::getReferenceSource() const
{
    return refSourceStringFromNumber(ask("FMOD?").toInt());
}

void SR844::initReferenceTriggerOutputZList()
{
    this->referenceTriggerOutputZList.clear();

    this->referenceTriggerOutputZList.push_back("50Ohms");
    this->referenceTriggerOutputZList.push_back("10kOhms");

    return;
}

QStringList SR844::getReferenceTriggerOutputZList() const
{
    return this->referenceTriggerOutputZList;
}

int SR844::refTriggerOutputZNumberFromString(const QString &referenceTriggerOutputZ_string) const
{
    return numberFromString(this->referenceTriggerOutputZList, referenceTriggerOutputZ_string);
}

QString SR844::refTriggerOutputZStringFromNumber(const int &referenceTriggerOutputZ_number) const
{
    return stringFromNumber(this->referenceTriggerOutputZList, referenceTriggerOutputZ_number);
}

bool SR844::setReferenceTriggerOutputZ(const int &referenceTriggerOutputZ) const
{
    if (!isValidNumber(this->referenceTriggerOutputZList, referenceTriggerOutputZ))
        return false;

    QString command = "REFZ " + QString::number(referenceTriggerOutputZ);
    return sendCommand(command);
}

bool SR844::setReferenceTriggerOutputZ(const QString &referenceTriggerOutputZ) const
{
    return setReferenceTriggerOutputZ(refTriggerOutputZNumberFromString(referenceTriggerOutputZ));
}

QString SR844::getReferenceTriggerOutputZ() const
{
    return refTriggerOutputZStringFromNumber(ask("REFZ?").toInt());
}

void SR844::initWideReserveModeList()
{
    this->wideReserveModeList.clear();

    this->wideReserveModeList.push_back("High Reserve");
    this->wideReserveModeList.push_back("Normal");
    this->wideReserveModeList.push_back("Low Noise");

    return;
}

QStringList SR844::getWideReserveModeList() const
{
    return this->wideReserveModeList;
}

int SR844::wideReserveModeNumberFromString(const QString &wideReserveMode_string) const
{
    return numberFromString(this->wideReserveModeList, wideReserveMode_string);
}

QString SR844::wideReserveModeStringFromNumber(const int &wideReserveMode_number) const
{
    return stringFromNumber(this->wideReserveModeList, wideReserveMode_number);
}

bool SR844::setWideReserveMode(const int &wideReserveMode) const
{
    if (!isValidNumber(this->wideReserveModeList, wideReserveMode))
        return false;

    QString command = "WRSV " + QString::number(wideReserveMode);
    return sendCommand(command);
}

bool SR844::setWideReserveMode(const QString &wideReserveMode) const
{
    return setWideReserveMode(wideReserveModeNumberFromString(wideReserveMode));
}

QString SR844::getWideReserveMode() const
{
    return wideReserveModeStringFromNumber(ask("WRSV?").toInt());
}

void SR844::initSignalInputZList()
{
    this->signalInputZList.clear();

    this->signalInputZList.push_back("50Ohms");
    this->signalInputZList.push_back("1MOhms");

    return;
}

QStringList SR844::getSignalInputZList() const
{
    return this->signalInputZList;
}

int SR844::signalInputZNumberFromString(const QString &signalInputZ_string) const
{
    return numberFromString(this->signalInputZList, signalInputZ_string);
}

QString SR844::signalInputZStringFromNumber(const int &signalInputZ_number) const
{
    return stringFromNumber(this->signalInputZList, signalInputZ_number);
}

bool SR844::setSignalInputZ(const int &signalInputZ) const
{
    if (!isValidNumber(this->signalInputZList, signalInputZ))
        return false;

    QString command = "INPZ " + QString::number(signalInputZ);
    return sendCommand(command);
}

bool SR844::setSignalInputZ(const QString &signalInputZ) const
{
    return setSignalInputZ(signalInputZNumberFromString(signalInputZ));
}

QString SR844::getSignalInputZ() const
{
    return signalInputZStringFromNumber(ask("INPZ?").toInt());
}

void SR844::initSensivityList()
{
    this->sensivityList.clear();

    this->sensivityList.push_back("100 nV/fA");
    this->sensivityList.push_back("300 nV/fA");
    this->sensivityList.push_back(  "1 uV/pA");
    this->sensivityList.push_back(  "3 uV/pA");
    this->sensivityList.push_back( "10 uV/pA");
    this->sensivityList.push_back( "30 uV/pA");
    this->sensivityList.push_back("100 uV/pA");
    this->sensivityList.push_back("300 uV/pA");
    this->sensivityList.push_back(  "1 mV/nA");
    this->sensivityList.push_back(  "3 mV/nA");
    this->sensivityList.push_back( "10 mV/nA");
    this->sensivityList.push_back( "30 mV/nA");
    this->sensivityList.push_back("100 mV/nA");
    this->sensivityList.push_back("300 mV/nA");
    this->sensivityList.push_back(  "1 V/uA");

    return;
}

QStringList SR844::getSensivityList() const
{
    return this->sensivityList;
}

int SR844::sensivityNumberFromString(const QString &sensivity_string) const
{
    return numberFromString(this->sensivityList, sensivity_string);
}

QString SR844::sensivityStringFromNumber(const int &sensivity_number) const
{
    return stringFromNumber(this->sensivityList, sensivity_number);
}

bool SR844::setSensivity(const int &sensivity) const
{
    if (!isValidNumber(this->sensivityList, sensivity))
        return false;

    QString command = "SENS " + QString::number(sensivity);
    return sendCommand(command);
}

bool SR844::setSensivity(const QString &sensivity) const
{
    return setSensivity(sensivityNumberFromString(sensivity));
}

QString SR844::getSensivity() const
{
    return sensivityStringFromNumber(ask("SENS?").toInt());
}

void SR844::initCloseReserveModeList()
{
    this->closeReserveModeList.clear();

    this->closeReserveModeList.push_back("High Reserve");
    this->closeReserveModeList.push_back("Normal");
    this->closeReserveModeList.push_back("Low Noise");

    return;
}

QStringList SR844::getCloseReserveModeList() const
{
    return this->closeReserveModeList;
}

int SR844::closeReserveModeNumberFromString(const QString &closeReserveMode_string) const
{
    return numberFromString(this->closeReserveModeList, closeReserveMode_string);
}

QString SR844::closeReserveModeStringFromNumber(const int &closeReserveMode_number) const
{
    return stringFromNumber(this->closeReserveModeList, closeReserveMode_number);
}

bool SR844::setCloseReserveMode(const int &closeReserveMode) const
{
    if (!isValidNumber(this->closeReserveModeList, closeReserveMode))
        return false;

    QString command = "CRSV " + QString::number(closeReserveMode);
    return sendCommand(command);
}

bool SR844::setCloseReserveMode(const QString &closeReserveMode) const
{
    return setCloseReserveMode(closeReserveModeNumberFromString(closeReserveMode));
}

QString SR844::getCloseReserveMode() const
{
    return closeReserveModeStringFromNumber(ask("CRSV?").toInt());
}

void SR844::initTimeConstantList()
{
    this->timeConstantList.clear();

    this->timeConstantList.push_back("100 us");
    this->timeConstantList.push_back("300 us");
    this->timeConstantList.push_back(  "1 ms");
    this->timeConstantList.push_back(  "3 ms");
    this->timeConstantList.push_back( "10 ms");
    this->timeConstantList.push_back( "30 ms");
    this->timeConstantList.push_back("100 ms");
    this->timeConstantList.push_back("300 ms");
    this->timeConstantList.push_back(  "1 s");
    this->timeConstantList.push_back(  "3 s");
    this->timeConstantList.push_back( "10 s");
    this->timeConstantList.push_back( "30 s");
    this->timeConstantList.push_back("100 s");
    this->timeConstantList.push_back("300 s");
    this->timeConstantList.push_back(  "1 ks");
    this->timeConstantList.push_back(  "3 ks");
    this->timeConstantList.push_back( "10 ks");
    this->timeConstantList.push_back( "30 ks");

    return;
}

QStringList SR844::getTimeConstantList() const
{
    return this->timeConstantList;
}

int SR844::timeConstantNumberFromString(const QString &timeConstant_string) const
{
    return numberFromString(this->timeConstantList, timeConstant_string);
}

QString SR844::timeConstantStringFromNumber(const int &timeConstant_number) const
{
    return stringFromNumber(this->timeConstantList, timeConstant_number);
}

bool SR844::setTimeConstant(const int &timeConstant) const
{
    if (!isValidNumber(this->timeConstantList, timeConstant))
        return false;

    QString command = "OFLT " + QString::number(timeConstant);
    return sendCommand(command);
}

bool SR844::setTimeConstant(const QString &timeConstant) const
{
    return setTimeConstant(timeConstantNumberFromString(timeConstant));
}

QString SR844::getTimeConstant() const
{
    return timeConstantStringFromNumber(ask("OFLT?").toInt());
}

void SR844::initFilterList()
{
    this->filterList.clear();

    this->filterList.push_back("No Filter");
    this->filterList.push_back( "6 dB/oct");
    this->filterList.push_back("12 dB/oct");
    this->filterList.push_back("18 dB/oct");
    this->filterList.push_back("24 dB/oct");

    return;
}

QStringList SR844::getFilterList() const
{
    return this->filterList;
}

int SR844::filterNumberFromString(const QString &filter_string) const
{
    return numberFromString(this->filterList, filter_string);
}

QString SR844::filterStringFromNumber(const int &filter_number) const
{
    return stringFromNumber(this->filterList, filter_number);
}

bool SR844::setFilter(const int &filter) const
{
    if (!isValidNumber(this->filterList, filter))
        return false;

    QString command = "OFSL " + QString::number(filter);
    return sendCommand(command);
}

bool SR844::setFilter(const QString &filter) const
{
    return setFilter(filterNumberFromString(filter));
}

QString SR844::getFilter() const
{
    return filterStringFromNumber(ask("OFSL?").toInt());
}

bool SR844::enableRS232outputInterface() const
{
    return sendCommand("OUTX 0");
}

bool SR844::autoWideReserve() const
{
    return sendCommand("AWRS");
}

bool SR844::autoCloseReserve() const
{
    return sendCommand("ACRS");
}

bool SR844::autoGain() const
{
    return sendCommand("AGAN");
}

bool SR844::autoPhase() const
{
    return sendCommand("APHS");
}

bool SR844::autoOffsetAll() const
{
    bool ans = true;

    ans &= sendCommand("AOFF 1, 0");
    ans &= sendCommand("AOFF 1, 1");
    ans &= sendCommand("AOFF 1, 2");
    ans &= sendCommand("AOFF 2, 0");

    return ans;
}

void SR844::initSampleRateList()
{
    this->sampleRateList.clear();

    this->sampleRateList.push_back("62.5 mHz");
    this->sampleRateList.push_back( "125 mHz");
    this->sampleRateList.push_back( "250 mHz");
    this->sampleRateList.push_back( "500 mHz");
    this->sampleRateList.push_back(   "1 Hz");
    this->sampleRateList.push_back(   "2 Hz");
    this->sampleRateList.push_back(   "4 Hz");
    this->sampleRateList.push_back(   "8 Hz");
    this->sampleRateList.push_back(  "16 Hz");
    this->sampleRateList.push_back(  "32 Hz");
    this->sampleRateList.push_back(  "64 Hz");
    this->sampleRateList.push_back( "128 Hz");
    this->sampleRateList.push_back( "256 Hz");
    this->sampleRateList.push_back( "512 Hz");
    this->sampleRateList.push_back("Trigger");

    return;
}

QStringList SR844::getSampleRateList() const
{
    return this->sampleRateList;
}

int SR844::sampleRateNumberFromString(const QString &sampleRate_string) const
{
    return numberFromString(this->sampleRateList, sampleRate_string);
}

QString SR844::sampleRateStringFromNumber(const int &sampleRate_number) const
{
    return stringFromNumber(this->sampleRateList, sampleRate_number);
}

bool SR844::setSampleRate(const int &sampleRate) const
{
    if (!isValidNumber(this->sampleRateList, sampleRate))
        return false;

    QString command = "SRAT " + QString::number(sampleRate);
    return sendCommand(command);
}

bool SR844::setSampleRate(const QString &sampleRate) const
{
    return setSampleRate(sampleRateNumberFromString(sampleRate));
}

QString SR844::getSampleRate() const
{
    return sampleRateStringFromNumber(ask("SRAT?").toInt());
}

void SR844::initBufferModeList()
{
    this->bufferModeList.clear();

    this->bufferModeList.push_back("Shot");
    this->bufferModeList.push_back("Loop");

    return;
}

QStringList SR844::getBufferModeList() const
{
    return this->bufferModeList;
}

int SR844::bufferModeNumberFromString(const QString &bufferMode_string) const
{
    return numberFromString(this->bufferModeList, bufferMode_string);
}

QString SR844::bufferModeStringFromNumber(const int &bufferMode_number) const
{
    return stringFromNumber(this->bufferModeList, bufferMode_number);
}

bool SR844::setBufferMode(const int &bufferMode) const
{
    if (!isValidNumber(this->bufferModeList, bufferMode))
        return false;

    QString command = "SEND " + QString::number(bufferMode);
    return sendCommand(command);
}

bool SR844::setBufferMode(const QString &bufferMode) const
{
    return setBufferMode(bufferModeNumberFromString(bufferMode));
}

QString SR844::getBufferMode() const
{
    return bufferModeStringFromNumber(ask("SEND?").toInt());
}

bool SR844::startBuffer() const
{
    return sendCommand("STRT");
}

bool SR844::pauseBuffer() const
{
    return sendCommand("PAUS");
}

bool SR844::stopBuffer() const
{
    return sendCommand("REST");
}

void SR844::initOutputNumberList()
{
    this->outputNumberList.clear();

    this->outputNumberList.push_back("X");
    this->outputNumberList.push_back("Y");
    this->outputNumberList.push_back("R [V]");
    this->outputNumberList.push_back("R [dBm]");
    this->outputNumberList.push_back("Theta");
    this->outputNumberList.push_back("Aux In 1");
    this->outputNumberList.push_back("Aux In 2");
    this->outputNumberList.push_back("Reference Frequency");
    this->outputNumberList.push_back("CH1 display");
    this->outputNumberList.push_back("CH2 display");

    return;
}

QStringList SR844::getOutputNumberList() const
{
    return this->outputNumberList;
}

int SR844::outpNumberFromString(const QString &outp_string) const
{
    return numberFromString(this->outputNumberList, outp_string);
}

QString SR844::outpStringFromNumber(const int &outp_number) const
{
    return stringFromNumber(this->outputNumberList, outp_number);
}

double SR844::getOUTP(const int &i) const
{
    if (!isValidNumber(this->outputNumberList, i))
        return -1;

    QString command = "OUTP? " + QString::number(i);
    QString response;
    sendQuery(command, response);
    return response.trimmed().toDouble();
}

double SR844::getOUTP(const QString &i) const
{
    if (outputNumberList.indexOf(i) != -1)
        return getOUTP(outputNumberList.indexOf(i));
    return -1;
}

double SR844::getX() const
{
    return getOUTP(1);
}

double SR844::getY() const
{
    return getOUTP(2);
}

double SR844::getR() const
{
    return getOUTP(3);
}

double SR844::getTheta() const
{
    return getOUTP(5);
}

bool SR844::getAB(const int & Apos, double &A, const int &Bpos, double &B) const
{
    QString command = "SNAP? " + QString::number(Apos) + "," + QString::number(Bpos);
    QString response;
    if (!sendQuery(command, response))
        return false;

    QStringList responseList = response.trimmed().split(',');
    QString _a = responseList.at(0);
    QString _b = responseList.at(1);
    A = _a.trimmed().toDouble();
    B = _b.trimmed().toDouble();

    return true;
}

bool SR844::getABC(const int &Apos, double &A, const int &Bpos, double &B, const int &Cpos, double &C) const
{
    QString command = "SNAP? " + QString::number(Apos) + "," + QString::number(Bpos) + "," + QString::number(Cpos);
    QString response;
    if (!sendQuery(command, response))
        return false;

    QStringList responseList = response.trimmed().split(',');
    QString _a = responseList.at(0);
    QString _b = responseList.at(1);
    QString _c = responseList.at(2);
    A = _a.trimmed().toDouble();
    B = _b.trimmed().toDouble();
    C = _c.trimmed().toDouble();

    return true;
}

bool SR844::getABCDE(const int &Apos, double &A, const int &Bpos, double &B, const int &Cpos, double &C, const int &Dpos, double &D, const int &Epos, double &E) const
{
    QString command = "SNAP? " + QString::number(Apos) + "," + QString::number(Bpos) + "," + QString::number(Cpos) + "," + QString::number(Dpos) + "," + QString::number(Epos);
    QString response;
    if (!sendQuery(command, response))
        return false;

    QStringList responseList = response.trimmed().split(',');
    QString _a = responseList.at(0);
    QString _b = responseList.at(1);
    QString _c = responseList.at(2);
    QString _d = responseList.at(3);
    QString _e = responseList.at(4);
    A = _a.trimmed().toDouble();
    B = _b.trimmed().toDouble();
    C = _c.trimmed().toDouble();
    D = _d.trimmed().toDouble();
    E = _e.trimmed().toDouble();

    return true;
}

bool SR844::getABCDEF(const int &Apos, double &A, const int &Bpos, double &B, const int &Cpos, double &C, const int &Dpos, double &D, const int &Epos, double &E, const int &Fpos, double &F) const
{
    QString command = "SNAP? " + QString::number(Apos) + "," + QString::number(Bpos) + "," + QString::number(Cpos) + "," + QString::number(Dpos) + "," + QString::number(Epos) + "," + QString::number(Fpos);
    QString response;
    if (!sendQuery(command, response))
        return false;

    QStringList responseList = response.trimmed().split(',');
    QString _a = responseList.at(0);
    QString _b = responseList.at(1);
    QString _c = responseList.at(2);
    QString _d = responseList.at(3);
    QString _e = responseList.at(4);
    QString _f = responseList.at(5);
    A = _a.trimmed().toDouble();
    B = _b.trimmed().toDouble();
    C = _c.trimmed().toDouble();
    D = _d.trimmed().toDouble();
    E = _e.trimmed().toDouble();
    F = _f.trimmed().toDouble();

    return true;
}

bool SR844::getXY(double &X, double &Y) const
{
    return getAB(1, X, 2, Y);
}

bool SR844::getRTheta(double &R, double &Theta) const
{
    return getAB(3, R, 5, Theta);
}

bool SR844::getRThetaF(double &R, double &Theta, double &F) const
{
    return getABC(3, R, 5, Theta, 8, F);
}

bool SR844::getXYRThetaF(double &X, double&Y, double &R, double &Theta, double &F) const
{
    return getABCDE(1, X, 2, Y, 3, R, 5, Theta, 8, F);
}

bool SR844::setDisplayData(const int &channel, const int &data) const
{
    return sendCommand("DDEF " + QString::number(channel) + "," + QString::number(data));
}

int SR844:: getBufferSize() const
{
    return ask("SPTS?").toInt();
}

double SR844::getPointFromBuffer(const int &channel, const int &number) const
{
    return ask("TRCA? " + QString::number(channel) + "," + QString::number(number) + ",1").toDouble();
}

std::vector < double > SR844::getChannelFromBuffer(const int &channel) const
{
    std::vector < double > ans;

    int size = getBufferSize();
    for (int i = 0;i < size;i++) {
        ans.push_back(getPointFromBuffer(channel, i));
    }

    return ans;
}

int SR844::getBuffer(std::vector<double> &ch1, std::vector<double> &ch2) const
{
    ch1.clear();
    ch2.clear();

    int size = getBufferSize();
    for (int i = 0;i < size;i++) {
        ch1.push_back(getPointFromBuffer(1, i));
        ch2.push_back(getPointFromBuffer(2, i));
    }

    return size;
}

void SR844::catchErrorSignal(const QString &s) const
{
    emit this->errorSignal(s);
}

void SR844::catchResponseSignal(const QString &s) const
{
    emit this->responseSignal(s);
}

void SR844::catchCommandSignal(const QString &s) const
{
    emit this->commandSignal(s);
}

void SR844::catchTimeoutSignal(const QString &s) const
{
    emit this->timeoutSignal(s);
}
