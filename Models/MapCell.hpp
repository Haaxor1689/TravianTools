#ifndef MAPCELL_HPP
#define MAPCELL_HPP

#include <QString>

#include "Other/json.hpp"

class Cell {
public:
	unsigned id;
	unsigned kingdomId;
	QString landscape;
	QString oasis;
	QString resType;
	int x;
	int y;

	Cell() = default;
	explicit Cell(const nlohmann::json& json) {
		*this = json.get<Cell>();
	}

private:
	friend void to_json(nlohmann::json&, const Cell&);
	friend void from_json(const nlohmann::json&, Cell&);
};

inline void to_json(nlohmann::json& json, const Cell& model) {
	json = { { "id", model.id },
	         { "kingdomId", model.kingdomId },
	         { "landscape", model.landscape.toStdString() },
	         { "oasis", model.oasis.toStdString() },
	         { "resType", model.resType.toStdString() },
	         { "x", model.x },
	         { "y", model.y } };
}

inline void from_json(const nlohmann::json& json, Cell& model) {
	model.id = std::stoi(json.at("id").get<std::string>());
	model.kingdomId = Utilities::getInt(json.at("kingdomId"));
	model.landscape = QString::fromStdString(json.at("landscape").get<std::string>());
	model.oasis = QString::fromStdString(json.at("oasis").get<std::string>());
	model.resType = QString::fromStdString(json.at("resType").get<std::string>());
	model.x = Utilities::getInt(json.at("x"));
	model.y = Utilities::getInt(json.at("y"));
}

#endif // MAPCELL_HPP
