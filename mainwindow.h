#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;

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
