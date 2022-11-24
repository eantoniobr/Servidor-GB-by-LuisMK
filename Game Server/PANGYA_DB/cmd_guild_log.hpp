// Arquivo cmd_guild_log.hpp
// Criado em 24/03/2018 as 20:18 por Acrisio
// Defini��o da classe CmdGuildLog

#pragma once
#ifndef _STDA_CMD_GUILD_LOG_HPP
#define _STDA_CMD_GUILD_LOG_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/guild_system_type.hpp"
#include <map>
namespace stdA {
	class CmdGuildLog : public pangya_db {
		public:
			explicit CmdGuildLog(bool _waiter = false);
			CmdGuildLog(uint32_t _uid, bool _waiter = false);
			virtual ~CmdGuildLog();

			GuildLog& getInfo();
		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdGuildLog"; };
			virtual std::wstring _wgetName() override { return L"CmdGuildLog"; };

		private:
			uint32_t m_uid;
		std::map<std::string,GuildLog> m_gi;

			const char* m_szConsulta = "pangya.ProcGetPlayerGuildAtividade";
	};
}

#endif // !_STDA_CMD_GUILD_LOG_HPP
