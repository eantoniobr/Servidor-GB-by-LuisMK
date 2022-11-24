// Arquivo cmd_scratch_card_coupon.hpp
// Criado em 29/06/2022
// Defini��o da classe CmdScratchCardCoupon

#pragma once
#ifndef _STDA_CMD_PAPEL_SHOP_COUPON_HPP
#define _STDA_CMD_PAPEL_SHOP_COUPON_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/scratch_card_type.hpp"
#include <map>

namespace stdA {
	class CmdScratchCardCoupon : public pangya_db {
	public:
		explicit CmdScratchCardCoupon(bool _waiter = false);
		virtual ~CmdScratchCardCoupon();

		std::map< uint32_t, ctx_scratch_card_coupon >& getInfo();

	protected:
		void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
		response* prepareConsulta(database& _db) override;

		// get Class name
		virtual std::string _getName() override { return "CmdScratchCardCoupon"; };
		virtual std::wstring _wgetName() override { return L"CmdScratchCardCoupon"; };

	private:
		std::map< uint32_t, ctx_scratch_card_coupon > m_ctx_psc;

		const char* m_szConsulta = "SELECT typeid FROM pangya.scratch_card_coupon where active = 1";
	};
}

#endif // !_STDA_CMD_PAPEL_SHOP_COUPON_HPP
