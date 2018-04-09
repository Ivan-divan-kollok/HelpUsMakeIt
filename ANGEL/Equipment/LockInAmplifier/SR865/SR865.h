#ifndef SR865_H
#define SR865_H

#include <QObject>
#include <QTime>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#include "../../CommonFunctionsForSRS/SRS.h"

class SR865 : public QObject
{
    Q_OBJECT

private:
    const double minInternalFrequency = 1e-3;
    const double maxInternalFrequency = 4.0e6;

    const double minSineOutputAmplitude = 1e-9;
    const double maxSineOutputAmplitude = 2;

    const double minSineOffset = -5;
    const double maxSineOffset = 5;

    const int minHarmonic = 1;
    const int maxHarmonic = 99;

    const int minHarmonicDual = 1;
    const int maxHarmonicDual = 99;

    SRS* srs;
    QSerialPort* serial;

    QStringList frequencyPostfixList;
    QStringList voltagePostfixList;

    QStringList baudrateList;
    QStringList referenceSourceList;
    QStringList referenceTriggerModeList;
    QStringList referenceTriggerOutputZList;
    QStringList signalInputList;
    QStringList voltageInputModeList;
    QStringList voltageInputCouplingList;
    QStringList voltageInputShieldsList;
    QStringList voltageInputRangeList;
    QStringList currrentInputGainList;
    QStringList sensivityList;
    QStringList timeConstantList;
    QStringList filterList;
    QStringList outputNumberListLongName;
    QStringList outputNumberListShortName;

public:
    explicit SR865(QObject *parent = 0);
    explicit SR865(const QString &portName, const int &baudrate, const int &stopBit = 1, const int &parity = 0);
    ~SR865();

    void init();

    void setSerial(QSerialPort* new_serial);
    QSerialPort* getSerial() const;

    bool setConnection(const QString &portName, const int &baudrate, const int &stopBit = 1, const int &parity = 0);
    bool setConnectionBrute(const QString &portName);
    void disconnect() const;

    void initBaudrateList();
    QStringList getBaudrateList() const;
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

    int numberFromString(const QStringList &list, const QString &string) const;
    QString stringFromNumber(const QStringList &list, const int &number) const;
    bool isValidString(const QStringList &list, const QString &string) const;
    bool isValidNumber(const QStringList &list, const int &number) const;

    void initFrequencyPostfixList();
    QStringList getFrequencyPostfixList() const;

    void initVoltagePostfixList();
    QStringList getVoltagePostfixList() const;

    bool isValidInternalFrequency(const double &frequency, const QString &postfix = "") const;
    double getMinInternalFrequency() const;
    double getMaxInternalFrequency() const;
    bool setInternalFrequency(const double &frequency, const QString &postfix = "") const;
    double getInternalFrequency() const;
    double getExternalFrequency() const;
    double getFrequency() const;
    double getFrequencyDetect() const;

    int getMinHarmonic() const;
    int getMaxHarmonic() const;
    bool isValidHarmonic(const int &i) const;
    bool setHarmonic(const int &i) const;
    int getHarmonic() const;

    int getMinHarmonicDual() const;
    int getMaxHarmonicDual() const;
    bool isValidHarmonicDual(const int &i) const;
    bool setHarmonicDual(const int &i) const;
    int getHarmonicDual() const;

    bool isValidSineOutAmplitude(const double &sineAmplitude, const QString &postfix = "") const;
    double getMinSineOutAmplitude() const;
    double getMaxSineOutAmplitude() const;
    bool setSineOutAmplitude(const double &sineAmplitude, const QString &postfix = "") const;
    double getSineOutAmplitude() const;

    bool isValidSineOffset(const double &offset, const QString &postfix = "") const;
    double getMinSineOffset() const;
    double getMaxSineOffset() const;
    bool setSineOffset(const double &offset, const QString &postfix = "") const;
    double getSineOffset() const;

    void initReferenceSourceList();
    QStringList getReferenceSourceList() const;
    int refSourceNumberFromString(const QString &ref_string) const;
    QString refSourceStringFromNumber(const int &ref_number) const;
    bool setReferenceSource(const int &source) const;
    bool setReferenceSource(const QString &source) const;
    QString getReferenceSource() const;

    void initReferenceTriggerModeList();
    QStringList getReferenceTriggerModeList() const;
    int refModeNumberFromString(const QString &mode_string) const;
    QString refModeStringFromNumber(const int &mode_number) const;
    bool setReferenceTriggerMode(const int &mode) const;
    bool setReferenceTriggerMode(const QString &mode) const;
    QString getReferenceTriggerMode() const;

