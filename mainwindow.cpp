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

    //初始化画笔
    PenColor = Qt::black;

    //初始化各项绘制状态
    isDrawing=false;
    CurrentMode=Drawing;
    CurrentFigureMode=DrawLine;
    CurrentEditMode=Move;
    currentFigure=NULL;
    EditCenter.setX(-1);
    EditCenter.setY(-1);
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
    QPainter qpainter(this);
//    painter.drawPixmap(0,56,tempPixMap);
    qpainter.drawPixmap(0,0,tempPixMap);  //无偏移量
    UpdateUI();
}

/*----------------鼠标事件处理函数---------------------*/
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(CurrentMode==Drawing){           //当处于绘制模式时，对鼠标事件的处理
        if(event->buttons()==Qt::LeftButton){
            if(CurrentFigureMode==DrawPolygon)
            {
                isDrawing=true;
                if(PolygonVertex.size()==0){        //如果是第一个点直接加入顶点集
                    startPoint=event->pos();
                    PolygonPixMap=pixMap;           //初始化多边形画布
                    QPoint s = event->pos();
                    PolygonVertex.push_back(s);
                }
            }
            else if(CurrentFigureMode==DrawCurve||CurrentFigureMode==DrawCurveBSpline){
                isDrawing=true;
                startPoint=event->pos();
                QPoint s = event->pos();
                CurveControlPoint.push_back(s);
            }
            else
            {
                isDrawing=true;
                startPoint=event->pos();
                endPoint=event->pos();
                update();
            }
        }
        else if(event->buttons()==Qt::RightButton){  //多边形和曲线画完触发
//            qDebug()<<"press right button"<<endl;
            QPainter pp(&tempPixMap);
            pp.setPen(PenColor);
            if(CurrentFigureMode==DrawPolygon){      //点击鼠标右键意味着一个多边形已画完，需自动补齐最后一条边
                Line::DrawUseBresenham(pp,PolygonVertex[PolygonVertex.size()-1],PolygonVertex[0]);
                Polygon* one_poly=new Polygon(PolygonVertex);
                currentFigure=one_poly;
                PolygonVertex.clear();      //清空当前多边形顶点集，下次鼠标左键事件开始画新的多边形
                CurrentMode=Editing;
                CutVertex.clear();
                update();
            }
            else if(CurrentFigureMode==DrawCurve){   //点击鼠标右键意味着一条曲线各个控制点已确定，调用绘制函数进行绘制
                 Curve* oneCurve=new Curve(CurveControlPoint,CurveType::BezierCurve);
                 currentFigure=oneCurve;
                 oneCurve->DrawUseBezier(pp);
                 CurveControlPoint.clear();
                 CurrentMode=Editing;
                 CutVertex.clear();
                 update();
            }
            else if(CurrentFigureMode==DrawCurveBSpline){
                Curve* oneCurve=new Curve(CurveControlPoint,CurveType::BSplineCurve);
                currentFigure=oneCurve;
                oneCurve->DrawUseBSpline(pp);
                CurveControlPoint.clear();
                CurrentMode=Editing;
                CutVertex.clear();
                update();
            }
        }
    }
    else if(CurrentMode==Editing){          //当处于编辑模式时，对鼠标事件的处理
        if(event->buttons()==Qt::LeftButton){
//            qDebug()<<"Press left button in editing mode"<<endl;
            if(CurrentEditMode==Move){
                EditStartPoint=event->pos();
                EditEndPoint=event->pos();
            }
            else if(CurrentEditMode==Scale){
                EditCenter=event->pos();
            }
            else if(CurrentEditMode==Rotate){
                EditCenter=event->pos();
            }
            else if(CurrentEditMode==Cut){
                QPoint pos=event->pos();
//                qDebug()<<pos<<endl;
                CutVertex.push_back(pos);
                if(CutVertex.size()==2){
//                    currentFigure->CutUseBarsky(CutVertex[0].x(),CutVertex[0].y(),CutVertex[1].x(),CutVertex[1].y());
                    currentFigure->CutUseCohen(CutVertex[0].x(),CutVertex[0].y(),CutVertex[1].x(),CutVertex[1].y());
                    tempPixMap=pixMap;
                    QPainter pp(&tempPixMap);
                    pp.setPen(PenColor);
                    currentFigure->DrawFigure(pp);
                    pixMap=tempPixMap;
                    CurrentMode=Drawing;
                    //重置一下绘制时的初始点，防止误画
                    startPoint.setX(-1);
                    startPoint.setY(-1);
                    update();
                    CutVertex.clear();
                }
            }
        }
        if(event->buttons()==Qt::RightButton){
            pixMap=tempPixMap;      //点击右键表示该次变换已完成，保存画布，切换回绘制状态
            CurrentMode=Drawing;
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(CurrentMode==Drawing){           //当处于绘制模式时，对鼠标事件的处理
        if(event->buttons()==Qt::LeftButton&&isDrawing){
            endPoint=event->pos();
            if(CurrentFigureMode==DrawPolygon)
                tempPixMap=PolygonPixMap;
            else
                tempPixMap=pixMap;//每次以上一次保存下的画布为基础，在上面进行绘制，移动时仅对tempPixMap绘制；多边形需要特殊处理，每次以多边形特制画布为基础进行绘制
            QPainter pp(&tempPixMap);
            pp.setPen(PenColor);
            if(CurrentFigureMode==DrawLine)
            {
                Line::DrawUseBresenham(pp,startPoint,endPoint);
    //            Line::DrawUseDDA(pp,startPoint,endPoint);
                update();
                return;
            }
            if(CurrentFigureMode==DrawCircle)
            {
                Circle::DrawUseMidCircle(pp,startPoint,endPoint);
                update();
                return;
            }
            if(CurrentFigureMode==DrawOval)
            {
                Ellipse::DrawUseMidOval(pp,startPoint,endPoint);
                update();
                return;
            }
            if(CurrentFigureMode==DrawPolygon)
            {
                if(PolygonVertex.size()>0){
                    QPoint tempPoint = event->pos();
                    Line::DrawUseBresenham(pp,PolygonVertex[PolygonVertex.size()-1],tempPoint);
                }
                update();
            }
        }
    }
    else if(CurrentMode==Editing){          //当处于绘制模式时，对鼠标事件的处理
        tempPixMap=pixMap;
        QPainter pp(&tempPixMap);
        pp.setPen(PenColor);
        if(event->buttons()==Qt::LeftButton){
            if(CurrentEditMode==Move){
                EditEndPoint=event->pos();
                currentFigure->Move(EditEndPoint.x()-EditStartPoint.x(),EditEndPoint.y()-EditStartPoint.y());
                currentFigure->DrawFigure(pp);
//                currentFigure->PrintMyself();
                EditStartPoint=EditEndPoint;
                update();
                return;
            }
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(CurrentMode==Drawing&&event->button()==Qt::LeftButton){           //当处于绘制模式时，对鼠标事件的处理
        isDrawing=false;
        qDebug()<<startPoint<<endl;
        if(startPoint.x()==-1&&startPoint.y()==-1)      //表面初始点尚未初始化，此次鼠标松开事件不处理
            return;
        endPoint=event->pos();
        if(CurrentFigureMode==DrawPolygon)
            tempPixMap=PolygonPixMap;
        else
            tempPixMap=pixMap;//每次以上一次保存下的画布为基础，在上面进行绘制，移动时仅对tempPixMap绘制；多边形需要特殊处理，每次以多边形特制画布为基础进行绘制
        QPainter pp(&tempPixMap);
        pp.setPen(PenColor);
        if(CurrentFigureMode==DrawLine)     //直线画完触发
        {
            Line* one_line=new Line(0,startPoint,endPoint);
            currentFigure = one_line;
            Line::DrawUseBresenham(pp,startPoint,endPoint);
    //        Line::DrawUseDDA(pp,startPoint,endPoint);
            CurrentMode=Editing;
            CutVertex.clear();
        }
        if(CurrentFigureMode==DrawCircle)   //圆画完触发
        {
            Circle* one_circle=new Circle(startPoint,endPoint);
            currentFigure=one_circle;
            Circle::DrawUseMidCircle(pp,startPoint,endPoint);
            CurrentMode=Editing;
            CutVertex.clear();
        }
        if(CurrentFigureMode==DrawOval)    //椭圆画完触发
        {
            Ellipse::DrawUseMidOval(pp,startPoint,endPoint);
            int cx=(startPoint.x()+endPoint.x())/2;
            int cy=(startPoint.y()+endPoint.y())/2;
            int rx=abs(startPoint.x()-endPoint.x())/2;
            int ry=abs(startPoint.y()-endPoint.y())/2;
            Ellipse* one_ellipse=new Ellipse(0,cx,cy,rx,ry);
            currentFigure=one_ellipse;
            CurrentMode=Editing;
            CutVertex.clear();
        }
        if(CurrentFigureMode==DrawPolygon) //多边形尚未画完！多边形画完的触发函数在PressEvent中，曲线同理
        {
            if(PolygonVertex.size()!=0){        //如果顶点集为空，证明之前点击了右键，一个多边形已完成，顶点集被清空
                PolygonVertex.push_back(event->pos());
                Line::DrawUseBresenham(pp,PolygonVertex[PolygonVertex.size()-2],PolygonVertex[PolygonVertex.size()-1]);
                PolygonPixMap=tempPixMap;       //将多边形绘制过程临时保存在专用画布上
            }
        }
        update();
    }
    else if(CurrentMode==Editing){          //当处于绘制模式时，对鼠标事件的处理
        if(CurrentEditMode==Move){
            if(event->button()==Qt::LeftButton){
                EditEndPoint=event->pos();
//                pixMap=tempPixMap;          //平移结束后将临时画布保存到正式画布上固定住
//                qDebug()<<"画布已固定"<<endl;
//                CurrentMode=Drawing;
                update();
            }
        }
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    tempPixMap=pixMap;
    QPainter pp(&tempPixMap);
    pp.setPen(PenColor);
    if(CurrentMode==Editing){
        if(CurrentEditMode==Scale){
            if(EditCenter.x()==-1){
                qDebug()<<"尚未确定缩放中心，操作取消"<<endl;
                return;
            }

            if(event->delta()>0){
                currentFigure->ScaleFigure(EditCenter,1.1f);
            }
            else{
                currentFigure->ScaleFigure(EditCenter,0.9f);
            }
            currentFigure->DrawFigure(pp);
            update();
        }
        else if(CurrentEditMode==Rotate){
            if(EditCenter.x()==-1){
                qDebug()<<"尚未确定缩放中心，操作取消"<<endl;
                return;
            }

            if(event->delta()>0){
                currentFigure->RotateFigure(EditCenter,3);
            }
            else{
                currentFigure->RotateFigure(EditCenter,-3);
            }
            currentFigure->DrawFigure(pp);
            update();
        }
    }
}

void MainWindow::DrawAllFigures()
{
    resetPixMap(windowWidth,windowHeight);
    QPainter pp(&pixMap);
    for(size_t i=0;i<Figures.size();i++){
        pp.setPen(Colors[i]);               //根据每个图元的颜色分别设置画笔
        switch(Algorithms[i]){
        case Default:
            Figures[i]->DrawFigure(pp);
            break;
        case Bresenham:
            Figures[i]->DrawUseBresenham(pp);
            break;
        case DDA:
            Figures[i]->DrawUseDDA(pp);
            break;
        case Bezier:
            Figures[i]->DrawUseBezier(pp);
            break;
        case BSpline:
            Figures[i]->DrawUseBSpline(pp);
            break;
        }
    }
}

void MainWindow::UpdateUI()
{
    if(CurrentMode==Drawing){
        ui->currentMode->setText("绘制模式:");
        switch(CurrentFigureMode){
            case DrawLine:ui->currentMode_2->setText("直线");break;
            case DrawPolygon:ui->currentMode_2->setText("多边形");break;
            case DrawCircle:ui->currentMode_2->setText("圆形");break;
            case DrawOval:ui->currentMode_2->setText("椭圆");break;
            case DrawCurve:ui->currentMode_2->setText("贝塞尔曲线");break;
            case DrawCurveBSpline:ui->currentMode_2->setText("B样条曲线");break;
            case Clear:ui->currentMode_2->setText("清空");break;
        }
    }
    else if(CurrentMode==Editing){
        ui->currentMode->setText("编辑模式:");
        switch(CurrentEditMode){
            case Move:ui->currentMode_2->setText("平移");break;
            case Rotate:ui->currentMode_2->setText("旋转");break;
            case Scale:ui->currentMode_2->setText("缩放");break;
            case Cut:ui->currentMode_2->setText("剪裁");break;
        }
    }
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
        if(instruction.size()>=2&&instruction[0]=='/'&&instruction[1]=='/'){
            qDebug()<<"这是一行注释:"<<instruction<<endl;
            continue;
        }
        qDebug()<<instrList;
        if(instrList.at(0)=="drawLine")
        {
            QPoint start(instrList[2].toInt(),instrList[3].toInt());
            QPoint end(instrList[4].toInt(),instrList[5].toInt());
            Line* oneLine = new Line(instrList[1].toInt(),start,end);
            Algorithm a;
            if(instrList[6]=="Bresenham")
                a=Bresenham;
            else if(instrList[6]=="DDA")
                a=DDA;
            Figures.push_back(oneLine);
            Algorithms.push_back(a);
            Colors.push_back(PenColor);
            update();
            continue;
        }
        if(instrList.at(0)=="drawPolygon")
        {
            int id = instrList[1].toInt();
            int vertex_count = instrList[2].toInt();
            QString instr2 = inputStream.readLine();
            QStringList vertexes = instr2.split(" ");
            Polygon* onePoly = new Polygon(id);
            for(int i=0;i<vertex_count;i++){
                QPoint p(vertexes[i].toInt(),vertexes[i+1].toInt());
                onePoly->AddVertex(p);
            }
            Algorithm a;
            if(instrList[3]=="Bresenham")
                a=Bresenham;
            else if(instrList[3]=="DDA")
                a=DDA;
            Figures.push_back(onePoly);
            Algorithms.push_back(a);
            Colors.push_back(PenColor);
            update();
            continue;
        }
        else if(instrList.at(0)=="drawEllipse")
        {
            int id = instrList[1].toInt();
            int centerX = instrList[2].toInt();
            int centerY = instrList[3].toInt();
            int Rx = instrList[4].toInt();
            int Ry = instrList[5].toInt();
            Ellipse* oneEllipse = new Ellipse(id,centerX,centerY,Rx,Ry);
            Algorithm a = Default;
            Figures.push_back(oneEllipse);
            Algorithms.push_back(a);
            Colors.push_back(PenColor);
            update();
            continue;
        }
        else if(instrList.at(0)=="drawCurve")
        {
            int id = instrList[1].toInt();
            int point_count = instrList[2].toInt();
            QString instr2 = inputStream.readLine();
            QStringList points = instr2.split(" ");
            Curve* oneCurve = new Curve(id);
            for(int i=0;i<point_count;i++){
                QPoint p(points[i].toInt(),points[i+1].toInt());
                oneCurve->AddControlPoint(p);
            }

            Algorithm a;
            if(instrList[3]=="Bezier")
                a=Bezier;
            else if(instrList[3]=="B-Spline")
                a=BSpline;
            Figures.push_back(oneCurve);
            Algorithms.push_back(a);
            Colors.push_back(PenColor);
            update();
            continue;
        }
        else if(instrList.at(0)=="translate"){
            int id = instrList[1].toInt();
            int dx = instrList[2].toInt();
            int dy = instrList[3].toInt();
            for(size_t i=0;i<Figures.size();i++){
                if(Figures[i]->id==id){
                    Figures[i]->Move(dx,dy);
                    break;
                }
            }
            update();
            continue;
        }
        else if(instrList.at(0)=="rotate"){
            int id = instrList[1].toInt();
            int x = instrList[2].toInt();
            int y = instrList[3].toInt();
            int r = instrList[4].toInt();
            for(size_t i=0;i<Figures.size();i++){
                if(Figures[i]->id==id){
                    QPoint RotateCenter(x,y);
                    Figures[i]->RotateFigure(RotateCenter,r);
                    break;
                }
            }
            update();
            continue;
        }
        else if(instrList.at(0)=="scale"){
            int id = instrList[1].toInt();
            int x = instrList[2].toInt();
            int y = instrList[3].toInt();
            float s = instrList[4].toFloat();
            for(size_t i=0;i<Figures.size();i++){
                if(Figures[i]->id==id){
                    QPoint ScaleCenter(x,y);
                    Figures[i]->ScaleFigure(ScaleCenter,s);
                    break;
                }
            }
            update();
            continue;
        }
        else if(instrList.at(0)=="clip"){
            int id = instrList[1].toInt();
            int x1 = instrList[2].toInt();
            int y1 = instrList[3].toInt();
            int x2 = instrList[4].toInt();
            int y2 = instrList[5].toInt();

            for(size_t i=0;i<Figures.size();i++){
                if(Figures[i]->id==id){
                    if(instrList[6]=="Liang-Barsky")
                        Figures[i]->CutUseBarsky(x1,y1,x2,y2);
                    else if(instrList[6]=="Cohen-Sutherland")
                        Figures[i]->CutUseCohen(x1,y1,x2,y2);
                    break;
                }
            }
            update();
            continue;
        }
        else if(instrList.at(0)=="setColor"){
            int R = instrList[1].toInt();
            int G = instrList[2].toInt();
            int B = instrList[3].toInt();
            QColor c(R,G,B);
            PenColor=c;
        }
        else if(instrList.at(0)=="saveCanvas"){
            QString save_path = dir_path + instrList.at(1);

            //由于命令行程序需要存储所有图元，并且涉及到图元的编辑，因此只有在保存之前，才会将存储图元统一绘制到一张画布上
            //并且每次绘制之前需要先清空上一张画布内容，根据存储的图元集合重新绘制
            DrawAllFigures();
            qDebug()<<save_path<<endl;
            SavePixMap(save_path);
            update();
            continue;
        }
        else if(instrList.at(0)=="resetCanvas")
        {
            resetPixMap(instrList[1].toInt(),instrList[2].toInt());
            Figures.clear();
            Algorithms.clear();
            Colors.clear();
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
    CutVertex.clear();
    pixMap=tempPixMap;
    PenColor=QColorDialog::getColor(Qt::black,this);
    qDebug()<<PenColor<<endl;
    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

void MainWindow::on_actionDrawLine_triggered()
{
    CutVertex.clear();
    pixMap=tempPixMap;
    CurrentMode=Drawing;
    CurrentFigureMode=DrawLine;
    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

void MainWindow::on_actionDrawPolygon_triggered()
{
    CutVertex.clear();
    pixMap=tempPixMap;
    CurrentMode=Drawing;
    CurrentFigureMode=DrawPolygon;
    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

void MainWindow::on_actionDrawCircle_triggered()
{
    CutVertex.clear();
    pixMap=tempPixMap;
    CurrentMode=Drawing;
    CurrentFigureMode=DrawCircle;
    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

void MainWindow::on_actionDrawOval_triggered()
{
    CutVertex.clear();
    pixMap=tempPixMap;
    CurrentMode=Drawing;
    CurrentFigureMode=DrawOval;
    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

void MainWindow::on_actionDrawCurve_triggered()
{
    CutVertex.clear();
    pixMap=tempPixMap;
    CurrentMode=Drawing;
    CurrentFigureMode=DrawCurve;
    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

void MainWindow::on_actionDrawCurveBSpline_triggered()
{
    CutVertex.clear();
    pixMap=tempPixMap;
    CurrentMode=Drawing;
    CurrentFigureMode=DrawCurveBSpline;
    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

void MainWindow::on_actionResetPix_triggered()
{
    CutVertex.clear();
    CurrentFigureMode=Clear;
    resetPixMap(windowWidth,windowHeight);
    update();
    cout<<"CurrentFigureMode="<<CurrentFigureMode<<endl;
}

void MainWindow::on_actionMove_triggered()
{
    CutVertex.clear();
    CurrentMode=Editing;
    CurrentEditMode=Move;
    cout<<"CurrentEditMode="<<CurrentEditMode<<endl;
}

void MainWindow::on_actionRotate_triggered()
{
    CutVertex.clear();
    CurrentMode=Editing;
    CurrentEditMode=Rotate;
    cout<<"CurrentEditMode="<<CurrentEditMode<<endl;
}

void MainWindow::on_actionScale_triggered()
{
    CutVertex.clear();
    CurrentMode=Editing;
    CurrentEditMode=Scale;
    cout<<"CurrentEditMode="<<CurrentEditMode<<endl;
}

void MainWindow::on_actionClip_triggered()
{
    CutVertex.clear();
    CurrentMode=Editing;
    CurrentEditMode=Cut;
    cout<<"CurrentEditMode="<<CurrentEditMode<<endl;
}

