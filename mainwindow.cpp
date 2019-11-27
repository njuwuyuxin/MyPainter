#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化画布
    QPainter painter(this);
    windowWidth=800;
    windowHeight=600;
    resetPixMap(windowWidth,windowHeight);

    //初始化各项绘制状态
    isDrawing=false;
    CurrentFigureMode=DrawLine;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetPixMap(int width, int height)
{
    windowWidth=width;
    windowHeight=height;
    resize(width,height);
    QPixmap newPixMap(width,height);
    newPixMap.fill(Qt::white);
    pixMap=newPixMap;
    tempPixMap=pixMap;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
//    painter.drawPixmap(0,56,tempPixMap);
    painter.drawPixmap(0,0,tempPixMap);  //无偏移量
}

/*----------------鼠标事件处理函数---------------------*/
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton){
        if(CurrentFigureMode==DrawPolygon)
        {
            isDrawing=true;
            if(PolygonVertex.size()==0){
                QPoint s = event->pos();
                PolygonVertex.push_back(s);
            }
        }
        else
        {
            isDrawing=true;
            startPoint=event->pos();
            endPoint=event->pos();
            update();
        }
    }
    else if(event->buttons()==Qt::RightButton){
        if(CurrentFigureMode==DrawPolygon){      //点击鼠标右键意味着一个多边形已画完，需自动补齐最后一条边
            QPainter pp(&tempPixMap);
            Line::DrawUseBresenham(pp,PolygonVertex[PolygonVertex.size()-1],PolygonVertex[0]);
            pixMap = tempPixMap;
            PolygonVertex.clear();      //清空当前多边形顶点集，下次鼠标左键事件开始画新的多边形
        }

    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton&&isDrawing){
        endPoint=event->pos();
        if(CurrentFigureMode==DrawLine)
        {
            tempPixMap=pixMap;  //每次以上一次保存下的画布为基础，在上面进行绘制，移动时仅对tempPixMap绘制
            QPainter pp(&tempPixMap);
            Line::DrawUseBresenham(pp,startPoint,endPoint);
//            Line::DrawUseDDA(pp,startPoint,endPoint);
            update();
            return;
        }
        if(CurrentFigureMode==DrawCircle)
        {
            tempPixMap=pixMap;  //每次以上一次保存下的画布为基础，在上面进行绘制，移动时仅对tempPixMap绘制
            QPainter pp(&tempPixMap);
            Circle::DrawUseMidCircle(pp,startPoint,endPoint);
            update();
            return;
        }
        if(CurrentFigureMode==DrawOval)
        {
            tempPixMap=pixMap;  //每次以上一次保存下的画布为基础，在上面进行绘制，移动时仅对tempPixMap绘制
            QPainter pp(&tempPixMap);
            Ellipse::DrawUseMidOval(pp,startPoint,endPoint);
            update();
            return;
        }
        if(CurrentFigureMode==DrawPolygon)
        {
            if(PolygonVertex.size()>0){
                tempPixMap=pixMap;  //每次以上一次保存下的画布为基础，在上面进行绘制，移动时仅对tempPixMap绘制
                QPainter pp(&tempPixMap);
                QPoint tempPoint = event->pos();
                Line::DrawUseBresenham(pp,PolygonVertex[PolygonVertex.size()-1],tempPoint);
            }
            update();
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    isDrawing=false;
    endPoint=event->pos();
    tempPixMap=pixMap;  //每次以上一次保存下的画布为基础，在上面进行绘制，移动时仅对tempPixMap绘制
    QPainter pp(&tempPixMap);
    if(CurrentFigureMode==DrawLine)
    {
        Line::DrawUseBresenham(pp,startPoint,endPoint);
//        Line::DrawUseDDA(pp,startPoint,endPoint);
    }
    if(CurrentFigureMode==DrawCircle)
    {
        Circle::DrawUseMidCircle(pp,startPoint,endPoint);
    }
    if(CurrentFigureMode==DrawOval)
    {
        Ellipse::DrawUseMidOval(pp,startPoint,endPoint);
    }
    if(CurrentFigureMode==DrawPolygon)
    {
        if(PolygonVertex.size()!=0){        //如果顶点集为空，证明之前点击了右键，一个多边形已完成，顶点集被清空
            PolygonVertex.push_back(event->pos());
            Line::DrawUseBresenham(pp,PolygonVertex[PolygonVertex.size()-2],PolygonVertex[PolygonVertex.size()-1]);
        }
    }

    pixMap=tempPixMap;       //鼠标松开时，认为该次绘制已完成，保存到pixMap中
    update();
}
/*----------------鼠标事件处理函数---------------------*/

/*-------------从文件中读取指令并绘图-------------------*/
void MainWindow::DrawFromInstruction(QString path,QString dir_path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream inputStream(&file);
    while(!inputStream.atEnd())
    {
        QString instruction = inputStream.readLine();
        QStringList instrList = instruction.split(" ");
        qDebug()<<instrList;

        if(instrList.at(0)=="drawLine")
        {
            QPoint start(instrList[2].toInt(),instrList[3].toInt());
            QPoint end(instrList[4].toInt(),instrList[5].toInt());
            Line oneLine(instrList[1].toInt(),start,end);
            QPainter pp(&pixMap); //不涉及鼠标事件，直接在pixMap上绘制即可
            if(instrList[6]=="Bresenham")
                oneLine.DrawUseBresenham(pp);

            tempPixMap=pixMap;
            update();
            continue;
        }
        else if(instrList.at(0)=="drawEllipse")
        {
            int centerX = instrList[2].toInt();
            int centerY = instrList[3].toInt();
            int Rx = instrList[4].toInt();
            int Ry = instrList[5].toInt();
            Ellipse oneEllipse(centerX,centerY,Rx,Ry);
            QPainter pp(&pixMap); //不涉及鼠标事件，直接在pixMap上绘制即可
            oneEllipse.DrawFigure(pp);
            tempPixMap=pixMap;
            update();
            continue;
        }
        else if(instrList.at(0)=="saveCanvas"){
//            QString save_path = dir_path + instrList.at(1);
            QString save_path = instrList.at(1);
            save_path = QDir::toNativeSeparators(save_path);
            qDebug()<<save_path<<endl;
            SavePixMap(save_path);
            continue;
        }
        else if(instrList.at(0)=="resetCanvas")
        {
            resetPixMap(instrList[1].toInt(),instrList[1].toInt());
        }
        else
        {
            qDebug()<<"暂时未实现该指令:";
            qDebug()<<instrList[0];
        }
    }
}

void MainWindow::SavePixMap(QString file_name)
{
    pixMap.save(file_name,"BMP",-1);
}

void MainWindow::on_actionLoad_triggered()
{
    QString file_path = QFileDialog::getOpenFileName(this, "请选择读取文件", "./");
    qDebug()<<file_path;
    if(file_path.isEmpty())
    {
        return;
    }
//    DrawFromInstruction(file_path);
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
    resetPixMap(windowWidth,windowHeight);
    update();
    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

