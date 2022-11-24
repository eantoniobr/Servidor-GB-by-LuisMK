// Arquivo cmd_guild_info.hpp
// Criado em 24/03/2018 as 20:18 por Acrisio
// Defini��o da classe CmdGuildAceita

#pragma once
#ifndef _STDA_CMD_GUILD_ACEITA_HPP
#define _STDA_CMD_GUILD_ACEITA_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include <map>
namespace stdA {
	class CmdGuildAceita : public pangya_db {
		public:
			explicit CmdGuildAceita(bool _waiter = false);
			CmdGuildAceita(uint32_t _uid, uint32_t guild_id, uint32_t _uid_owner, bool _waiter = false);
			virtual ~CmdGuildAceita();
			
		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdGuildAceita"; };
			virtual std::wstring _wgetName() override { return L"CmdGuildAceita"; };

		private:
			uint32_t m_uid;
			uint32_t m_uid_owner;
			uint32_t m_guild_id;
			const char* m_szConsulta = "pangya.ProcGuildAceitaPedido";
	};
}

#endif // !_STDA_CMD_GUILD_JOIN_HPP
