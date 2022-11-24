// Arquivo Guild_system.cpp
// Implementa��o da classe GuildSystem

#if defined(_WIN32)
#pragma pack(1)
#endif

#if defined(_WIN32)
#include <WinSock2.h>
#endif

#include "guild_system.hpp"

#include "item_manager.h"
#include "../../Projeto IOCP/UTIL/exception.h"
#include "../../Projeto IOCP/TYPE/stda_error.h"
#include "../../Projeto IOCP/UTIL/message_pool.h"
#include "../PACKET/packet_func_sv.h"

#include "../PANGYA_DB/cmd_guild_info_list.hpp"
#include "../PANGYA_DB/cmd_guild_infos.hpp"
#include "../PANGYA_DB/cmd_guild_log.hpp"
#include "../../Projeto IOCP/DATABASE/normal_manager_db.hpp"

#include "../../Projeto IOCP/UTIL/string_util.hpp"
#include "../PANGYA_DB/cmd_guild_member.hpp"
#include "../PANGYA_DB/cmd_guild_promote.hpp"
#include "../PANGYA_DB/cmd_guild_create.hpp"
#include "../PANGYA_DB/cmd_guild_available.hpp"
#include "../PANGYA_DB/cmd_guild_join.hpp"
#include "../PANGYA_DB/cmd_guild_aceita.hpp"
#include "../PANGYA_DB/cmd_guild_info.hpp"
#include "../PANGYA_DB/cmd_guild_kick.hpp"
#include "../PANGYA_DB/cmd_update_guild_intro.hpp"
#include "../PANGYA_DB/cmd_update_guild_msg.hpp"
#include "../PANGYA_DB/cmd_guild_message.hpp"
#include "../PANGYA_DB/cmd_guild_image.hpp"
#include "../PANGYA_DB/cmd_guild_mark.hpp"
#include "../PANGYA_DB/cmd_guild_cancel.hpp"
#define CHECK_SESSION_BEGIN(method) if (!_session.getState()) \
										throw exception("[GuildSystem" + std::string((method)) +"][Error] player nao esta connectado.", STDA_MAKE_ERROR(STDA_ERROR_TYPE::GUILD, 1, 0)); \



using namespace stdA;

GuildSystem::GuildSystem()
{
}

GuildSystem::~GuildSystem()
{
}

void GuildSystem::requestCallGuildList(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("PlayerCallGuildList");

	packet header;
	packet p;
	try
	{
		auto PageSelected = _packet->readUint32();

		CmdGuildInfos guild_list(PageSelected, 0, true);	// Waiter

		snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

		guild_list.waitEvent();

		if (guild_list.getException().getCodeError() != 0)
			throw guild_list.getException();

		_smp::message_pool::getInstance().push(new message("[GuildSystem::PlayerCallGuildList][Log] player[UID=" + std::to_string(_session.m_pi.uid) + "] Page[number=" + std::to_string(PageSelected) + "]", CL_FILE_LOG_AND_CONSOLE));

		auto v_element = guild_list.getInfo();
		p.init_plain((unsigned short)0x1BC);
		p.addUint32(1);
		p.addUint32(PageSelected);
		p.addUint32((uint32_t)v_element.size());
		p.addUint16((uint16_t)v_element.size());
		for (auto& guild : v_element)
		{
			p.addBuffer(&guild.second, sizeof(GuildInfoList));
		}
		packet_func::session_send(p, &_session, 1);
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::PlayerCallGuildList][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1BC);
		p.addUint32((STDA_SOURCE_ERROR_DECODE(e.getCodeError()) == STDA_ERROR_TYPE::CHANNEL) ? STDA_SYSTEM_ERROR_DECODE(e.getCodeError()) : 0x6300300);
		packet_func::session_send(p, &_session, 1);
	}

}

