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

  /*  ui->labelFilter->hide();
    ui->comboBoxFilter->hide();*/

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

        if (this->lia->getSR865()->getSerial()->baudRate() == 9600)
            ui->comboBoxBaud->setCurrentText("9600");
        if (this->lia->getSR865()->getSerial()->baudRate() == 19200)
            ui->comboBoxBaud->setCurrentText("19200");
        if (this->lia->getSR865()->getSerial()->baudRate() == 38400)
            ui->comboBoxBaud->setCurrentText("38400");

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
         //get started



        if (this->lia->workWithFilter()) {
            this->listLoad = true;

            ui->labelFilter->show();
            ui->comboBoxFilter->show();
            ui->comboBoxFilter->clear();
            ui->comboBoxFilter->addItems(this->lia->getFilterList());
            ui->comboBoxFilter->setCurrentText(this->lia->getFilter());

            this->listLoad = false;
        }


        // TO ADD

        //ui->lineEditR->setText(QString::number(this->lia->getR()));
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

        ui->labelFilter->hide();
        ui->comboBoxFilter->hide();
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

void MainWindow::on_comboBoxFilter_currentTextChanged(const QString &arg1)
{
    if (this->listLoad == true)
        return;

    this->lia->setFilter(arg1);

    return;
}
