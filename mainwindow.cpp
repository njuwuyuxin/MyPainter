#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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

