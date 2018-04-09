#ifndef LOCKINAMPLIFIER_H
#define LOCKINAMPLIFIER_H

#include <QObject>
#include <QDebug>

#include <QTime>

#include <QSerialPort>
#include <QSerialPortInfo>

#include <QTest>

#include "../../../Functions/AllFunctions.h"
#include "../../CommonFunctionsForSRS/SRS.h"
#include "../AllLockInAmplifiers.h"

struct LockInAmplifier_State
{
    QString model;
    double internalFrequency;
    int harmonic;
    int harmonicDual;
    double sineOutAmplitude;
    double sineOffset;
    QString referenceSource;
    QString referenceTriggerMode;
    QString referenceTriggerOutputZ;
    QString signalInput;
    QString signalInputZ;
    QString voltageInputMode;
    QString voltageInputCoupling;
    QString voltageInputShields;
    QString voltageInputRange;
    QString currentInputGain;
    QString inputLineNotchFilter;
    QString sensivity;
    QString reserveMode;
    QString wideReserveMode;
    QString closeReserveMode;
    QString timeConstant;
    QString filter;
    bool synchronousFilter;
    bool advancedFilter;
    QString sampleRate;
    QString bufferMode;
};

class LockInAmplifier : public QObject
{
    Q_OBJECT

private:
    SRS* srs;

    SR830* sr830;
    SR844* sr844;
    SR865* sr865;

    QString lockInAmplifierModel;

    const double sensivityReserve = 1.5;
    const double inputRangeReserve = 3;

    const double Err = 1E-11;

    const int waitTime = 500;

    const double longWait = 2;

public:
    explicit LockInAmplifier(QObject *parent = 0);
    explicit LockInAmplifier(const QString &portName, const int &baudrate, const int &stopBit = 1, const int &parity = 0, const QString &new_lockInAmplifierModel = "");
    explicit LockInAmplifier(QSerialPort *serial, const QString &new_lockInAmplifierModel = "");
    explicit LockInAmplifier(SR830* new_sr830);
    explicit LockInAmplifier(SR844* new_sr844);
    explicit LockInAmplifier(SR865* new_sr865);
    ~LockInAmplifier();

    void toNULL();
    void init();

    LockInAmplifier_State getState();
    bool setState(const LockInAmplifier_State &state);

    void wait(const double &x = 1) const;

    void setSR830(SR830* new_sr830);
    SR830* getSR830() const;
    void setSR844(SR844* new_sr844);
    SR844* getSR844() const;
    void setSR865(SR865* new_sr865);
    SR865* getSR865() const;

    bool openSerial(QSerialPort *serial) const;

    QStringList getSupportedModels() const;
    void setLockInAmplifierModel(const QString &new_lockInAmplifierModel);
    QString getLockInAmplifierModel() const;
    bool autoSetLockInAmplifierModel(QSerialPort *serial);
    bool autoSetLockInAmplifierModel(const QString &portName, const int &baudrate);
    bool autoSetLockInAmplifierModel(const QString &portName);

    bool setConnection(const QString &portName, const int &baudrate, const int &stopBit = 1, const int &parity = 0, const QString &new_lockInAmplifierModel = "");
    bool setConnectionBrute(const QString &portName, const QString &new_lockInAmplifierModel = "");

    bool disconnect() const;

    QStringList getBaudrateList() const;
    bool isValidBaudrateAll(const int &baudrate) const;
    bool isValidBaudrate(const int &baudrate) const;
    bool changeBaudrate(const int &baudrate);

    void setWriteTimeout(const int &new_writeTimeout);
    int getWriteTimeout() const;

    void setReadTimeout(const int &new_readTimeout);
    int getReadTimeout() const;

    void setReadWaitTimeout(const int &new_readWaitTimeout);
    int getReadWaitTimeout() const;

    void setAttemptsToConnect(const int &new_attemptsToConnect);
    int getAttemptsToConnect() const;

    bool isActive() const;

