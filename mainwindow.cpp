#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "figure.h"
#include "line.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPainter painter(this);
    resize(800,600);
    pixMap=QPixmap(800,600);
    pixMap.fill(Qt::white);
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
    painter.drawPixmap(0,56,pixMap);
}

void MainWindow::mousePressEvent(QMouseEvent *)
{

}

void MainWindow::mouseMoveEvent(QMouseEvent *)
{

}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{

}

void MainWindow::on_actionSelectColor_triggered()
{
    cout<<"press select_color!"<<endl;
}

void MainWindow::on_actionDrawLine_triggered()
{
    cout<<"press draw_line!"<<endl;
}

void MainWindow::on_actionDrawPolygon_triggered()
{
    cout<<"press draw_polygon!"<<endl;
}

void MainWindow::on_actionDrawCircle_triggered()
{
    cout<<"press draw_circle!"<<endl;
}

void MainWindow::on_actionDrawOval_triggered()
{
    cout<<"press draw_oval!"<<endl;
}

void MainWindow::on_actionDrawCurve_triggered()
{
    cout<<"press draw_curve!"<<endl;
}

void MainWindow::on_actionResetPix_triggered()
{
    cout<<"press reset_pix"<<endl;
}

