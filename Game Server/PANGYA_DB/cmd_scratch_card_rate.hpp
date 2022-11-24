// Arquivo cmd_scratch_card_rate.hpp
// Criado em 29/06/2022 as 20:27 luisMK
// Defini��o da classe CmdScratchCardRate

#pragma once
#ifndef _STDA_CMD_SCRATCH_CARD_RATE_HPP
#define _STDA_CMD_SCRATCH_CARD_RATE_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/scratch_card_type.hpp"
#include <vector>
#include <map>

namespace stdA {
	class CmdScratchCardRate : public pangya_db {
	public:
		explicit CmdScratchCardRate(bool _waiter = false);
		virtual ~CmdScratchCardRate();

		ctx_scratch_card_rate& getInfo(SCRATCH_CARD_TYPE _type);
		std::map< SCRATCH_CARD_TYPE, ctx_scratch_card_rate >& getInfo();
	protected:
		void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
		response* prepareConsulta(database& _db) override;

		// get Class name
		virtual std::string _getName() override { return "CmdScratchCardRate"; };
		virtual std::wstring _wgetName() override { return L"CmdScratchCardRate"; };

	private:
		std::map<SCRATCH_CARD_TYPE,ctx_scratch_card_rate> m_rate;

		const char* m_szConsulta = "SELECT nome, tipo,probabilidade FROM pangya.scratchy_rate order by tipo";
	};
}

#endif // !_STDA_CMD_SCRATCH_CARD_RATE_HPP