    bool send(const QString &command, QString &response, const bool &waitForResponse) const;
    bool sendCommand(const QString &command) const;
    bool sendQuery(const QString &command, QString &response) const;
    QString ask(const QString &command) const;

    bool getIDN(QString &idn) const;

    bool test() const;

    bool setDefaultSettings() const;

    double getAverageInputTime() const;
    double getAverageOutputTime() const;

    bool workWithFrequencyPostfix() const;
    QString getDefaultFrequencyPostfix() const;
    QStringList getFrequencyPostfixList() const;

    bool workWithVoltagePostfix() const;
    QString getDefaultVoltagePostfix() const;
    QStringList getVoltagePostfixList() const;

    bool workWithInternalFrequency() const;
    double getDefaultInternalFrequency() const;
    bool setDefaultInternalFrequency() const;
    double getMinInternalFrequency() const;
    double getMaxInternalFrequency() const;
    bool isValidInternalFrequency(const double &frequency, const QString &postfix = "") const;
    bool setInternalFrequency(const double &frequency, const QString &postfix = "") const;
    double getInternalFrequency() const;
    double getExternalFrequency() const;
    double getFrequency() const;
    double getFrequencyDetect() const;

    bool workWithHarmonic() const;
    int getDefaultHarmonic() const;
    bool setDefaultHarmonic() const;
    int getMinHarmonic() const;
    int getMaxHarmonic() const;
    bool isValidHarmonic(const int &i) const;
    bool setHarmonic(const int &i) const;
    int getHarmonic() const;

    bool workWithHarmonicDual() const;
    int getDefaultHarmonicDual() const;
    bool setDefaultHarmonicDual() const;
    int getMinHarmonicDual() const;
    int getMaxHarmonicDual() const;
    bool isValidHarmonicDual(const int &i) const;
    bool setHarmonicDual(const int &i) const;
    int getHarmonicDual() const;

    bool workWithSineOutAmplitude() const;
    double getDefaultSineAmplitude() const;
    bool setDefaultSineAmplitude() const;
    bool isValidSineOutAmplitude(const double &sineAmplitude, const QString &postfix = "") const;
    double getMinSineOutAmplitude() const;
    double getMaxSineOutAmplitude() const;
    bool setSineOutAmplitude(const double &sineAmplitude, const QString &postfix = "") const;
    double getSineOutAmplitude() const;

    bool workWithSineOffset() const;
    double getDefaultSineOffset() const;
    bool setDefaultSineOffset() const;
    bool isValidSineOffset(const double &offset, const QString &postfix = "") const;
    double getMinSineOffset() const;
    double getMaxSineOffset() const;
    bool setSineOffset(const double &offset, const QString &postfix = "") const;
    double getSineOffset() const;

    bool workWithReferenceSource()const;
    QString getDefaultReferenceSource() const;
    bool setDefaultReferenceSource() const;
    QStringList getReferenceSourceList() const;
    int refSourceNumberFromString(const QString &ref_string) const;
    QString refSourceStringFromNumber(const int &ref_number) const;
    bool setReferenceSource(const int &source) const;
    bool setReferenceSource(const QString &source) const;
    QString getReferenceSource() const;

    bool workWithReferenceTriggerMode() const;
    QString getDefaultReferenceTriggerMode() const;
    bool setDefaultReferenceTriggerMode() const;
    QStringList getReferenceTriggerModeList() const;
    int refModeNumberFromString(const QString &mode_string) const;
    QString refModeStringFromNumber(const int &mode_number) const;
    bool setReferenceTriggerMode(const int &mode) const;
    bool setReferenceTriggerMode(const QString &mode) const;
    QString getReferenceTriggerMode() const;

    bool workWithReferenceTriggerOutputZ() const;
    QString getDefaultReferenceTriggerOutputZ() const;
    bool setDefaultReferenceTriggerOutputZ() const;
    QStringList getReferenceTriggerOutputZList() const;
    int refOutputNumberFromString(const QString &outpZ_string) const;
    QString refOutputStringFromNumber(const int &outpZ_number) const;
    bool setReferenceTriggerOutputZ(const int &outpZ) const;
    bool setReferenceTriggerOutputZ(const QString &outpZ) const;
    QString getReferenceTriggerOutputZ() const;

