// Arquivo cmd_scratch_card_item.cpp
// Implementa��o da classe CmdScratchCardItem

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_scratch_card_item.hpp"

using namespace stdA;

CmdScratchCardItem::CmdScratchCardItem(bool _waiter) : pangya_db(_waiter), m_ctx_psi() {
}

CmdScratchCardItem::~CmdScratchCardItem() {
}

void CmdScratchCardItem::lineResult(result_set::ctx_res* _result, uint32_t /*_index_result*/) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);

	ctx_scratch_card_item ctx_psi{ 0 };
	ctx_psi._typeid = IFNULL(atoi, _result->data[0]);
	ctx_psi.qntd = IFNULL(atoi, _result->data[1]);
	ctx_psi.probabilidade = IFNULL(atoi, _result->data[2]);
	ctx_psi.numero = IFNULL(atoi, _result->data[3]);
	ctx_psi.tipo = SCRATCH_CARD_TYPE((unsigned char)IFNULL(atoi, _result->data[4]));
	ctx_psi.active = 1;//ja vem ativo
	m_ctx_psi.push_back(ctx_psi);
}

response* CmdScratchCardItem::prepareConsulta(database& _db) {

	auto r = consulta(_db, m_szConsulta);

	checkResponse(r, "nao conseguiu pegar os scratch card itens ativos !");

	return r;
}

std::vector< ctx_scratch_card_item >& CmdScratchCardItem::getInfo() {
	return m_ctx_psi;
}
