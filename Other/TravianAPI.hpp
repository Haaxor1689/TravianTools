#ifndef TRAVIANAPI_HPP
#define TRAVIANAPI_HPP

#include <string>
#include <QObject>

class TravianAPI: public QObject {
	Q_OBJECT
	explicit TravianAPI(QObject *parent = nullptr);
public:
	static TravianAPI* shared;

	bool isSending = false;

	void requestApiKey(const QString& email, const QString& siteName, const QString& siteURL, bool isPublic);
	void updateSiteData(const QString& privateApiKey, const QString& email, const QString& siteName, const QString& siteURL, bool isPublic);
	void getMapData(const QString& privateApiKey);

private:
	QString sendRequest(const QString& action, std::vector<std::pair<QString, QString>> list);
	QString rawSend(const QString& server, const QString& message);

signals:
	void requestApiKeyResponse(QString data);
	void updateSiteDataResponse(QString data);
	void getMapDataResponse(QString data);

public slots:
	void requestTimedOut();
};

#endif // TRAVIANAPI_HPP
