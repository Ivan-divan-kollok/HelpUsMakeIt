#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSerialPort>
#include <QSerialPortInfo>

#include <iostream>
#include <iomanip>
#include <stdio.h>

#include <string>

#include "../ANGEL/Angel.h"

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
