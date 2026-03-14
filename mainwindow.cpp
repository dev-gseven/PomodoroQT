#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

#define DIGITS 2
#define BASE 10

#define FOCUS 1
#define BREAK 5
#define LONG 15


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , pomodoroCore(FOCUS,BREAK,LONG), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::setWindowTitle("Pomodoro Loop");

    timer.setInterval(1000); // ms

    connect(&timer ,&QTimer::timeout, this, [this](){
        pomodoroCore.tick();
        updateUI();
    });


    updateUI();

}

void MainWindow::updateUI(){ // updates each second
    int seconds = pomodoroCore.getRemainingSeconds();

    int mins = seconds / 60;
    int secs = seconds % 60;

    ui->labelTimer->setText(QString("%1:%2").arg (mins, DIGITS, BASE, QChar('0')).arg(secs, DIGITS, BASE, QChar('0')));

    windowFocus();

}

MainWindow::~MainWindow()
{
    delete ui;
}



QString MainWindow::currentSession(int number){
    QString str = QString::number(number);
    return "Session: " +  str;
}

void MainWindow::on_skipButton_clicked(bool checked)
{
    pomodoroCore.skipCycle();
    ui->labelCycle->setText("");
}

void MainWindow::on_stopButton_clicked(bool checked)
{
    pomodoroCore.reset();
    currentSession(pomodoroCore.getCycleCount());
    showTemporaryStatus("Stopped","");
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

void MainWindow::showTemporaryStatus(QString temporaryText,QString persistentText){
    ui->labelCycle->setText(temporaryText);

    QTimer::singleShot(2000, this, [this,persistentText](){
        ui->labelCycle->setText(persistentText);
    });
}

void MainWindow::windowFocus(){
    if (pomodoroCore.isFinished){
        // realmente focar a janela aqui.
        qDebug() << "Chegou até windowFocus";
        this->showNormal();
        this->raise();
        this->activateWindow();

        pomodoroCore.isFinished = false;
    }
}


/*

- (void)showTemporaryStatus:(NSString *)text {
    self.statusLabel.stringValue = text;

    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)),
                   dispatch_get_main_queue(), ^{
        // TODO: fazer algma merda aqui
        if ([self.statusLabel.stringValue isEqualToString:text]) {
            self.statusLabel.stringValue = @"";
        }
    });
}

  */











