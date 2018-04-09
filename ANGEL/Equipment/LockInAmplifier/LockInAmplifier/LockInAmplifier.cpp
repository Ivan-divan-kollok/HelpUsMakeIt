#include "LockInAmplifier.h"

LockInAmplifier::LockInAmplifier(QObject *parent) : QObject(parent)
{
    toNULL();
}

LockInAmplifier::LockInAmplifier(const QString &portName, const int &baudrate, const int &stopBit, const int &parity, const QString &new_lockInAmplifierModel)
{
    toNULL();
    setConnection(portName, baudrate, stopBit, parity, new_lockInAmplifierModel);
}

LockInAmplifier::LockInAmplifier(QSerialPort *serial, const QString &new_lockInAmplifierModel)
{
    toNULL();
	QString _lockInAmplifierModel = new_lockInAmplifierModel.trimmed().toUpper();
    if (_lockInAmplifierModel == "SR830") {
        if (this->sr830 == nullptr)
            this->sr830 = new SR830(serial->portName(), serial->baudRate());
        else
            this->sr830->setSerial(serial);
    }
    if (_lockInAmplifierModel == "SR844") {
        if (this->sr844 == nullptr)
            this->sr844 = new SR844(serial->portName(), serial->baudRate());
        else
            this->sr844->setSerial(serial);
    }
    if (_lockInAmplifierModel == "SR865") {
        if (this->sr865 == nullptr)
            this->sr865 = new SR865(serial->portName(), serial->baudRate());
        else
            this->sr865->setSerial(serial);
    }
    if (_lockInAmplifierModel.isEmpty() ||
        _lockInAmplifierModel == "AUTO") {
        autoSetLockInAmplifierModel(serial);
    }
}

LockInAmplifier::LockInAmplifier(SR830* new_sr830)
{
    toNULL();
    setSR830(new_sr830);
}

LockInAmplifier::LockInAmplifier(SR844* new_sr844)
{
    toNULL();
    setSR844(new_sr844);
}

LockInAmplifier::LockInAmplifier(SR865* new_sr865)
{
    toNULL();
    setSR865(new_sr865);
}

LockInAmplifier::~LockInAmplifier()
{
    this->lockInAmplifierModel.clear();
    if (this->sr830 != nullptr)
        this->sr830->~SR830();
    delete this->sr830;
    if (this->sr844 != nullptr)
        this->sr844->~SR844();
    delete this->sr844;
    if (this->sr865 != nullptr)
        this->sr865->~SR865();
    delete this->sr865;
    if (this->srs != nullptr)
        this->srs->~SRS();
    delete this->srs;

    this->sr830 = nullptr;
    this->sr844 = nullptr;
    this->sr865 = nullptr;
    this->srs = nullptr;
}

void LockInAmplifier::toNULL()
{
    if (this->sr830 != nullptr) {
        this->sr830 = nullptr;
    }
    if (this->sr844 != nullptr) {
        this->sr844 = nullptr;
    }
    if (this->sr865 != nullptr) {
        this->sr865 = nullptr;
    }
    if (this->srs != nullptr) {
        this->srs = nullptr;
    }

    init();

    return;
}

void LockInAmplifier::init()
{
    if (this->srs == nullptr)
        this->srs = new SRS();

    if (this->srs != nullptr) {
        connect(this->srs,   SIGNAL(errorSignal(QString)),    this, SLOT(catchErrorSignal(QString)),    Qt::DirectConnection);
        connect(this->srs,   SIGNAL(responseSignal(QString)), this, SLOT(catchResponseSignal(QString)), Qt::DirectConnection);
        connect(this->srs,   SIGNAL(commandSignal(QString)),  this, SLOT(catchCommandSignal(QString)),  Qt::DirectConnection);
        connect(this->srs,   SIGNAL(timeoutSignal(QString)),  this, SLOT(catchTimeoutSignal(QString)),  Qt::DirectConnection);
    }
    if (this->sr830 != nullptr) {
        connect(this->sr830, SIGNAL(errorSignal(QString)),    this, SLOT(catchErrorSignal(QString)),    Qt::DirectConnection);
        connect(this->sr830, SIGNAL(responseSignal(QString)), this, SLOT(catchResponseSignal(QString)), Qt::DirectConnection);
        connect(this->sr830, SIGNAL(commandSignal(QString)),  this, SLOT(catchCommandSignal(QString)),  Qt::DirectConnection);
        connect(this->sr830, SIGNAL(timeoutSignal(QString)),  this, SLOT(catchTimeoutSignal(QString)),  Qt::DirectConnection);
    }
    if (this->sr844 != nullptr) {
        connect(this->sr844, SIGNAL(errorSignal(QString)),    this, SLOT(catchErrorSignal(QString)),    Qt::DirectConnection);
        connect(this->sr844, SIGNAL(responseSignal(QString)), this, SLOT(catchResponseSignal(QString)), Qt::DirectConnection);
        connect(this->sr844, SIGNAL(commandSignal(QString)),  this, SLOT(catchCommandSignal(QString)),  Qt::DirectConnection);
        connect(this->sr844, SIGNAL(timeoutSignal(QString)),  this, SLOT(catchTimeoutSignal(QString)),  Qt::DirectConnection);
    }
    if (this->sr865 != nullptr) {
        connect(this->sr865, SIGNAL(errorSignal(QString)),    this, SLOT(catchErrorSignal(QString)),    Qt::DirectConnection);
        connect(this->sr865, SIGNAL(responseSignal(QString)), this, SLOT(catchResponseSignal(QString)), Qt::DirectConnection);
        connect(this->sr865, SIGNAL(commandSignal(QString)),  this, SLOT(catchCommandSignal(QString)),  Qt::DirectConnection);
        connect(this->sr865, SIGNAL(timeoutSignal(QString)),  this, SLOT(catchTimeoutSignal(QString)),  Qt::DirectConnection);
    }

    return;
}

LockInAmplifier_State LockInAmplifier::getState()
{
    LockInAmplifier_State current_state;

    current_state.model = this->lockInAmplifierModel;

    if (workWithInternalFrequency())
        current_state.internalFrequency = getInternalFrequency();
    if (workWithHarmonic())
        current_state.harmonic = getHarmonic();
    if (workWithHarmonicDual())
        current_state.harmonicDual = getHarmonicDual();
    if (workWithSineOutAmplitude())
        current_state.sineOutAmplitude = getSineOutAmplitude();
    if (workWithSineOffset())
        current_state.sineOffset = getSineOffset();
    if (workWithReferenceSource())
        current_state.referenceSource = getReferenceSource();
    if (workWithReferenceTriggerMode())
        current_state.referenceTriggerMode = getReferenceTriggerMode();
    if (workWithReferenceTriggerOutputZ())
        current_state.referenceTriggerOutputZ = getReferenceTriggerOutputZ();
    if (workWithSignalInput())
        current_state.signalInput = getSignalInput();
    if (workWithSignalInputZ())
        current_state.signalInputZ = getSignalInputZ();
    if (workWithVoltageInputMode())
        current_state.voltageInputMode = getVoltageInputMode();
    if (workWithVoltageInputCoupling())
        current_state.voltageInputCoupling = getVoltageInputCoupling();
    if (workWithVoltageInputShields())
        current_state.voltageInputShields = getVoltageInputShields();
    if (workWithVoltageInputRange())
        current_state.voltageInputRange = getVoltageInputRange();
    if (workWithCurrentInputGain())
        current_state.currentInputGain = getCurrentInputGain();
    if (workWithInputLineNotchFilter())
        current_state.inputLineNotchFilter = getInputLineNotchFilter();
    if (workWithSensivity())
        current_state.sensivity = getSensivity();
    if (workWithReserveMode())
        current_state.reserveMode = getReserveMode();
    if (workWithWideReserveMode())
        current_state.wideReserveMode = getWideReserveMode();
    if (workWithCloseReserveMode())
        current_state.closeReserveMode = getCloseReserveMode();
    if (workWithTimeConstant())
        current_state.timeConstant = getTimeConstant();
    if (workWithFilter())
        current_state.filter = getFilter();
    if (workWithSynchronousFilter())
        current_state.synchronousFilter = getSynchronousFilterEnabled();
    if (workWithAdvancedFilter())
        current_state.advancedFilter = getAdvancedFilterEnabled();
    if (workWithSampleRate())
        current_state.sampleRate = getSampleRate();
    if (workWithBufferMode())
        current_state.bufferMode = getBufferMode();

    return current_state;
}

bool LockInAmplifier::setState(const LockInAmplifier_State &state)
{
    bool result = true;

    if (state.model != this->lockInAmplifierModel)
        result = false;
    if (workWithInternalFrequency())
        result &= this->setInternalFrequency(state.internalFrequency);
    if (workWithHarmonic())
        result &= this->setHarmonic(state.harmonic);
    if (workWithHarmonicDual())
        result &= this->setHarmonicDual(state.harmonicDual);
    if (workWithSineOutAmplitude())
        result &= this->setSineOutAmplitude(state.sineOutAmplitude);
    if (workWithSineOffset())
        result &= this->setSineOffset(state.sineOffset);
    if (workWithReferenceSource())
        result &= this->setReferenceSource(state.referenceSource);
    if (workWithReferenceTriggerMode())
        result &= this->setReferenceTriggerMode(state.referenceTriggerMode);
    if (workWithReferenceTriggerOutputZ())
        result &= this->setReferenceTriggerOutputZ(state.referenceTriggerOutputZ);
    if (workWithSignalInput())
        result &= this->setSignalInput(state.signalInput);
    if (workWithSignalInputZ())
        result &= this->setSignalInputZ(state.signalInputZ);
    if (workWithVoltageInputMode())
        result &= this->setVoltageInputMode(state.voltageInputMode);
    if (workWithVoltageInputCoupling())
        result &= this->setVoltageInputCoupling(state.voltageInputCoupling);
    if (workWithVoltageInputShields())
        result &= this->setVoltageInputShields(state.voltageInputShields);
    if (workWithVoltageInputRange())
        result &= this->setVoltageInputRange(state.voltageInputRange);
    if (workWithCurrentInputGain())
        result &= this->setCurrentInputGain(state.currentInputGain);
    if (workWithInputLineNotchFilter())
        result &= this->setInputLineNotchFilter(state.inputLineNotchFilter);
    if (workWithSensivity())
        result &= this->setSensivity(state.sensivity);
    if (workWithReserveMode())
        result &= this->setReserveMode(state.reserveMode);
    if (workWithWideReserveMode())
        result &= this->setWideReserveMode(state.wideReserveMode);
    if (workWithCloseReserveMode())
        result &= this->setCloseReserveMode(state.closeReserveMode);
    if (workWithTimeConstant())
        result &= this->setTimeConstant(state.timeConstant);
    if (workWithFilter())
        result &= this->setFilter(state.filter);
    if (workWithSynchronousFilter())
        result &= this->enableSynchronousFilter(state.synchronousFilter);
    if (workWithAdvancedFilter())
        result &= this->enableAdvancedFilter(state.advancedFilter);
    if (workWithSampleRate())
        result &= this->setSampleRate(state.sampleRate);
    if (workWithBufferMode())
        result &= this->setBufferMode(state.bufferMode);

    return result;
}

