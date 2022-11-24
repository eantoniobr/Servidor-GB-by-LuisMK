// Arquivo cmd_guild_info.hpp
// Criado em 24/03/2018 as 20:18 por Acrisio
// Defini��o da classe CmdGuildPromote

#pragma once
#ifndef _STDA_CMD_GUILD_PROMOTE_HPP
#define _STDA_CMD_GUILD_PROMOTE_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/guild_system_type.hpp"
#include <map>
namespace stdA {
	class CmdGuildPromote : public pangya_db {
		public:
			explicit CmdGuildPromote(bool _waiter = false);
			CmdGuildPromote(uint32_t _uid, uint32_t _member,uint32_t _promote, bool _waiter = false);
			virtual ~CmdGuildPromote();

			uint32_t& getInfo();
			
		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdGuildPromote"; };
			virtual std::wstring _wgetName() override { return L"CmdGuildPromote"; };

		private:
			uint32_t m_guild_id;
			uint32_t m_member_id;
			uint32_t m_promote;
			
			uint32_t m_code = -2;
			const char* m_szConsulta = "pangya.ProcGuildChangeAuthorityMember";
	};
}

#endif // !_STDA_CMD_GUILD_PROMOTE_HPP
