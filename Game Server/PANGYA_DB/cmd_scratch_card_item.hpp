// Arquivo cmd_scratch_card_item.hpp
// Criado em 29/06/2022 as 20:27 luisMK
// Defini��o da classe CmdScratchCardItem

#pragma once
#ifndef _STDA_CMD_SCRATCH_CARD_ITEM_HPP
#define _STDA_CMD_SCRATCH_CARD_ITEM_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/scratch_card_type.hpp"
#include <vector>

namespace stdA {
	class CmdScratchCardItem : public pangya_db {
	public:
		explicit CmdScratchCardItem(bool _waiter = false);
		virtual ~CmdScratchCardItem();

		std::vector< ctx_scratch_card_item >& getInfo();

	protected:
		void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
		response* prepareConsulta(database& _db) override;

		// get Class name
		virtual std::string _getName() override { return "CmdScratchCardItem"; };
		virtual std::wstring _wgetName() override { return L"CmdScratchCardItem"; };

	private:
		std::vector< ctx_scratch_card_item > m_ctx_psi;

		const char* m_szConsulta = "SELECT TypeID, Quantidade, Probabilidade, numero, tipo FROM pangya.scratchy_item where active = 1 ORDER BY Tipo";
	};
}

#endif // !_STDA_CMD_SCRATCH_CARD_ITEM_HPP