void LockInAmplifier::wait(const double &x) const
{
    QTest::qWait(_round(this->waitTime*x));

    return;
}

void LockInAmplifier::setSR830(SR830* new_sr830)
{
    this->sr830 = new_sr830;
    init();

    return;
}

SR830* LockInAmplifier::getSR830() const
{
    return this->sr830;
}

void LockInAmplifier::setSR844(SR844* new_sr844)
{
    this->sr844 = new_sr844;
    init();

    return;
}

SR844* LockInAmplifier::getSR844() const
{
    return this->sr844;
}

void LockInAmplifier::setSR865(SR865* new_sr865)
{
    this->sr865 = new_sr865;
    init();

    return;
}

SR865* LockInAmplifier::getSR865() const
{
    return this->sr865;
}

bool LockInAmplifier::openSerial(QSerialPort *serial) const
{
    return this->srs->openSerial(serial);
}

QStringList LockInAmplifier::getSupportedModels() const
{
    QStringList ans;

    ans.push_back("SR830");
    ans.push_back("SR844");
    ans.push_back("SR865");
    ans.push_back("AUTO");

    return ans;
}

void LockInAmplifier::setLockInAmplifierModel(const QString &new_lockInAmplifierModel)
{
    this->lockInAmplifierModel = new_lockInAmplifierModel;

    return;
}

QString LockInAmplifier::getLockInAmplifierModel() const
{
    return this->lockInAmplifierModel;
}

bool LockInAmplifier::autoSetLockInAmplifierModel(QSerialPort *serial)
{
    this->lockInAmplifierModel.clear();

    QString model = this->srs->autoDetect(serial);

    if (model.trimmed().isEmpty()) {
        this->srs->disconnect(serial);

        return false;
    }

    this->lockInAmplifierModel = model;
    if (model == "SR830") {
        this->sr830 = new SR830();
        this->sr830->setSerial(serial);
        init();

        return true;
    }
    if (model == "SR844") {
        this->sr844 = new SR844();
        this->sr844->setSerial(serial);
        init();

        return true;
    }
    if (model == "SR865") {
        this->sr865 = new SR865();
        this->sr865->setSerial(serial);
        init();

        return true;
    }

    this->srs->disconnect(serial);

    return false;
}

bool LockInAmplifier::autoSetLockInAmplifierModel(const QString &portName, const int &baudrate)
{
    QSerialPort *serial = new QSerialPort();

    serial->setPortName(portName);
    serial->setBaudRate(baudrate);
    serial->setDataBits(QSerialPort::Data8);

    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    if(autoSetLockInAmplifierModel(serial))
        return true;
    serial->setParity(QSerialPort::OddParity);
    serial->setStopBits(QSerialPort::OneStop);
    if(autoSetLockInAmplifierModel(serial))
        return true;
    serial->setParity(QSerialPort::EvenParity);
    serial->setStopBits(QSerialPort::OneStop);
    if(autoSetLockInAmplifierModel(serial))
        return true;
    
    // Just to be in case
    /*
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::TwoStop);
    if(autoSetLockInAmplifierModel(serial))
        return true;
    serial->setParity(QSerialPort::OddParity);
    serial->setStopBits(QSerialPort::TwoStop);
    if(autoSetLockInAmplifierModel(serial))
        return true;
    serial->setParity(QSerialPort::EvenParity);
    serial->setStopBits(QSerialPort::TwoStop);
    if(autoSetLockInAmplifierModel(serial))
        return true;
    //*/
    
    return false;
}

bool LockInAmplifier::autoSetLockInAmplifierModel(const QString &portName)
{
    // LEGACY PART
    /*
    this->lockInAmplifierModel = "";

    QString type = this->srs->autoDetect(portName);

    if (type.trimmed().isEmpty()) {
        this->srs->disconnect(serial);

        return false;
    }

    this->lockInAmplifierModel = type;
    if (type == "SR830") {
        this->sr830 = new SR830();
        this->sr830->setConnection(portName, 19200);
        init();

        return true;
    }
    if (type == "SR844") {
        this->sr844 = new SR844();
        this->sr844->setConnection(portName, 19200);
        init();

        return true;
    }
    if (type == "SR865") {
        this->sr865 = new SR865();
        this->sr865->setConnection(portName, 19200);
        init();

        return true;
    }

    this->srs->disconnect(serial);

    return false;
    //*/

    QStringList baudrates = this->srs->getBaudrateList();
    for (int baud = 0;baud < baudrates.size();baud++) {
        int baudrate = baudrates[baud].toInt();

        if (autoSetLockInAmplifierModel(portName, baudrate))
            return true;
    }

    return false;
}

bool LockInAmplifier::setConnection(const QString &portName, const int &baudrate, const int &stopBit, const int &parity, const QString &new_lockInAmplifierModel)
{
    QString _lockInAmplifierModel = new_lockInAmplifierModel.trimmed().toUpper();
    if (_lockInAmplifierModel == "SR830") {
        if (this->sr830 == nullptr)
            this->sr830 = new SR830();
        this->lockInAmplifierModel = "SR830";
        init();

        return this->sr830->setConnection(portName, baudrate, stopBit, parity);
    }
    if (_lockInAmplifierModel == "SR844") {
        if (this->sr844 == nullptr)
            this->sr844 = new SR844();
        this->lockInAmplifierModel = "SR844";
        init();

        return this->sr844->setConnection(portName, baudrate, stopBit, parity);
    }
    if (_lockInAmplifierModel == "SR865") {
        if (this->sr865 == nullptr)
            this->sr865 = new SR865();
        this->lockInAmplifierModel = "SR865";
        init();

        return this->sr865->setConnection(portName, baudrate, stopBit, parity);
    }
    if (_lockInAmplifierModel.isEmpty() ||
        _lockInAmplifierModel == "AUTO") {
        QSerialPort *serial = new QSerialPort();
        serial->setPortName(portName);
        serial->setBaudRate(baudrate);

        if (stopBit == 1)
            serial->setStopBits(QSerialPort::OneStop);
        if (stopBit == 2)
            serial->setStopBits(QSerialPort::TwoStop);
        if (stopBit == 3)
            serial->setStopBits(QSerialPort::OneAndHalfStop);

        if (parity == 0)
            serial->setParity(QSerialPort::NoParity);
        if (parity == 1)
            serial->setParity(QSerialPort::OddParity);
        if (parity == 2)
            serial->setParity(QSerialPort::EvenParity);

        return autoSetLockInAmplifierModel(serial);
    }

    return false;
}

bool LockInAmplifier::setConnectionBrute(const QString &portName, const QString &new_lockInAmplifierModel)
{
    QStringList baudRates = this->srs->getBaudrateList();
    for (int i = 0;i < baudRates.length();i++) {
        if (setConnection(portName, baudRates[i].toInt(), 1, 0, new_lockInAmplifierModel))
            return true;
        if (setConnection(portName, baudRates[i].toInt(), 1, 1, new_lockInAmplifierModel))
            return true;
        if (setConnection(portName, baudRates[i].toInt(), 1, 2, new_lockInAmplifierModel))
            return true;
        // Just in case
        /*
        if (setConnection(portName, baudRates[i].toInt(), 2, 0, lockInAmplifierModel))
            return true;
        if (setConnection(portName, baudRates[i].toInt(), 2, 1, lockInAmplifierModel))
            return true;
        if (setConnection(portName, baudRates[i].toInt(), 2, 2, lockInAmplifierModel))
            return true;
        //*/
    }

    return false;
}

bool LockInAmplifier::disconnect() const
{
    if (this->lockInAmplifierModel == "SR830") {
        this->sr830->disconnect();

        return true;
    }
    if (this->lockInAmplifierModel == "SR844") {
        this->sr844->disconnect();

        return true;
    }
    if (this->lockInAmplifierModel == "SR865") {
        this->sr865->disconnect();

        return true;
    }
    return false;
}

QStringList LockInAmplifier::getBaudrateList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getBaudrateList();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getBaudrateList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getBaudrateList();
    return QStringList();
}

bool LockInAmplifier::isValidBaudrateAll(const int &baudrate) const
{
    SR830 temp830;
    SR844 temp844;
    SR865 temp865;
    bool answer = temp830.isValidBaudrate(baudrate);
    answer &= temp844.isValidBaudrate(baudrate);
    answer &= temp865.isValidBaudrate(baudrate);
    return answer;
}

bool LockInAmplifier::isValidBaudrate(const int &baudrate) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->isValidBaudrate(baudrate);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->isValidBaudrate(baudrate);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->isValidBaudrate(baudrate);
    return false;
}

bool LockInAmplifier::changeBaudrate(const int &baudrate)
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->changeBaudrate(baudrate);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->changeBaudrate(baudrate);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->changeBaudrate(baudrate);
    return false;
}

void LockInAmplifier::setWriteTimeout(const int &new_writeTimeout)
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setWriteTimeout(new_writeTimeout);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setWriteTimeout(new_writeTimeout);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setWriteTimeout(new_writeTimeout);
    return;
}

int LockInAmplifier::getWriteTimeout() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getWriteTimeout();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getWriteTimeout();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getWriteTimeout();
    return 0;
}

void LockInAmplifier::setReadTimeout(const int &new_readTimeout)
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setReadTimeout(new_readTimeout);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setReadTimeout(new_readTimeout);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setReadTimeout(new_readTimeout);
    return;
}

int LockInAmplifier::getReadTimeout() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getReadTimeout();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getReadTimeout();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getReadTimeout();
    return 0;
}

void LockInAmplifier::setReadWaitTimeout(const int &new_readWaitTimeout)
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setReadWaitTimeout(new_readWaitTimeout);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setReadWaitTimeout(new_readWaitTimeout);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setReadWaitTimeout(new_readWaitTimeout);
    return;
}

int LockInAmplifier::getReadWaitTimeout() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getReadWaitTimeout();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getReadWaitTimeout();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getReadWaitTimeout();
    return 0;
}

void LockInAmplifier::setAttemptsToConnect(const int &new_attemptsToConnect)
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setAttemptsToConnect(new_attemptsToConnect);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setAttemptsToConnect(new_attemptsToConnect);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setAttemptsToConnect(new_attemptsToConnect);
    return;
}

int LockInAmplifier::getAttemptsToConnect() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getAttemptsToConnect();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getAttemptsToConnect();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getAttemptsToConnect();
    return 0;
}

bool LockInAmplifier::isActive() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->isActive();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->isActive();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->isActive();
    return false;
}

bool LockInAmplifier::send(const QString &command, QString &response, const bool &waitForResponse) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->send(command, response, waitForResponse);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->send(command, response, waitForResponse);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->send(command, response, waitForResponse);
    return false;
}

bool LockInAmplifier::sendCommand(const QString &command) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->sendCommand(command);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->sendCommand(command);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->sendCommand(command);
    return false;
}

bool LockInAmplifier::sendQuery(const QString &command, QString &response) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->sendQuery(command, response);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->sendQuery(command, response);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->sendQuery(command, response);
    return false;
}

