#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include "QTimer"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void updateTime();
    void updateShutdownTime();
    bool isNextDay(QTime, QTime);
    int calculateDiffTime();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    int shutdownTime = -1; // -1 means the shutdown timer is disabled
    QTimer *tmr;
};
#endif // MAINWINDOW_H
