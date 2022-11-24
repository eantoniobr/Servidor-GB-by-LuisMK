#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_guild_message.hpp"

using namespace stdA;

CmdGuildMessage::CmdGuildMessage(bool _waiter) : pangya_db(_waiter), m_msg(), m_guild_id(0), m_uid(0) {
}

CmdGuildMessage::CmdGuildMessage(uint32_t _uid, uint32_t guild_id, std::string intro, bool _waiter) : pangya_db(_waiter), m_uid(_uid),m_guild_id(guild_id), m_msg(intro)
{
}
CmdGuildMessage::~CmdGuildMessage() {
}

void CmdGuildMessage::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);
}

response* CmdGuildMessage::prepareConsulta(database& _db) {

	auto r = _update(_db, m_szConsulta[0] + _db.makeText(m_msg) + m_szConsulta[1] + std::to_string(m_guild_id) + " AND MEMBER_UID = " + std::to_string(m_uid));

	checkResponse(r, "nao conseguiu setar mensagem na  guild");
	return r;
}

