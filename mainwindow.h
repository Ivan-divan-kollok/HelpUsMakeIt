#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSerialPort>
#include <QSerialPortInfo>

#include <iostream>
#include <iomanip>
#include <stdio.h>

#include <string>

#include "ANGEL/Angel.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    LockInAmplifier* lia;

    bool listLoad = false;

private slots:
    void on_pushButtonAction_clicked();

    void on_comboBoxSensivity_currentTextChanged(const QString &arg1);
    void on_comboBoxInputRange_currentTextChanged(const QString &arg1);

    void on_comboBoxFilter_currentTextChanged(const QString &arg1);

    void on_comboBoxTimeConstant_currentTextChanged(const QString &arg1);

    void on_comboBoxSignalInput_currentTextChanged(const QString &arg1);

    void on_comboBoxWideReserveMode_currentTextChanged(const QString &arg1);

    void on_comboBoxCloseReserveMode_currentTextChanged(const QString &arg1);

    void on_comboBoxSignalInputZ_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
