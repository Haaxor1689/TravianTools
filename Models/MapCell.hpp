#ifndef MAPCELL_HPP
#define MAPCELL_HPP

#include "Other/json.hpp"

class MapCell {
public:
	unsigned id;
	unsigned kingdomId;
	unsigned landscape;
	unsigned oasis;
	unsigned resType;
	int x;
	int y;

	MapCell() = default;
	explicit MapCell(const nlohmann::json& json) {
		*this = json.get<MapCell>();
	}

private:
	friend void to_json(nlohmann::json&, const MapCell&);
	friend void from_json(const nlohmann::json&, MapCell&);
};

inline void to_json(nlohmann::json& json, const MapCell& model) {
	json = { { "id", std::to_string(model.id) },
	         { "kingdomId", std::to_string(model.kingdomId) },
	         { "landscape", std::to_string(model.landscape) },
	         { "oasis", std::to_string(model.oasis) },
	         { "resType", std::to_string(model.id) },
	         { "x", std::to_string(model.x) },
	         { "y", std::to_string(model.y) } };
}

inline void from_json(const nlohmann::json& json, MapCell& model) {
	model.id = std::stoi(json.at("id").get<std::string>());
	model.kingdomId = std::stoi(json.at("kingdomId").get<bool>());
	model.landscape = std::stoi(json.at("landscape").get<std::string>());
	model.oasis = std::stoi(json.at("oasis").get<std::string>());
	model.resType = std::stoi(json.at("resType").get<std::string>());
	model.x = std::stoi(json.at("x").get<std::string>());
	model.y = std::stoi(json.at("y").get<std::string>());
}

#endif // MAPCELL_HPP
