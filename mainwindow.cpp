#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) ://конструктор, не трогать
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

    QStringList bauds;//сделать аналичные для других настроек порта прямо в конструкторе
    bauds.push_back("9600");
    bauds.push_back("19200");
    bauds.push_back("38400");
    ui->comboBoxBaud->addItems(bauds);
    ui->comboBoxBaud->addItem("NO");
    ui->comboBoxBaud->setCurrentText("NO");

    ui->labelSensivity->hide();
    ui->comboBoxSensivity->hide();

}

MainWindow::~MainWindow() //деструктор не трогать
{
    delete ui;
}

void MainWindow::on_pushButtonAction_clicked()
{
    if (ui->pushButtonAction->text() == "Connect") {//отсюда магия
        if (this->lia->isActive())//this можно не писать
            return;

        if (!this->lia->setConnectionBrute(ui->comboBoxCOM->currentText()))
            return;

        ui->comboBoxModel->setCurrentText(this->lia->getLockInAmplifierModel());

        ui->pushButtonAction->setText("Disconnect");//до сюда магия, нахер нам не надо, не трогать

        if (this->lia->getSR865()->getSerial()->baudRate() == 9600)//настройки порта, нужно сделать еще другие
            ui->comboBoxBaud->setCurrentText("9600");
        if (this->lia->getSR865()->getSerial()->baudRate() == 19200)
            ui->comboBoxBaud->setCurrentText("19200");
        if (this->lia->getSR865()->getSerial()->baudRate() == 38400)
            ui->comboBoxBaud->setCurrentText("38400");

        if (this->lia->workWithSensivity()) {//Lia - синхронник, он уже сделан, после ворквиз ставим параметр, наличие который хотим проверить
            this->listLoad = true;//это начало, это обязательно

            ui->labelSensivity->show();//не писать более
            ui->comboBoxSensivity->show();//не писать более
            ui->comboBoxSensivity->clear();//клизьма
            ui->comboBoxSensivity->addItems(this->lia->getSensivityList());//заполняем возможные вариаеты настройки
            ui->comboBoxSensivity->setCurrentText(this->lia->getSensivity());//на текущий момент

            this->listLoad = false;//это конец, должно стоять по умолчанию
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
    }

    return;
}

void MainWindow::on_comboBoxSensivity_currentTextChanged(const QString &arg1)
{
    if (this->listLoad)
        return;

    this->lia->setSensivity(arg1);

    return;
}

void MainWindow::on_comboBoxInputRange_currentTextChanged(const QString &arg1)//sssssыыыыы
{
    if (this->listLoad)
        return;

    this->lia->setVoltageInputRange(arg1);

    return;
}
