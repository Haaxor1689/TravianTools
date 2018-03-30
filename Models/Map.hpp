#ifndef MAP_HPP
#define MAP_HPP

#include <QString>

#include "Other/json.hpp"
#include "MapCell.hpp"

class Map {
public:
	std::vector<Cell> cells;
	unsigned radius;

	Map() = default;
	explicit Map(const nlohmann::json& json) {
		*this = json.get<Map>();
	}

private:
	friend void to_json(nlohmann::json&, const Map&);
	friend void from_json(const nlohmann::json&, Map&);
};

inline void to_json(nlohmann::json& json, const Map& model) {
	json = { { "cells", model.cells },
	         { "radius", model.radius } };
}

inline void from_json(const nlohmann::json& json, Map& model) {
	model.cells = json.at("cells").get<std::vector<Cell>>();
	model.radius = std::stoi(json.at("radius").get<std::string>());
}

#endif // MAP_HPP
