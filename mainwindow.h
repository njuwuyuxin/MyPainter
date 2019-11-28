#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <iostream>
#include <QFileDialog>
#include <QColorDialog>
#include <QDebug>

#include "figure.h"
#include "line.h"
#include "circle.h"
#include "ellipse.h"
#include "polygon.h"
#include "curve.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum FigureMode{DrawLine,DrawCircle,DrawOval,DrawPolygon,DrawCurve,Clear};
enum Algorithm{Default,Bresenham,DDA,Bezier,BSpline};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void DrawFromInstruction(QString path,QString dir_path);

protected:
    void paintEvent(QPaintEvent* );
    void mousePressEvent(QMouseEvent* );
    void mouseMoveEvent(QMouseEvent* );
    void mouseReleaseEvent(QMouseEvent* );

private:
    Ui::MainWindow *ui;
    int windowWidth;
    int windowHeight;

    QPixmap tempPixMap;               //临时画布，一些预览性质的内容会暂时画在临时画布上，确定绘制完成时会转移到pixMap上
    QPixmap pixMap;                   //全局变量画布
    QColor PenColor;                  //当前画笔颜色
    bool isDrawing;                   //是否正在绘制（鼠标按下到抬起的过程）
    QPoint startPoint;                //鼠标起始坐标
    QPoint endPoint;                  //鼠标最终坐标
    QImage imageMap;
    vector<QPoint> PolygonVertex;     //用于记录当前所画多边形顶点集，每次画新的多边形时会首先清空内部元素
    vector<QPoint> CurveControlPoint; //用于记录绘制曲线的控制点集，每次画新的曲线时会首先清空内部元素

    vector<Figure*> Figures;          //存储的图元集（仅命令行程序使用）
    vector<Algorithm> Algorithms;     //存储的图元对应的绘制算法，与图元集一一对应

    void resetPixMap(int width,int height);

    void SavePixMap(QString file_name);
    void DrawAllFigures();

    FigureMode CurrentFigureMode;     //表示当前按钮点击了某个图形图标，接下来会绘制该图形



private slots:
    void on_actionLoad_triggered();
    void on_actionSave_triggered();
    void on_actionSelectColor_triggered();
    void on_actionDrawLine_triggered();
    void on_actionDrawPolygon_triggered();
    void on_actionDrawCircle_triggered();
    void on_actionDrawOval_triggered();
    void on_actionDrawCurve_triggered();
    void on_actionResetPix_triggered();
};
#endif // MAINWINDOW_H
