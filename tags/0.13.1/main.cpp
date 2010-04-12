#include <QtGui/QApplication>
#ifdef Q_WS_WIN
//#   include <QWindowsVistaStyle>
#   include <QPlastiqueStyle>
#elif defined(Q_WS_MAC)
#   include <QFileOpenEvent>
#endif
#include <QDebug>
#include <QSettings>
#include <QTranslator>
#include <QLibraryInfo>
#include <QTextCodec>
#include <QDir>
#include <QMessageBox>
#include "appdef.h"
#include "mainwindow.h"


QString getTranslationPath(){
    QString appPath = qApp->applicationDirPath();
    QStringList pathList;

#ifdef Q_WS_WIN
    pathList << appPath + "/translations";
#elif defined(Q_WS_X11)
    pathList << appPath + "/translations"
             << "/usr/share/" APPNAME "/translations"
             << "/usr/local/share/" APPNAME "/translations";
#elif defined(Q_WS_MAC)
    pathList << QFileInfo(appPath + "/../Resources/translations/").absolutePath()
             << "./translations";
#endif
    QStringList::iterator iter = pathList.begin();
    while (iter != pathList.end()){
        QDir dir(*iter);
        if (dir.exists())
            return *iter;
        ++iter;
    }

    return "./";
}

class Application : public QApplication{
public:
    Application(int argc, char** argv) : QApplication(argc, argv), mainWindow(NULL){}
    virtual ~Application();

#if defined(Q_WS_MAC)
    bool event(QEvent*);
#endif

    MainWindow* newMainWindow();

private:
    MainWindow* mainWindow;
};

Application::~Application(){
    delete mainWindow;
}

#if defined(Q_WS_MAC)
bool Application::event(QEvent* e){
    switch(e->type()){
        case QEvent::FileOpen:{
            if (mainWindow)
                mainWindow->fileOpen( static_cast<QFileOpenEvent*>(e)->file() );
            return true;
        }

        default:
            return QApplication::event(e);
    }
}
#endif

MainWindow* Application::newMainWindow(){
    mainWindow = new MainWindow;
    mainWindow->show();
    return mainWindow;
}

int main(int argc, char *argv[])
{
// is QFileOpenEvent received on macx??
    Application a(argc, argv);
    a.setOrganizationName(AUTHOR);
    a.setApplicationName(APPNAME);
    a.setApplicationVersion(VERSION);
#ifdef Q_WS_WIN
//    a.setStyle(new QWindowsVistaStyle);
    a.setStyle(new QPlastiqueStyle);
#endif

    // Load translation
    QSettings settings;
    QString locale = settings.value("language").toString();
    if (locale.isEmpty())
        locale = QLocale::system().name();

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    myappTranslator.load("mugo." + locale, getTranslationPath());
    a.installTranslator(&myappTranslator);

    QTextCodec::setCodecForCStrings( QTextCodec::codecForLocale() );
    QTextCodec::setCodecForTr( QTextCodec::codecForLocale() );

    a.newMainWindow();
    return a.exec();
}