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
	         { "population", model.population },
	         { "villageId", model.villageId },
	         { "x", model.x },
	         { "y", model.y } };
}

inline void from_json(const nlohmann::json& json, Village& model) {
	model.isCity = json.at("isCity").get<bool>();
	model.isMainVillage = json.at("isMainVillage").get<bool>();
	model.name = QString::fromStdString(json.at("name").get<std::string>());
	model.population = Utilities::getInt(json.at("population"));
	model.villageId = Utilities::getInt(json.at("villageId"));
	model.x = Utilities::getInt(json.at("x"));
	model.y = Utilities::getInt(json.at("y"));
}

#endif // VILLAGE_HPP
