#ifndef KINGDOM_HPP
#define KINGDOM_HPP

#include <QString>
#include "Other/json.hpp"
#include "AppConfigs/Macros.hpp"

class Kingdom {
public:
	unsigned creationTime;
	unsigned kingdomId;
	QString kingdomTag;
	unsigned victoryPoints;

	Kingdom() = default;
	explicit Kingdom(const nlohmann::json& json) {
		*this = json.get<Kingdom>();
	}

private:
	friend void to_json(nlohmann::json&, const Kingdom&);
	friend void from_json(const nlohmann::json&, Kingdom&);
};

inline void to_json(nlohmann::json& json, const Kingdom& model) {
	json = { { "creationTime", std::to_string(model.creationTime) },
	         { "kingdomId", std::to_string(model.kingdomId) },
	         { "kingdomTag", model.kingdomTag.toStdString() },
	         { "victoryPoints", std::to_string(model.victoryPoints) } };
}

inline void from_json(const nlohmann::json& json, Kingdom& model) {
	model.creationTime = std::stoi(json.at("creationTime").get<std::string>());
	model.kingdomId = std::stoi(json.at("kingdomId").get<std::string>());
	model.kingdomTag = QString::fromStdString(json.at("kingdomTag").get<std::string>());
	model.victoryPoints = std::stoi(json.at("victoryPoints").get<std::string>());
}

#endif // KINGDOM_HPP
