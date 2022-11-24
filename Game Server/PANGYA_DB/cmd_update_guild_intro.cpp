#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_update_guild_intro.hpp"

using namespace stdA;

CmdGuildChangeIntro::CmdGuildChangeIntro(bool _waiter) : pangya_db(_waiter), m_intro(), m_guild_id(0) {
}

CmdGuildChangeIntro::CmdGuildChangeIntro(uint32_t guild_id, std::string intro, bool _waiter) : pangya_db(_waiter),m_guild_id(guild_id), m_intro(intro)
{
}
CmdGuildChangeIntro::~CmdGuildChangeIntro() {
}

void CmdGuildChangeIntro::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);
}

response* CmdGuildChangeIntro::prepareConsulta(database& _db) {

	auto r = procedure(_db, m_szConsulta, std::to_string(m_guild_id) +", " + _db.makeText(m_intro));

	checkResponse(r, "nao conseguiu change intro na  guild");
	return r;
}

