#include "TravianAPI.hpp"

#include <windows.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <future> // std::async

using namespace std;

#pragma comment(lib,"ws2_32.lib")

void TravianAPI::requestApiKey(const std::string& email, const std::string& siteName, const std::string& siteURL, bool isPublic) {

}

void TravianAPI::updateSiteData(const std::string& privateApiKey, const std::string& email, const std::string& siteName, const std::string& siteURL, bool isPublic) {

}

void TravianAPI::getMapData(const std::string& privateApiKey) {
	auto response = std::async(std::launch::async, sendRequest, {{"privateApiKey", privateApiKey}}});
}

std::string TravianAPI::sendRequest(std::initializer_list<std::pair<string, string> > list) {
	if (WSAStartup(0x101, &wsaData) != 0)
		throw std::exception("Error occured in WSAStartup.");

	long responseSize;
	char* headerBuffer;
}

HINSTANCE hInst;
WSADATA wsaData;
void mParseUrl(string url, string& serverName, string& filepath, string& filename);
SOCKET connectToServer(char* szServerName, WORD portNum);
int getHeaderLength(char* content);
char* readUrl2(string& szUrl, long& bytesReturnedOut, char** headerOut);

int main() {
	const int bufLen = 1024;
	string szUrl = "http://com1x3.kingdoms.com/api/external.php";

	long fileSize;

	char* headerBuffer = nullptr;

	if (WSAStartup(0x101, &wsaData) != 0)
		return -1;

	char* memBuffer = readUrl2(szUrl, fileSize, &headerBuffer);

	cout << "Returned from readUrl" << endl;
	cout << "Data returned:\n" << memBuffer << endl;

	if (fileSize != 0) {
		cout << "Got some data" << endl;

		FILE * fp = fopen("downloaded.txt", "wb");
		fwrite(memBuffer, 1, fileSize, fp);
		fclose(fp);
		delete(memBuffer);
		delete(headerBuffer);
	}

	WSACleanup();
	return 0;
}

void mParseUrl(string url, string& serverName, string& filepath, string& filename) {
	if (url.substr(0, 7) == "http://")
		url.erase(0, 7);

	if (url.substr(0, 8) == "https://")
		url.erase(0, 8);

	auto n = url.find('/');
	if (n != string::npos) {
		serverName = url.substr(0, n);
		filepath = url.substr(n);
		n = filepath.rfind('/');
		filename = filepath.substr(n + 1);
	} else {
		serverName = url;
		filepath = "/";
		filename = "";
	}
}

SOCKET connectToServer(char* szServerName, WORD portNum) {
	struct hostent* hp;
	struct sockaddr_in server;

	SOCKET conn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (conn == INVALID_SOCKET)
		return NULL;

	if (inet_addr(szServerName) == INADDR_NONE) {
		hp = gethostbyname(szServerName);
	} else {
		unsigned int addr = inet_addr(szServerName);
		hp = gethostbyaddr(reinterpret_cast<char*>(&addr), sizeof(addr), AF_INET);
	}

	if (hp == nullptr) {
		closesocket(conn);
		return NULL;
	}

	server.sin_addr.s_addr = *reinterpret_cast<unsigned long*>(hp->h_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(portNum);
	if (connect(conn, reinterpret_cast<struct sockaddr*>(&server), sizeof(server))) {
		closesocket(conn);
		return NULL;
	}
	return conn;
}

int getHeaderLength(char* content) {
	const char* srchStr1 = "\r\n\r\n", * srchStr2 = "\n\r\n\r";
	int ofset = -1;

	char * findPos = strstr(content, srchStr1);
	if (findPos != nullptr) {
		ofset = findPos - content;
		ofset += strlen(srchStr1);
	} else {
		findPos = strstr(content, srchStr2);
		if (findPos != nullptr) {
			ofset = findPos - content;
			ofset += strlen(srchStr2);
		}
	}
	return ofset;
}

char* readUrl2(string& szUrl, long& bytesReturnedOut, char** headerOut) {
	const int bufSize = 1024;
	char readBuffer[bufSize];
	char sendBuffer[bufSize];
	char tmpBuffer[bufSize];
	char* tmpResult = nullptr;

	string server, filepath, filename;

	mParseUrl(szUrl, server, filepath, filename);

	///////////// step 1, connect //////////////////////
	SOCKET conn = connectToServer(&server[0], 80);
	//SOCKET conn = connectToServer("http://com1x3.kingdoms.com/", 80);

	///////////// step 2, send GET request /////////////
	sprintf(tmpBuffer, "GET %s HTTP/1.0", filepath.c_str());
	strcpy(sendBuffer, tmpBuffer);
	strcat(sendBuffer, "\r\n");
	sprintf(tmpBuffer, "Host: %s", server.c_str());
	strcat(sendBuffer, tmpBuffer);
	strcat(sendBuffer, "\r\n");
	strcat(sendBuffer, "\r\n");

	string message = "GET /api/external.php?action=requestApiKey&email=betkomaros@gmail.com&siteName=TestTool&siteUrl=https://github.com/Haaxor1689&public=false HTTP/1.0\r\nHost: com1x3.kingdoms.com\r\n\r\n";

	//send(conn, sendBuffer, strlen(sendBuffer), 0);
	send(conn, &message[0], message.length(), 0);

	//    SetWindowText(edit3Hwnd, sendBuffer);
	printf("Buffer being sent:\n%s", sendBuffer);

	///////////// step 3 - get received bytes ////////////////
	// Receive until the peer closes the connection
	long totalBytesRead = 0;
	while (true) {
		memset(readBuffer, 0, bufSize);
		long thisReadSize = recv(conn, readBuffer, bufSize, 0);

		if (thisReadSize <= 0)
			break;

		tmpResult = (char*)realloc(tmpResult, thisReadSize + totalBytesRead);

		memcpy(tmpResult + totalBytesRead, readBuffer, thisReadSize);
		totalBytesRead += thisReadSize;
	}

	long headerLen = getHeaderLength(tmpResult);
	long contenLen = totalBytesRead - headerLen;
	char* result = new char[contenLen + 1];
	memcpy(result, tmpResult + headerLen, contenLen);
	result[contenLen] = 0x0;

	char * myTmp = new char[headerLen + 1];
	strncpy(myTmp, tmpResult, headerLen);
	myTmp[headerLen] = NULL;
	delete(tmpResult);
	*headerOut = myTmp;

	bytesReturnedOut = contenLen;
	closesocket(conn);
	return (result);
}
