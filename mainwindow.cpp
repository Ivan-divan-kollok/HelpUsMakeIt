#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList allCom;

    allCom.clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        allCom.push_back(info.portName());
    allCom.push_back("SetIt");

    ui->comboBoxCOM->clear();
    ui->comboBoxCOM->addItems(allCom);
    ui->comboBoxCOM->setCurrentText("SetIt");

    this->lia = new LockInAmplifier();
    ui->comboBoxModel->addItems(this->lia->getSupportedModels());
    ui->comboBoxModel->addItem("NO");
    ui->comboBoxModel->setCurrentText("NO");

    QStringList bauds;
    bauds.push_back("9600");
    bauds.push_back("19200");
    bauds.push_back("38400");
    ui->comboBoxBaud->addItems(bauds);
    ui->comboBoxBaud->addItem("NO");
    ui->comboBoxBaud->setCurrentText("NO");

    ui->labelSensivity->hide();
    ui->comboBoxSensivity->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonAction_clicked()
{
    if (ui->pushButtonAction->text() == "Connect") {
        if (this->lia->isActive())
            return;

        if (!this->lia->setConnectionBrute(ui->comboBoxCOM->currentText()))
            return;

        ui->comboBoxModel->setCurrentText(this->lia->getLockInAmplifierModel());

        ui->pushButtonAction->setText("Disconnect");

//        if (this->lia->getSR865()->getSerial()->baudRate() == 9600)
//            ui->comboBoxBaud->setCurrentText("9600");
//        if (this->lia->getSR865()->getSerial()->baudRate() == 19200)
//            ui->comboBoxBaud->setCurrentText("19200");
//        if (this->lia->getSR865()->getSerial()->baudRate() == 38400)
//            ui->comboBoxBaud->setCurrentText("38400");

        if (this->lia->workWithSensivity()) {
            this->listLoad = true;

            ui->labelSensivity->show();
            ui->comboBoxSensivity->show();
            ui->comboBoxSensivity->clear();
            ui->comboBoxSensivity->addItems(this->lia->getSensivityList());
            ui->comboBoxSensivity->setCurrentText(this->lia->getSensivity());

            this->listLoad = false;
        }

        if (this->lia->workWithVoltageInputRange()) {
            this->listLoad = true;

            ui->labelInputRange->show();
            ui->comboBoxInputRange->show();
            ui->comboBoxInputRange->clear();
            ui->comboBoxInputRange->addItems(this->lia->getVoltageInputRangeList());
            ui->comboBoxInputRange->setCurrentText(this->lia->getVoltageInputRange());

            this->listLoad = false;
        }

        //started1

        if (this->lia->workWithFilter()) {
            this->listLoad = true;

            ui->labelFilter->show();
            ui->comboBoxFilter->show();
            ui->comboBoxFilter->clear();
            ui->comboBoxFilter->addItems(this->lia->getFilterList());
            ui->comboBoxFilter->setCurrentText(this->lia->getFilter());

            this->listLoad = false;
        }

        if (this->lia->workWithTimeConstant()) {
            this->listLoad = true;

            ui->labelTimeConstant->show();
            ui->comboBoxTimeConstant->show();
            ui->comboBoxTimeConstant->clear();
            ui->comboBoxTimeConstant->addItems(this->lia->getTimeConstantList());
            ui->comboBoxTimeConstant->setCurrentText(this->lia->getTimeConstant());

            this->listLoad = false;
        }

        if (this->lia->workWithSignalInput()) {
            this->listLoad = true;

            ui->labelSignalInput->show();
            ui->comboBoxSignalInput->show();
            ui->comboBoxSignalInput->clear();
            ui->comboBoxSignalInput->addItems(this->lia->getSignalInputList());
            ui->comboBoxSignalInput->setCurrentText(this->lia->getSignalInput());

            this->listLoad = false;
        }

        if (this->lia->workWithWideReserveMode()) {
            this->listLoad = true;

            ui->labelWideReserveMode->show();
            ui->comboBoxWideReserveMode->show();
            ui->comboBoxWideReserveMode->clear();
            ui->comboBoxWideReserveMode->addItems(this->lia->getWideReserveModeList());
            ui->comboBoxWideReserveMode->setCurrentText(this->lia->getWideReserveMode());

            this->listLoad = false;
        }

        if (this->lia->workWithCloseReserveMode()) {
            this->listLoad = true;

            ui->labelCloseReserveMode->show();
            ui->comboBoxCloseReserveMode->show();
            ui->comboBoxCloseReserveMode->clear();
            ui->comboBoxCloseReserveMode->addItems(this->lia->getCloseReserveModeList());
            ui->comboBoxCloseReserveMode->setCurrentText(this->lia->getCloseReserveMode());

            this->listLoad = false;
        }

        if (this->lia->workWithSignalInputZ()) {
            this->listLoad = true;

            ui->labelSignalInputZ->show();
            ui->comboBoxSignalInputZ->show();
            ui->comboBoxSignalInputZ->clear();
            ui->comboBoxSignalInputZ->addItems(this->lia->getSignalInputZList());
            ui->comboBoxSignalInputZ->setCurrentText(this->lia->getSignalInputZ());

            this->listLoad = false;
        }

        if (this->lia->workWithReferenceSource()) {
            this->listLoad = true;

            ui->labelReferenceSource->show();
            ui->comboBoxReferenceSource->show();
            ui->comboBoxReferenceSource->clear();
            ui->comboBoxReferenceSource->addItems(this->lia->getReferenceSourceList());
            ui->comboBoxReferenceSource->setCurrentText(this->lia->getReferenceSource());

            this->listLoad = false;
        }

        if (this->lia->workWithReferenceTriggerMode()) {
            this->listLoad = true;

            ui->labelReferenceTriggerMode->show();
            ui->comboBoxReferenceTriggerMode->show();
            ui->comboBoxReferenceTriggerMode->clear();
            ui->comboBoxReferenceTriggerMode->addItems(this->lia->getReferenceTriggerModeList());
            ui->comboBoxReferenceTriggerMode->setCurrentText(this->lia->getReferenceTriggerMode());

            this->listLoad = false;
        }

        if (this->lia->workWithReferenceTriggerOutputZ()) {
            this->listLoad = true;

            ui->labelReferenceTriggerOutputZ->show();
            ui->comboBoxReferenceTriggerOutputZ->show();
            ui->comboBoxReferenceTriggerOutputZ->clear();
            ui->comboBoxReferenceTriggerOutputZ->addItems(this->lia->getReferenceTriggerOutputZList());
            ui->comboBoxReferenceTriggerOutputZ->setCurrentText(this->lia->getReferenceTriggerOutputZ());

            this->listLoad = false;
        }




        ui->lineEditR->setText(QString::number(this->lia->getR()));
    } else {
        if (!this->lia->isActive())
            return;

        this->lia->disconnect();

        ui->pushButtonAction->setText("Connect");

        ui->comboBoxModel->setCurrentText("NO");
        ui->comboBoxBaud->setCurrentText("NO");

        ui->labelSensivity->hide();
        ui->comboBoxSensivity->hide();

        ui->labelInputRange->hide();
        ui->comboBoxInputRange->hide();

        //started2

        ui->labelFilter->hide();
        ui->comboBoxFilter->hide();

        ui->labelTimeConstant->hide();
        ui->comboBoxTimeConstant->hide();

        ui->labelSignalInput->hide();
        ui->comboBoxSignalInput->hide();

        ui->labelWideReserveMode->hide();
        ui->comboBoxWideReserveMode->hide();

        ui->labelCloseReserveMode->hide();
        ui->comboBoxCloseReserveMode->hide();

        ui->labelSignalInputZ->hide();
        ui->comboBoxSignalInputZ->hide();

        ui->labelReferenceSource->hide();
        ui->comboBoxReferenceSource->hide();

        ui->labelReferenceTriggerMode->hide();
        ui->comboBoxReferenceTriggerMode->hide();

        ui->labelReferenceTriggerOutputZ->hide();
        ui->comboBoxReferenceTriggerOutputZ->hide();

    }

    return;
}