void GuildSystem::requestCallGuildSearch(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("PlayerCallGuildSearch");

	packet p;
	try
	{

		auto PageSelected = _packet->readUint32();
		auto findguild = _packet->readString();
		CmdGuildInfos guild_list(PageSelected, 0, 0, findguild, true);	// Waiter

		snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

		guild_list.waitEvent();

		if (guild_list.getException().getCodeError() != 0)
			throw guild_list.getException();

		_smp::message_pool::getInstance().push(new message("[GuildSystem::PlayerCallGuildSearch][Log] player[UID=" + std::to_string(0) + "] Page[number=" + std::to_string(PageSelected) + "]", CL_FILE_LOG_AND_CONSOLE));

		auto v_element = guild_list.getInfo();
		p.init_plain((unsigned short)0x1BD);
		p.addUint32(1);
		p.addUint32(PageSelected);
		p.addUint32((uint32_t)guild_list.getInfo(findguild).total_member);//total de membros
		p.addUint16((uint16_t)v_element.size());
		for (auto& guild : v_element)
		{
			p.addBuffer(&guild.second, sizeof(GuildInfoList));
		}
		packet_func::session_send(p, &_session, 1);
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::PlayerCallGuildSearch][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1BC);
		p.addUint32((STDA_SOURCE_ERROR_DECODE(e.getCodeError()) == STDA_ERROR_TYPE::CHANNEL) ? STDA_SYSTEM_ERROR_DECODE(e.getCodeError()) : 0x6300300);
		packet_func::session_send(p, &_session, 1);
	}
}

void GuildSystem::requestCallGuildData(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("PlayerCallGuildData");

	packet p;
	try
	{

		auto Guild_ID = _packet->readUint32();

		_smp::message_pool::getInstance().push(new message("[GuildSystem::RequestCallGuildData][Log] player[UID=" + std::to_string(0) + "] ID[number=" + std::to_string(Guild_ID) + "]", CL_FILE_LOG_AND_CONSOLE));

		_session.ReloadGuildInfo();

		p.init_plain((unsigned short)0x1B8);
		p.addUint32(1);
		if (Guild_ID == _session.guild_info.uid)
		{
			p.addBuffer(&_session.guild_info, sizeof(GuildInfoEx));
		}
		else
		{
			p.addZeroByte(sizeof(GuildInfoEx));
		}
		packet_func::session_send(p, &_session, 1);
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::RequestCallGuildData][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1BB);
		p.addUint32((STDA_SOURCE_ERROR_DECODE(e.getCodeError()) == STDA_ERROR_TYPE::CHANNEL) ? STDA_SYSTEM_ERROR_DECODE(e.getCodeError()) : 0x6300300);
		packet_func::session_send(p, &_session, 1);
	}
}

void GuildSystem::requestCallGuildLog(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("requestCallGuildLog");

	packet p;
	try
	{
		CmdGuildLog guild_list(_session.m_pi.uid, true);	// Waiter

		snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

		guild_list.waitEvent();

		if (guild_list.getException().getCodeError() != 0)
			throw guild_list.getException();

		p.init_plain((unsigned short)0x1BE);
		p.addUint32(1);
		p.addUint16(1);
		auto data = guild_list.getInfo();
		p.addBuffer(&data, sizeof(GuildLog)); //GuilD_IMAGE 
		packet_func::session_send(p, &_session, 1);
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::PlayerCallGuildLog][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1BC);
		p.addUint32((STDA_SOURCE_ERROR_DECODE(e.getCodeError()) == STDA_ERROR_TYPE::CHANNEL) ? STDA_SYSTEM_ERROR_DECODE(e.getCodeError()) : 0x6300300);
		packet_func::session_send(p, &_session, 1);
	}
}

