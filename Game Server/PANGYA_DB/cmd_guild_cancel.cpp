#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_guild_cancel.hpp"

using namespace stdA;

CmdGuildCancel::CmdGuildCancel(bool _waiter) : pangya_db(_waiter), m_guild_id(0), m_uid(0) {
}

CmdGuildCancel::CmdGuildCancel(uint32_t _uid, uint32_t guild_id, bool _waiter) : pangya_db(_waiter), m_uid(_uid),m_guild_id(guild_id){
}
CmdGuildCancel::~CmdGuildCancel() {
}

void CmdGuildCancel::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);
}

response* CmdGuildCancel::prepareConsulta(database& _db) {

	auto r = procedure(_db, m_szConsulta, std::to_string(m_uid) + ", " + std::to_string(m_guild_id));

	checkResponse(r, "nao conseguiu cancelar o pedido na  guild");
	return r;
}

