// Arquivo cmd_guild_log.cpp
// Implementa��o da classe CmdGuildLog

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_guild_log.hpp"

using namespace stdA;

CmdGuildLog::CmdGuildLog(bool _waiter) : pangya_db(_waiter), m_uid(0), m_gi() {
}

CmdGuildLog::CmdGuildLog(uint32_t _uid, bool _waiter) : pangya_db(_waiter), m_uid(_uid), m_gi() {
}

CmdGuildLog::~CmdGuildLog() {
}

void CmdGuildLog::lineResult(result_set::ctx_res* _result, uint32_t /*_index_result*/) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);
	GuildLog gi{ 0 };
	
	if (is_valid_c_string(_result->data[0]))
		STRCPY_TO_MEMORY_FIXED_SIZE(gi.name, sizeof(gi.name), _result->data[0]);

	gi.uid = m_uid;
	gi.unknown = -1;
	gi.flag = IFNULL(atoi, _result->data[1]);
	
	if (_result->data[2] != nullptr) {
		_translateDate(_result->data[2], &gi.reg_date);
	}


	auto it = m_gi.find(std::string(gi.name));

	if (it == m_gi.end())	// Add m_gioin ao map
		m_gi[std::string(gi.name)] = gi;
}

response* CmdGuildLog::prepareConsulta(database& _db) {

	m_gi.clear();

	auto r = procedure(_db, m_szConsulta, std::to_string(m_uid));

	checkResponse(r, "nao conseguiu pegar o guild info do player: " + std::to_string(m_uid));

	return r;
}

GuildLog& CmdGuildLog::getInfo() {
	for (auto gi: m_gi)
	{
		return gi.second;
	}
	GuildLog gi{ 0 };
	return gi;
}
