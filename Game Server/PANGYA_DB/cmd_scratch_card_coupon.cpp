// Arquivo cmd_scratch_card_coupon.cpp
// Implementa��o da classe CmdScratchCardCoupon

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_scratch_card_coupon.hpp"
#include "../../Projeto IOCP/UTIL/exception.h"
#include "../../Projeto IOCP/TYPE/stda_error.h"
#include "../../Projeto IOCP/UTIL/message_pool.h"

using namespace stdA;

CmdScratchCardCoupon::CmdScratchCardCoupon(bool _waiter) : pangya_db(_waiter), m_ctx_psc() {
}

CmdScratchCardCoupon::~CmdScratchCardCoupon() {
}

void CmdScratchCardCoupon::lineResult(result_set::ctx_res* _result, uint32_t /*_index_result*/) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);

	ctx_scratch_card_coupon ctx_psc{ 0 };

	ctx_psc._typeid = IFNULL(atoi, _result->data[0]);
	if (ctx_psc._typeid != 0)
	{
		ctx_psc.active = 1;
	}
	
	auto it = m_ctx_psc.find(ctx_psc._typeid);

	if (it == m_ctx_psc.end())	// N�o tem add um novo coupon
		m_ctx_psc[ctx_psc._typeid] = ctx_psc;
	else	// J� tem um coupon no map, est� duplicado no banco de dados
		_smp::message_pool::getInstance().push(new message("[CmdScratchCardCoupon::lineResult][WARNING] ja tem Scratch Coupon[TYPEID=" + std::to_string(ctx_psc._typeid) + "] duplicado no banco de dados.", CL_FILE_LOG_AND_CONSOLE));
}

response* CmdScratchCardCoupon::prepareConsulta(database& _db) {

	auto r = consulta(_db, m_szConsulta);

	checkResponse(r, "nao conseguiu pegar os papel shop coupon(s).");

	return r;
}

std::map< uint32_t, ctx_scratch_card_coupon >& CmdScratchCardCoupon::getInfo() {
	return m_ctx_psc;
}
