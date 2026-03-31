#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>

#include "pomodorocore.h"
#include "systemsound.h"

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

    void on_skipButton_clicked(bool checked);

    void on_stopButton_clicked(bool checked);

    void on_playButton_clicked(bool checked);

private:
    QString currentCycle();
    void windowFocus();
    void updateUI();
    QString currentSession(int number);
    void showTemporaryStatus(QString temporaryText,QString persistentText);

    QTimer timer;
    PomodoroCore pomodoroCore;
    SystemSound systemSound;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
