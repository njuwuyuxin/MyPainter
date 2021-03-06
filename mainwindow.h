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

enum Mode{Drawing,Editing};
enum FigureMode{DrawLine,DrawCircle,DrawOval,DrawPolygon,DrawCurve,DrawCurveBSpline,Clear};
enum EditMode{Move,Scale,Rotate,Cut};
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
    void wheelEvent(QWheelEvent *event);

private:
    Ui::MainWindow *ui;
    int windowWidth;
    int windowHeight;

    QPixmap tempPixMap;               //临时画布，一些预览性质的内容会暂时画在临时画布上，确定绘制完成时会转移到pixMap上,PainterEvent中时刻更新该画布
    QPixmap PolygonPixMap;            //多边形专用画布，为了实现多边形每条边实时显示功能
    QPixmap pixMap;                   //全局变量画布，用来保存最终定型的画布
    QColor PenColor;                  //当前画笔颜色
    bool isDrawing;                   //是否正在绘制（鼠标按下到抬起的过程）
    QPoint startPoint;                //鼠标起始坐标（绘制时）
    QPoint endPoint;                  //鼠标最终坐标（绘制时）
    QPoint EditStartPoint;            //鼠标起始坐标（编辑时）
    QPoint EditEndPoint;              //鼠标最终坐标（编辑时）
    QPoint EditCenter;                //编辑模式下，用来确定旋转和缩放时的中心点
    QImage imageMap;
    vector<QPoint> PolygonVertex;     //用于记录当前所画多边形顶点集，每次画新的多边形时会首先清空内部元素
    vector<QPoint> CurveControlPoint; //用于记录绘制曲线的控制点集，每次画新的曲线时会首先清空内部元素
    vector<QPoint> CutVertex;         //用于记录直线剪裁时两顶点坐标，每次剪裁时会首先清空内部元素

    vector<Figure*> Figures;          //存储的图元集（仅命令行程序使用）
    vector<Algorithm> Algorithms;     //存储的图元对应的绘制算法，与图元集一一对应
    vector<QColor> Colors;            //存储每个图元对应的颜色，与图元集一一对应
    Figure* currentFigure;            //用来存储刚刚画好的图元，准备进行图元变换

    void resetPixMap(int width,int height);

    void SavePixMap(QString file_name);
    void DrawAllFigures();
    void UpdateUI();

    Mode CurrentMode;                 //表示当前软件所处状态：绘制图元或编辑图元
    FigureMode CurrentFigureMode;     //表示当前按钮点击了某个图形图标，接下来会绘制该图形
    EditMode CurrentEditMode;         //表示当前点击了某个编辑图表，切换编辑功能



private slots:
    void on_actionLoad_triggered();
    void on_actionSave_triggered();
    void on_actionSelectColor_triggered();
    void on_actionDrawLine_triggered();
    void on_actionDrawPolygon_triggered();
    void on_actionDrawCircle_triggered();
    void on_actionDrawOval_triggered();
    void on_actionDrawCurve_triggered();
    void on_actionDrawCurveBSpline_triggered();
    void on_actionResetPix_triggered();
    void on_actionMove_triggered();
    void on_actionRotate_triggered();
    void on_actionScale_triggered();
    void on_actionClip_triggered();
};
#endif // MAINWINDOW_H
