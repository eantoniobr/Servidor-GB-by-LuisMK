// Arquivo cmd_guild_info.hpp
// Criado em 24/03/2018 as 20:18 por Acrisio
// Defini��o da classe CmdGuildJoin

#pragma once
#ifndef _STDA_CMD_GUILD_JOIN_HPP
#define _STDA_CMD_GUILD_JOIN_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
namespace stdA {
	class CmdGuildJoin : public pangya_db {
		public:
			explicit CmdGuildJoin(bool _waiter = false);
			CmdGuildJoin(uint32_t _uid, uint32_t guild_id, std::string _intro, bool _waiter = false);
			virtual ~CmdGuildJoin();
//code 
			uint32_t& getInfo();
			
		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdGuildJoin"; };
			virtual std::wstring _wgetName() override { return L"CmdGuildJoin"; };

		private:
			uint32_t m_uid;
			uint32_t m_guild_id;
			std::string m_intro;
			unsigned int code;
			const char* m_szConsulta = "pangya.ProcRequestJoinGuild";
	};
}

#endif // !_STDA_CMD_GUILD_JOIN_HPP
