#include "TravianAPI.hpp"

#include <QApplication>
#include <QDebug>
#include <QThread>
#include <QTimer>

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <future>
#pragma comment(lib,"ws2_32.lib")

#include "AppConfigs/AppConfigs.hpp"
#include "WorkerThread.hpp"

using namespace std;

TravianAPI* TravianAPI::shared = new TravianAPI(QApplication::instance());

TravianAPI::TravianAPI(QObject *parent) : QObject(parent) {

}

void TravianAPI::requestApiKey(const QString& email, const QString& siteName, const QString& siteUrl, bool isPublic) {
	qDebug() << "requestApiKey (thread: " << QThread::currentThreadId() << ")";

	auto thread = new WorkerThread(this);
	thread->task = std::bind(&TravianAPI::sendRequest, this, "requestApiKey",
	                         vector<pair<QString, QString>>{
	                             {"email", email},
	                             {"siteName", siteName},
	                             {"siteUrl", siteUrl},
	                             {"public", isPublic ? "true" : "false"}});
	QObject::connect(thread, SIGNAL(resultReady(QString)), this, SIGNAL(requestApiKeyResponse(QString)));
	thread->start();
}

void TravianAPI::updateSiteData(const QString& privateApiKey, const QString& email, const QString& siteName, const QString& siteUrl, bool isPublic) {
	qDebug() << "updateSiteData (thread: " << QThread::currentThreadId() << ")";

	auto thread = new WorkerThread(this);
	thread->task = std::bind(&TravianAPI::sendRequest, this, "updateSiteData",
	                         vector<pair<QString, QString>>{
	                             {"privateApiKey", privateApiKey},
	                             {"email", email},
	                             {"siteName", siteName},
	                             {"siteUrl", siteUrl},
	                             {"public", isPublic ? "true" : "false"}});
	QObject::connect(thread, SIGNAL(resultReady(QString)), this, SIGNAL(updateSiteDataResponse(QString)));
	thread->start();
}

void TravianAPI::getMapData(const QString& privateApiKey) {
	qDebug() << "getMapData ( thread: " << QThread::currentThreadId() << ")";

	auto thread = new WorkerThread(this);
	thread->task = std::bind(&TravianAPI::sendRequest, this, "getMapData",
	                         vector<pair<QString, QString>>{
	                             {"privateApiKey", privateApiKey}});
	QObject::connect(thread, SIGNAL(resultReady(QString)), this, SIGNAL(getMapDataResponse(QString)));
	thread->start();
}

QString TravianAPI::sendRequest(const QString& action, vector<pair<QString, QString>> list) {
	qDebug() << "sendRequest ( thread: " << QThread::currentThreadId() << ")";
	if (isSending) {
		while (isSending) {}
	}
	isSending = true;

	QString serverName = Defaults::server() + ".kingdoms.com";

	// SetUp
	WSADATA wsaData;
	if (WSAStartup(0x101, &wsaData) != 0) {
		qDebug() << "sendRequest error: WSAStartup failed.";
		isSending = false;
		return "";
	}

	struct hostent* hp;
	struct sockaddr_in server;

	SOCKET connectionSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connectionSocket == INVALID_SOCKET) {
		qDebug() << "sendRequest error: INVALID_SOCKET.";
		WSACleanup();
		isSending = false;
		return "";
	}

	if (inet_addr(serverName.toLatin1().data()) == INADDR_NONE) {
		hp = gethostbyname(serverName.toLatin1().data());
	} else {
		unsigned int addr = inet_addr(serverName.toLatin1().data());
		hp = gethostbyaddr(reinterpret_cast<char*>(&addr), sizeof(addr), AF_INET);
	}

	if (hp == nullptr) {
		closesocket(connectionSocket);
		qDebug() << "sendRequest error: hostent is nulltptr.";
		WSACleanup();
		isSending = false;
		return "";
	}

	server.sin_addr.s_addr = *reinterpret_cast<unsigned long*>(hp->h_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(80);
	if (::connect(connectionSocket, reinterpret_cast<struct sockaddr*>(&server), sizeof(server))) {
		closesocket(connectionSocket);
		qDebug() << "sendRequest error: Connection failed.";
		WSACleanup();
		isSending = false;
		return "";
	}

	// Create message form list
	QString message = "GET /api/external.php?action=" + action;
	for (const auto& item : list)
		message.append("&" + item.first + "=" + item.second);
	message.append(" HTTP/1.0\r\nHost: " + serverName + "\r\n\r\n");

	qDebug() << "sendRequest - Message:\n " << message;

	// Send message
	send(connectionSocket, message.toLatin1().data(), message.length(), 0);

	// Time out timer
	auto timeOut = new QTimer();
	timeOut->setSingleShot(true);
	timeOut->setInterval(5000);
	QObject::connect(timeOut, SIGNAL(timeout()), this, SLOT(requestTimedOut()));
	timeOut->start();

	// Wait for response
	QString response = "";
	char buffer[2048];
	unsigned responseLength = 0;
	while (isSending) {
		while ((responseLength = recv(connectionSocket, buffer, 2048, 0)) > 0) {
			for (unsigned i = 0; i < responseLength; ++i)
				response.append(buffer[i]);
		}

		break;
	}

	WSACleanup();
	isSending = false;

	int i = response.indexOf("\r\n\r\n");
	response = response.remove(0, i + 4);

	return response;
}

void TravianAPI::requestTimedOut() {
	qDebug() << "requestTimedOut ( thread: " << QThread::currentThreadId() << ")";
	isSending = false;
}
