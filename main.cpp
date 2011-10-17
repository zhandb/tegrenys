#include "stdafx.h"
#include "tegrenys.h"
#include <QtGui/QApplication>

#ifdef _DEBUG
#ifdef _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif /* _CRTDBG_MAP_ALLOC */



#include <crtdbg.h>
//#include "TGCodec.h"
//#include "TGCodec/tgcodec.h"

#endif /* _DEBUG */

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) |_CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(446);
	
	QApplication a(argc, argv);
	Tegrenys w;
	//w.show();

	//QWidget ww;
	//ww.show();
	return a.exec();
}
