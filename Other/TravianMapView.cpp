#include "TravianMapView.hpp"

#include <QCoreApplication>

using namespace TravianMap;

bool operator<(const QPoint& lhs, const QPoint& rhs) {
	return std::to_string(lhs.x()) + std::to_string(lhs.y()) < std::to_string(rhs.x()) + std::to_string(rhs.y());
}

// TravianMap
QPoint TravianMap::getMapPosition(const QPointF& pos) {
	return getMapPosition(int(pos.x()), int(pos.y()));
}

QPoint TravianMap::getMapPosition(const QPoint& pos) {
	return getMapPosition(pos.x(), pos.y());
}

QPoint TravianMap::getMapPosition(qreal x, qreal y) {
	return { int(x / Defaults::cellWidth()),
		     int(-y / Defaults::cellHeight()) };
}

QPoint TravianMap::getScenePosition(const QPoint& pos) {
	return getScenePosition(pos.x(), pos.y());
}

QPoint TravianMap::getScenePosition(int x, int y) {
	return { (Defaults::cellWidth() / 2) * (x + y), (Defaults::cellHeight() / 2) * (x - y) };
}

// GraphicsView
GraphicsView::GraphicsView(QGraphicsScene* scene, QWidget* parent) : QGraphicsView(scene, parent), zoomLevel(1) {}

void GraphicsView::wheelEvent(QWheelEvent* event) {
	event->delta() > 0 ? zoomLevel += 2 : zoomLevel -= 2;
	qDebug() << "Scale is " << zoomLevel << "x.";

	qreal scaleFactor = zoomLevel < 0.0 ? 1.0 / abs(zoomLevel) : zoomLevel;
	QMatrix transformMatrix;
	transformMatrix.scale(scaleFactor, scaleFactor);
	setMatrix(transformMatrix);
}

// GraphicsScene
GraphicsScene::GraphicsScene(QWidget* parent) : QGraphicsScene(parent), hasMoved(true) {}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	QGraphicsScene::mousePressEvent(event);

//	if (event->button() == Qt::MouseButton::LeftButton) {
//		hasMoved = false;
//		return;
//	}
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
	QGraphicsScene::mouseMoveEvent(event);

//	hasMoved = true;
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
	QGraphicsScene::mouseReleaseEvent(event);

//	if (event->button() == Qt::MouseButton::LeftButton && !hasMoved) {
//		qDebug() << event->scenePos() << getMapPosition(event->scenePos());
//	}
}

// TravianCellItem
TravianCellItem::TravianCellItem(const QPixmap& pixmap, const QPoint& worldPos) : QGraphicsPixmapItem(pixmap, nullptr), worldPos(worldPos) {
	setOffset(getScenePosition(worldPos));
}

void TravianCellItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	QGraphicsPixmapItem::mousePressEvent(event);
	qDebug() << "Cell at" << worldPos;
}

void TravianCellItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
	QGraphicsPixmapItem::mouseReleaseEvent(event);
	qDebug() << "Cell at" << worldPos;
}

void TravianCellItem::setLandscape(const QString& landscape) {
	auto cellPixmap = Defaults::mapSheet()(landscape);
	landscapeItem = new QGraphicsPixmapItem(cellPixmap, this);
	landscapeItem->setOffset({ offset().x(), offset().y() - (cellPixmap.height() == Defaults::cellOverlayHeight() ? 16.0 : 0.0) });
}

void TravianCellItem::setOasis(const QString& oasis) {
	if (oasis != "0") {
		auto cellPixmap = Defaults::mapSheet()("o" + oasis);
		oasisItem = new QGraphicsPixmapItem(cellPixmap, this);
		oasisItem->setOffset({ offset().x() - qreal(cellPixmap.width() / 2 - Defaults::cellWidth() / 2),
		                       offset().y() -qreal(cellPixmap.height() / 2 - Defaults::cellHeight() / 2) });
	}
}

void TravianCellItem::setCity(Player::Tribe tribe, int population, bool isCity) {
	QString pixmapKey;
	switch (tribe) {
	    case Player::Tribe::Roman: pixmapKey = "roman"; break;
	    case Player::Tribe::Teuton: pixmapKey = "teuton"; break;
	    case Player::Tribe::Gaul: pixmapKey = "gaul"; break;
	}
	if (isCity) {
		pixmapKey.append("City");
	} else if (population < 100) {
		pixmapKey.append("Tiny");
	} else if (population < 250) {
		pixmapKey.append("Small");
	} else if (population < 500) {
		pixmapKey.append("Medium");
	} else if (population < 1000) {
		pixmapKey.append("Big");
	} else {
		pixmapKey.append("Huge");
	}

	auto cellPixmap = Defaults::mapSheet()(pixmapKey);
	cityItem = new QGraphicsPixmapItem(cellPixmap, this);
	cityItem->setOffset(offset());
}

// TravianMapView
TravianMapView::TravianMapView(QWidget *parent): QWidget(parent) {
	mapScene = new GraphicsScene(this);
	mapView = new GraphicsView(mapScene, this);
	mapView->setDragMode(QGraphicsView::ScrollHandDrag);
	mapView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	mapView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

TravianCellItem*TravianMapView::getCellAt(int x, int y) const {
	return getCellAt({ x, y });
}

TravianCellItem* TravianMapView::getCellAt(const QPoint& position) const {
	auto iter = cells.find(position);

	if (iter == cells.end()) {
		qWarning() << "Cell at" << position << "doesn't exist";
		return nullptr;
	}
	return iter.value();
}

void TravianMapView::populateWithData(const ServerData& data) {
	int refreshCountdown = 100;
	for (int j = -int(data.map.radius); j <= int(data.map.radius); ++j) {
		for (int i = -int(data.map.radius); i <= int(data.map.radius); ++i) {
			auto cell = new TravianCellItem(Defaults::mapSheet()("grass"), { i, j });
			mapScene->addItem(cell);
			cells.insert({ i, j }, cell);

			--refreshCountdown;
			if (refreshCountdown == 0) {
				QCoreApplication::processEvents();
				refreshCountdown = 100;
			}
		}
	}

	for (const auto& mapCell : data.map.cells) {
		auto cell = getCellAt(mapCell.x, mapCell.y);
		if (cell) {
			cell->setLandscape(mapCell.landscape);
			cell->setOasis(mapCell.oasis);
		}

		--refreshCountdown;
		if (refreshCountdown == 0) {
			QCoreApplication::processEvents();
			refreshCountdown = 100;
		}
	}

	for (const auto& player : data.players) {
		for (const auto& village : player.villages) {
			auto cell = getCellAt(village.x, village.y);
			if (cell) {
				cell->setCity(player.tribeId, village.population, village.isCity);
			}

			--refreshCountdown;
			if (refreshCountdown == 0) {
				QCoreApplication::processEvents();
				refreshCountdown = 100;
			}
		}
	}

	mapView->centerOn(getCellAt(0, 0));
}

void TravianMapView::setGeometry(const QRect& rect) {
	QWidget::setGeometry(rect);
	mapView->setGeometry(0, 0, rect.width(), rect.height());
}

void TravianMapView::setGeometry(int x, int y, int w, int h) {
	setGeometry(QRect(x, y, w, h));
}
