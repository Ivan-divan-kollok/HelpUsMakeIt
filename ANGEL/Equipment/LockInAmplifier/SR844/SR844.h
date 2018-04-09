#ifndef SR844_H
#define SR844_H

#include <QObject>
#include <QTime>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#include "../../CommonFunctionsForSRS/SRS.h"

class SR844 : public QObject
{
    Q_OBJECT

private:
    const double minInternalFrequency = 2.5E4;
    const double maxInternalFrequency = 2.0e8;

    const double minSineOutputAmplitude = 0.004;
    const double maxSineOutputAmplitude = 5;

    const int minHarmonic = 1;
    const int maxHarmonic = 2;

    SRS* srs;
    QSerialPort* serial;

    QStringList baudrateList;
    QStringList referenceSourceList;
    QStringList referenceTriggerOutputZList;
    QStringList wideReserveModeList;
    QStringList signalInputZList;
    QStringList sensivityList;
    QStringList closeReserveModeList;
    QStringList timeConstantList;
    QStringList filterList;
    QStringList sampleRateList;
    QStringList outputNumberList;
    QStringList bufferModeList;

public:
    explicit SR844(QObject *parent = 0);
    explicit SR844(const QString &portName, const int &baudrate, const int &stopBit = 1, const int &parity = 0);
    ~SR844();

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

    bool send(const QString &command, QString &response, const bool &wait_for_response) const;
    bool sendCommand(const QString &command) const;
    bool sendQuery(const QString &command, QString &response) const;
    QString ask(const QString &command) const;

    bool getIDN(QString &idn) const;

    int numberFromString(const QStringList &list, const QString &string) const;
    QString stringFromNumber(const QStringList &list, const int &number) const;
    bool isValidString(const QStringList &list, const QString &string) const;
    bool isValidNumber(const QStringList &list, const int &number) const;

    double getMinInternalFrequency() const;
    double getMaxInternalFrequency() const;
    bool isValidInternalFrequency(const double &frequency) const;
    bool setInternalFrequency(const double &frequency) const;
    double getFrequency() const;
    double getFrequencyDetect() const;

    int getMinHarmonic() const;
    int getMaxHarmonic() const;
    bool isValidHarmonic(const int &i) const;
    bool setHarmonic(const int &i) const;
    int getHarmonic() const;

    void initReferenceSourceList();
    QStringList getReferenceSourceList() const;
    int refSourceNumberFromString(const QString &ref_string) const;
    QString refSourceStringFromNumber(const int &ref_number) const;
    bool setReferenceSource(const int &source) const;
    bool setReferenceSource(const QString &source) const;
    QString getReferenceSource() const;

    void initReferenceTriggerOutputZList();
    QStringList getReferenceTriggerOutputZList() const;
    int refTriggerOutputZNumberFromString(const QString &referenceTriggerOutputZ_string) const;
    QString refTriggerOutputZStringFromNumber(const int &referenceTriggerOutputZ_number) const;
    bool setReferenceTriggerOutputZ(const int &referenceTriggerOutputZ) const;
    bool setReferenceTriggerOutputZ(const QString &referenceTriggerOutputZ) const;
    QString getReferenceTriggerOutputZ() const;

    void initWideReserveModeList();
    QStringList getWideReserveModeList() const;
    int wideReserveModeNumberFromString(const QString &wideReserveMode_string) const;
    QString wideReserveModeStringFromNumber(const int &wideReserveMode_number) const;
    bool setWideReserveMode(const int &wideReserveMode) const;
    bool setWideReserveMode(const QString &wideReserveMode) const;
    QString getWideReserveMode() const;

    void initSignalInputZList();
    QStringList getSignalInputZList() const;
    int signalInputZNumberFromString(const QString &signalInputZ_string) const;
    QString signalInputZStringFromNumber(const int &signalInputZ_number) const;
    bool setSignalInputZ(const int &signalInputZ) const;
    bool setSignalInputZ(const QString &signalInputZ) const;
    QString getSignalInputZ() const;

    void initSensivityList();
    QStringList getSensivityList() const;
    int sensivityNumberFromString(const QString &sensivity_string) const;
    QString sensivityStringFromNumber(const int &sensivity_number) const;
    bool setSensivity(const int &sensivity) const;
    bool setSensivity(const QString &sensivity) const;
    QString getSensivity() const;

    void initCloseReserveModeList();
    QStringList getCloseReserveModeList() const;
    int closeReserveModeNumberFromString(const QString &closeReserveMode_string) const;
    QString closeReserveModeStringFromNumber(const int &closeReserveMode_number) const;
    bool setCloseReserveMode(const int &closeReserveMode) const;
    bool setCloseReserveMode(const QString &closeReserveMode) const;
    QString getCloseReserveMode() const;

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

    bool enableRS232outputInterface() const;

    bool autoWideReserve() const;

    bool autoCloseReserve() const;

    bool autoGain() const;

    bool autoPhase() const;

    bool autoOffsetAll() const;

    void initSampleRateList();
    QStringList getSampleRateList() const;
    int sampleRateNumberFromString(const QString &sampleRate_string) const;
    QString sampleRateStringFromNumber(const int &sampleRate_number) const;
    bool setSampleRate(const int &sampleRate) const;
    bool setSampleRate(const QString &sampleRate) const;
    QString getSampleRate() const;

    void initBufferModeList();
    QStringList getBufferModeList() const;
    int bufferModeNumberFromString(const QString &bufferMode_string) const;
    QString bufferModeStringFromNumber(const int &bufferMode_number) const;
    bool setBufferMode(const int &bufferMode) const;
    bool setBufferMode(const QString &bufferMode) const;
    QString getBufferMode() const;

    bool startBuffer() const;
    bool pauseBuffer() const;
    bool stopBuffer() const;

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
    bool getABCDE(const int &Apos, double &A, const int &Bpos, double &B, const int &Cpos, double &C, const int &Dpos, double &D, const int &Epos, double &E) const;
    bool getABCDEF(const int &Apos, double &A, const int &Bpos, double &B, const int &Cpos, double &C, const int &Dpos, double &D, const int &Epos, double &E, const int &Fpos, double &F) const;
    bool getXY(double &X, double &Y) const;
    bool getRTheta(double &R, double &Theta) const;
    bool getRThetaF(double &R, double &Theta, double &F) const;
    bool getXYRThetaF(double &X, double&Y, double &R, double &Theta, double &F) const;

    bool setDisplayData(const int &channel, const int &data) const;
    int getBufferSize() const;

    double getPointFromBuffer(const int &channel, const int &number) const;
    std::vector < double > getChannelFromBuffer(const int &channel) const;
    int getBuffer(std::vector < double > &ch1, std::vector < double > &ch2) const;

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

#endif // SR844_H