bool LockInAmplifier::getIDN(QString &idn) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getIDN(idn);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getIDN(idn);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getIDN(idn);
    return false;
}

bool LockInAmplifier::test() const
{
    bool ans = true;

    qDebug() << "Testling Lock-in Amplifier";

    setDefaultSettings();

    wait();

    if (workWithInternalFrequency()) {
        qDebug() << "Lock-in Amplifier internal frequency command test";

        if (!setReferenceSource("INT")) {
            qDebug() << "Lock-in Amplifier internal frequency settings command failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (!setInternalFrequency(getMinInternalFrequency())) {
            qDebug() << "Lock-in Amplifier internal frequency command failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (_abs(getInternalFrequency() - getMinInternalFrequency()) <= this->Err)
            qDebug() << "Min internal frequency passed";
        else {
            qDebug() << "Min internal frequency failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (!setInternalFrequency(getMaxInternalFrequency())) {
            qDebug() << "Lock-in Amplifier internal frequency command failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (_abs(getInternalFrequency() - getMaxInternalFrequency()) <= this->Err)
            qDebug() << "Max internal frequency passed";
        else {
            qDebug() << "Max internal frequency failed";

            ans = false;
        }

        setDefaultInternalFrequency();
        wait();
    }

    if (workWithHarmonic()) {
        qDebug() << "Lock-in Amplifier harmonic command test";

        if (!setReferenceSource("INT")) {
            qDebug() << "Lock-in Amplifier internal reference command failed";

            ans = false;
        }

        wait();

        if (!setInternalFrequency(52000)) {
            qDebug() << "Lock-in Amplifier internal frequency command failed";

            ans = false;
        }

        wait();

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (!setHarmonic(getMinHarmonic())) {
            qDebug() << "Lock-in Amplifier harmonic command failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (getHarmonic() == getMinHarmonic())
            qDebug() << "Min harmonic passed";
        else {
            qDebug() << "Min harmonic failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (!setHarmonic(getMaxHarmonic())) {
            qDebug() << "Lock-in Amplifier harmonic command failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (getHarmonic() == getMaxHarmonic())
            qDebug() << "Max harmonic passed";
        else {
            qDebug() << "Max harmonic failed";

            ans = false;
        }

        setDefaultHarmonic();
        wait();

        setDefaultInternalFrequency();
        wait();
    }

    if (workWithHarmonicDual()) {
        qDebug() << "Lock-in Amplifier harmonic dual command test";

        if (!setHarmonicDual(getMinHarmonicDual())) {
            qDebug() << "Lock-in Amplifier harmonic dual command failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (getHarmonicDual() == getMinHarmonicDual())
            qDebug() << "Min harmonic dual passed";
        else {
            qDebug() << "Min harmonic dual failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (!setHarmonicDual(getMaxHarmonicDual())) {
            qDebug() << "Lock-in Amplifier harmonic dual command failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (getHarmonicDual() == getMaxHarmonicDual())
            qDebug() << "Max harmonic dual passed";
        else {
            qDebug() << "Max harmonic dual failed";

            ans = false;
        }

        setDefaultHarmonicDual();
        wait();
    }

    if (workWithSineOutAmplitude()) {
        qDebug() << "Lock-in Amplifier sine amplitude command test";

        if (this->lockInAmplifierModel == "SR865") {
            if (!setSineOutAmplitude(1, "NV")) {
                qDebug() << "Lock-in Amplifier sine amplitude command failed";

                ans = false;
            }
        } else {
            if (!setSineOutAmplitude(getMinSineOutAmplitude())) {
                qDebug() << "Lock-in Amplifier sine amplitude command failed";

                ans = false;
            }
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (_abs(getSineOutAmplitude() - getMinSineOutAmplitude()) < this->Err)
            qDebug() << "Min sine amplitude passed";
        else {
            qDebug() << "Min sine amplitude failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (!setSineOutAmplitude(getMaxSineOutAmplitude())) {
            qDebug() << "Lock-in Amplifier sine amplitude command failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (_abs(getSineOutAmplitude() - getMaxSineOutAmplitude()) < this->Err)
            qDebug() << "Max sine amplitude passed";
        else {
            qDebug() << "Max sine amplitude failed";

            ans = false;
        }

        setDefaultSineAmplitude();
        wait();
    }

    if (workWithSineOffset()) {
        qDebug() << "Lock-in Amplifier sine offset command test";

        if (!setSineOffset(getMinSineOffset())) {
            qDebug() << "Lock-in Amplifier sine offset command failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (_abs(getSineOffset() - getMinSineOffset()) < this->Err)
            qDebug() << "Min sine offset passed";
        else {
            qDebug() << "Min sine offset failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (!setSineOffset(getMaxSineOffset())) {
            qDebug() << "Lock-in Amplifier sine offset command failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (_abs(getSineOffset() - getMaxSineOffset()) < this->Err)
            qDebug() << "Max sine amplitude passed";
        else {
            qDebug() << "Max sine amplitude failed";

            ans = false;
        }

        setDefaultSineOffset();
        wait();
    }

    if (workWithReferenceSource()) {
        qDebug() << "Lock-in Amplifier reference source command test";

        foreach (const QString &referenceSource, getReferenceSourceList()) {
            if (!setReferenceSource(referenceSource)) {
                qDebug() << "Lock-in Amplifier reference source command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getReferenceSource() == referenceSource)
                qDebug() << "Reference source passed";
            else {
                qDebug() << "Reference source failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultReferenceSource();
        wait();
    }

    if (workWithReferenceTriggerMode()) {
        qDebug() << "Lock-in Amplifier reference trigger mode command test";

        foreach (const QString &referenceTriggerMode, getReferenceTriggerModeList()) {
            if (!setReferenceTriggerMode(referenceTriggerMode)) {
                qDebug() << "Lock-in Amplifier reference trigger mode command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getReferenceTriggerMode() == referenceTriggerMode)
                qDebug() << "Reference trigger mode passed";
            else {
                qDebug() << "Reference trigger mode failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultReferenceTriggerMode();
        wait();
    }

    if (workWithReferenceTriggerOutputZ()) {
        qDebug() << "Lock-in Amplifier reference trigger output Z command test";

        foreach (const QString &referenceTriggerOutputZ, getReferenceTriggerOutputZList()) {
            if (!setReferenceTriggerOutputZ(referenceTriggerOutputZ)) {
                qDebug() << "Lock-in Amplifier reference trigger output Z command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getReferenceTriggerOutputZ() == referenceTriggerOutputZ)
                qDebug() << "Reference trigger output Z passed";
            else {
                qDebug() << "Reference trigger output Z failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultReferenceTriggerOutputZ();
        wait();
    }

    if (workWithSignalInput()) {
        qDebug() << "Lock-in Amplifier signal input command test";

        if (!setSensivity("10 mV/nA")) {
            qDebug() << "Lock-in Amplifier sensivity command failed";

            ans = false;
        }

        foreach (const QString &signalInput, getSignalInputList()) {
            if (!setSignalInput(signalInput)) {
                qDebug() << "Lock-in Amplifier signal input command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getSignalInput() == signalInput)
                qDebug() << "Signal input passed";
            else {
                qDebug() << "Signal input failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultSignalInput();
        wait();

        setDefaultSensivity();
        wait();
    }

    if (workWithSignalInputZ()) {
        qDebug() << "Lock-in Amplifier signal input Z command test";

        foreach (const QString &signalInputZ, getSignalInputZList()) {
            if (!setSignalInputZ(signalInputZ)) {
                qDebug() << "Lock-in Amplifier signal input Z command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getSignalInputZ() == signalInputZ)
                qDebug() << "Signal input Z passed";
            else {
                qDebug() << "Signal input Z failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultSignalInputZ();
        wait();
    }

    if (workWithVoltageInputMode()) {
        qDebug() << "Lock-in Amplifier voltage input mode command test";

        foreach (const QString &voltageInputMode, getVoltageInputModeList()) {
            if (!setVoltageInputMode(voltageInputMode)) {
                qDebug() << "Lock-in Amplifier voltage input mode command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getVoltageInputMode() == voltageInputMode)
                qDebug() << "Voltage input mode passed";
            else {
                qDebug() << "Voltage input mode failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultVoltageInputMode();
        wait();
    }

    if (workWithVoltageInputCoupling()) {
        qDebug() << "Lock-in Amplifier voltage input coupling command test";

        foreach (const QString &voltageInputCoupling, getVoltageInputCouplingList()) {
            if (!setVoltageInputCoupling(voltageInputCoupling)) {
                qDebug() << "Lock-in Amplifier voltage input coupling command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getVoltageInputCoupling() == voltageInputCoupling)
                qDebug() << "Voltage input coupling passed";
            else {
                qDebug() << "Voltage input coupling failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultVoltageInputCoupling();
        wait();
    }

    if (workWithVoltageInputShields()) {
        qDebug() << "Lock-in Amplifier voltage input shields command test";

        foreach (const QString &voltageInputShield, getVoltageInputShieldsList()) {
            if (!setVoltageInputShields(voltageInputShield)) {
                qDebug() << "Lock-in Amplifier voltage input shields command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getVoltageInputShields() == voltageInputShield)
                qDebug() << "Voltage input shields passed";
            else {
                qDebug() << "Voltage input shields failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultVoltageInputShields();
        wait();
    }

    if (workWithVoltageInputRange()) {
        qDebug() << "Lock-in Amplifier voltage input range command test";

        foreach (const QString &voltageInputRange, getVoltageInputRangeList()) {
            if (!setVoltageInputRange(voltageInputRange)) {
                qDebug() << "Lock-in Amplifier voltage input range command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getVoltageInputRange() == voltageInputRange)
                qDebug() << "Voltage input range passed";
            else {
                qDebug() << "Voltage input range failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultVoltageInputRange();
        wait();
    }

    if (workWithCurrentInputGain()) {
        qDebug() << "Lock-in Amplifier current input gain command test";

        foreach (const QString &currentInputGain, getCurrentInputGainList()) {
            if (!setCurrentInputGain(currentInputGain)) {
                qDebug() << "Lock-in Amplifier current input gain command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getCurrentInputGain() == currentInputGain)
                qDebug() << "Current input gain passed";
            else {
                qDebug() << "Current input gain failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultCurrentInputGain();
        wait();
    }

    if (workWithInputLineNotchFilter()) {
        qDebug() << "Lock-in Amplifier line noch filter command test";

        foreach (const QString &lineNochFilter, getInputLineNotchFilterList()) {
            if (!setInputLineNotchFilter(lineNochFilter)) {
                qDebug() << "Lock-in Amplifier line noch filter command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getInputLineNotchFilter() == lineNochFilter)
                qDebug() << "Line noch filter passed";
            else {
                qDebug() << "Line noch filter failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultInputLineNotchFilter();
        wait();
    }

    if (workWithSensivity()) {
        qDebug() << "Lock-in Amplifier sensivity command test";

        foreach (const QString &sensivity, getSensivityList()) {
            if (!setSensivity(sensivity)) {
                qDebug() << "Lock-in Amplifier sensivity command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getSensivity() == sensivity)
                qDebug() << "Sensivity passed";
            else {
                qDebug() << "Sensivity failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultSensivity();
        wait();
    }

    if (workWithReserveMode()) {
        qDebug() << "Lock-in Amplifier reserve mode command test";

        foreach (const QString &reserveMode, getReserveModeList()) {
            if (!setReserveMode(reserveMode)) {
                qDebug() << "Lock-in Amplifier reserve mode command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getReserveMode() == reserveMode)
                qDebug() << "Reserve mode passed";
            else {
                qDebug() << "Reserve mode failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultReserveMode();
        wait();
    }

    if (workWithWideReserveMode()) {
        qDebug() << "Lock-in Amplifier wide reserve mode command test";

        foreach (const QString &wideReserveMode, getWideReserveModeList()) {
            if (!setWideReserveMode(wideReserveMode)) {
                qDebug() << "Lock-in Amplifier wide reserve mode command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getWideReserveMode() == wideReserveMode)
                qDebug() << "Wide reserve mode passed";
            else {
                qDebug() << "Wide reserve mode failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultWideReserveMode();
        wait();
    }

    if (workWithWideReserveMode()) {
        qDebug() << "Lock-in Amplifier close reserve mode command test";

        foreach (const QString &closeReserveMode, getCloseReserveModeList()) {
            if (!setCloseReserveMode(closeReserveMode)) {
                qDebug() << "Lock-in Amplifier close reserve mode command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getCloseReserveMode() == closeReserveMode)
                qDebug() << "Close reserve mode passed";
            else {
                qDebug() << "Close reserve mode failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultCloseReserveMode();
        wait();
    }

    if (workWithTimeConstant()) {
        qDebug() << "Lock-in Amplifier time constant command test";

        if (!setReferenceSource("INT")) {
            qDebug() << "Lock-in Amplifier reference command failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        if (!setInternalFrequency(getMinInternalFrequency())) {
            qDebug() << "Lock-in Amplifier min internal frequency command failed";

            ans = false;
        }

        if (this->lockInAmplifierModel != "SR865")
            wait(this->longWait);

        foreach (const QString &timeConstant, getTimeConstantList()) {
            if (!setTimeConstant(timeConstant)) {
                qDebug() << "Lock-in Amplifier time constant command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getTimeConstant() == timeConstant)
                qDebug() << "Time constant passed";
            else {
                qDebug() << "Time constant failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultTimeConstant();
        wait();

        setDefaultInternalFrequency();
        wait();

        setDefaultReferenceSource();
        wait();
    }

    if (workWithFilter()) {
        qDebug() << "Lock-in Amplifier filter command test";

        foreach (const QString &filter, getFilterList()) {
            if (!setFilter(filter)) {
                qDebug() << "Lock-in Amplifier filter command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getFilter() == filter)
                qDebug() << "Filter passed";
            else {
                qDebug() << "Filter failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultFilter();
        wait();
    }

    if (workWithSynchronousFilter()) {
        qDebug() << "Lock-in Amplifier synchronous filter command test";

        for (int i = 1;i >= 0;i--) {
            if (i == 0)
                qDebug() << "Lock-in Amplifier synchronous filter disbling";
            else
                qDebug() << "Lock-in Amplifier synchronous filter enabling";

            if (!enableSynchronousFilter(i)) {
                qDebug() << "Lock-in Amplifier synchronous filter comand failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getSynchronousFilterEnabled() == (bool) i)
                qDebug() << "Lock-in Amplifier synchronous filter settings accepted";
            else {
                qDebug() << "Lock-in Amplifier synchronous filter settings not accepted";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultSynchronousFilter();
        wait();
    }

    if (workWithAdvancedFilter()) {
        qDebug() << "Lock-in Amplifier advanced filter command test";

        for (int i = 1;i >= 0;i--) {
            if (i == 0)
                qDebug() << "Lock-in Amplifier advanced filter disbling";
            else
                qDebug() << "Lock-in Amplifier advanced filter enabling";

            if (!enableAdvancedFilter(i)) {
                qDebug() << "Lock-in Amplifier advanced filter comand failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getAdvancedFilterEnabled() == (bool) i)
                qDebug() << "Lock-in Amplifier advanced filter settings accepted";
            else {
                qDebug() << "Lock-in Amplifier advanced filter settings not accepted";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultAdvancedFilter();
        wait();
    }

    if (workWithSampleRate()) {
        qDebug() << "Lock-in Amplifier sample rate command test";

        foreach (const QString &sampleRate, getSampleRateList()) {
            if (!setSampleRate(sampleRate)) {
                qDebug() << "Lock-in Amplifier sample rate command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getSampleRate() == sampleRate)
                qDebug() << "Sample rate passed";
            else {
                qDebug() << "Sample rate failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultSampleRate();
        wait();
    }

    if (workWithBufferMode()) {
        qDebug() << "Lock-in Amplifier buffer mode command test";

        foreach (const QString &bufferMode, getBufferModeList()) {
            if (!setBufferMode(bufferMode)) {
                qDebug() << "Lock-in Amplifier buffer mode command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);

            if (getBufferMode() == bufferMode)
                qDebug() << "Buffer mode passed";
            else {
                qDebug() << "Buffer mode failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        setDefaultBufferMode();
        wait();
    }

    if (true) {
        qDebug() << "Lock-in Amplifier output command test";

        foreach (const QString &output, getOutputNumberList()) {
            if (abs(getOUTP(output)-(-1)) <= this->Err) {
                qDebug() << "Lock-in Amplifier output command failed";

                ans = false;
            }

            if (this->lockInAmplifierModel != "SR865")
                wait(this->longWait);
        }

        wait();
    }

    return ans;
}

bool LockInAmplifier::setDefaultSettings() const
{
    bool ans = true;

    if (workWithInternalFrequency())
        ans &= setDefaultInternalFrequency();
    if (workWithHarmonic())
        ans &= setDefaultHarmonic();
    if (workWithHarmonicDual())
        ans &= setDefaultHarmonicDual();
    if (workWithSineOutAmplitude())
        ans &= setDefaultSineAmplitude();
    if (workWithSineOffset())
        ans &= setDefaultSineOffset();
    if (workWithReferenceSource())
        ans &= setDefaultReferenceSource();
    if (workWithReferenceTriggerMode())
        ans &= setDefaultReferenceTriggerMode();
    if (workWithReferenceTriggerOutputZ())
        ans &= setDefaultReferenceTriggerOutputZ();
    if (workWithSignalInput())
        ans &= setDefaultSignalInput();
    if (workWithSignalInputZ())
        ans &= setDefaultSignalInputZ();
    if (workWithVoltageInputMode())
        ans &= setDefaultVoltageInputMode();
    if (workWithVoltageInputCoupling())
        ans &= setDefaultVoltageInputCoupling();
    if (workWithVoltageInputShields())
        ans &= setDefaultVoltageInputShields();
    if (workWithVoltageInputRange())
        ans &= setDefaultVoltageInputRange();
    if (workWithCurrentInputGain())
        ans &= setDefaultCurrentInputGain();
    if (workWithInputLineNotchFilter())
        ans &= setDefaultInputLineNotchFilter();
    if (workWithSensivity())
        ans &= setDefaultSensivity();
    if (workWithReserveMode())
        ans &= setDefaultReserveMode();
    if (workWithWideReserveMode())
        ans &= setDefaultWideReserveMode();
    if (workWithCloseReserveMode())
        ans &= setDefaultCloseReserveMode();
    if (workWithTimeConstant())
        ans &= setDefaultTimeConstant();
    if (workWithFilter())
        ans &= setDefaultFilter();
    if (workWithSynchronousFilter())
        ans &= setDefaultSynchronousFilter();
    if (workWithAdvancedFilter())
        ans &= setDefaultAdvancedFilter();
    if (workWithEnablingRS232outputInterface())
        ans &= setDefaultRS232outputInterface();
    if (workWithSampleRate())
        ans &= setDefaultSampleRate();
    if (workWithBufferMode())
        ans &= setDefaultBufferMode();

    return ans;
}

double LockInAmplifier::getAverageInputTime() const
{
    if (this->lockInAmplifierModel == "SR830")
        return 1;
    if (this->lockInAmplifierModel == "SR844")
        return 1;
    if (this->lockInAmplifierModel == "SR865")
        return 1;
    return 1E5;
}

double LockInAmplifier::getAverageOutputTime() const
{
    if (this->lockInAmplifierModel == "SR830")
        return 50;
    if (this->lockInAmplifierModel == "SR844")
        return 50;
    if (this->lockInAmplifierModel == "SR865")
        return 150;
    return 1E5;
}

bool LockInAmplifier::workWithFrequencyPostfix() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

QString LockInAmplifier::getDefaultFrequencyPostfix() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return "HZ";
    return "";
}

QStringList LockInAmplifier::getFrequencyPostfixList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return QStringList();
    if (this->lockInAmplifierModel == "SR844")
        return QStringList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getFrequencyPostfixList();
    return QStringList();
}

bool LockInAmplifier::workWithVoltagePostfix() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

QString LockInAmplifier::getDefaultVoltagePostfix() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return "V";
    return "";
}

QStringList LockInAmplifier::getVoltagePostfixList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return QStringList();
    if (this->lockInAmplifierModel == "SR844")
        return QStringList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getVoltagePostfixList();
    return QStringList();
}

bool LockInAmplifier::workWithInternalFrequency() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

double LockInAmplifier::getDefaultInternalFrequency() const
{
    if (this->lockInAmplifierModel == "SR830")
        return 100000;
    if (this->lockInAmplifierModel == "SR844")
        return 100000;
    if (this->lockInAmplifierModel == "SR865")
        return 100000;
    return 0;
}

bool LockInAmplifier::setDefaultInternalFrequency() const
{
    return setInternalFrequency(getDefaultInternalFrequency(), getDefaultFrequencyPostfix());
}

bool LockInAmplifier::isValidInternalFrequency(const double &frequency, const QString &postfix) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->isValidInternalFrequency(frequency);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->isValidInternalFrequency(frequency);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->isValidInternalFrequency(frequency, postfix);
    return false;
}

double LockInAmplifier::getMinInternalFrequency() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getMinInternalFrequency();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getMinInternalFrequency();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getMinInternalFrequency();
    return -1;
}

double LockInAmplifier::getMaxInternalFrequency() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getMaxInternalFrequency();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getMaxInternalFrequency();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getMaxInternalFrequency();
    return -1;
}

bool LockInAmplifier::setInternalFrequency(const double &frequency, const QString &postfix) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setInternalFrequency(frequency);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setInternalFrequency(frequency);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setInternalFrequency(frequency, postfix);
    return false;
}

double LockInAmplifier::getInternalFrequency() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getFrequency();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getFrequency();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getInternalFrequency();
    return -1;
}

double LockInAmplifier::getExternalFrequency() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getFrequency();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getFrequency();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getExternalFrequency();
    return -1;
}

double LockInAmplifier::getFrequency() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getFrequency();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getFrequency();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getFrequency();
    return -1;
}

double LockInAmplifier::getFrequencyDetect() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getFrequency();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getFrequencyDetect();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getFrequencyDetect();
    return -1;
}

bool LockInAmplifier::workWithHarmonic() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

int LockInAmplifier::getDefaultHarmonic() const
{
    if (this->lockInAmplifierModel == "SR830")
        return 1;
    if (this->lockInAmplifierModel == "SR844")
        return 1;
    if (this->lockInAmplifierModel == "SR865")
        return 1;
    return -1;
}

bool LockInAmplifier::setDefaultHarmonic() const
{
    return setHarmonic(getDefaultHarmonic());
}

int LockInAmplifier::getMinHarmonic() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getMinHarmonic();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getMinHarmonic();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getMinHarmonic();
    return -1;
}

int LockInAmplifier::getMaxHarmonic() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getMaxHarmonic();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getMaxHarmonic();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getMaxHarmonic();
    return -1;
}

bool LockInAmplifier::isValidHarmonic(const int &i) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->isValidHarmonic(i);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->isValidHarmonic(i);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->isValidHarmonic(i);
    return false;
}

bool LockInAmplifier::setHarmonic(const int &i) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setHarmonic(i);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setHarmonic(i);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setHarmonic(i);
    return false;
}

int LockInAmplifier::getHarmonic() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getHarmonic();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getHarmonic();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getHarmonic();
    return -1;
}

bool LockInAmplifier::workWithHarmonicDual() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

int LockInAmplifier::getDefaultHarmonicDual() const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return 1;
    return -1;
}

bool LockInAmplifier::setDefaultHarmonicDual() const
{
    return setHarmonicDual(getDefaultHarmonicDual());
}

int LockInAmplifier::getMinHarmonicDual() const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getMinHarmonicDual();
    return -1;
}

int LockInAmplifier::getMaxHarmonicDual() const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getMaxHarmonicDual();
    return -1;
}

bool LockInAmplifier::isValidHarmonicDual(const int &i) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->isValidHarmonicDual(i);
    return false;
}

bool LockInAmplifier::setHarmonicDual(const int &i) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setHarmonicDual(i);
    return false;
}

int LockInAmplifier::getHarmonicDual() const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getHarmonicDual();
    return -1;
}

bool LockInAmplifier::workWithSineOutAmplitude() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

double LockInAmplifier::getDefaultSineAmplitude() const
{
    if (this->lockInAmplifierModel == "SR830")
        return 0.1;
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return 0.1;
    return -1;
}

bool LockInAmplifier::setDefaultSineAmplitude() const
{
    return setSineOutAmplitude(getDefaultSineAmplitude());
}

bool LockInAmplifier::isValidSineOutAmplitude(const double &sineAmplitude, const QString &postfix) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->isValidSineOutAmplitude(sineAmplitude);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->isValidSineOutAmplitude(sineAmplitude, postfix);
    return false;
}

double LockInAmplifier::getMinSineOutAmplitude() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getMinSineOutAmplitude();
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getMinSineOutAmplitude();
    return -1;
}

double LockInAmplifier::getMaxSineOutAmplitude() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getMaxSineOutAmplitude();
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getMaxSineOutAmplitude();
    return -1;
}

bool LockInAmplifier::setSineOutAmplitude(const double &sineAmplitude, const QString &postfix) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setSineOutAmplitude(sineAmplitude);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setSineOutAmplitude(sineAmplitude, postfix);
    return false;
}

double LockInAmplifier::getSineOutAmplitude() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getSineOutAmplitude();
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getSineOutAmplitude();
    return -1;
}

bool LockInAmplifier::workWithSineOffset() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

double LockInAmplifier::getDefaultSineOffset() const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return 0;
    return -1;
}

bool LockInAmplifier::setDefaultSineOffset() const
{
    return setSineOffset(getDefaultSineOffset());
}

bool LockInAmplifier::isValidSineOffset(const double &offset, const QString &postfix) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->isValidSineOffset(offset, postfix);
    return false;
}

double LockInAmplifier::getMinSineOffset() const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getMinSineOffset();
    return -1;
}

double LockInAmplifier::getMaxSineOffset() const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getMaxSineOffset();
    return -1;
}

bool LockInAmplifier::setSineOffset(const double &offset, const QString &postfix) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setSineOffset(offset, postfix);
    return false;
}

double LockInAmplifier::getSineOffset() const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getSineOffset();
    return -1;
}

bool LockInAmplifier::workWithReferenceSource() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

QString LockInAmplifier::getDefaultReferenceSource() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "EXT";
    if (this->lockInAmplifierModel == "SR844")
        return "EXT";
    if (this->lockInAmplifierModel == "SR865")
        return "EXT";
    return "";
}

bool LockInAmplifier::setDefaultReferenceSource() const
{
    return setReferenceSource(getDefaultReferenceSource());
}

QStringList LockInAmplifier::getReferenceSourceList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getReferenceSourceList();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getReferenceSourceList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getReferenceSourceList();
    return QStringList();
}

int LockInAmplifier::refSourceNumberFromString(const QString &ref_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->refSourceNumberFromString(ref_string);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->refSourceNumberFromString(ref_string);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->refSourceNumberFromString(ref_string);
    return -1;
}

QString LockInAmplifier::refSourceStringFromNumber(const int &ref_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->refSourceStringFromNumber(ref_number);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->refSourceStringFromNumber(ref_number);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->refSourceStringFromNumber(ref_number);
    return "";
}

bool LockInAmplifier::setReferenceSource(const int &source) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setReferenceSource(source);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setReferenceSource(source);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setReferenceSource(source);
    return false;
}

bool LockInAmplifier::setReferenceSource(const QString &source) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setReferenceSource(source);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setReferenceSource(source);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setReferenceSource(source);
    return false;
}

QString LockInAmplifier::getReferenceSource() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getReferenceSource();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getReferenceSource();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getReferenceSource();
    return "";
}

bool LockInAmplifier::workWithReferenceTriggerMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

QString LockInAmplifier::getDefaultReferenceTriggerMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "TTL Rising";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return "POSTTL";
    return "";
}

bool LockInAmplifier::setDefaultReferenceTriggerMode() const
{
    return setReferenceTriggerMode(getDefaultReferenceTriggerMode());
}

QStringList LockInAmplifier::getReferenceTriggerModeList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getReferenceTriggerModeList();
    if (this->lockInAmplifierModel == "SR844")
        return QStringList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getReferenceTriggerModeList();
    return QStringList();
}

int LockInAmplifier::refModeNumberFromString(const QString &mode_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->refModeNumberFromString(mode_string);
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->refModeNumberFromString(mode_string);
    return -1;
}

QString LockInAmplifier::refModeStringFromNumber(const int &mode_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->refModeStringFromNumber(mode_number);
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->refModeStringFromNumber(mode_number);
    return "";
}

bool LockInAmplifier::setReferenceTriggerMode(const int &mode) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setReferenceTriggerMode(mode);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setReferenceTriggerMode(mode);
    return false;
}

bool LockInAmplifier::setReferenceTriggerMode(const QString &mode) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setReferenceTriggerMode(mode);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setReferenceTriggerMode(mode);
    return false;
}

QString LockInAmplifier::getReferenceTriggerMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getReferenceTriggerMode();
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getReferenceTriggerMode();
    return "";
}

bool LockInAmplifier::workWithReferenceTriggerOutputZ() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

QString LockInAmplifier::getDefaultReferenceTriggerOutputZ() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return "50Ohms";
    if (this->lockInAmplifierModel == "SR865")
        return "50OHMS";
    return "";
}

bool LockInAmplifier::setDefaultReferenceTriggerOutputZ() const
{
    return setReferenceTriggerOutputZ(getDefaultReferenceTriggerOutputZ());
}

QStringList LockInAmplifier::getReferenceTriggerOutputZList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return QStringList();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getReferenceTriggerOutputZList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getReferenceTriggerOutputZList();
    return QStringList();
}

int LockInAmplifier::refOutputNumberFromString(const QString &outpZ_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->refTriggerOutputZNumberFromString(outpZ_string);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->refOutputZNumberFromString(outpZ_string);
    return -1;
}

QString LockInAmplifier::refOutputStringFromNumber(const int &outpZ_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->refTriggerOutputZStringFromNumber(outpZ_number);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->refOutputZStringFromNumber(outpZ_number);
    return "";
}

bool LockInAmplifier::setReferenceTriggerOutputZ(const int &outpZ) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setReferenceTriggerOutputZ(outpZ);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setReferenceTriggerOutputZ(outpZ);
    return false;
}

bool LockInAmplifier::setReferenceTriggerOutputZ(const QString &outpZ) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setReferenceTriggerOutputZ(outpZ);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setReferenceTriggerOutputZ(outpZ);
    return false;
}

QString LockInAmplifier::getReferenceTriggerOutputZ() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getReferenceTriggerOutputZ();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getReferenceTriggerOutputZ();
    return "";
}

bool LockInAmplifier::workWithSignalInput() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

QString LockInAmplifier::getDefaultSignalInput() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "Vol A";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return "VOLTAGE";
    return "";
}

bool LockInAmplifier::setDefaultSignalInput() const
{
    return setSignalInput(getDefaultSignalInput());
}

QStringList LockInAmplifier::getSignalInputList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getSignalInputList();
    if (this->lockInAmplifierModel == "SR844")
        return QStringList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getSignalInputList();
    return QStringList();
}

int LockInAmplifier::signalInputNumberFromString(const QString &signalInput_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->signalInputNumberFromString(signalInput_string);
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->signalInputNumberFromString(signalInput_string);
    return -1;
}

QString LockInAmplifier::signalInputStringFromNumber(const int &signalInput_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->signalInputStringFromNumber(signalInput_number);
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->signalInputStringFromNumber(signalInput_number);
    return "";
}

bool LockInAmplifier::setSignalInput(const int &signalInput) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setSignalInput(signalInput);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setSignalInput(signalInput);
    return false;
}

bool LockInAmplifier::setSignalInput(const QString &signalInput) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setSignalInput(signalInput);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setSignalInput(signalInput);
    return false;
}

QString LockInAmplifier::getSignalInput() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getSignalInput();
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getSignalInput();
    return "";
}

bool LockInAmplifier::workWithSignalInputZ() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

QString LockInAmplifier::getDefaultSignalInputZ() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return "1MOhms";
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::setDefaultSignalInputZ() const
{
    return setSignalInputZ(getDefaultSignalInputZ());
}

QStringList LockInAmplifier::getSignalInputZList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return QStringList();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getSignalInputZList();
    if (this->lockInAmplifierModel == "SR865")
        return QStringList();
    return QStringList();
}

int LockInAmplifier::signalInputZNumberFromString(const QString &signalInputZ_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->signalInputZNumberFromString(signalInputZ_string);
    if (this->lockInAmplifierModel == "SR865")
        return -1;
    return -1;
}

QString LockInAmplifier::signalInputZStringFromNumber(const int &signalInputZ_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->signalInputZStringFromNumber(signalInputZ_number);
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::setSignalInputZ(const int &signalInputZ) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setSignalInputZ(signalInputZ);
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::setSignalInputZ(const QString &signalInputZ) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setSignalInputZ(signalInputZ);
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

QString LockInAmplifier::getSignalInputZ() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getSignalInputZ();
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::workWithVoltageInputMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

QString LockInAmplifier::getDefaultVoltageInputMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return "A";
    return "";
}

bool LockInAmplifier::setDefaultVoltageInputMode() const
{
    return setVoltageInputMode(getDefaultVoltageInputMode());
}

QStringList LockInAmplifier::getVoltageInputModeList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return QStringList();
    if (this->lockInAmplifierModel == "SR844")
        return QStringList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getVoltageInputModeList();
    return QStringList();
}

int LockInAmplifier::voltageInputModeNumberFromString(const QString &voltageInputMode_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->voltageInputModeNumberFromString(voltageInputMode_string);
    return -1;
}

QString LockInAmplifier::voltageInputModeStringFromNumber(const int &voltageInputMode_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->voltageInputModeStringFromNumber(voltageInputMode_number);
    return "";
}

bool LockInAmplifier::setVoltageInputMode(const int &voltageInputMode) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setVoltageInputMode(voltageInputMode);
    return false;
}

bool LockInAmplifier::setVoltageInputMode(const QString &voltageInputMode) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setVoltageInputMode(voltageInputMode);
    return false;
}

QString LockInAmplifier::getVoltageInputMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getVoltageInputMode();
    return "";
}

bool LockInAmplifier::workWithVoltageInputCoupling() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

QString LockInAmplifier::getDefaultVoltageInputCoupling() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "AC";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return "AC";
    return "";
}

bool LockInAmplifier::setDefaultVoltageInputCoupling() const
{
    return setVoltageInputCoupling(getDefaultVoltageInputCoupling());
}

QStringList LockInAmplifier::getVoltageInputCouplingList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getVoltageInputCouplingList();
    if (this->lockInAmplifierModel == "SR844")
        return QStringList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getVoltageInputCouplingList();
    return QStringList();
}

int LockInAmplifier::voltageInputCouplingNumberFromString(const QString &voltageInputCoupling_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->voltageInputCouplingNumberFromString(voltageInputCoupling_string);
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->voltageInputCouplingNumberFromString(voltageInputCoupling_string);
    return -1;
}

QString LockInAmplifier::voltageInputCouplingStringFromNumber(const int &voltageInputCoupling_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->voltageInputCouplingStringFromNumber(voltageInputCoupling_number);
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->voltageInputCouplingStringFromNumber(voltageInputCoupling_number);
    return "";
}

bool LockInAmplifier::setVoltageInputCoupling(const int &voltageInputCoupling) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setVoltageInputCoupling(voltageInputCoupling);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setVoltageInputCoupling(voltageInputCoupling);
    return false;
}

bool LockInAmplifier::setVoltageInputCoupling(const QString &voltageInputCoupling) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setVoltageInputCoupling(voltageInputCoupling);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setVoltageInputCoupling(voltageInputCoupling);
    return false;
}

QString LockInAmplifier::getVoltageInputCoupling() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getVoltageInputCoupling();
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getVoltageInputCoupling();
    return "";
}

bool LockInAmplifier::workWithVoltageInputShields() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

QString LockInAmplifier::getDefaultVoltageInputShields() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "GROUND";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return "GROUND";
    return "";
}

bool LockInAmplifier::setDefaultVoltageInputShields() const
{
    return setVoltageInputShields(getDefaultVoltageInputShields());
}

QStringList LockInAmplifier::getVoltageInputShieldsList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getVoltageInputShieldsList();
    if (this->lockInAmplifierModel == "SR844")
        return QStringList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getVoltageInputShieldsList();
    return QStringList();
}

int LockInAmplifier::voltageInputShieldsNumberFromString(const QString &voltageInputShields_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->voltageInputShieldsNumberFromString(voltageInputShields_string);
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->voltageInputShieldsNumberFromString(voltageInputShields_string);
    return -1;
}

QString LockInAmplifier::voltageInputShieldsStringFromNumber(const int &voltageInputShields_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->voltageInputShieldsStringFromNumber(voltageInputShields_number);
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->voltageInputShieldsStringFromNumber(voltageInputShields_number);
    return "";
}

bool LockInAmplifier::setVoltageInputShields(const int &voltageInputShields) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setVoltageInputShields(voltageInputShields);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setVoltageInputShields(voltageInputShields);
    return false;
}

bool LockInAmplifier::setVoltageInputShields(const QString &voltageInputShields) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setVoltageInputShields(voltageInputShields);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setVoltageInputShields(voltageInputShields);
    return false;
}

QString LockInAmplifier::getVoltageInputShields() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getVoltageInputShields();
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getVoltageInputShields();
    return "";
}

bool LockInAmplifier::workWithVoltageInputRange() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

QString LockInAmplifier::getDefaultVoltageInputRange() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return "1V";
    return "";
}

bool LockInAmplifier::setDefaultVoltageInputRange() const
{
    return setVoltageInputRange(getDefaultVoltageInputRange());
}

QStringList LockInAmplifier::getVoltageInputRangeList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return QStringList();
    if (this->lockInAmplifierModel == "SR844")
        return QStringList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getVoltageInputRangeList();
    return QStringList();
}

int LockInAmplifier::voltageInputRangeNumberFromString(const QString &voltageInputRange_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->voltageInputRangeNumberFromString(voltageInputRange_string);
    return -1;
}

QString LockInAmplifier::voltageInputRangeStringFromNumber(const int &voltageInputRange_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->voltageInputRangeStringFromNumber(voltageInputRange_number);
    return "";
}

bool LockInAmplifier::setVoltageInputRange(const int &voltageInputRange) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setVoltageInputRange(voltageInputRange);
    return false;
}

bool LockInAmplifier::setVoltageInputRange(const QString &voltageInputRange) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setVoltageInputRange(voltageInputRange);
    return false;
}

