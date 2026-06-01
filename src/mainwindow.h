#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include "pomodorocore.h"

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
    QTimer statusTimer;
    QString persistentStatus;
    QString currentCycle();
    QString currentSession(const int &number);
    void windowFocus();
    void updateUI();
    void showTemporaryStatus(const QString &temporaryText, const QString &persistentText);

    PomodoroCore pomodoroCore;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
