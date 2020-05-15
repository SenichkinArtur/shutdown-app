#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QTime"
#include "QTimer"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tmr = new QTimer();
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateShutdownTime()));
    tmr->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
    ui->label->setText(QTime::currentTime().toString());
}

void MainWindow::updateShutdownTime()
{
    if (shutdownTime != -1) {
        qint64 updatedShutdownTime = QDateTime::fromSecsSinceEpoch(shutdownTime).addSecs(-1).toSecsSinceEpoch();
        shutdownTime = updatedShutdownTime;
        QString shutdownTimeStr = QDateTime::fromTime_t(updatedShutdownTime).toUTC().toString("hh:mm:ss");
        ui->label_4->setText(shutdownTimeStr);
    }
}


void MainWindow::on_pushButton_clicked()
{
    int currentAndShutdownTimeDiff = calculateDiffTime();
    shutdownTime = calculateDiffTime();
    QString shutdownTimeStr = QDateTime::fromTime_t(currentAndShutdownTimeDiff).toUTC().toString("hh:mm:ss");
    ui->label_4->setText(shutdownTimeStr);

}

void MainWindow::on_pushButton_2_clicked()
{
    shutdownTime = -1;
    ui->label_4->setText("00:00:00");
}

bool MainWindow::isNextDay(QTime currentTime, QTime shutdownTime)
{
    int currentTimeHour = currentTime.hour();
    int currentTimeMinute = currentTime.minute();
    int shutdownTimeHour = shutdownTime.hour();
    int shutdownMinute = shutdownTime.minute();
    return shutdownTimeHour < currentTimeHour || (shutdownTimeHour == currentTimeHour && shutdownMinute < currentTimeMinute);
}

int MainWindow::calculateDiffTime()
{
    QDate currentDate = QDate::currentDate();
    QTime currentTime = QTime::currentTime();
    qint64 currentTimeSinceEpoch = QDateTime::currentSecsSinceEpoch();

    QString shutdownTimeString = ui->timeEdit->text();
    QDateTime qShutdownDateTime = QDateTime::fromString(shutdownTimeString, "hh:mm:ss");
    qShutdownDateTime.setDate(currentDate);
    QTime qShutdownTime = qShutdownDateTime.time();

    if (isNextDay(currentTime, qShutdownTime)) {
        qShutdownDateTime = qShutdownDateTime.addDays(1);
    }

    qint64 shutdownTimeSinceEpoch = qShutdownDateTime.toSecsSinceEpoch();
    return shutdownTimeSinceEpoch - currentTimeSinceEpoch;
}
