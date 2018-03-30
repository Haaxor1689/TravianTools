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
	         { "kingdomId", model.kingdomId },
	         { "name", model.name.toStdString() },
	         { "playerId", model.playerId },
	         { "role", static_cast<int>(model.role) },
	         { "treasures", model.treasures },
	         { "tribeId", static_cast<int>(model.tribeId) },
	         { "villages", model.villages } };
}

inline void from_json(const nlohmann::json& json, Player& model) {
	model.externalLoginToken = QString::fromStdString(json.at("externalLoginToken").get<std::string>());
	model.kingdomId = Utilities::getInt(json.at("kingdomId"));
	model.name = QString::fromStdString(json.at("name").get<std::string>());
	model.playerId = Utilities::getInt(json.at("playerId"));
	model.role = static_cast<Player::Role>(Utilities::getInt(json.at("role")));
	model.treasures = Utilities::getInt(json.at("treasures"));
	model.tribeId = static_cast<Player::Tribe>(Utilities::getInt(json.at("tribeId")));
	model.villages = json.at("villages").get<std::vector<Village>>();
}

#endif // PLAYER_HPP
