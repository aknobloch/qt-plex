#include <keyevents.h>
#include <mediakeys.h>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QX11Info>

void KeyEventThread::run()
{
	qDebug() << "Key event service started!";

	Key result("Dummy Key", 1);
	emit resultReady(result);
}

void KeyEventController::handleResults(const Key &keyPressed)
{
	qDebug() << "Event " << keyPressed.getName() << " registered.";
}

Q_DECLARE_METATYPE(Key)
void KeyEventController::startKeyEventService()
{
	qRegisterMetaType<Key>();

	qDebug() << "Starting key event service...";
	KeyEventThread *eventThread = new KeyEventThread();
	connect(eventThread, &KeyEventThread::resultReady, this, &KeyEventController::handleResults);
	connect(eventThread, &KeyEventThread::finished, eventThread, &QObject::deleteLater);
	eventThread -> start();
}
