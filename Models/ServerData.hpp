#ifndef SERVERDATA_HPP
#define SERVERDATA_HPP

#include <vector>

#include "Other/json.hpp"
#include "Gameworld.hpp"
#include "Kingdom.hpp"
#include "Map.hpp"
#include "Player.hpp"

class ServerData {
public:
	Gameworld gameworld;
	std::vector<Kingdom> kingdoms;
	Map map;
	std::vector<Player> players;

	ServerData() = default;
	explicit ServerData(const nlohmann::json& json) {
		*this = json.get<ServerData>();
	}

private:
	friend void to_json(nlohmann::json&, const ServerData&);
	friend void from_json(const nlohmann::json&, ServerData&);
};

inline void to_json(nlohmann::json& json, const ServerData& model) {
	json = { { "gameworld", model.gameworld },
	         { "kingdoms", model.kingdoms },
	         { "map", model.map },
	         { "players", model.players } };
}

inline void from_json(const nlohmann::json& json, ServerData& model) {
	model.gameworld = json.at("gameworld").get<Gameworld>();
	model.kingdoms = json.at("kingdoms").get<std::vector<Kingdom>>();
	model.map = json.at("map").get<Map>();
	model.players = json.at("players").get<std::vector<Player>>();
}

#endif // SERVERDATA_HPP
