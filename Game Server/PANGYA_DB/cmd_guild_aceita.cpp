// Arquivo cmd_guild_infos.cpp
// Criado em 24/03/2018 as 20:23 por Acrisio
// Implementa��o da classe GuildMember

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_guild_aceita.hpp"

using namespace stdA;

CmdGuildAceita::CmdGuildAceita(bool _waiter) : pangya_db(_waiter), m_uid(0), m_guild_id(0), m_uid_owner(0) {
}

CmdGuildAceita::CmdGuildAceita(uint32_t _uid, uint32_t guild_id, uint32_t _uid_owner, bool _waiter) : pangya_db(_waiter), m_uid(_uid),m_guild_id(guild_id), m_uid_owner(_uid_owner)
{
}
CmdGuildAceita::~CmdGuildAceita() {
}

void CmdGuildAceita::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);
}

response* CmdGuildAceita::prepareConsulta(database& _db) {

	auto r = procedure(_db, m_szConsulta, std::to_string(m_uid_owner) +", " + std::to_string(m_uid) +", "+ std::to_string(m_guild_id));

	checkResponse(r, "nao conseguiu aceitar membro na  guild");
	return r;
}

