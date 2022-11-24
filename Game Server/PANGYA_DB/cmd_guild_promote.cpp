// Arquivo cmd_guild_infos.cpp
// Criado em 24/03/2018 as 20:23 por Acrisio
// Implementa��o da classe GuildMember

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_guild_promote.hpp"

using namespace stdA;

CmdGuildPromote::CmdGuildPromote(bool _waiter) : pangya_db(_waiter), m_guild_id(0), m_promote(0), m_member_id(0) {
}

CmdGuildPromote::CmdGuildPromote(uint32_t _uid, uint32_t _member, uint32_t _promote, bool _waiter) : pangya_db(_waiter),
	m_guild_id(_uid), m_promote(_promote), m_member_id(_member)
{
}
CmdGuildPromote::~CmdGuildPromote() {
}

void CmdGuildPromote::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);
	m_code = IFNULL(atoi, _result->data[0]);
}

response* CmdGuildPromote::prepareConsulta(database& _db) {

	auto r = procedure(_db, m_szConsulta, std::to_string(m_guild_id) +","+ std::to_string(m_member_id) + "," + std::to_string(m_promote));

	checkResponse(r, "nao conseguiu pegar a code promote guild");
	return r;
}

uint32_t& CmdGuildPromote::getInfo() {
	return m_code;
}