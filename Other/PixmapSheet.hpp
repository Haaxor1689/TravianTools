#ifndef PIXMAPSHEET_HPP
#define PIXMAPSHEET_HPP

#include <QPixmap>
#include <QMap>

class PixmapSheet {
public:
	explicit PixmapSheet(const QString& fileName) : _pixmap(fileName) {}
	PixmapSheet(const PixmapSheet& other) : _pixmap(other._pixmap), _aliases(other._aliases) {}
	void operator=(const PixmapSheet& other) {
		_pixmap = other._pixmap;
		_aliases = other._aliases;
	}

	QPixmap operator()(const QString& key) const {
		if (!_aliases.contains(key)) {
			qWarning() << "Tried to get value for " << key << " which isn't inside PixmapSheet.";
			return QPixmap();
		}

		return _pixmap.copy(_aliases.value(key));
	}

	void addKey(const QString& key, const QRect& rect) {
		if (!_pixmap.rect().contains(rect)) {
			qWarning() << "Tried to save rectangle out of bounds for " << key << ".";
			return;
		}

		_aliases.insert(key, rect);
	}

private:
	QPixmap _pixmap;
	QMap<QString, QRect> _aliases;

signals:

public slots:
};

#endif // PIXMAPSHEET_HPP