QString LockInAmplifier::getVoltageInputRange() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getVoltageInputRange();
    return "";
}

QString LockInAmplifier::getAutoVoltageInputRange(const double &r) const
{
    if (this->lockInAmplifierModel != "SR865")
        return "";

    double temp_r = r*this->inputRangeReserve;
    if (temp_r < 0.01)
            return "10M";
    if (temp_r < 0.03)
            return "30M";
    if (temp_r < 0.1)
            return "10M";
    if (temp_r < 0.3)
            return "30M";
    return "1V";
}

bool LockInAmplifier::setAutoVoltageInputRange(const double &r) const
{
    return setVoltageInputRange(getAutoVoltageInputRange(r));
}

bool LockInAmplifier::workWithCurrentInputGain() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

QString LockInAmplifier::getDefaultCurrentInputGain() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return "1uA";
    return "";
}

bool LockInAmplifier::setDefaultCurrentInputGain() const
{
    return setCurrentInputGain(getDefaultCurrentInputGain());
}

QStringList LockInAmplifier::getCurrentInputGainList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return QStringList();
    if (this->lockInAmplifierModel == "SR844")
        return QStringList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getCurrentInputGainList();
    return QStringList();
}

int LockInAmplifier::currentInputGainNumberFromString(const QString &currentInputGain_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->currentInputGainNumberFromString(currentInputGain_string);
    return -1;
}

