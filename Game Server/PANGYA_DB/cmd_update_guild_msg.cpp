#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_update_guild_msg.hpp"

using namespace stdA;

CmdGuildChangeMsg::CmdGuildChangeMsg(bool _waiter) : pangya_db(_waiter), m_msg(), m_guild_id(0) {
}

CmdGuildChangeMsg::CmdGuildChangeMsg(uint32_t guild_id, std::string msg, bool _waiter) : pangya_db(_waiter),m_guild_id(guild_id), m_msg(msg)
{
}
CmdGuildChangeMsg::~CmdGuildChangeMsg() {
}

void CmdGuildChangeMsg::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);
}

response* CmdGuildChangeMsg::prepareConsulta(database& _db) {

	auto r = procedure(_db, m_szConsulta, std::to_string(m_guild_id) +", " + _db.makeText(m_msg));

	checkResponse(r, "nao conseguiu change msg na  guild");
	return r;
}

