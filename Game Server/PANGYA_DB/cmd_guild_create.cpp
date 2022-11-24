// Arquivo cmd_guild_infos.cpp
// Criado em 24/03/2018 as 20:23 por Acrisio
// Implementa��o da classe GuildMember

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_guild_create.hpp"

using namespace stdA;

CmdGuildMake::CmdGuildMake(bool _waiter) : pangya_db(_waiter), m_name(std::string("")), m_intro(std::string("")), code(0) {
}

CmdGuildMake::CmdGuildMake(std::string _name, std::string _intro, bool _waiter) : pangya_db(_waiter), m_name(_name), m_intro(_intro), code(0)
{
}
CmdGuildMake::~CmdGuildMake() {
}

void CmdGuildMake::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);
	code = IFNULL(atoi, _result->data[0]);

	
}

response* CmdGuildMake::prepareConsulta(database& _db) {

	auto r = procedure(_db, m_szConsulta, _db.makeText(m_name) +", "+ _db.makeText(m_intro));

	checkResponse(r, "nao conseguiu criar  guild");
	return r;
}

uint32_t& CmdGuildMake::getInfo() {
	return code;
}
