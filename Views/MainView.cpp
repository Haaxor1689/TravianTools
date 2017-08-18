#include "MainView.hpp"

#include <QApplication>
#include <QStyleOption>
#include <QPainter>
#include <QtDebug>
#include <QThread>

#include <fstream>

#include "Other/json.hpp"
#include "AppConfigs/AppConfigs.hpp"
#include "Other/TravianAPI.hpp"

using namespace std;

// App entry point
int main(int argc, char **argv) {
	QApplication app (argc, argv);
	new MainView();
	return app.exec();
}

MainView::MainView(QWidget *parent) : QWidget(parent) {
	setFixedSize(800, 600);
	setStyleSheet(StyleSheet::normal());

	// Load Defaults
	Defaults::setserver("com1x3");

	// TravianAPI callbacks
	ConnectPair(TravianAPI::shared, this, requestApiKeyResponse(QString))
	ConnectPair(TravianAPI::shared, this, updateSiteDataResponse(QString))
	ConnectPair(TravianAPI::shared, this, getMapDataResponse(QString))


	// Buttons
	ConstructButton(requestApiKeyButton, "Request Api Key");
	requestApiKeyButton->setGeometry(10, 10, 100, 40);

	ConstructButton(updateSiteDataButton, "Update Site Data");
	updateSiteDataButton->setGeometry(120, 10, 100, 40);

	ConstructButton(getMapDataButton, "Get Map Data");
	getMapDataButton->setGeometry(230, 10, 100, 40);
	show();
}

void MainView::paintEvent(QPaintEvent *) {
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

// Button callbacks
void MainView::requestApiKeyButtonTapped() {
	qDebug() << "requestApiKeyButtonTapped (thread: " << QThread::currentThreadId() << ")";
	TravianAPI::shared->requestApiKey("betkomaros@gmail.com", "TestTool", "https://github.com/Haaxor1689/TravianTools.git", false);
}

void MainView::updateSiteDataButtonTapped() {
	qDebug() << "updateSiteDataButtonTapped (thread: " << QThread::currentThreadId() << ")";
	if (Defaults::privateApiKey().isEmpty()) {
		qDebug() << "No privateApiKey.";
		return;
	}

	qDebug() << "updateSiteDataButtonTapped - Key: " << Defaults::privateApiKey();
	TravianAPI::shared->updateSiteData(Defaults::privateApiKey(), "betkomaros@gmail.com", "TestTools", "https://github.com/Haaxor1689/TravianTools.git", false);
}

void MainView::getMapDataButtonTapped() {
	qDebug() << "getMapDataButtonTapped (thread: " << QThread::currentThreadId() << ")";
	if (Defaults::privateApiKey().isEmpty()) {
		qDebug() << "No privateApiKey.";
		return;
	}

	TravianAPI::shared->getMapData(Defaults::privateApiKey());
}

// Response callbacks
void MainView::requestApiKeyResponse(QString data) {
	qDebug() << "requestApiKeyResponse (thread: " << QThread::currentThreadId() << ")";

	auto json = nlohmann::json::parse(data.toStdString().c_str());
	ofstream file("requestApiKeyResponse.json");
	file << json.dump(4);

	Defaults::setprivateApiKey(QString::fromStdString(json.at("response").at("privateApiKey").get<std::string>()));
	Defaults::setpublicSiteKey(QString::fromStdString(json.at("response").at("publicSiteKey").get<std::string>()));
}

void MainView::updateSiteDataResponse(QString data) {
	qDebug() << "updateSiteDataResponse (thread: " << QThread::currentThreadId() << ")";

	auto json = nlohmann::json::parse(data.toStdString().c_str());
	ofstream file("updateSiteDataResponse.json");
	file << json.dump(4);
}

void MainView::getMapDataResponse(QString data) {
	qDebug() << "getMapDataResponse (thread: " << QThread::currentThreadId() << ")";

	auto json = nlohmann::json::parse(data.toStdString().c_str());
	ofstream file("getMapDataResponse.json");
	file << json.dump(4);

	serverData = json.at("response").get<ServerData>();
}