    void initReferenceTriggerOutputZList();
    QStringList getReferenceTriggerOutputZList() const;
    int refOutputZNumberFromString(const QString &outpZ_string) const;
    QString refOutputZStringFromNumber(const int &outpZ_number) const;
    bool setReferenceTriggerOutputZ(const int &outpZ) const;
    bool setReferenceTriggerOutputZ(const QString &outpZ) const;
    QString getReferenceTriggerOutputZ() const;

    void initSignalInputList();
    QStringList getSignalInputList() const;
    int signalInputNumberFromString(const QString &signalInput_string) const;
    QString signalInputStringFromNumber(const int &signalInput_number) const;
    bool setSignalInput(const int &signalInput) const;
    bool setSignalInput(const QString &signalInput) const;
    QString getSignalInput() const;

    void initVoltageInputModeList();
    QStringList getVoltageInputModeList() const;
    int voltageInputModeNumberFromString(const QString &voltageInputMode_string) const;
    QString voltageInputModeStringFromNumber(const int &voltageInputMode_number) const;
    bool setVoltageInputMode(const int &voltageInputMode) const;
    bool setVoltageInputMode(const QString &voltageInputMode) const;
    QString getVoltageInputMode() const;

    void initVoltageInputCouplingList();
    QStringList getVoltageInputCouplingList() const;
    int voltageInputCouplingNumberFromString(const QString &voltageInputCoupling_string) const;
    QString voltageInputCouplingStringFromNumber(const int &voltageInputCoupling_number) const;
    bool setVoltageInputCoupling(const int &voltageInputCoupling) const;
    bool setVoltageInputCoupling(const QString &voltageInputCoupling) const;
    QString getVoltageInputCoupling() const;

    void initVoltageInputShieldsList();
    QStringList getVoltageInputShieldsList() const;
    int voltageInputShieldsNumberFromString(const QString &voltageInputShields_string) const;
    QString voltageInputShieldsStringFromNumber(const int &voltageInputShields_number) const;
    bool setVoltageInputShields(const int &voltageInputShields) const;
    bool setVoltageInputShields(const QString &voltageInputShields) const;
    QString getVoltageInputShields() const;

    void initVoltageInputRangeList();
    QStringList getVoltageInputRangeList() const;
    int voltageInputRangeNumberFromString(const QString &voltageInputRange_string) const;
    QString voltageInputRangeStringFromNumber(const int &voltageInputRange_number) const;
    bool setVoltageInputRange(const int &voltageInputRange) const;
    bool setVoltageInputRange(const QString &voltageInputRange) const;
    QString getVoltageInputRange() const;

    void initCurrentInputGainList();
    QStringList getCurrentInputGainList() const;
    int currentInputGainNumberFromString(const QString &currentInputGain_string) const;
    QString currentInputGainStringFromNumber(const int &currentInputGain_number) const;
    bool setCurrentInputGain(const int &currentInputGain) const;
    bool setCurrentInputGain(const QString &currentInputGain) const;
    QString getCurrentInputGain() const;

    int getSignalStrength() const;

    void initSensivityList();
    QStringList getSensivityList() const;
    int sensivityNumberFromString(const QString &sensivity_string) const;
    QString sensivityStringFromNumber(const int &sensivity_number) const;
    bool setSensivity(const int &sensivity) const;
    bool setSensivity(const QString &sensivity) const;
    QString getSensivity() const;

    void initTimeConstantList();
    QStringList getTimeConstantList() const;
    int timeConstantNumberFromString(const QString &timeConstant_string) const;
    QString timeConstantStringFromNumber(const int &timeConstant_number) const;
    bool setTimeConstant(const int &timeConstant) const;
    bool setTimeConstant(const QString &timeConstant) const;
    QString getTimeConstant() const;

    void initFilterList();
    QStringList getFilterList() const;
    int filterNumberFromString(const QString &filter_string) const;
    QString filterStringFromNumber(const int &filter_number) const;
    bool setFilter(const int &filter) const;
    bool setFilter(const QString &filter) const;
    QString getFilter() const;

    bool enableSynchronousFilter(const bool &enable) const;
    bool getSynchronousFilterEnabled() const;

    bool enableAdvancedFilterFilter(const bool &enable) const;
    bool getAdvancedFilterEnabled() const;

    bool autoPhase() const;

    bool autoRange() const;// LIA DOES NOT EXECUTE THIS COMMAND!!!

    bool autoScale() const;

    void initOutputNumberList();
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
    bool getXY(double &X, double &Y) const;
    bool getRTheta(double &R, double &Theta) const;
    bool getRThetaFint(double &R, double &Theta, double &F) const;
    bool getRThetaFext(double &R, double &Theta, double &F) const;
    bool getRThetaF(double &R, double &Theta, double &F) const;

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

#endif // SR865_H
