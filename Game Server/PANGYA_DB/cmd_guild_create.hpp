// Arquivo cmd_guild_info.hpp
// Criado em 24/03/2018 as 20:18 por Acrisio
// Defini��o da classe CmdGuildMake

#pragma once
#ifndef _STDA_CMD_GUILD_MAKE_HPP
#define _STDA_CMD_GUILD_MAKE_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/guild_system_type.hpp"
#include <map>
namespace stdA {
	class CmdGuildMake : public pangya_db {
		public:
			explicit CmdGuildMake(bool _waiter = false);
			CmdGuildMake(std::string _name, std::string _intro, bool _waiter = false);
			virtual ~CmdGuildMake();
//code 
			uint32_t& getInfo();
			
		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdGuildMake"; };
			virtual std::wstring _wgetName() override { return L"CmdGuildMake"; };

		private:
			std::string m_name;
			std::string m_intro;
			uint32_t code;
			const char* m_szConsulta = "pangya.ProcMakeGuild";
	};
}

#endif // !_STDA_CMD_GUILD_MAKE_HPP
