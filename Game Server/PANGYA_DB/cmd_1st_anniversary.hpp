// Arquivo cmd_scratch_card_rate.hpp
// Criado em 29/06/2022 as 20:27 luisMK
// Defini��o da classe CmdFirstAnniversary

#pragma once
#ifndef _STDA_CMD_FIRST_ANNIVERSARY_HPP
#define _STDA_CMD_FIRST_ANNIVERSARY_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"

namespace stdA {
	class CmdFirstAnniversary : public pangya_db {
	public:
		explicit CmdFirstAnniversary(bool _waiter = false);
		virtual ~CmdFirstAnniversary();

	protected:
		void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
		response* prepareConsulta(database& _db) override;

		// get Class name
		virtual std::string _getName() override { return "CmdFirstAnniversary"; };
		virtual std::wstring _wgetName() override { return L"CmdFirstAnniversary"; };

	private:
		const char* m_szConsulta = "pangya.ProcDo1stAnniversary";
	};
}

#endif // !_STDA_CMD_FIRST_ANNIVERSARY_HPP