void GuildSystem::requestCallGuildPlayer(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("requestCallGuildPlayer");

	packet p;
	try
	{
		auto Guild_ID = _packet->readUint32();
		auto PageSelected = _packet->readUint32();


		CmdGuildMemberInfo guild_list(Guild_ID, true);	// Waiter

		snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

		guild_list.waitEvent();

		if (guild_list.getException().getCodeError() != 0)
			throw guild_list.getException();

		auto v_element = guild_list.getInfo();
		p.init_plain((unsigned short)0x1C6);
		p.addUint32(1);
		p.addUint32(PageSelected);
		p.addUint32((uint32_t)v_element.size());
		p.addUint16((uint16_t)v_element.size());
		for (auto& guild : v_element)
		{
			p.addBuffer(&guild.second, sizeof(GuildMemberInfo));
		}

		packet_func::session_send(p, &_session, 1);
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::requestCallGuildPlayer][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1BC);
		p.addUint32((STDA_SOURCE_ERROR_DECODE(e.getCodeError()) == STDA_ERROR_TYPE::CHANNEL) ? STDA_SYSTEM_ERROR_DECODE(e.getCodeError()) : 0x6300300);
		packet_func::session_send(p, &_session, 1);
	}
}

void GuildSystem::requestCallGuildPromote(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("requestCallGuildPromote");

	packet p;
	try
	{
		auto Guild_ID = _packet->readUint32();
		auto UID = _packet->readUint32();
		auto Position = _packet->readUint32();
		CmdGuildPromote guild_list(Guild_ID, UID, Position, true);	// Waiter

		snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

		guild_list.waitEvent();

		if (guild_list.getException().getCodeError() != 0)
			throw guild_list.getException();

		p.init_plain((unsigned short)0x1C4);
		p.addUint32(guild_list.getInfo());
		p.addUint32(Position); //GuilD_IMAGE 
		packet_func::session_send(p, &_session, 1);
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::requestCallGuildPromote][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1C4);
		p.addUint32((STDA_SOURCE_ERROR_DECODE(e.getCodeError()) == STDA_ERROR_TYPE::CHANNEL) ? STDA_SYSTEM_ERROR_DECODE(e.getCodeError()) : 0x6300300);
		packet_func::session_send(p, &_session, 1);
	}
}

