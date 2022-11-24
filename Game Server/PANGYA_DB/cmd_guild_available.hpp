#pragma once
#ifndef _STDA_CMD_GUILD_AVAILABLE_HPP
#define _STDA_CMD_GUILD_AVAILABLE_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/guild_system_type.hpp"
#include <map>
namespace stdA {
	class CmdGuildAvailable : public pangya_db {
		public:
			explicit CmdGuildAvailable(bool _waiter = false);
			CmdGuildAvailable(std::string _name, bool _waiter = false);
			virtual ~CmdGuildAvailable();
//code 
			uint32_t& getInfo();
			
		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdGuildAvailable"; };
			virtual std::wstring _wgetName() override { return L"CmdGuildAvailable"; };

		private:
			std::string m_name;
			std::string m_intro;
			uint32_t code;
			const char* m_szConsulta = "SELECT GUILD_UID FROM pangya.pangya_guild where GUILD_NAME =";
	};
}

#endif // !_STDA_CMD_GUILD_AVAILABLE_HPP