    bool workWithSignalInput() const;
    QString getDefaultSignalInput() const;
    bool setDefaultSignalInput() const;
    QStringList getSignalInputList() const;
    int signalInputNumberFromString(const QString &signalInput_string) const;
    QString signalInputStringFromNumber(const int &signalInput_number) const;
    bool setSignalInput(const int &signalInput) const;
    bool setSignalInput(const QString &signalInput) const;
    QString getSignalInput() const;

    bool workWithSignalInputZ() const;
    QString getDefaultSignalInputZ() const;
    bool setDefaultSignalInputZ() const;
    QStringList getSignalInputZList() const;
    int signalInputZNumberFromString(const QString &signalInputZ_string) const;
    QString signalInputZStringFromNumber(const int &signalInputZ_number) const;
    bool setSignalInputZ(const int &signalInputZ) const;
    bool setSignalInputZ(const QString &signalInputZ) const;
    QString getSignalInputZ() const;

    bool workWithVoltageInputMode() const;
    QString getDefaultVoltageInputMode() const;
    bool setDefaultVoltageInputMode() const;
    QStringList getVoltageInputModeList() const;
    int voltageInputModeNumberFromString(const QString &voltageInputMode_string) const;
    QString voltageInputModeStringFromNumber(const int &voltageInputMode_number) const;
    bool setVoltageInputMode(const int &voltageInputMode) const;
    bool setVoltageInputMode(const QString &voltageInputMode) const;
    QString getVoltageInputMode() const;

    bool workWithVoltageInputCoupling() const;
    QString getDefaultVoltageInputCoupling() const;
    bool setDefaultVoltageInputCoupling() const;
    QStringList getVoltageInputCouplingList() const;
    int voltageInputCouplingNumberFromString(const QString &voltageInputCoupling_string) const;
    QString voltageInputCouplingStringFromNumber(const int &voltageInputCoupling_number) const;
    bool setVoltageInputCoupling(const int &voltageInputCoupling) const;
    bool setVoltageInputCoupling(const QString &voltageInputCoupling) const;
    QString getVoltageInputCoupling() const;

    bool workWithVoltageInputShields() const;
    QString getDefaultVoltageInputShields() const;
    bool setDefaultVoltageInputShields() const;
    QStringList getVoltageInputShieldsList() const;
    int voltageInputShieldsNumberFromString(const QString &voltageInputShields_string) const;
    QString voltageInputShieldsStringFromNumber(const int &voltageInputShields_number) const;
    bool setVoltageInputShields(const int &voltageInputShields) const;
    bool setVoltageInputShields(const QString &voltageInputShields) const;
    QString getVoltageInputShields() const;

    bool workWithVoltageInputRange() const;
    QString getDefaultVoltageInputRange() const;
    bool setDefaultVoltageInputRange() const;
    QStringList getVoltageInputRangeList() const;
    int voltageInputRangeNumberFromString(const QString &voltageInputRange_string) const;
    QString voltageInputRangeStringFromNumber(const int &voltageInputRange_number) const;
    bool setVoltageInputRange(const int &voltageInputRange) const;
    bool setVoltageInputRange(const QString &voltageInputRange) const;
    QString getVoltageInputRange() const;
    QString getAutoVoltageInputRange(const double &r) const;
    bool setAutoVoltageInputRange(const double &r) const;

    bool workWithCurrentInputGain() const;
    QString getDefaultCurrentInputGain() const;
    bool setDefaultCurrentInputGain() const;
    QStringList getCurrentInputGainList() const;
    int currentInputGainNumberFromString(const QString &currentInputGain_string) const;
    QString currentInputGainStringFromNumber(const int &currentInputGain_number) const;
    bool setCurrentInputGain(const int &currentInputGain) const;
    bool setCurrentInputGain(const QString &currentInputGain) const;
    QString getCurrentInputGain() const;

    bool workWithSignalStrength() const;
    int getSignalStrength() const;

