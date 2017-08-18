#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QString>

#include "Other/json.hpp"
#include "Village.hpp"

class Player {
public:
	enum class Role {
		None = 0,
		King = 1,
		Duke = 2,
		Governor = 3
	};
	enum class Tribe {
		Roman = 1,
		Gaul = 2,
		Teuton = 3
	};

	QString externalLoginToken;
	unsigned kingdomId;
	QString name;
	unsigned playerId;
	Role role;
	unsigned treasures;
	Tribe tribeId;
	std::vector<Village> villages;

	Player() = default;
	explicit Player(const nlohmann::json& json) {
		*this = json.get<Player>();
	}
private:
	friend void to_json(nlohmann::json&, const Player&);
	friend void from_json(const nlohmann::json&, Player&);
};

inline void to_json(nlohmann::json& json, const Player& model) {
	json = { { "externalLoginToken", model.externalLoginToken.toStdString() },
	         { "kingdomId", std::to_string(model.kingdomId) },
	         { "name", model.name.toStdString() },
	         { "playerId", std::to_string(model.playerId) },
	         { "role", static_cast<int>(model.role) },
	         { "treasures", model.treasures },
	         { "tribeId", std::to_string(static_cast<int>(model.tribeId)) },
	         { "villages", model.villages } };
}

inline void from_json(const nlohmann::json& json, Player& model) {
	model.externalLoginToken = QString::fromStdString(json.at("externalLoginToken").get<std::string>());
	model.kingdomId = std::stoi(json.at("kingdomId").get<std::string>());
	model.name = QString::fromStdString(json.at("name").get<std::string>());
	model.playerId = std::stoi(json.at("playerId").get<std::string>());
	model.role = static_cast<Player::Role>(json.at("role").get<int>());
	model.treasures = json.at("treasures").get<unsigned>();
	model.tribeId = static_cast<Player::Tribe>(std::stoi(json.at("tribeId").get<std::string>()));
	model.villages = json.at("villages").get<std::vector<Village>>();
}

#endif // PLAYER_HPP
