// Arquivo Guild_system.hpp
// Criado em05/07/22, por LUISMK
// Definicao da classe GuildSystem

#pragma once
#ifndef _STDA_GUILD_SYSTEM_HPP
#define _STDA_GUILD_SYSTEM_HPP

#include "../../Projeto IOCP/TYPE/singleton.h"
#include "../SESSION/player.hpp"
#include "../TYPE/guild_system_type.hpp"

#define ITEM_CREATE_GUILD_TYPEID			436207919
#define ITEM_GUILD_UPLOAD_MARK			436207920
namespace stdA {

	class GuildSystem {

	public:
		GuildSystem();
		virtual ~GuildSystem();

		void requestCallGuildList(player& _session, packet* _packet);
		void requestCallGuildSearch(player& _session, packet* _packet);
		void requestCallGuildData(player& _session, packet* _packet);
		void requestCallGuildLog(player& _session, packet* _packet);
		void requestCallGuildPlayer(player& _session, packet* _packet);		
		void requestCallGuildJoin(player& _session, packet* _packet);
		void requestCallGuilCancelJoinGuild(player& _session, packet* _packet);
		void requestCallGuildAccept(player& _session, packet* _packet);
		void requestCallGuildKick(player& _session, packet* _packet);
		void requestCallGuildPromote(player& _session, packet* _packet);
		void requestCallGuildUploadMark(player& _session, packet* _packet);
		void requestCallGuildAfterUploadMark(player& _session, packet* _packet);
		void requestCallGuildChangeIntro(player& _session, packet* _packet);
		void requestCallGuildChangeNotice(player& _session, packet* _packet);
		void requestCallGuildCreate(player& _session, packet* _packet);
		void requestCallGuildCheckName(player& _session, packet* _packet);

		void requestCallGuildNoticeSetPlayer(player& _session, packet* _packet);

	};

	typedef Singleton< GuildSystem > sGuildSystem;
}

#endif // !_STDA_Guild_SYSTEM_HPP
