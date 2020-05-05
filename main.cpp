#include "standarddialog.h"
#include <QApplication>
#include <QDebug>
#include <QProgressDialog>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StandardDialog w;
    w.setWindowTitle("文本编辑器");

    QProgressDialog dlg("程序启动","跳过",0,200000);
    dlg.setWindowTitle("程序启动");
    dlg.setModal(true);
    dlg.show();
    for (int i=0;i<200000;i++) {
        dlg.setValue(i);
        QCoreApplication::processEvents();
        if(dlg.wasCanceled()){
            break;
        }
    }
    dlg.setValue(200000);
    w.show();

    return a.exec();
}
