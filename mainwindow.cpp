#include "mainwindow.h"
#include "./ui_mainwindow.h"


#define FOCUS 25
#define BREAK 5
#define LONG 15


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    pomodoroCore(FOCUS,BREAK,LONG), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::setWindowTitle("Pomodoro Loop");

    timer.setInterval(1000); // ms

    connect(&timer ,&QTimer::timeout, this, [this](){
        pomodoroCore.tick();
        updateUI();
    });

    ui->labelTimer->setText(pomodoroCore.updateUI());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUI(){ // updates each second
        ui->labelTimer->setText(pomodoroCore.updateUI());
        windowFocus();
}

void MainWindow::on_skipButton_clicked(bool checked)
{
    pomodoroCore.skipCycle();
    showTemporaryStatus("Skipped Session",currentCycle());
    updateUI();
}

void MainWindow::on_stopButton_clicked(bool checked)
{
    pomodoroCore.reset();
    currentSession(pomodoroCore.getCycleCount());
    showTemporaryStatus("Stopped",currentCycle());
    updateUI();
}

void MainWindow::on_playButton_clicked(bool checked)
{
    pomodoroCore.start();
    timer.start();
    showTemporaryStatus(currentSession(pomodoroCore.getCycleCount()),currentCycle());
}

QString MainWindow::currentCycle(){
    QString string = pomodoroCore.cycleToString();
    return string;
}

QString MainWindow::currentSession(int number){
    QString str = QString::number(number);
    return "Session: " +  str;
}

void MainWindow::showTemporaryStatus(QString temporaryText,QString persistentText){
    ui->labelCycle->setText(temporaryText);

    QTimer::singleShot(1500, this, [this,persistentText](){
        ui->labelCycle->setText(persistentText);
    });
}

void MainWindow::windowFocus(){
    if (pomodoroCore.isFinished){
        showTemporaryStatus("Timer Finished",currentCycle());

        this->showNormal();
        this->raise();
        this->activateWindow();
        QApplication::alert(this);
        systemSound.playSystemSound();

        pomodoroCore.isFinished = false;
    }
}
