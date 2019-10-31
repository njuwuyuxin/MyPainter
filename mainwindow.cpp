#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "figure.h"
#include "line.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化画布
    QPainter painter(this);
    resize(800,600);
    pixMap=QPixmap(800,600);
    pixMap.fill(Qt::white);
    prePixMap=pixMap;

    //初始化各项绘制状态
    isDrawing=false;
    CurrentFigureMode=DrawLine;

    //测试画线功能
    QPainter pp(&pixMap);
    Line testLine;
    QPoint start(0,0);
    QPoint end(100,100);
    testLine.DrawUseBresenham(pp,start,end);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
//    painter.drawPixmap(0,56,pixMap);
    painter.drawPixmap(0,0,pixMap);  //无偏移量
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton){
        isDrawing=true;
        startPoint=event->pos();
        endPoint=event->pos();
        update();
    }


}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton&&isDrawing){
        endPoint=event->pos();
        Line tempLine;
        pixMap=prePixMap;
        QPainter pp(&pixMap);
        tempLine.DrawUseBresenham(pp,startPoint,endPoint);
        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    isDrawing=false;
    endPoint=event->pos();
    Line tempLine(1,startPoint,endPoint);
    QPainter pp(&pixMap);
    tempLine.DrawUseBresenham(pp);
    prePixMap=pixMap;
    update();
}

void MainWindow::on_actionLoad_triggered()
{
    QString file_path = QFileDialog::getOpenFileName(this, "请选择读取文件", "./");
    qDebug()<<file_path;
    if(file_path.isEmpty())
    {
        return;
    }
}

void MainWindow::on_actionSave_triggered()
{
    return;
}

void MainWindow::on_actionSelectColor_triggered()
{

    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

void MainWindow::on_actionDrawLine_triggered()
{
    CurrentFigureMode=DrawLine;
    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

void MainWindow::on_actionDrawPolygon_triggered()
{
    CurrentFigureMode=DrawPolygon;
    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

void MainWindow::on_actionDrawCircle_triggered()
{
    CurrentFigureMode=DrawCircle;
    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

void MainWindow::on_actionDrawOval_triggered()
{
    CurrentFigureMode=DrawOval;
    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

void MainWindow::on_actionDrawCurve_triggered()
{
    CurrentFigureMode=DrawCurve;
    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

void MainWindow::on_actionResetPix_triggered()
{
    CurrentFigureMode=Clear;
    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

