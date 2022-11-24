#pragma once
#ifndef _STDA_CMD_GUILD_INTRO_HPP
#define _STDA_CMD_GUILD_INTRO_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
namespace stdA {
	class CmdGuildChangeIntro : public pangya_db {
		public:
			explicit CmdGuildChangeIntro(bool _waiter = false);
			CmdGuildChangeIntro(uint32_t guild_id, std::string intro, bool _waiter = false);
			virtual ~CmdGuildChangeIntro();
			
		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdGuildChangeIntro"; };
			virtual std::wstring _wgetName() override { return L"CmdGuildChangeIntro"; };

		private:
			std::string m_intro;
			uint32_t m_guild_id;
			const char* m_szConsulta = "pangya.ProcUpdateGuildMessageIntro";
	};
}

#endif // !_STDA_CMD_GUILD_INTRO_HPP