QString LockInAmplifier::currentInputGainStringFromNumber(const int &currentInputGain_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->currentInputGainStringFromNumber(currentInputGain_number);
    return "";
}

bool LockInAmplifier::setCurrentInputGain(const int &currentInputGain) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setCurrentInputGain(currentInputGain);
    return false;
}

bool LockInAmplifier::setCurrentInputGain(const QString &currentInputGain) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setCurrentInputGain(currentInputGain);
    return false;
}

QString LockInAmplifier::getCurrentInputGain() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getCurrentInputGain();
    return "";
}

bool LockInAmplifier::workWithSignalStrength() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

int LockInAmplifier::getSignalStrength() const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getSignalStrength();
    return -1;
}

bool LockInAmplifier::workWithInputLineNotchFilter() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

QString LockInAmplifier::getDefaultInputLineNotchFilter() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "No filter";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::setDefaultInputLineNotchFilter() const
{
    return setInputLineNotchFilter(getDefaultInputLineNotchFilter());
}

QStringList LockInAmplifier::getInputLineNotchFilterList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getInputLineNotchFilterList();
    if (this->lockInAmplifierModel == "SR844")
        return QStringList();
    if (this->lockInAmplifierModel == "SR865")
        return QStringList();
    return QStringList();
}

int LockInAmplifier::inputLineNotchFilterNumberFromString(const QString &inputLineNotchFilter_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->inputLineNotchFilterNumberFromString(inputLineNotchFilter_string);
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return -1;
    return -1;
}

