// Arquivo cmd_update_scratch_card_info.cpp
// Implementa��o da classe CmdUpdateScratchCardInfo

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_update_scratch_card_info.hpp"
#include "../../Projeto IOCP/UTIL/util_time.h"

using namespace stdA;

CmdUpdateScratchCardInfo::CmdUpdateScratchCardInfo(bool _waiter) : pangya_db(_waiter), m_uid(0u), m_ppsi{ 0 }, m_last_update{ 0 } {
}

CmdUpdateScratchCardInfo::CmdUpdateScratchCardInfo(uint32_t _uid, PlayerScratchCardInfo& _ppsi, SYSTEMTIME& _last_update, bool _waiter)
	: pangya_db(_waiter), m_uid(_uid), m_ppsi(_ppsi), m_last_update(_last_update) {
}

CmdUpdateScratchCardInfo::~CmdUpdateScratchCardInfo() {
}

void CmdUpdateScratchCardInfo::lineResult(result_set::ctx_res* /*_result*/, uint32_t /*_index_result*/) {

	// N�o usa por que � um UPDATE
	return;
}

response* CmdUpdateScratchCardInfo::prepareConsulta(database& _db) {

	if (m_uid == 0)
		throw exception("[CmdUpdateScratchCardInfo::prepareConsulta][Error] m_uid is invalid(zero)", STDA_MAKE_ERROR(STDA_ERROR_TYPE::PANGYA_DB, 4, 0));

	std::string last_update_dt = "null";

	if (!isEmpty(m_last_update))
		last_update_dt = _db.makeText(_formatDate(m_last_update));

	auto r = procedure(_db, m_szConsulta, std::to_string(m_uid) + ", " + std::to_string(m_ppsi.current_count)
		+ ", " + std::to_string(m_ppsi.remain_count)
		+ ", " + std::to_string(m_ppsi.limit_count)
		+ ", " + last_update_dt
	);

	checkResponse(r, "nao conseguiu atualizar o Scratch Card Info[current_cnt=" + std::to_string(m_ppsi.current_count)
		+ ", remain_cnt=" + std::to_string(m_ppsi.remain_count) + ", limit_cnt="
		+ std::to_string(m_ppsi.limit_count) + ", last_update=" + last_update_dt + "] do player[UID=" + std::to_string(m_uid) + "]");

	return r;
}

uint32_t CmdUpdateScratchCardInfo::getUID() {
	return m_uid;
}

void CmdUpdateScratchCardInfo::setUID(uint32_t _uid) {
	m_uid = _uid;
}

SYSTEMTIME& CmdUpdateScratchCardInfo::getLastUpdate() {
	return m_last_update;
}

void CmdUpdateScratchCardInfo::setLastUpdate(SYSTEMTIME& _last_update) {
	m_last_update = _last_update;
}

PlayerScratchCardInfo& CmdUpdateScratchCardInfo::getInfo() {
	return m_ppsi;
}

void CmdUpdateScratchCardInfo::setInfo(PlayerScratchCardInfo& _ppsi) {
	m_ppsi = _ppsi;
}