    bool workWithInputLineNotchFilter() const;
    QString getDefaultInputLineNotchFilter() const;
    bool setDefaultInputLineNotchFilter() const;
    QStringList getInputLineNotchFilterList() const;
    int inputLineNotchFilterNumberFromString(const QString &inputLineNotchFilter_string) const;
    QString inputLineNotchFilterStringFromNumber(const int &inputLineNotchFilter_number) const;
    bool setInputLineNotchFilter(const int &inputLineNotchFilter) const;
    bool setInputLineNotchFilter(const QString &inputLineNotchFilter) const;
    QString getInputLineNotchFilter() const;

    bool workWithSensivity() const;
    QString getDefaultSensivity() const;
    bool setDefaultSensivity() const;
    QStringList getSensivityList() const;
    int sensivityNumberFromString(const QString &sensivity_string) const;
    QString sensivityStringFromNumber(const int &sensivity_number) const;
    bool setSensivity(const int &sensivity) const;
    bool setSensivity(const QString &sensivity) const;
    QString getSensivity() const;
    QString getAutoSensivity(const double &r) const;
    bool setAutoSensivity(const double &r) const;

    bool workWithReserveMode() const;
    QString getDefaultReserveMode() const;
    bool setDefaultReserveMode() const;
    void initReserveModeList();
    QStringList getReserveModeList() const;
    int reserveModeNumberFromString(const QString &reserveMode_string) const;
    QString reserveModeStringFromNumber(const int &reserveMode_number) const;
    bool setReserveMode(const int &reserveMode) const;
    bool setReserveMode(const QString &reserveMode) const;
    QString getReserveMode() const;

    bool workWithWideReserveMode() const;
    QString getDefaultWideReserveMode() const;
    bool setDefaultWideReserveMode() const;
    void initWideReserveModeList();
    QStringList getWideReserveModeList() const;
    int wideReserveModeNumberFromString(const QString &wideReserveMode_string) const;
    QString wideReserveModeStringFromNumber(const int &wideReserveMode_number) const;
    bool setWideReserveMode(const int &wideReserveMode) const;
    bool setWideReserveMode(const QString &wideReserveMode) const;
    QString getWideReserveMode() const;

    bool workWithCloseReserveMode() const;
    QString getDefaultCloseReserveMode() const;
    bool setDefaultCloseReserveMode() const;
    void initCloseReserveModeList();
    QStringList getCloseReserveModeList() const;
    int closeReserveModeNumberFromString(const QString &closeReserveMode_string) const;
    QString closeReserveModeStringFromNumber(const int &closeReserveMode_number) const;
    bool setCloseReserveMode(const int &closeReserveMode) const;
    bool setCloseReserveMode(const QString &closeReserveMode) const;
    QString getCloseReserveMode() const;

    bool workWithTimeConstant() const;
    QString getDefaultTimeConstant() const;
    bool setDefaultTimeConstant() const;
    QStringList getTimeConstantList() const;
    int timeConstantNumberFromString(const QString &timeConstant_string) const;
    QString timeConstantStringFromNumber(const int &timeConstant_number) const;
    bool setTimeConstant(const int &timeConstant) const;
    bool setTimeConstant(const QString &timeConstant) const;
    QString getTimeConstant() const;

    bool workWithFilter() const;
    QString getDefaultFilter() const;
    bool setDefaultFilter() const;
    QStringList getFilterList() const;
    int filterNumberFromString(const QString &filter_string) const;
    QString filterStringFromNumber(const int &filter_number) const;
    bool setFilter(const int &filter) const;
    bool setFilter(const QString &filter) const;
    QString getFilter() const;

    bool workWithSynchronousFilter() const;
    bool setDefaultSynchronousFilter() const;
    bool enableSynchronousFilter(const bool &enable) const;
    bool getSynchronousFilterEnabled() const;

    bool workWithAdvancedFilter() const;
    bool setDefaultAdvancedFilter() const;
    bool enableAdvancedFilter(const bool &enable) const;
    bool getAdvancedFilterEnabled() const;

