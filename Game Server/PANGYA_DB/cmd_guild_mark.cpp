#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_guild_mark.hpp"

using namespace stdA;

CmdGuildMark::CmdGuildMark(bool _waiter) : pangya_db(_waiter), m_guild_id(0), m_guild(0) {
}

CmdGuildMark::CmdGuildMark(uint32_t guild_id, bool _waiter) : pangya_db(_waiter),m_guild_id(guild_id), m_guild(0)
{
}
CmdGuildMark::~CmdGuildMark() {
}

GuildMark& CmdGuildMark::getInfo()
{
	return m_guild;
}

void CmdGuildMark::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);

	m_guild.mark_idx = IFNULL(atoi, _result->data[0]);
	m_guild.mark_image = std::string(_result->data[1]);
}

response* CmdGuildMark::prepareConsulta(database& _db) {

	auto r = consulta(_db, m_szConsulta + std::to_string(m_guild_id));

	checkResponse(r, "nao conseguiu imagem da guild");
	return r;
}

