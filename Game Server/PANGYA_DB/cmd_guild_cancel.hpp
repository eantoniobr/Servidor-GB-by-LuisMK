#pragma once
#ifndef _STDA_CMD_GUILD_CANCEL_HPP
#define _STDA_CMD_GUILD_CANCEL_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
namespace stdA {
	class CmdGuildCancel : public pangya_db {
		public:
			explicit CmdGuildCancel(bool _waiter = false);
			CmdGuildCancel(uint32_t _uid, uint32_t guild_id, bool _waiter = false);
			virtual ~CmdGuildCancel();
			
		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdGuildCancel"; };
			virtual std::wstring _wgetName() override { return L"CmdGuildCancel"; };

		private:
			uint32_t m_guild_id;
			uint32_t m_uid;
			const char* m_szConsulta = { "[pangya].[ProcGuildCancelaPedido]" };

	};
}

#endif // !_STDA_CMD_GUILD_MESSAGE_HPP
