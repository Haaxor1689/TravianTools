#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include <QString>

#include "Other/json.hpp"

class Gameworld {
public:
	unsigned date;
	unsigned lastUpdateTime;
	QString name;
	unsigned speed;
	unsigned speedTroops;
	unsigned startTime;
	QString version;

	Gameworld() = default;
	explicit Gameworld(const nlohmann::json& json) {
		*this = json.get<Gameworld>();
	}

private:
	friend void to_json(nlohmann::json&, const Gameworld&);
	friend void from_json(const nlohmann::json&, Gameworld&);
};

inline void to_json(nlohmann::json& json, const Gameworld& model) {
	json = { { "date", model.date },
	         { "lastUpdateTime", model.lastUpdateTime },
	         { "name", model.name.toStdString() },
	         { "speed", model.speed },
	         { "speedTroops", model.speedTroops },
	         { "startTime", model.startTime },
	         { "version", model.version.toStdString() } };
}

inline void from_json(const nlohmann::json& json, Gameworld& model) {
	model.date = json.at("date").get<unsigned>();
	model.lastUpdateTime = std::stoi(json.at("lastUpdateTime").get<std::string>());
	model.name = QString::fromStdString(json.at("name").get<std::string>());
	model.speed = json.at("speed").get<unsigned>();
	model.speedTroops = json.at("speedTroops").get<unsigned>();
	model.startTime = json.at("startTime").get<unsigned>();
	model.version = QString::fromStdString(json.at("version").get<std::string>());
}

#endif // GAMEWORLD_HPP