QString LockInAmplifier::inputLineNotchFilterStringFromNumber(const int &inputLineNotchFilter_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->inputLineNotchFilterStringFromNumber(inputLineNotchFilter_number);
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::setInputLineNotchFilter(const int &inputLineNotchFilter) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setInputLineNotchFilter(inputLineNotchFilter);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::setInputLineNotchFilter(const QString &inputLineNotchFilter) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setInputLineNotchFilter(inputLineNotchFilter);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

QString LockInAmplifier::getInputLineNotchFilter() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getInputLineNotchFilter();
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::workWithSensivity() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

QString LockInAmplifier::getDefaultSensivity() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "1 V/uA";
    if (this->lockInAmplifierModel == "SR844")
        return "1 V/uA";
    if (this->lockInAmplifierModel == "SR865")
        return "1 V/uA";
    return "";
}

bool LockInAmplifier::setDefaultSensivity() const
{
    return setSensivity(getDefaultSensivity());
}

QStringList LockInAmplifier::getSensivityList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getSensivityList();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getSensivityList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getSensivityList();
    return QStringList();
}

int LockInAmplifier::sensivityNumberFromString(const QString &sensivity_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->sensivityNumberFromString(sensivity_string);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->sensivityNumberFromString(sensivity_string);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->sensivityNumberFromString(sensivity_string);
    return -1;
}

QString LockInAmplifier::sensivityStringFromNumber(const int &sensivity_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->sensivityStringFromNumber(sensivity_number);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->sensivityStringFromNumber(sensivity_number);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->sensivityStringFromNumber(sensivity_number);
    return "";
}

bool LockInAmplifier::setSensivity(const int &sensivity) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setSensivity(sensivity);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setSensivity(sensivity);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setSensivity(sensivity);
    return false;
}

bool LockInAmplifier::setSensivity(const QString &sensivity) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setSensivity(sensivity);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setSensivity(sensivity);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setSensivity(sensivity);
    return false;
}

QString LockInAmplifier::getSensivity() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getSensivity();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getSensivity();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getSensivity();
    return "";
}

