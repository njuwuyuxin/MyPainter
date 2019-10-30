#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <iostream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
    QPixmap pixMap;
    QImage imageMap;

private slots:
    void on_actionSelectColor_triggered();
    void on_actionDrawLine_triggered();
    void on_actionDrawPolygon_triggered();
    void on_actionDrawCircle_triggered();
    void on_actionDrawOval_triggered();
    void on_actionDrawCurve_triggered();
    void on_actionResetPix_triggered();
};
#endif // MAINWINDOW_H
