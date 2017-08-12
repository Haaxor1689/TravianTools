#include "MainView.hpp"

#include <QApplication>
#include <QStyleOption>
#include <QPainter>

#include "AppConfigs/AppConfigs.hpp"

// App entry point
int main(int argc, char **argv) {
	QApplication app (argc, argv);
	new MainView();
	return app.exec();
}

MainView::MainView(QWidget *parent) : QWidget(parent) {
	setFixedSize(800, 600);
	setStyleSheet(StyleSheet::normal());

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

void MainView::requestApiKeyButtonTapped() {
	std::cout << "requestApiKeyButtonTapped" << std::endl;
}

void MainView::updateSiteDataButtonTapped() {
	std::cout << "updateSiteDataButtonTapped" << std::endl;
}

void MainView::getMapDataButtonTapped() {
	std::cout << "getMapDataButtonTapped" << std::endl;
}
