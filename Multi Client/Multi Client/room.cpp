// Arquivo Room.cpp
// Implementa��o da classe Room

#if defined(_WIN32)
#pragma pack(1)
#endif

#if defined(_WIN32)
#include <WinSock2.h>
#endif

#include "room.hpp"


#include "../../Projeto IOCP/UTIL/exception.h"
#include "../../Projeto IOCP/TYPE/stda_error.h"
#include "../../Projeto IOCP/UTIL/message_pool.h"
#include "../PACKET/packet_func_client.h"


#include "../../Projeto IOCP/DATABASE/normal_manager_db.hpp"

#include "../../Projeto IOCP/UTIL/string_util.hpp"

#define CHECK_SESSION_BEGIN(method) if (!_session.getState()) \
										throw exception("[Room" + std::string((method)) +"][Error] player nao esta connectado.", STDA_MAKE_ERROR(STDA_ERROR_TYPE::GUILD, 1, 0)); \



using namespace stdA;

Room::Room()
{
}

Room::~Room()
{
}


// DB 2A 00 18 C8 08 00 00 40 9C 00 00 00 00 00 00 02 00 03 0D 00 0D 00 43 68 61 6C 6C 65 6E 67 65 20 4D 65 21 04 00 31 32 33 35 00 00 00 00
ClientRoomInfo Room::create_room( std::string room_name, int player_num, int hole_num, int type_map, unsigned int time_min, std::string password)
{
	float time_hex = time_min * TIME_TRASF_HEX;

	ClientRoomInfo room;
	auto tmp = time_min * OFFSET_60_MINUTOS / 60;

	strcpy_s(room.nome, room_name.c_str());
	room.max_player = player_num;
	room.qntd_hole = hole_num;
	room.course = ServerRoomInfo::eCOURSE(type_map);
	room.time_30s = time_hex;
	room.modo = 0;
	room.tipo_show = 0;
	strcpy_s(room.senha, password.c_str());

	return room;
}

void Room::enter_room(player* _session, unsigned short sala_id, std::string senha)
{
	// Tenta entrar na sala 0
	packet p((unsigned short)0x09);

	p.addUint16(sala_id);	// Sala Número 0
	if (senha.size() == 0)
	{
		p.addUint16(0u);	// Nenhum senha
	}
	else
	{
		p.addString(senha);
	}
	packet_func::session_send(p, _session, 1);
}

void Room::ReadyRoom(player _session, bool type)
{
	packet p((unsigned short)0x0D);	// Estado de Ready do player na sala
	p.addUint8(type == true ? 0 : 1);
	packet_func::session_send(p, &_session, 1);
};


void Room::MasterPlayerGame(player _session)
{
	auto r = create_room("teste", 1, 18, 0, 35, "");

	packet p;

	p.init_plain((unsigned short)0x08);
	p.addBuffer(&r, sizeof(ClientRoomInfo));
	packet_func::session_send(p, &_session, 1);
}



