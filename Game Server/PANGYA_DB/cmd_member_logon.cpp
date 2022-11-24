#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_member_logon.hpp"

using namespace stdA;

CmdMemberLogon::CmdMemberLogon(bool _waiter) : pangya_db(_waiter), m_uid(0) {
}

CmdMemberLogon::CmdMemberLogon(uint32_t _uid, bool _waiter) : pangya_db(_waiter), m_uid(_uid)
{
}
CmdMemberLogon::~CmdMemberLogon() {
}

void CmdMemberLogon::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);
}

response* CmdMemberLogon::prepareConsulta(database& _db) {

	auto r = consulta(_db, m_szConsulta + std::to_string(m_uid));

	checkResponse(r, "nao conseguiu logon membros  desse game server");
	return r;
}