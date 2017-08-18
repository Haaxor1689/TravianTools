#ifndef WORKERTHREAD_HPP
#define WORKERTHREAD_HPP

#include <QThread>
#include <functional>

class WorkerThread : public QThread {
	Q_OBJECT
public:
	std::function<QString()> task;

	explicit WorkerThread(QObject* parent = nullptr) : QThread(parent) {}

private:
	void run() override {
		emit resultReady(task());
	}
signals:
	void resultReady(const QString &s);
};


#endif // WORKERTHREAD_HPP
