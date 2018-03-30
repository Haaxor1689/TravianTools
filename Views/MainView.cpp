#include "MainView.hpp"

#include <QApplication>
#include <QStyleOption>
#include <QPainter>
#include <QtDebug>
#include <QThread>
#include <QElapsedTimer>
#include <QPixmap>

#include <fstream>

#include "Other/json.hpp"
#include "Other/PixmapSheet.hpp"
#include "Other/TravianAPI.hpp"
#include "Other/WorkerThread.hpp"
#include "AppConfigs/AppConfigs.hpp"

using namespace std;

// App entry point
int main(int argc, char **argv) {
	QApplication app (argc, argv);
	qDebug() << "App path : " << qApp->applicationDirPath();
	new MainView();
	return app.exec();
}

MainView::MainView(QWidget *parent) : QWidget(parent) {
	setFixedSize(1920, 800);
	setStyleSheet(StyleSheet::normal());

	// Load Defaults
	Defaults::server() = "com1x3";

	// TravianAPI callbacks
	ConnectPair(TravianAPI::shared, this, requestApiKeyResponse(QString))
	ConnectPair(TravianAPI::shared, this, updateSiteDataResponse(QString))
	ConnectPair(TravianAPI::shared, this, getMapDataResponse(QString))

	// Buttons
	requestApiKeyButton = new QPushButton("Request Api Key", this);
	QObject::connect(requestApiKeyButton, SIGNAL (released()), this, SLOT (requestApiKeyButtonTapped()));
	requestApiKeyButton->setGeometry(10, 10, 100, 40);

	updateSiteDataButton = new QPushButton("Update Site Data", this);
	QObject::connect(updateSiteDataButton, SIGNAL (released()), this, SLOT (updateSiteDataButtonTapped()));
	updateSiteDataButton->setGeometry(120, 10, 100, 40);

	getMapDataButton = new QPushButton("Get Map Data", this);
	QObject::connect(getMapDataButton, SIGNAL (released()), this, SLOT (getMapDataButtonTapped()));
	getMapDataButton->setGeometry(230, 10, 100, 40);

	mapView = new TravianMapView(this);
	mapView->setGeometry(10, 60, 1900, 730);

	show();
}

void MainView::paintEvent(QPaintEvent *) {
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QString MainView::processMapData(const QString& data) {
	qDebug() << "processMapData ( thread: " << QThread::currentThreadId() << ")";
	auto json = nlohmann::json::parse(data.toStdString().c_str());
	serverData = json.at("response").get<ServerData>();

	json = { serverData };
	ofstream file("getMapDataResponse.json");
	file << json.dump(4);
	return {};
}

// Button callbacks
void MainView::requestApiKeyButtonTapped() {
	qDebug() << "requestApiKeyButtonTapped ( thread: " << QThread::currentThreadId() << ")";
	TravianAPI::shared->requestApiKey("betkomaros@gmail.com", "TestTool", "https://github.com/Haaxor1689/TravianTools.git", false);
}

void MainView::updateSiteDataButtonTapped() {
	qDebug() << "updateSiteDataButtonTapped ( thread: " << QThread::currentThreadId() << ")";
	if (Defaults::privateApiKey().isEmpty()) {
		qDebug() << "No privateApiKey.";
		return;
	}

	qDebug() << "updateSiteDataButtonTapped - Key: " << Defaults::privateApiKey();
	TravianAPI::shared->updateSiteData(Defaults::privateApiKey(), "betkomaros@gmail.com", "TestTools", "https://github.com/Haaxor1689/TravianTools.git", false);
}

void MainView::getMapDataButtonTapped() {
	qDebug() << "getMapDataButtonTapped ( thread: " << QThread::currentThreadId() << ")";
	if (Defaults::privateApiKey().isEmpty()) {
		qDebug() << "No privateApiKey.";
		return;
	}

	TravianAPI::shared->getMapData(Defaults::privateApiKey());
}

// Response callbacks
void MainView::requestApiKeyResponse(QString data) {
	qDebug() << "requestApiKeyResponse ( thread: " << QThread::currentThreadId() << ")";

	auto json = nlohmann::json::parse(data.toStdString().c_str());
	ofstream file("requestApiKeyResponse.json");
	file << json.dump(4);

	Defaults::privateApiKey() = QString::fromStdString(json.at("response").at("privateApiKey").get<std::string>());
	Defaults::publicSiteKey() = QString::fromStdString(json.at("response").at("publicSiteKey").get<std::string>());
}

void MainView::updateSiteDataResponse(QString data) {
	qDebug() << "updateSiteDataResponse ( thread: " << QThread::currentThreadId() << ")";

	auto json = nlohmann::json::parse(data.toStdString().c_str());
	ofstream file("updateSiteDataResponse.json");
	file << json.dump(4);
}

void MainView::getMapDataResponse(QString data) {
	qDebug() << "getMapDataResponse ( thread: " << QThread::currentThreadId() << ")";

	auto thread = new WorkerThread(this);
	thread->task = std::bind(&MainView::processMapData, this, data);
	QObject::connect(thread, SIGNAL(resultReady(QString)), this, SLOT(mapDataProcessed(QString)));
	thread->start();
}

void MainView::mapDataProcessed(QString data) {
	qDebug() << "mapDataProcessed ( thread: " << QThread::currentThreadId() << ")";
	mapView->populateWithData(serverData);
}