void GuildSystem::requestCallGuildCreate(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("requestCallGuildCreate");

	packet p;
	try
	{
		if (_session.guild_info.uid > 0)
		{
			throw exception("[guildsytem::requestCallGuildCreate][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", ja esta em guild ou ja tem uma ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));

		}
		if (_session.m_pi.ui.level < 11)
		{
			throw exception("[guildsytem::requestCallGuildCreate][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", nao tem level suficiente ! ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}
		// Update ON Server
		auto pWi = _session.m_pi.findWarehouseItemByTypeid(ITEM_CREATE_GUILD_TYPEID);

		if (pWi == nullptr)
		{
			throw exception("[guildsytem::requestCallGuildCreate][Error] player[UID=" + std::to_string(_session.m_pi.uid) + "] nao conseguiu excluir/(atualizar qntd) item[TYPEID="
				+ std::to_string(ITEM_CREATE_GUILD_TYPEID) + "]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));

		}
		std::vector< stItem > v_item;
		stItem item{ 0 };
		item.clear();

		item.type = 2;
		item._typeid = ITEM_CREATE_GUILD_TYPEID;
		item.id = pWi->id;
		item.qntd = 1;
		item.STDA_C_ITEM_QNTD = (short)item.qntd * -1;

		// //item que cria guild
		if (item_manager::removeItem(item, _session) <= 0)
			throw exception("[guildsytem::requestCallGuildCreate][Error] player[UID=" + std::to_string(_session.m_pi.uid) + "] nao conseguiu excluir/(atualizar qntd) item[TYPEID="
				+ std::to_string(item._typeid) + ", ID=" + std::to_string(item.id) + "]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));

		v_item.push_back(item);

		auto Name = _packet->readString();
		auto Intro = _packet->readString();
		CmdGuildMake guild_list(Name, Intro, true);	// Waiter

		snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

		guild_list.waitEvent();

		if (guild_list.getException().getCodeError() != 0)
			throw guild_list.getException();


		auto code = guild_list.getInfo();

		if (code == -3)
		{
			throw exception("[guildsytem::requestCallGuildCreate][ErrorCode] player[UID=" + std::to_string(_session.m_pi.uid) + "] nao tem pangs suficientes"
				+ std::to_string(ITEM_CREATE_GUILD_TYPEID) + "]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}


		if (code == -2)
		{
			throw exception("[guildsytem::requestCallGuildCreate][ErrorCode] player[UID=" + std::to_string(_session.m_pi.uid) + "] Não pode criar a guild, faz menos de 24 horas que ele criou outra guild"
				+ std::to_string(ITEM_CREATE_GUILD_TYPEID) + "]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}

		if (code == -4)
		{
			throw exception("[guildsytem::requestCallGuildCreate][ErrorCode] player[UID=" + std::to_string(_session.m_pi.uid) + "] Player já é membro de outra guild, saia dela para poder criar outra guild"
				+ std::to_string(ITEM_CREATE_GUILD_TYPEID) + "]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}

		if (code > 0)
		{
			p.init_plain((unsigned short)0x0C5);
			p.addUint8(1);
			p.addUint32(item._typeid); //GuilD_IMAGE 
			p.addUint32(1); //GuilD_IMAGE 
			p.addUint32(pWi->id); //GuilD_IMAGE 
			packet_func::session_send(p, &_session, 1);

			p.init_plain((unsigned short)0x1B5);

			p.addUint32(1);
			packet_func::session_send(p, &_session, 1);

			_session.m_pi.gi.uid = code;//seta o guild id

			_session.SendGuildData();
		}
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::requestCallGuildCreate][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1C4);
		p.addUint32(54001);
		packet_func::session_send(p, &_session, 1);
	}
}

void GuildSystem::requestCallGuildCheckName(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("requestCallGuildCheckName");

	packet p;
	try
	{
		if (_session.guild_info.uid > 0)
		{
			throw exception("[guildsytem::requestCallGuildCheckName][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", ja esta em guild ou ja tem uma ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));

		}
		if (_session.m_pi.ui.level < 11)
		{
			throw exception("[guildsytem::requestCallGuildCheckName][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", nao tem level suficiente ! ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}
		auto Name = _packet->readString();
		CmdGuildAvailable guild_list(Name, true);	// Waiter

		snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

		guild_list.waitEvent();

		if (guild_list.getException().getCodeError() != 0)
			throw guild_list.getException();


		auto code = guild_list.getInfo();
		//sucess ! 
		if (code == 0)
		{
			p.init_plain((unsigned short)0x1B6);

			p.addUint32(1);
			p.addString(Name);
			packet_func::session_send(p, &_session, 1);
		}
		else
		{
			throw exception("[guildsytem::requestCallGuildCheckName][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", guild name ja existe ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::requestCallGuildCheckName][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1B6);
		p.addUint32(54510);
		packet_func::session_send(p, &_session, 1);
	}
}

void GuildSystem::requestCallGuildJoin(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("requestCallGuildJoin");

	packet p;
	try
	{
		if (_session.guild_info.uid > 0)
		{
			throw exception("[guildsytem::requestCallGuildCreate][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", ja esta em guild ou ja tem uma ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));

		}
		/*if (_session.m_pi.ui.level < 11)
		{
			throw exception("[guildsytem::requestCallGuildCreate][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", nao tem level suficiente ! ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}*/

		auto ID = _packet->readUint32();
		auto Intro = _packet->readString();
		CmdGuildJoin guild_list(_session.m_pi.uid, ID, Intro, true);	// Waiter

		snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

		guild_list.waitEvent();

		if (guild_list.getException().getCodeError() != 0)
			throw guild_list.getException();


		auto code = guild_list.getInfo();
		//sucess ! 
		if (code ==1)
		{
			p.init_plain((unsigned short)0x1C0);

			p.addUint32(1);
			packet_func::session_send(p, &_session, 1);

			_session.m_pi.gi.uid = code;//seta o guild id

			_session.SendGuildData();
		}
		else if (code < 0)
		{
			throw exception("[guildsytem::requestCallGuildJoin][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", guild name ja existe ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::requestCallGuildJoin][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1C0);
		p.addUint32(0);
		packet_func::session_send(p, &_session, 1);
	}
}

void GuildSystem::requestCallGuilCancelJoinGuild(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("requestCallGuilCancelJoinGuild");

	packet p;
	try
	{
		if (_session.guild_info.uid > 0)
		{
			throw exception("[guildsytem::requestCallGuilCancelJoinGuild][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", ja esta em guild ou ja tem uma ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));

		}

		auto ID = _packet->readUint32();
		CmdGuildCancel guild_list(_session.m_pi.uid, ID, true);	// Waiter

		snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

		guild_list.waitEvent();

		if (guild_list.getException().getCodeError() != 0)
			throw guild_list.getException();


		_session.ReloadGuildInfo();
		//sucess ! 
		if (_session.guild_info.uid == 0)
		{
			p.init_plain((unsigned short)0x1C1);

			p.addUint32(1);
			packet_func::session_send(p, &_session, 1);
			_session.SendGuildData();
		}
		else
		{
			throw exception("[guildsytem::requestCallGuilCancelJoinGuild][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", guild name ja existe ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::requestCallGuilCancelJoinGuild][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1C1);
		p.addUint32(54510);
		packet_func::session_send(p, &_session, 1);
	}
}

void GuildSystem::requestCallGuildAccept(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("requestCallGuildAccept");

	packet p;
	try
	{
		/*if (_session.m_pi.ui.level < 11)
		{
			throw exception("[guildsytem::requestCallGuildCreate][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", nao tem level suficiente ! ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}*/

		auto ID = _packet->readUint32();
		auto UID = _packet->readUint32();
		CmdGuildAceita guild_list(UID, ID, _session.m_pi.uid, true);	// Waiter

		snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

		guild_list.waitEvent();

		if (guild_list.getException().getCodeError() != 0)
			throw guild_list.getException();


		//sucess ! 
		if (_session.guild_info.Position == 1 || _session.guild_info.Position == 2)
		{
			p.init_plain((unsigned short)0x1C2);

			p.addUint32(1);
			packet_func::session_send(p, &_session, 1);

			p.init_plain((unsigned short)0x1D1);

			p.addUint32(42);
			p.addUint32(UID);
			packet_func::session_send(p, &_session, 1);

			_session.ReloadGuildInfo();
			
		}
		else
		{
			throw exception("[guildsytem::requestCallGuildAccept][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", guild name ja existe ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::requestCallGuildAccept][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1D1);
		p.addUint32(0);
		packet_func::session_send(p, &_session, 1);
	}
}

void GuildSystem::requestCallGuildKick(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("requestCallGuildAccept");

	packet p;
	try
	{
		auto ID = _packet->readUint32();
		auto UID = _packet->readUint32();
		CmdGuildKickMember guild_list(UID, ID, _session.m_pi.uid, true);	// Waiter

		snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

		guild_list.waitEvent();

		if (guild_list.getException().getCodeError() != 0)
			throw guild_list.getException();


		//sucess ! 
		if (_session.guild_info.Position == 1 || _session.guild_info.Position == 2)
		{
			p.init_plain((unsigned short)0x1C8);
			p.addUint32(1);
			packet_func::session_send(p, &_session, 1);

			p.init_plain((unsigned short)0x1D1);

			p.addUint32(43);
			p.addUint32(UID);
			packet_func::session_send(p, &_session, 1);

			_session.ReloadGuildInfo();

		}
		else
		{
			throw exception("[guildsytem::requestCallGuildKick][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", guild name ja existe ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::requestCallGuildKick][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1D1);
		p.addUint32(0);
		packet_func::session_send(p, &_session, 1);
	}
}

void GuildSystem::requestCallGuildChangeIntro(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("requestCallGuildChangeIntro");

	packet p;
	try
	{
		auto ID = _packet->readUint32();
		auto UID = _packet->readUint32();
		auto Intro = _packet->readString();
		CmdGuildChangeIntro guild_list(ID, Intro, true);	// Waiter

		snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

		guild_list.waitEvent();

		if (guild_list.getException().getCodeError() != 0)
			throw guild_list.getException();

		//sucess ! 
		if (_session.guild_info.Position == 1 || _session.guild_info.Position == 2)
		{
			p.init_plain((unsigned short)0x1BA);
			p.addUint32(1);
			packet_func::session_send(p, &_session, 1);
			_session.ReloadGuildInfo();


			CmdGuildInfos guild_list(1, 0, true);	// Waiter

			snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

			guild_list.waitEvent();

			if (guild_list.getException().getCodeError() != 0)
				throw guild_list.getException();

			auto v_element = guild_list.getInfo();
			p.init_plain((unsigned short)0x1BC);
			p.addUint32(1);
			p.addUint32(1);
			p.addUint32((uint32_t)v_element.size());
			p.addUint16((uint16_t)v_element.size());
			for (auto& guild : v_element)
			{
				p.addBuffer(&guild.second, sizeof(GuildInfoList));
			}
			packet_func::session_send(p, &_session, 1);
		}
		else
		{
			throw exception("[guildsytem::requestCallGuildChangeIntro][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", guild name ja existe ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::requestCallGuildChangeIntro][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1BA);
		p.addUint32(0);
		packet_func::session_send(p, &_session, 1);
	}
}

void GuildSystem::requestCallGuildChangeNotice(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("requestCallGuildChangeNotice");

	packet p;
	try
	{
		auto ID = _packet->readUint32();
		auto UID = _packet->readUint32();
		auto Message = _packet->readString();
		CmdGuildChangeMsg guild_list(ID, Message, true);	// Waiter

		snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

		guild_list.waitEvent();

		if (guild_list.getException().getCodeError() != 0)
			throw guild_list.getException();

		//sucess ! 
		if (_session.guild_info.Position == 1 || _session.guild_info.Position == 2)
		{
			p.init_plain((unsigned short)0x1B9);
			p.addUint32(1);
			packet_func::session_send(p, &_session, 1);
			_session.ReloadGuildInfo();

			CmdGuildInfos guild_list(1, 0, true);	// Waiter

			snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

			guild_list.waitEvent();

			if (guild_list.getException().getCodeError() != 0)
				throw guild_list.getException();


			auto v_element = guild_list.getInfo();
			p.init_plain((unsigned short)0x1BC);
			p.addUint32(1);
			p.addUint32(1);
			p.addUint32((uint32_t)v_element.size());
			p.addUint16((uint16_t)v_element.size());
			for (auto& guild : v_element)
			{
				p.addBuffer(&guild.second, sizeof(GuildInfoList));
			}
			packet_func::session_send(p, &_session, 1);
		}
		else
		{
			throw exception("[guildsytem::requestCallGuildChangeNotice][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", guild name ja existe ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::requestCallGuildChangeNotice][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1B9);
		p.addUint32(0);
		packet_func::session_send(p, &_session, 1);
	}
}

void GuildSystem::requestCallGuildNoticeSetPlayer(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("requestCallGuildNoticeSetPlayer");

	packet p;
	try
	{
		/*if (_session.m_pi.ui.level < 11)
		{
			throw exception("[guildsytem::requestCallGuildCreate][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", nao tem level suficiente ! ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}*/

		auto ID = _packet->readUint32();
		auto UID = _packet->readUint32();
		auto Message = _packet->readString();
		CmdGuildMessage guild_list(UID, ID, Message, true);	// Waiter

		snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

		guild_list.waitEvent();

		if (guild_list.getException().getCodeError() != 0)
			throw guild_list.getException();

		//sucess ! 
		if (_session.guild_info.uid == ID)
		{
			p.init_plain((unsigned short)0x1C5);
			p.addUint32(1);
			packet_func::session_send(p, &_session, 1);
		}
		else
		{
			throw exception("[guildsytem::requestCallGuildChangeNotice][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", guild name ja existe ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::requestCallGuildChangeNotice][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1B9);
		p.addUint32(0);
		packet_func::session_send(p, &_session, 1);
	}
}

// nao feitos -----------------------------
void GuildSystem::requestCallGuildUploadMark(player& _session, packet* _packet)
{
	CHECK_SESSION_BEGIN("requestCallGuildUploadMark");

	packet p;
	try
	{
	
		if (_session.m_pi.ui.level < 11)
		{
			throw exception("[guildsytem::requestCallGuildUploadMark][Error] player[UID=" + std::to_string(_session.m_pi.uid) + ", nao tem level suficiente ! ]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}
		// Update ON Server
		auto pWi = _session.m_pi.findWarehouseItemByTypeid(ITEM_GUILD_UPLOAD_MARK);

		if (pWi == nullptr)
		{
			throw exception("[guildsytem::requestCallGuildUploadMark][Error] player[UID=" + std::to_string(_session.m_pi.uid) + "] nao conseguiu excluir/(atualizar qntd) item[TYPEID="
				+ std::to_string(ITEM_GUILD_UPLOAD_MARK) + "]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));

		}
		std::vector< stItem > v_item;
		stItem item{ 0 };
		item.clear();

		item.type = 2;
		item._typeid = ITEM_GUILD_UPLOAD_MARK;
		item.id = pWi->id;
		item.qntd = 1;
		item.STDA_C_ITEM_QNTD = (short)item.qntd * -1;

		// //item que cria guild
		if (item_manager::removeItem(item, _session) <= 0)
			throw exception("[guildsytem::requestCallGuildUploadMark][Error] player[UID=" + std::to_string(_session.m_pi.uid) + "] nao conseguiu excluir/(atualizar qntd) item[TYPEID="
				+ std::to_string(item._typeid) + ", ID=" + std::to_string(item.id) + "]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));

		v_item.push_back(item);

		auto ID = _packet->readUint32();
		CmdGuildImagem guild_list(ID, true);	// Waiter

		snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

		guild_list.waitEvent();

		if (guild_list.getException().getCodeError() != 0)
			throw guild_list.getException();


		auto code = guild_list.getInfo();

	
		if (code == -2)
		{
			throw exception("[guildsytem::requestCallGuildUploadMark][ErrorCode] player[UID=" + std::to_string(_session.m_pi.uid) + "] Não pode criar a guild, faz menos de 24 horas que ele criou outra guild"
				+ std::to_string(ITEM_GUILD_UPLOAD_MARK) + "]", STDA_MAKE_ERROR(STDA_ERROR_TYPE::CHANNEL, 858, 0x5200859));
		}
		
		if (code > 0)
		{
			_session.ReloadGuildInfo();
			
			CmdGuildMark guild_list(ID, true);	// Waiter

			snmdb::NormalManagerDB::getInstance().add(0, &guild_list, nullptr, nullptr);

			guild_list.waitEvent();

			if (guild_list.getException().getCodeError() != 0)
				throw guild_list.getException();


			auto data = guild_list.getInfo();

			p.init_plain((unsigned short)0x1C9);
			p.addUint8(1);
			p.addUint32(data.mark_idx); //Guild emblem
			p.addString(data.mark_image); //GuilD_IMAGE 
			packet_func::session_send(p, &_session, 1);

		}
	}

	catch (exception& e)
	{
		_smp::message_pool::getInstance().push(new message("[GuildSystem::requestCallGuildUploadMark][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));

		p.init_plain((unsigned short)0x1C9);
		p.addUint32(54001);
		packet_func::session_send(p, &_session, 1);
	}
}

void GuildSystem::requestCallGuildAfterUploadMark(player& _session, packet* _packet)
{
}
// ------------------------------------------ //