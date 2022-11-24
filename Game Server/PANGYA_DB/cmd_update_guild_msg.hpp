#pragma once
#ifndef _STDA_CMD_GUILD_MSG_HPP
#define _STDA_CMD_GUILD_MSG_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
namespace stdA {
	class CmdGuildChangeMsg : public pangya_db {
		public:
			explicit CmdGuildChangeMsg(bool _waiter = false);
			CmdGuildChangeMsg(uint32_t guild_id, std::string msg, bool _waiter = false);
			virtual ~CmdGuildChangeMsg();
			
		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdGuildChangeMsg"; };
			virtual std::wstring _wgetName() override { return L"CmdGuildChangeMsg"; };

		private:
			std::string m_msg;
			uint32_t m_guild_id;
			const char* m_szConsulta = "pangya.ProcUpdateGuildIntroImg";
	};
}

#endif // !_STDA_CMD_GUILD_MSG_HPP
