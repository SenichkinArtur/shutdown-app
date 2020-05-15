#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QTime"
#include "QTimer"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    tmr = new QTimer();
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();
}

MainWindow::~MainWindow()
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    delete ui;
}

void MainWindow::updateTime()
{
    ui->label->setText(QTime::currentTime().toString());
}


void MainWindow::on_pushButton_clicked()
{
    shutdownTime = ui->timeEdit->text();
    localTime = QTime::currentTime();
    QString localTimeString = localTime.toString("hh:mm");
    qDebug() << localTimeString;

    ui->label->setText("qwe");
}

