// Arquivo Guild_system.hpp
// Criado em05/07/22, por LUISMK
// Definicao da classe Room

#pragma once
#ifndef _STDA_GUILD_SYSTEM_HPP
#define _STDA_GUILD_SYSTEM_HPP

#include "../../Projeto IOCP/TYPE/singleton.h"
#include "../SESSION/player.hpp"
// MAPAS IDS
#define BLUE_LAGOON     0x00
#define BLUE_WATER      0x01
#define SEPIA_WIND      0x02
#define WIND_HILL       0x03
#define WIZWIZ          0x04
#define WESTWIZ         0x05
#define BLUE_MOON       0x06
#define SILVIA_CANNON   0x07
#define ICE_CANNON      0x08
#define WHITEWIZ        0x09
#define SHINING_SAND    0x0A
#define WIND            0x0B
#define UNKNOWN         0x0C
#define DEEP_INFERNO    0x0D
#define ICE_SPA         0x0E
#define LOST_SEAWAY     0x0F
#define EASTERB_VALLEY  0x10
#define ICE_INFERNO     0x12
#define WIZCITY         0x13
#define ABBOT_MINE      0x14

#define RANDOM 0x7f

#define TIME_WAIT_MASTER 8

/*
0x40 - 40 minutos (1,6*40 = 64 = 0x40)
0x60 - 60 minutos (1,6*60 = 96 = 0x60)
0x90 - 90 minutos (1,6*90 = 144 = 0x90)
0xC0 - 120 minutos (1,6*120 = 192 = 0xC0)
*/
#define TIME_TRASF_HEX 1.6f
#define OFFSET_60_MINUTOS 0xEA


static int quantity_player_confirmed = 0;


namespace stdA {

	class Room {

	public:
		Room();
		virtual ~Room();

		
		ClientRoomInfo create_room(std::string room_name, int player_num, int hole_num, int type_map, unsigned int time_min, std::string password);
			void enter_room(player* _session, unsigned short sala_id, std::string senha);
		void ReadyRoom(player _session, bool type);
		void MasterPlayerGame(player _session);
		
	};

	typedef Singleton< Room > sRoom;
}

#endif // !_STDA_Guild_SYSTEM_HPP
