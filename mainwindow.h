#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <iostream>
#include <QFileDialog>
#include <QDebug>

#include "figure.h"
#include "line.h"
#include "circle.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum FigureMode{DrawLine,DrawCircle,DrawOval,DrawPolygon,DrawCurve,Clear};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent* );
    void mousePressEvent(QMouseEvent* );
    void mouseMoveEvent(QMouseEvent* );
    void mouseReleaseEvent(QMouseEvent* );

private:
    Ui::MainWindow *ui;

    QPixmap tempPixMap;               //临时画布，一些预览性质的内容会暂时画在临时画布上，确定绘制完成时会转移到pixMap上
    QPixmap pixMap;                   //全局变量画布
    bool isDrawing;                   //是否正在绘制（鼠标按下到抬起的过程）
    QPoint startPoint;                //鼠标起始坐标
    QPoint endPoint;                  //鼠标最终坐标
    QImage imageMap;

    FigureMode CurrentFigureMode;     //表示当前按钮点击了某个图形图标，接下来会绘制该图形

    void DrawFromInstruction(QString path);

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