    bool workWithEnablingRS232outputInterface() const;
    bool setDefaultRS232outputInterface() const;
    bool enableRS232outputInterface() const;

    bool workWithAutoGain() const;
    bool autoGain() const;

    bool workWithAutoReserve() const;
    bool autoReserve() const;

    bool workWithAutoWideReserve() const;
    bool autoWideReserve() const;

    bool workWithAutoCloseReserve() const;
    bool autoCloseReserve() const;

    bool workWithAutoPhase() const;
    bool autoPhase() const;

    bool workWithAutoOffset() const;
    bool autoOffset(const int &i) const;

    bool workWithAutoOffsetAll() const;
    bool autoOffsetAll() const;

    bool workWithAutoRange() const;
    bool autoRange() const;

    bool workWithAutoScale() const;
    bool autoScale() const;

    bool autoAll() const;

    bool workWithSampleRate() const;
    QString getDefaultSampleRate() const;
    bool setDefaultSampleRate() const;
    QStringList getSampleRateList() const;
    int sampleRateNumberFromString(const QString &sampleRate_string) const;
    QString sampleRateStringFromNumber(const int &sampleRate_number) const;
    bool setSampleRate(const int &sampleRate) const;
    bool setSampleRate(const QString &sampleRate) const;
    QString getSampleRate() const;

    bool workWithBufferMode() const;
    QString getDefaultBufferMode() const;
    bool setDefaultBufferMode() const;
    QStringList getBufferModeList() const;
    int bufferModeNumberFromString(const QString &bufferMode_string) const;
    QString bufferModeStringFromNumber(const int &bufferMode_number) const;
    bool setBufferMode(const int &bufferMode) const;
    bool setBufferMode(const QString &bufferMode) const;
    QString getBufferMode() const;

    bool workWithDisplayData() const;
    bool setDisplayData(const int &channel, const int &data) const;

    bool workWithBuffer() const;

    int getBufferSize() const;

    double getPointFromBuffer(const int &channel, const int &number) const;
    std::vector < double > getChannelFromBuffer(const int &channel) const;
    int getBuffer(std::vector < double > &ch1, std::vector < double > &ch2) const;

    bool startBuffer() const;
    bool pauseBuffer() const;
    bool stopBuffer() const;

    QStringList getOutputNumberList() const;
    int outpNumberFromString(const QString &outp_string) const;
    QString outpStringFromNumber(const int &outp_number) const;
    double getOUTP(const int &i) const;
    double getOUTP(const QString &i) const;
    double getX() const;
    double getY() const;
    double getR() const;
    double getTheta() const;
    bool getAB(const int &Apos, double &A, const int &Bpos, double &B) const;
    bool getABC(const int &Apos, double &A, const int &Bpos, double &B, const int &Cpos, double &C) const;
    bool getABCDE(const int &Apos, double &A, const int &Bpos, double &B, const int &Cpos, double &C, const int &Dpos, double &D, const int &Epos, double &E) const;
    bool getABCDEF(const int &Apos, double &A, const int &Bpos, double &B, const int &Cpos, double &C, const int &Dpos, double &D, const int &Epos, double &E, const int &Fpos, double &F) const;
    bool getXY(double &X, double &Y) const;
    bool getRTheta(double &R, double &Theta) const;
    bool getRThetaFint(double &R, double &Theta, double &F) const;
    bool getRThetaFext(double &R, double &Theta, double &F) const;
    bool getRThetaF(double &R, double &Theta, double &F) const;
    bool getXYRThetaF(double &X, double&Y, double &R, double &Theta, double &F) const;

public slots:
    void catchErrorSignal(const QString &s) const;
    void catchResponseSignal(const QString &s) const;
    void catchCommandSignal(const QString &s) const;
    void catchTimeoutSignal(const QString &s) const;

signals:
    void errorSignal(const QString &s) const;
    void responseSignal(const QString &s) const;
    void commandSignal(const QString &s) const;
    void timeoutSignal(const QString &s) const;
};

#endif // LOCKINAMPLIFIER_H
