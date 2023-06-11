#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QFile>
#include <stdio.h>
#include "ui_ControlProgram.h"
#include <QTextCodec>
#include <QFileInfo>
#include "UsbKey.h"

class ControlProgram : public QMainWindow
{
    Q_OBJECT

public:
    ControlProgram(QWidget *parent = Q_NULLPTR);

private:
    Ui::ControlProgramClass ui;
	QTimer *timer;
	QFile file;
	UsbKey usb;


	QTextCodec *StrCodec; //Для преобразования кодировки.
	int _ledStarus; //Состояние светодиода на плате, которым будем моргать.
	void LedBlinking(); //Мигание светодиодом.

private slots:
	void GetSerial();
	void SetSerial();
	void GetHWSerial();
	void GetLastDate();
	void SetLastDate();
	void TimerTick();
	void SaveKey();
};