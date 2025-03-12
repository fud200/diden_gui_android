#ifndef DIDEN_MAINWINDOW_H
#define DIDEN_MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class DidenMainWindow;
}

class DidenMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DidenMainWindow(QWidget *parent = nullptr);
    ~DidenMainWindow();

private:
    Ui::DidenMainWindow *ui;
};

#endif // DIDEN_MAINWINDOW_H
