#include "ControlProgram.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	ControlProgram w;
	w.show();
	return a.exec();	
}
