#pragma once
#ifndef _STDA_CMD_GUILD_MESSAGE_HPP
#define _STDA_CMD_GUILD_MESSAGE_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
namespace stdA {
	class CmdGuildMessage : public pangya_db {
		public:
			explicit CmdGuildMessage(bool _waiter = false);
			CmdGuildMessage(uint32_t _uid, uint32_t guild_id, std::string msg, bool _waiter = false);
			virtual ~CmdGuildMessage();
			
		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdGuildMessage"; };
			virtual std::wstring _wgetName() override { return L"CmdGuildMessage"; };

		private:
			std::string m_msg;
			uint32_t m_guild_id;
			uint32_t m_uid;
			const char* m_szConsulta[2] = { "UPDATE pangya.pangya_guild_member SET MEMBER_MSG = ", " WHERE [GUILD_UID] = " };

	};
}

#endif // !_STDA_CMD_GUILD_MESSAGE_HPP
