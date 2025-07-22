#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QApplication>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

private slots:
    void startGame();
    void showRules();
    void exitGame();

private:
    QLabel *titleLabel;
    QPushButton *startButton;
    QPushButton *rulesButton;
    QPushButton *exitButton;
};
#endif // MAINWINDOW_H
