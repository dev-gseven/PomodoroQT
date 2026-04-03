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

    connect(&pomodoroCore ,&PomodoroCore::updated, this, &MainWindow::updateUI);

    connect(&pomodoroCore, &PomodoroCore::finished, this, &MainWindow::windowFocus);

    updateUI();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUI(){
    ui->labelTimer->setText(pomodoroCore.updateUI());
}

void MainWindow::on_skipButton_clicked(bool checked)
{
    pomodoroCore.skipCycle();
    showTemporaryStatus("Skipped Session",currentCycle());
}

void MainWindow::on_stopButton_clicked(bool checked)
{
    pomodoroCore.reset();
    showTemporaryStatus("Stopped",currentCycle());
}

void MainWindow::on_playButton_clicked(bool checked)
{
    pomodoroCore.start();
    showTemporaryStatus(currentSession(pomodoroCore.getCycleCount()),currentCycle());
}

QString MainWindow::currentCycle(){
    return pomodoroCore.cycleToString();
}

QString MainWindow::currentSession(const int &number){
    QString str = QString::number(number);
    return "Session: " +  str;
}

void MainWindow::showTemporaryStatus(const QString &temporaryText,const QString &persistentText){
    ui->labelCycle->setText(temporaryText);

    QTimer::singleShot(1500, this, [this,persistentText](){
        ui->labelCycle->setText(persistentText);
    });
}

void MainWindow::windowFocus(){
    showTemporaryStatus("Timer Finished",currentCycle());

    this->showNormal();
    this->raise();
    this->activateWindow();
    QApplication::alert(this);
    QApplication::beep();
}
