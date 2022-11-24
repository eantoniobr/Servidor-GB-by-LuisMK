#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_insert_notice.hpp"

using namespace stdA;

CmdInsertNotice::CmdInsertNotice(bool _waiter) : pangya_db(_waiter), m_server_uid(0u), m_msg("") {
}

CmdInsertNotice::CmdInsertNotice(uint32_t _server_uid, std::string& _msg, bool _waiter)
	: pangya_db(_waiter), m_server_uid(_server_uid), m_msg(_msg) {
}

CmdInsertNotice::~CmdInsertNotice() {
}

void CmdInsertNotice::lineResult(result_set::ctx_res* /*_result*/, uint32_t /*_index_result*/) {

	// N�o usa por que � um UPDATE
	return;
}

response* CmdInsertNotice::prepareConsulta(database& _db) {

	
	if (m_server_uid == 0u)
		throw exception("[CmdInsertNotice::prepareConsulta][Error] m_server_uid is invalid(zero).", STDA_MAKE_ERROR(STDA_ERROR_TYPE::PANGYA_DB, 4, 0));

	auto r = procedure(_db, m_szConsulta, std::to_string(m_server_uid) + ", " + _db.makeText(m_msg));

	checkResponse(r, "nao conseguiu adicionar um Notice[MESSAGE=" + m_msg + "] para o server[UID=" + std::to_string(m_server_uid) + "]");

	return r;
}


uint32_t CmdInsertNotice::getServerUID() {
	return m_server_uid;
}

void CmdInsertNotice::setServerUID(uint32_t _server_uid) {
	m_server_uid = _server_uid;
}

std::string& CmdInsertNotice::getMessage() {
	return m_msg;
}

void CmdInsertNotice::setMessage(std::string& _msg) {
	m_msg = _msg;
}