QString LockInAmplifier::getAutoSensivity(const double &r) const
{
    double temp_r = r*this->sensivityReserve;

    if (temp_r < 1E-9)
        if (this->lockInAmplifierModel == "SR865")
            return "1 nV/fA";
    if (temp_r < 2E-9)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return   "2 nV/fA";
    if (temp_r < 5E-9)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return   "5 nV/fA";
    if (temp_r < 1E-8)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return  "10 nV/fA";
    if (temp_r < 2E-8)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return  "20 nV/fA";
    if (temp_r < 5E-8)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return  "50 nV/fA";
    if (temp_r < 1E-7)
        return "100 nV/fA";
    if (temp_r < 2E-7)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return "200 nV/fA";
    if (temp_r < 3E-7)
        if (this->lockInAmplifierModel == "SR844")
            return "300 nV/fA";
    if (temp_r < 5E-7)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return "500 nV/fA";
    if (temp_r < 1E-6)
        return   "1 uV/pA";
    if (temp_r < 2E-6)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return   "2 uV/pA";
    if (temp_r < 3E-6)
        if (this->lockInAmplifierModel == "SR844")
            return "3 uV/pA";
    if (temp_r < 5E-6)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return   "5 uV/pA";
    if (temp_r < 1E-5)
        return  "10 uV/pA";
    if (temp_r < 2E-5)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return  "20 uV/pA";
    if (temp_r < 3E-5)
        if (this->lockInAmplifierModel == "SR844")
            return "30 uV/pA";
    if (temp_r < 5E-5)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return  "50 uV/pA";
    if (temp_r < 1E-4)
        return "100 uV/pA";
    if (temp_r < 2E-4)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return "200 uV/pA";
    if (temp_r < 3E-4)
        if (this->lockInAmplifierModel == "SR844")
            return "300 uV/pA";
    if (temp_r < 5E-4)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return "500 uV/pA";
    if (temp_r < 1E-3)
        return   "1 mV/nA";
    if (temp_r < 2E-3)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return   "2 mV/nA";
    if (temp_r < 3E-3)
        if (this->lockInAmplifierModel == "SR844")
            return "3 mV/nA";
    if (temp_r < 5E-3)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return   "5 mV/nA";
    if (temp_r < 1E-2)
        return  "10 mV/nA";
    if (temp_r < 2E-2)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return  "20 mV/nA";
    if (temp_r < 3E-2)
        if (this->lockInAmplifierModel == "SR844")
            return "30 mV/nA";
    if (temp_r < 5E-2)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return  "50 mV/nA";
    if (temp_r < 1E-1)
        return "100 mV/nA";
    if (temp_r < 2E-1)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return "200 mV/nA";
    if (temp_r < 3E-1)
        if (this->lockInAmplifierModel == "SR844")
            return "300 mV/nA";
    if (temp_r < 5E-1)
        if (this->lockInAmplifierModel == "SR865" ||
            this->lockInAmplifierModel == "SR830")
            return "500 mV/nA";
    return "1 V/uA";
}

bool LockInAmplifier::setAutoSensivity(const double &r) const
{
    return setSensivity(getAutoSensivity(r));
}

bool LockInAmplifier::workWithReserveMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

QString LockInAmplifier::getDefaultReserveMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "Normal";
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::setDefaultReserveMode() const
{
    return setReserveMode(getDefaultReserveMode());
}

QStringList LockInAmplifier::getReserveModeList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getReserveModeList();
    if (this->lockInAmplifierModel == "SR844")
        return QStringList();
    if (this->lockInAmplifierModel == "SR865")
        return QStringList();
    return QStringList();
}

int LockInAmplifier::reserveModeNumberFromString(const QString &reserveMode_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->reserveModeNumberFromString(reserveMode_string);
    if (this->lockInAmplifierModel == "SR844")
        return -1;
    if (this->lockInAmplifierModel == "SR865")
        return -1;
    return -1;
}

QString LockInAmplifier::reserveModeStringFromNumber(const int &reserveMode_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->reserveModeStringFromNumber(reserveMode_number);
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::setReserveMode(const int &reserveMode) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setReserveMode(reserveMode);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::setReserveMode(const QString &reserveMode) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setReserveMode(reserveMode);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

QString LockInAmplifier::getReserveMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getReserveMode();
    if (this->lockInAmplifierModel == "SR844")
        return "";
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::workWithWideReserveMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

QString LockInAmplifier::getDefaultWideReserveMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return "Normal";
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::setDefaultWideReserveMode() const
{
    return setWideReserveMode(getDefaultWideReserveMode());
}

QStringList LockInAmplifier::getWideReserveModeList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return QStringList();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getWideReserveModeList();
    if (this->lockInAmplifierModel == "SR865")
        return QStringList();
    return QStringList();
}

int LockInAmplifier::wideReserveModeNumberFromString(const QString &wideReserveMode_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->wideReserveModeNumberFromString(wideReserveMode_string);
    if (this->lockInAmplifierModel == "SR865")
        return -1;
    return -1;
}

QString LockInAmplifier::wideReserveModeStringFromNumber(const int &wideReserveMode_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->wideReserveModeStringFromNumber(wideReserveMode_number);
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::setWideReserveMode(const int &wideReserveMode) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setWideReserveMode(wideReserveMode);
    if (this->lockInAmplifierModel == "Sr865")
        return false;
    return false;
}

bool LockInAmplifier::setWideReserveMode(const QString &wideReserveMode) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setWideReserveMode(wideReserveMode);
    if (this->lockInAmplifierModel == "Sr865")
        return false;
    return false;
}

QString LockInAmplifier::getWideReserveMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getWideReserveMode();
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::workWithCloseReserveMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

QString LockInAmplifier::getDefaultCloseReserveMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return "Normal";
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::setDefaultCloseReserveMode() const
{
    return setCloseReserveMode(getDefaultCloseReserveMode());
}

QStringList LockInAmplifier::getCloseReserveModeList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return QStringList();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getCloseReserveModeList();
    if (this->lockInAmplifierModel == "SR865")
        return QStringList();
    return QStringList();
}

int LockInAmplifier::closeReserveModeNumberFromString(const QString &closeReserveMode_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return -1;
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->closeReserveModeNumberFromString(closeReserveMode_string);
    if (this->lockInAmplifierModel == "SR865")
        return -1;
    return -1;

}

QString LockInAmplifier::closeReserveModeStringFromNumber(const int &closeReserveMode_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->closeReserveModeStringFromNumber(closeReserveMode_number);
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::setCloseReserveMode(const int &closeReserveMode) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setCloseReserveMode(closeReserveMode);
    if (this->lockInAmplifierModel == "Sr865")
        return false;
    return false;
}

bool LockInAmplifier::setCloseReserveMode(const QString &closeReserveMode) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setCloseReserveMode(closeReserveMode);
    if (this->lockInAmplifierModel == "Sr865")
        return false;
    return false;
}

QString LockInAmplifier::getCloseReserveMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "";
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getCloseReserveMode();
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::workWithTimeConstant() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

QString LockInAmplifier::getDefaultTimeConstant() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "30 ms";
    if (this->lockInAmplifierModel == "SR844")
        return "30 ms";
    if (this->lockInAmplifierModel == "SR865")
        return "30 ms";
    return "";
}

bool LockInAmplifier::setDefaultTimeConstant() const
{
    return setTimeConstant(getDefaultTimeConstant());
}

QStringList LockInAmplifier::getTimeConstantList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getTimeConstantList();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getTimeConstantList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getTimeConstantList();
    return QStringList();
}

int LockInAmplifier::timeConstantNumberFromString(const QString &timeConstant_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->timeConstantNumberFromString(timeConstant_string);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->timeConstantNumberFromString(timeConstant_string);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->timeConstantNumberFromString(timeConstant_string);
    return -1;
}

QString LockInAmplifier::timeConstantStringFromNumber(const int &timeConstant_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->timeConstantStringFromNumber(timeConstant_number);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->timeConstantStringFromNumber(timeConstant_number);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->timeConstantStringFromNumber(timeConstant_number);
    return "";
}

bool LockInAmplifier::setTimeConstant(const int &timeConstant) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setTimeConstant(timeConstant);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setTimeConstant(timeConstant);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setTimeConstant(timeConstant);
    return false;
}

bool LockInAmplifier::setTimeConstant(const QString &timeConstant) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setTimeConstant(timeConstant);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setTimeConstant(timeConstant);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setTimeConstant(timeConstant);
    return false;
}

QString LockInAmplifier::getTimeConstant() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getTimeConstant();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getTimeConstant();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getTimeConstant();
    return "";
}

bool LockInAmplifier::workWithFilter() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

QString LockInAmplifier::getDefaultFilter() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "24 dB/oct";
    if (this->lockInAmplifierModel == "SR844")
        return "24 dB/oct";
    if (this->lockInAmplifierModel == "SR865")
        return "24 dB/oct";
    return "";
}

bool LockInAmplifier::setDefaultFilter() const
{
    return setFilter(getDefaultFilter());
}

QStringList LockInAmplifier::getFilterList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getFilterList();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getFilterList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getFilterList();
    return QStringList();
}

int LockInAmplifier::filterNumberFromString(const QString &filter_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->filterNumberFromString(filter_string);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->filterNumberFromString(filter_string);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->filterNumberFromString(filter_string);
    return -1;
}

QString LockInAmplifier::filterStringFromNumber(const int &filter_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->filterStringFromNumber(filter_number);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->filterStringFromNumber(filter_number);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->filterStringFromNumber(filter_number);
    return "";
}

bool LockInAmplifier::setFilter(const int &filter) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setFilter(filter);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setFilter(filter);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setFilter(filter);
    return false;
}

bool LockInAmplifier::setFilter(const QString &filter) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setFilter(filter);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setFilter(filter);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->setFilter(filter);
    return false;
}

QString LockInAmplifier::getFilter() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getFilter();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getFilter();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getFilter();
    return "";
}

bool LockInAmplifier::workWithSynchronousFilter() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

bool LockInAmplifier::setDefaultSynchronousFilter() const
{
    return enableSynchronousFilter(false);
}

bool LockInAmplifier::enableSynchronousFilter(const bool &enable) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->enableSynchronousFilter(enable);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->enableSynchronousFilter(enable);
    return false;
}

bool LockInAmplifier::getSynchronousFilterEnabled() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getSynchronousFilterEnabled();
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getSynchronousFilterEnabled();
    return false;
}

bool LockInAmplifier::workWithAdvancedFilter() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

bool LockInAmplifier::setDefaultAdvancedFilter() const
{
    return enableAdvancedFilter(false);
}

bool LockInAmplifier::enableAdvancedFilter(const bool &enable) const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->enableAdvancedFilterFilter(enable);
    return false;
}

bool LockInAmplifier::getAdvancedFilterEnabled() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getAdvancedFilterEnabled();
    return false;
}

bool LockInAmplifier::workWithEnablingRS232outputInterface() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::setDefaultRS232outputInterface() const
{
    return enableRS232outputInterface();
}

bool LockInAmplifier::enableRS232outputInterface() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->enableRS232outputInterface();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->enableRS232outputInterface();
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::workWithAutoGain() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::autoGain() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->autoGain();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->autoGain();
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::workWithAutoReserve() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::autoReserve() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->autoReserve();
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::workWithAutoWideReserve() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::autoWideReserve() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->autoWideReserve();
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::workWithAutoCloseReserve() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::autoCloseReserve() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->autoCloseReserve();
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::workWithAutoPhase() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

