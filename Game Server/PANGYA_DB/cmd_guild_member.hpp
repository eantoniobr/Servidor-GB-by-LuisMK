// Arquivo cmd_guild_info.hpp
// Criado em 24/03/2018 as 20:18 por Acrisio
// Defini��o da classe CmdGuildMemberInfo

#pragma once
#ifndef _STDA_CMD_GUILD_MEMBER_HPP
#define _STDA_CMD_GUILD_MEMBER_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/guild_system_type.hpp"
#include <map>
namespace stdA {
	class CmdGuildMemberInfo : public pangya_db {
		public:
			explicit CmdGuildMemberInfo(bool _waiter = false);
			CmdGuildMemberInfo(uint32_t _uid, bool _waiter = false);
			virtual ~CmdGuildMemberInfo();

			std::map<uint32_t, GuildMemberInfo>& getInfo();
			GuildMemberInfo& getInfo(uint32_t _uid);
			GuildMemberInfo& getInfo(std::string _name);
			void setInfo(GuildMemberInfo& _gi);

			uint32_t getUID();
			void setUID(uint32_t _uid);

			uint32_t getOption();
			void setOption(uint32_t _option);

		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdGuildMemberInfo"; };
			virtual std::wstring _wgetName() override { return L"CmdGuildMemberInfo"; };

		private:
			uint32_t m_page;
			
			std::map<uint32_t,GuildMemberInfo> m_gi;

			const char* m_szConsulta = "pangya.ProcGetGuildMemberInfo";
	};
}

#endif // !_STDA_CMD_GUILD_MEMBER_HPP
