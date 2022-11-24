#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_guild_image.hpp"

using namespace stdA;

CmdGuildImagem::CmdGuildImagem(bool _waiter) : pangya_db(_waiter), m_guild_id(0), m_code(0) {
}

CmdGuildImagem::CmdGuildImagem(uint32_t guild_id, bool _waiter) : pangya_db(_waiter),m_guild_id(guild_id), m_code(0)
{
}
CmdGuildImagem::~CmdGuildImagem() {
}

uint32_t& stdA::CmdGuildImagem::getInfo()
{
	return m_code;
}

void CmdGuildImagem::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);

	m_code = IFNULL(atoi, _result->data[0]);
}

response* CmdGuildImagem::prepareConsulta(database& _db) {

	auto r = procedure(_db, m_szConsulta, std::to_string(m_guild_id));

	checkResponse(r, "nao conseguiu imagem da guild");
	return r;
}

