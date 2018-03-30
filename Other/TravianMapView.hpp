#ifndef TRAVIANMAPVIEW_HPP
#define TRAVIANMAPVIEW_HPP

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMoveEvent>
#include <QWheelEvent>
#include <QDebug>
#include <QMap>

#include "AppConfigs/AppConfigs.hpp"
#include "Models/ServerData.hpp"

namespace TravianMap {
	QPoint getMapPosition(const QPointF& pos);
	QPoint getMapPosition(const QPoint& pos);
	QPoint getMapPosition(qreal x, qreal y);
	QPoint getScenePosition(const QPoint& pos);
	QPoint getScenePosition(int x, int y);
}

class GraphicsView: public QGraphicsView {
public:
	explicit GraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);
	void wheelEvent(QWheelEvent* event);

private:
	qreal zoomLevel;
};

class GraphicsScene: public QGraphicsScene {
public:
	explicit GraphicsScene(QWidget* parent = nullptr);
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
	bool hasMoved;
};

class TravianCellItem: public QGraphicsPixmapItem {
public:
	explicit TravianCellItem(const QPixmap &pixmap, const QPoint& worldPos);
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	void setLandscape(const QString& landscape);
	void setOasis(const QString& oasis);
	void setCity(Player::Tribe tribe, int population, bool isCity);
private:
	const QPoint worldPos;
	QGraphicsPixmapItem* landscapeItem;
	QGraphicsPixmapItem* oasisItem;
	QGraphicsPixmapItem* cityItem;
};

class TravianMapView: public QWidget {
	Q_OBJECT
public:
	explicit TravianMapView(QWidget *parent = nullptr);

	TravianCellItem* getCellAt(int x, int y) const;
	TravianCellItem* getCellAt(const QPoint& position) const;
	void populateWithData(const ServerData& data);
	void setGeometry(const QRect& rect);
	void setGeometry(int x, int y, int w, int h);

private:
	GraphicsScene* mapScene;
	GraphicsView* mapView;
	QMap<QPoint, TravianCellItem*> cells;

signals:

public slots:

};

#endif // TRAVIANMAPVIEW_HPP
