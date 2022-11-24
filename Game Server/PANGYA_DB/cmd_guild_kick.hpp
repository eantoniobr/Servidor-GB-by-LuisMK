#pragma once
#ifndef _STDA_CMD_GUILD_KICK_HPP
#define _STDA_CMD_GUILD_KICK_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
namespace stdA {
	class CmdGuildKickMember : public pangya_db {
		public:
			explicit CmdGuildKickMember(bool _waiter = false);
			CmdGuildKickMember(uint32_t _uid, uint32_t guild_id, uint32_t _uid_owner, bool _waiter = false);
			virtual ~CmdGuildKickMember();
			
		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdGuildKickMember"; };
			virtual std::wstring _wgetName() override { return L"CmdGuildKickMember"; };

		private:
			uint32_t m_uid;
			uint32_t m_uid_owner;
			uint32_t m_guild_id;
			const char* m_szConsulta = "pangya.ProcGuildKickMember";
	};
}

#endif // !_STDA_CMD_GUILD_KICK_HPP
