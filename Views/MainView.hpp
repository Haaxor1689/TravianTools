#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include <iostream>

#include "AppConfigs/AppConfigs.hpp"
#include "Models/ServerData.hpp"

class MainView: public QWidget {
	Q_OBJECT
	AddButton(requestApiKeyButton)
	AddButton(updateSiteDataButton)
	AddButton(getMapDataButton)
public:
	ServerData serverData;

	explicit MainView(QWidget *parent = nullptr);
	void paintEvent(QPaintEvent *);

signals:

public slots:
	void requestApiKeyResponse(QString data);
	void updateSiteDataResponse(QString data);
	void getMapDataResponse(QString data);
};

#endif // MAINVIEW_HPP
