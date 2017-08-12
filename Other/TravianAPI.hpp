#ifndef TRAVIANAPIREQUEST_HPP
#define TRAVIANAPIREQUEST_HPP

#include <string>

class TravianAPI {
public:
	TravianAPI() = delete;

	static void requestApiKey(const std::string& email, const std::string& siteName, const std::string& siteURL, bool isPublic);
	static void updateSiteData(const std::string& privateApiKey, const std::string& email, const std::string& siteName, const std::string& siteURL, bool isPublic);
	static void getMapData(const std::string& privateApiKey);
private:
	static void sendRequest(std::initializer_list<std::pair<std::string, std::string>> list);
signals:
	static void requestApiKeyResponse(QString data);
	static void updateSiteDataResponse(QString data);
	static void getMapDataResponse(QString data);
};

#endif // TRAVIANAPIREQUEST_HPP
