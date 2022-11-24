
#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_guild_available.hpp"

using namespace stdA;

CmdGuildAvailable::CmdGuildAvailable(bool _waiter) : pangya_db(_waiter), m_name(std::string("")), code(0) {
}

CmdGuildAvailable::CmdGuildAvailable(std::string _name, bool _waiter) : pangya_db(_waiter), m_name(_name), code(0)
{
}
CmdGuildAvailable::~CmdGuildAvailable() {
}

void CmdGuildAvailable::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);
	code = IFNULL(atoi, _result->data[0]);//uid
}

response* CmdGuildAvailable::prepareConsulta(database& _db) {

	auto r = consulta(_db, m_szConsulta + m_name +";");

	checkResponse(r, "nao conseguiu avaliar a guild");
	return r;
}

uint32_t& CmdGuildAvailable::getInfo() {
	return code;
}
