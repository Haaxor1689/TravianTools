#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include <iostream>

#include "AppConfigs/AppConfigs.hpp"

class MainView: public QWidget {
	Q_OBJECT
	AddButton(requestApiKeyButton)
	AddButton(updateSiteDataButton)
	AddButton(getMapDataButton)
public:
	explicit MainView(QWidget *parent = nullptr);
	void paintEvent(QPaintEvent *);

signals:

};

#endif // MAINVIEW_HPP
