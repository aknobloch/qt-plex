#include <Qt>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine/QtWebEngine>
#include <keyevents.h>
#include <QDebug>
#include <QWebEngineView>
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

	QApplication app(argc, argv);

	QWebEngineView *view = new QWebEngineView();
	view -> setUrl(QUrl("http://192.168.1.100:32400/web"));

	KeyEventController runner;
	runner.startKeyEventService();

	view -> show();
	return app.exec();
}