bool LockInAmplifier::autoPhase() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->autoPhase();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->autoPhase();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->autoPhase();
    return false;
}

bool LockInAmplifier::workWithAutoOffset() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::autoOffset(const int &i) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->autoOffset(i);
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::workWithAutoOffsetAll() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::autoOffsetAll() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->autoOffsetAll();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr830->autoOffsetAll();
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::workWithAutoRange() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

bool LockInAmplifier::autoRange() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->autoRange();
    return false;
}

bool LockInAmplifier::workWithAutoScale() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return true;
    return false;
}

bool LockInAmplifier::autoScale() const
{
    if (this->lockInAmplifierModel == "SR830")
        return false;
    if (this->lockInAmplifierModel == "SR844")
        return false;
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->autoScale();
    return false;
}

bool LockInAmplifier::autoAll() const
{
    bool ans = true;

    if (this->lockInAmplifierModel == "SR830") {
        ans &= this->sr830->autoGain();
        ans &= this->sr830->autoReserve();
//        ans &= this->sr830->autoPhase();
//        ans &= this->sr830->autoOffsetAll();
    }
    if (this->lockInAmplifierModel == "SR844") {
        ans &= this->sr844->autoWideReserve();
        ans &= this->sr844->autoCloseReserve();
        ans &= this->sr844->autoGain();
//        ans &= this->sr844->autoPhase();
//        ans &= this->sr844->autoOffsetAll();
    }
    if (this->lockInAmplifierModel == "SR865") {
//        ans &= this->sr865->autoPhase();
        ans &= this->sr865->autoRange();
        ans &= this->sr865->autoScale();
    }

    return ans;
}

bool LockInAmplifier::workWithSampleRate() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

QString LockInAmplifier::getDefaultSampleRate() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "8 Hz";
    if (this->lockInAmplifierModel == "SR844")
        return "8 Hz";
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::setDefaultSampleRate() const
{
    return setSampleRate(getDefaultSampleRate());
}

QStringList LockInAmplifier::getSampleRateList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getSampleRateList();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getSampleRateList();
    if (this->lockInAmplifierModel == "SR865")
        return QStringList();
    return QStringList();
}

int LockInAmplifier::sampleRateNumberFromString(const QString &sampleRate_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->sampleRateNumberFromString(sampleRate_string);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->sampleRateNumberFromString(sampleRate_string);
    if (this->lockInAmplifierModel == "SR865")
        return -1;
    return -1;
}

QString LockInAmplifier::sampleRateStringFromNumber(const int &sampleRate_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->sampleRateStringFromNumber(sampleRate_number);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->sampleRateStringFromNumber(sampleRate_number);
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::setSampleRate(const int &sampleRate) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setSampleRate(sampleRate);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setSampleRate(sampleRate);
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::setSampleRate(const QString &sampleRate) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setSampleRate(sampleRate);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setSampleRate(sampleRate);
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

QString LockInAmplifier::getSampleRate() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getSampleRate();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getSampleRate();
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::workWithBufferMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

QString LockInAmplifier::getDefaultBufferMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return "Shot";
    if (this->lockInAmplifierModel == "SR844")
        return "Shot";
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::setDefaultBufferMode() const
{
    return setBufferMode(getDefaultBufferMode());
}

QStringList LockInAmplifier::getBufferModeList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getBufferModeList();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getBufferModeList();
    if (this->lockInAmplifierModel == "SR865")
        return QStringList();
    return QStringList();
}

int LockInAmplifier::bufferModeNumberFromString(const QString &bufferMode_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->bufferModeNumberFromString(bufferMode_string);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->bufferModeNumberFromString(bufferMode_string);
    if (this->lockInAmplifierModel == "SR865")
        return -1;
    return -1;
}

QString LockInAmplifier::bufferModeStringFromNumber(const int &bufferMode_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->bufferModeStringFromNumber(bufferMode_number);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->bufferModeStringFromNumber(bufferMode_number);
    if (this->lockInAmplifierModel == "SR865")
        return "";
    return "";
}

bool LockInAmplifier::setBufferMode(const int &bufferMode) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setBufferMode(bufferMode);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setBufferMode(bufferMode);
    if (this->lockInAmplifierModel == "SR869")
        return false;
    return false;
}

bool LockInAmplifier::setBufferMode(const QString &bufferMode) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setBufferMode(bufferMode);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setBufferMode(bufferMode);
    if (this->lockInAmplifierModel == "SR869")
        return false;
    return false;
}

QString LockInAmplifier::getBufferMode() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getBufferMode();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getBufferMode();
    if (this->lockInAmplifierModel == "SR869")
        return "";
    return "";
}

bool LockInAmplifier::workWithDisplayData() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::setDisplayData(const int &channel, const int &data) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->setDisplayData(channel, data);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->setDisplayData(channel, data);
    if (this->lockInAmplifierModel == "SR869")
        return false;
    return false;
}

bool LockInAmplifier::workWithBuffer() const
{
    if (this->lockInAmplifierModel == "SR830")
        return true;
    if (this->lockInAmplifierModel == "SR844")
        return true;
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

int LockInAmplifier::getBufferSize() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getBufferSize();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getBufferSize();
    if (this->lockInAmplifierModel == "SR869")
        return -1;
    return -1;
}

double LockInAmplifier::getPointFromBuffer(const int &channel, const int &number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getPointFromBuffer(channel, number);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getPointFromBuffer(channel, number);
    if (this->lockInAmplifierModel == "SR865")
        return -1;
    return -1;
}

std::vector < double > LockInAmplifier::getChannelFromBuffer(const int &channel) const
{
    std::vector < double > res;
    res.clear();

    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getChannelFromBuffer(channel);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getChannelFromBuffer(channel);
    if (this->lockInAmplifierModel == "SR869")
        return res;
    return res;
}

int LockInAmplifier::getBuffer(std::vector < double > &ch1, std::vector < double > &ch2) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getBuffer(ch1, ch2);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getBuffer(ch1, ch2);
    if (this->lockInAmplifierModel == "SR869")
        return -1;
    return -1;
}

bool LockInAmplifier::startBuffer() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->startBuffer();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->startBuffer();
    if (this->lockInAmplifierModel == "SR869")
        return false;
    return false;
}

bool LockInAmplifier::pauseBuffer() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->pauseBuffer();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->pauseBuffer();
    if (this->lockInAmplifierModel == "SR869")
        return false;
    return false;
}

bool LockInAmplifier::stopBuffer() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->stopBuffer();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->stopBuffer();
    if (this->lockInAmplifierModel == "SR869")
        return false;
    return false;
}

QStringList LockInAmplifier::getOutputNumberList() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getOutputNumberList();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getOutputNumberList();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getOutputNumberList();
    return QStringList();
}

int LockInAmplifier::outpNumberFromString(const QString &outp_string) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->outpNumberFromString(outp_string);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->outpNumberFromString(outp_string);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->outpNumberFromString(outp_string);
    return -1;
}

QString LockInAmplifier::outpStringFromNumber(const int &outp_number) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->outpStringFromNumber(outp_number);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->outpStringFromNumber(outp_number);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->outpStringFromNumber(outp_number);
    return "";
}

double LockInAmplifier::getOUTP(const int &i) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getOUTP(i);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getOUTP(i);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getOUTP(i);
    return -1;
}

double LockInAmplifier::getOUTP(const QString &i) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getOUTP(i);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getOUTP(i);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getOUTP(i);
    return -1;
}

double LockInAmplifier::getX() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getX();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getX();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getX();
    return -1;
}

double LockInAmplifier::getY() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getY();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getY();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getY();
    return -1;
}

double LockInAmplifier::getR() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getR();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getR();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getR();
    return -1;
}

double LockInAmplifier::getTheta() const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getTheta();
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getTheta();
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getTheta();
    return -1;
}

bool LockInAmplifier::getAB(const int &Apos, double &A, const int &Bpos, double &B) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getAB(Apos, A, Bpos, B);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getAB(Apos, A, Bpos, B);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getAB(Apos, A, Bpos, B);
    return false;
}

bool LockInAmplifier::getABC(const int &Apos, double &A, const int &Bpos, double &B, const int &Cpos, double &C) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getABC(Apos, A, Bpos, B, Cpos, C);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getABC(Apos, A, Bpos, B, Cpos, C);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getABC(Apos, A, Bpos, B, Cpos, C);
    return false;
}

bool LockInAmplifier::getABCDE(const int &Apos, double &A, const int &Bpos, double &B, const int &Cpos, double &C, const int &Dpos, double &D, const int &Epos, double &E) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getABCDE(Apos, A, Bpos, B, Cpos, C, Dpos, D, Epos, E);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getABCDE(Apos, A, Bpos, B, Cpos, C, Dpos, D, Epos, E);
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::getABCDEF(const int &Apos, double &A, const int &Bpos, double &B, const int &Cpos, double &C, const int &Dpos, double &D, const int &Epos, double &E, const int &Fpos, double &F) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getABCDEF(Apos, A, Bpos, B, Cpos, C, Dpos, D, Epos, E, Fpos, F);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getABCDEF(Apos, A, Bpos, B, Cpos, C, Dpos, D, Epos, E, Fpos, F);
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

bool LockInAmplifier::getXY(double &X, double &Y) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getXY(X, Y);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getXY(X, Y);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getXY(X, Y);
    return false;
}

bool LockInAmplifier::getRTheta(double &R, double &Theta) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getRTheta(R, Theta);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getRTheta(R, Theta);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getRTheta(R, Theta);
    return false;
}

bool LockInAmplifier::getRThetaFint(double &R, double &Theta, double &F) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getRThetaF(R, Theta, F);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getRThetaF(R, Theta, F);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getRThetaFint(R, Theta, F);
    return false;
}

bool LockInAmplifier::getRThetaFext(double &R, double &Theta, double &F) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getRThetaF(R, Theta, F);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getRThetaF(R, Theta, F);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getRThetaFext(R, Theta, F);
    return false;
}

bool LockInAmplifier::getRThetaF(double &R, double &Theta, double &F) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getRThetaF(R, Theta, F);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getRThetaF(R, Theta, F);
    if (this->lockInAmplifierModel == "SR865")
        return this->sr865->getRThetaF(R, Theta, F);
    return false;
}

bool LockInAmplifier::getXYRThetaF(double &X, double&Y, double &R, double &Theta, double &F) const
{
    if (this->lockInAmplifierModel == "SR830")
        return this->sr830->getXYRThetaF(X, Y, R, Theta, F);
    if (this->lockInAmplifierModel == "SR844")
        return this->sr844->getXYRThetaF(X, Y, R, Theta, F);
    if (this->lockInAmplifierModel == "SR865")
        return false;
    return false;
}

void LockInAmplifier::catchErrorSignal(const QString &s) const
{
    emit this->errorSignal(s);
}

void LockInAmplifier::catchResponseSignal(const QString &s) const
{
    emit this->responseSignal(s);
}

void LockInAmplifier::catchCommandSignal(const QString &s) const
{
    emit this->commandSignal(s);
}

void LockInAmplifier::catchTimeoutSignal(const QString &s) const
{
    emit this->timeoutSignal(s);
}
