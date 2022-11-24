#pragma once
#ifndef _STDA_CMD_GUILD_MARK_HPP
#define _STDA_CMD_GUILD_MARK_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/guild_system_type.hpp"
namespace stdA {
	class CmdGuildMark : public pangya_db {
		public:
			explicit CmdGuildMark(bool _waiter = false);
			CmdGuildMark(uint32_t guild_id, bool _waiter = false);
			virtual ~CmdGuildMark();
			GuildMark& getInfo();
		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdGuildMark"; };
			virtual std::wstring _wgetName() override { return L"CmdGuildMark"; };

		private:
			uint32_t m_guild_id;
			GuildMark m_guild;
			const char* m_szConsulta = { "SELECT [GUILD_MARK_IMG_IDX],[GUILD_MARK_IMG] FROM [pangya].[pangya_guild] where GUILD_UID =" };

	};
}

#endif // !_STDA_CMD_GUILD_MARK_HPP
