// Arquivo cmd_insert_papel_shop_rare_win_log.cpp
// Criado em 09/07/2018 as 22:13 por Acrisio
// Implementa��o da classe CmdInsertScratchCardRareWinLog

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_insert_scratch_card_rare_win_log.hpp"

using namespace stdA;

CmdInsertScratchCardRareWinLog::CmdInsertScratchCardRareWinLog(bool _waiter) : pangya_db(_waiter), m_uid(0u), m_ctx_psb{ 0 } {
}

CmdInsertScratchCardRareWinLog::CmdInsertScratchCardRareWinLog(uint32_t _uid, ctx_scratch_card_item_win& _ctx_psb, bool _waiter)
	: pangya_db(_waiter), m_uid(_uid), m_ctx_psb(_ctx_psb) {
}

CmdInsertScratchCardRareWinLog::~CmdInsertScratchCardRareWinLog() {
}

void CmdInsertScratchCardRareWinLog::lineResult(result_set::ctx_res* /*_result*/, uint32_t /*_index_result*/) {

	// N�o usa por que � um INSERT
	return;
}

response* CmdInsertScratchCardRareWinLog::prepareConsulta(database& _db) {

	if (m_uid == 0)
		throw exception("[CmdInsertScratchCardRareWinLog::prepareConsulta][Error] m_uid is invalid(zero)", STDA_MAKE_ERROR(STDA_ERROR_TYPE::PANGYA_DB, 4, 0));

	if (m_ctx_psb.ctx_psi._typeid == 0)
		throw exception("[CmdInsertScratchCardRareWinLog::prepareConsulta][Error] m_ctx_psb.ctx_psi._typeid is invalid(zero)", STDA_MAKE_ERROR(STDA_ERROR_TYPE::PANGYA_DB, 4, 0));

	auto r = procedure(_db, m_szConsulta, std::to_string(m_uid) + ", " + std::to_string(m_ctx_psb.ctx_psi._typeid));

	checkResponse(r, "nao conseguiu adicionar o Log de Rare Win[TYPEID=" + std::to_string(m_ctx_psb.ctx_psi._typeid) + ", QNTD="
		+ std::to_string(m_ctx_psb.qntd) +  ", PROBABILIDADE=" + std::to_string(m_ctx_psb.ctx_psi.probabilidade) + "] do Scratch Card para o player[UID=" + std::to_string(m_uid) + "]");

	return r;
}

uint32_t CmdInsertScratchCardRareWinLog::getUID() {
	return m_uid;
}

void CmdInsertScratchCardRareWinLog::setUID(uint32_t _uid) {
	m_uid = _uid;
}

ctx_scratch_card_item_win& CmdInsertScratchCardRareWinLog::getInfo() {
	return m_ctx_psb;
}

void CmdInsertScratchCardRareWinLog::setInfo(ctx_scratch_card_item_win& _ctx_psb) {
	m_ctx_psb = _ctx_psb;
}
