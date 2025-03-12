#include "diden_mainwindow.h"
#include "ui_diden_mainwindow.h"  // uic가 생성한 헤더 파일

DidenMainWindow::DidenMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DidenMainWindow)
{
    ui->setupUi(this);
    // 추가 초기화 코드가 필요하면 여기에 작성합니다.
}

DidenMainWindow::~DidenMainWindow()
{
    delete ui;
}
