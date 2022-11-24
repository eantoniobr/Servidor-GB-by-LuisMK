#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_guild_kick.hpp"

using namespace stdA;

CmdGuildKickMember::CmdGuildKickMember(bool _waiter) : pangya_db(_waiter), m_uid(0), m_guild_id(0), m_uid_owner(0) {
}

CmdGuildKickMember::CmdGuildKickMember(uint32_t _uid, uint32_t guild_id, uint32_t _uid_owner, bool _waiter) : pangya_db(_waiter), m_uid(_uid),m_guild_id(guild_id), m_uid_owner(_uid_owner)
{
}
CmdGuildKickMember::~CmdGuildKickMember() {
}

void CmdGuildKickMember::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);
}

response* CmdGuildKickMember::prepareConsulta(database& _db) {

	auto r = procedure(_db, m_szConsulta, std::to_string(m_uid_owner) +", " + std::to_string(m_uid) +", "+ std::to_string(m_guild_id));

	checkResponse(r, "nao conseguiu kicka membro na  guild");
	return r;
}

