#include "ControlProgram.h"

ControlProgram::ControlProgram(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	timer = new QTimer();
	timer->setInterval(1000);

	//Нажатие на кнопку GetSerial.
	connect(ui.BtnGetSerial, SIGNAL(clicked()), this, SLOT(GetSerial()));
	//Нажатие на кнопку SetSerial.
	connect(ui.BtnSetSerial, SIGNAL(clicked()), this, SLOT(SetSerial()));
	//connect(ui->BtnGetHWSerial, SIGNAL(clicked()), this, SLOT(GetHWSerial()));
	//Нажатие на кнопку Get Last Date.
	connect(ui.BtnGetDate, SIGNAL(clicked()), this, SLOT(GetLastDate()));
	//Нажатие на кнопку Set Last Date.
	connect(ui.BtnSetDate, SIGNAL(clicked()), this, SLOT(SetLastDate()));
	//Нажатие на кнопку Load New RSA Key.
	connect(ui.BtnKeyGen, SIGNAL(clicked()), this, SLOT(SaveKey()));
	//Нажатие на кнопку  Get HW Serial.
	connect(ui.BtnGetHWSerial, SIGNAL(clicked()), this, SLOT(GetHWSerial()));
	connect(timer, SIGNAL(timeout()), this, SLOT(TimerTick()));

	StrCodec = QTextCodec::codecForName("Windows-1251"); //Установка кодировки

	timer->start();
	usb.InitUsb();

	_ledStarus = 0;
}

//Получаем серийный номер из устройства.
void ControlProgram::GetSerial()
{
	//QString serial = QString::fromStdString(key.ProductSerial());
	//ui.TbSerial->setText(serial);
}

//Установка серийного номера.
void ControlProgram::SetSerial()
{	
	QMessageBox::information(0, "Информация.", "Операция выполнена успешно.");
}

void ControlProgram::GetHWSerial()
{
	ui.TbHWSerial->setText(QString::fromStdString(usb.GetHWSerial()));
}

void ControlProgram::GetLastDate()
{
	ui.dateEdit->setDate(usb.GetLastHwDate());
}

void ControlProgram::SetLastDate()
{
	usb.SetLastDate(ui.dateEdit->date());
}

void ControlProgram::TimerTick()
{
	//Определяю подключено ли устройство.
	if (usb.IsConnected())
	{
		LedBlinking();
		uint8_t btnStatus = usb.InputsValue();
		ui.statusBar->showMessage("Подключено. BtnValue=" + QString::number(btnStatus));
		//ui.statusBar->showMessage("Устройство подключено");
		ui.statusBar->setStyleSheet("color: green");
		ui.TbHWSerial->setText(QString::fromStdString(usb.GetHWSerial()));
	}
	else
	{
		ui.statusBar->showMessage("Устройство отключено");
		ui.statusBar->setStyleSheet("color: red");
	}
}

void ControlProgram::SaveKey()
{	
	QMessageBox::information(0, "Информация.", "Операция выполнена успешно.");
}

//Мигание светодиодом.
void ControlProgram::LedBlinking()
{
	if (!_ledStarus)
	{
		usb.OutputsSet(0x01);
		_ledStarus = 1;
	}
	else
	{
		usb.OutputsSet(0);
		_ledStarus = 0;
	}
}