void MainWindow::on_comboBoxSensivity_currentTextChanged(const QString &arg1)
{
    if (this->listLoad == true)
        return;

    this->lia->setSensivity(arg1);

    return;
}

void MainWindow::on_comboBoxInputRange_currentTextChanged(const QString &arg1)
{
    if (this->listLoad == true)
        return;

    this->lia->setVoltageInputRange(arg1);

    return;
}

//started3
void MainWindow::on_comboBoxFilter_currentTextChanged(const QString &arg1)
{
    if (this->listLoad == true)
        return;

    this->lia->setFilter(arg1);

    return;
}

void MainWindow::on_comboBoxTimeConstant_currentTextChanged(const QString &arg1)
{
    if (this->listLoad == true)
        return;

    this->lia->setTimeConstant(arg1);

    return;
}

void MainWindow::on_comboBoxSignalInput_currentTextChanged(const QString &arg1)
{
    if (this->listLoad == true)
        return;

    this->lia->setSignalInput(arg1);

    return;
}

void MainWindow::on_comboBoxWideReserveMode_currentTextChanged(const QString &arg1)
{
    if (this->listLoad == true)
        return;

    this->lia->setWideReserveMode(arg1);

    return;
}

void MainWindow::on_comboBoxCloseReserveMode_currentTextChanged(const QString &arg1)
{
    if (this->listLoad == true)
        return;

    this->lia->setCloseReserveMode(arg1);

    return;
}

void MainWindow::on_comboBoxSignalInputZ_currentTextChanged(const QString &arg1)
{
    if (this->listLoad == true)
        return;

    this->lia->setSignalInputZ(arg1);

    return;
}

void MainWindow::on_comboBoxReferenceSource_currentTextChanged(const QString &arg1)
{
    if (this->listLoad == true)
        return;

    this->lia->setReferenceSource(arg1);

    return;
}

void MainWindow::on_comboBoxReferenceTriggerMode_currentTextChanged(const QString &arg1)
{
    if (this->listLoad == true)
        return;

    this->lia->setReferenceTriggerMode(arg1);

    return;
}

void MainWindow::on_comboBoxReferenceTriggerOutputZ_currentTextChanged(const QString &arg1)
{
    if (this->listLoad == true)
        return;

    this->lia->setReferenceTriggerOutputZ(arg1);

    return;
}
