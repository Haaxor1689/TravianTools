#ifndef VILLAGE_HPP
#define VILLAGE_HPP

#include <QString>

#include "Other/json.hpp"

class Village {
public:
	bool isCity;
	bool isMainVillage;
	QString name;
	unsigned population;
	unsigned villageId;
	int x;
	int y;

	Village() = default;
	explicit Village(const nlohmann::json& json) {
		*this = json.get<Village>();
	}

private:
	friend void to_json(nlohmann::json&, const Village&);
	friend void from_json(const nlohmann::json&, Village&);
};

inline void to_json(nlohmann::json& json, const Village& model) {
	json = { { "isCity", model.isCity },
	         { "isMainVillage", model.isMainVillage },
	         { "name", model.name.toStdString() },
	         { "population", std::to_string(model.population) },
	         { "villageId", std::to_string(model.villageId) },
	         { "x", std::to_string(model.x) },
	         { "y", std::to_string(model.y) } };
}

inline void from_json(const nlohmann::json& json, Village& model) {
	model.isCity = json.at("isCity").get<bool>();
	model.isMainVillage = json.at("isMainVillage").get<bool>();
	model.name = QString::fromStdString(json.at("name").get<std::string>());
	model.population = std::stoi(json.at("population").get<std::string>());
	model.villageId = std::stoi(json.at("villageId").get<std::string>());
	model.x = std::stoi(json.at("x").get<std::string>());
	model.y = std::stoi(json.at("y").get<std::string>());
}

#endif // VILLAGE_HPP
