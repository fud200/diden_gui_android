#include <QApplication>
#include <QScreen>
#include "diden_mainwindow.h"
#include "diden_camerastream.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    DidenMainWindow window;

    QScreen *screen = app.primaryScreen();
    if(screen) {
        QRect screenGeometry = screen->availableGeometry();
        window.setGeometry(screenGeometry);
    }

    window.show();

    // 직접 UI의 QLabel과 버튼에 접근 (findChild 사용)
    QLabel* cameraLabel = window.findChild<QLabel*>("cameraLabel");
    QPushButton* startButton = window.findChild<QPushButton*>("pushButton_startStream");
    QPushButton* stopButton = window.findChild<QPushButton*>("pushButton_stopStream");

    if (!cameraLabel || !startButton || !stopButton) {
        qCritical() << "UI 요소를 찾을 수 없습니다!";
        return -1;
    }

    // DidenCameraStream 객체 생성
    DidenCameraStream cameraStreamer(cameraLabel);

    // 버튼 시그널 연결
    QObject::connect(startButton, &QPushButton::pressed, [&cameraStreamer]() {
        cameraStreamer.startStream("서버IP:포트");
    });

    QObject::connect(stopButton, &QPushButton::pressed, [&cameraStreamer]() {
        cameraStreamer.stopStream();
    });

    return app.exec();
}
