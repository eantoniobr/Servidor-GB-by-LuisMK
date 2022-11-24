// Arquivo cmd_guild_info.hpp
// Criado em 24/03/2018 as 20:18 por Acrisio
// Defini��o da classe CmdGuildMemberInfo

#pragma once
#ifndef _STDA_CMD_GUILD_MEMBER_INFO_HPP
#define _STDA_CMD_GUILD_MEMBER_INFO_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/pangya_game_st.h"

namespace stdA {
	class CmdGuildMemberInfo : public pangya_db {
		public:
			explicit CmdGuildMemberInfo(bool _waiter = false);
			CmdGuildMemberInfo(uint32_t _uid, bool _waiter = false);
			virtual ~CmdGuildMemberInfo();

			GuildInfoEx& getInfo();
			void setInfo(GuildInfoEx& _gi);

			uint32_t getUID();
			void setUID(uint32_t _uid);

		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdGuildMemberInfo"; };
			virtual std::wstring _wgetName() override { return L"CmdGuildMemberInfo"; };

		private:
			uint32_t m_uid;
			GuildInfoEx m_gi;

			const char* m_szConsulta = "pangya.ProcGetGuildMemberInfo";
	};
}

#endif // !_STDA_CMD_GUILD_MEMBER_INFO_HPP
