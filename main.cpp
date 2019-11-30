#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if(argc==3){  //接收到命令行参数
        QString instr_file(argv[1]);
        QString dir_path(argv[2]);
        w.DrawFromInstruction(instr_file,dir_path);
        a.exit();
    }
    else{
        w.show();
    }

    return a.exec();
}
