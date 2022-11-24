// Arquivo cmd_guild_infos.cpp
// Criado em 24/03/2018 as 20:23 por Acrisio
// Implementa��o da classe GuildMember

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_guild_join.hpp"

using namespace stdA;

CmdGuildJoin::CmdGuildJoin(bool _waiter) : pangya_db(_waiter), m_uid(0), m_guild_id(0), m_intro(std::string("")), code(0) {
}

CmdGuildJoin::CmdGuildJoin(uint32_t _uid, uint32_t guild_id, std::string _intro, bool _waiter) : pangya_db(_waiter), m_uid(_uid),m_guild_id(guild_id), m_intro(_intro), code(0)
{
}
CmdGuildJoin::~CmdGuildJoin() {
}

void CmdGuildJoin::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);
	code = IFNULL(atoi, _result->data[0]);
}

response* CmdGuildJoin::prepareConsulta(database& _db) {

	auto r = procedure(_db, m_szConsulta, std::to_string(m_uid) +", " + std::to_string(m_guild_id) +", "+ _db.makeText(m_intro));

	checkResponse(r, "nao conseguiu entrar na  guild");
	return r;
}

uint32_t& CmdGuildJoin::getInfo() {
	return code;
}
