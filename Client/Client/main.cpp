#include "application.h"
#include <QApplication>

/*------------------------------------------------------------------------------
--	FUNCTION:       int main(int argc, char *argv[])
--
--	PURPOSE:        Main entry point into the Client program. It creates the parent
--                  UI element and paints it to the screen.
--
--	DESIGNERS:		Auto-Generated
--
--	PROGRAMMER:		Auto-Generated
/*-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application w;
    w.show();

    return a.exec();
}
