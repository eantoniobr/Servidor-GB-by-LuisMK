// Arquivo cmd_guild_infos.cpp
// Criado em 24/03/2018 as 20:23 por Acrisio
// Implementa��o da classe GuildMember

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_guild_member.hpp"

using namespace stdA;

CmdGuildMemberInfo::CmdGuildMemberInfo(bool _waiter) : pangya_db(_waiter), m_page(0), m_gi() {
}

CmdGuildMemberInfo::CmdGuildMemberInfo(uint32_t _uid, bool _waiter) : pangya_db(_waiter), m_page(_uid), m_gi() {
}
CmdGuildMemberInfo::~CmdGuildMemberInfo() {
}

void CmdGuildMemberInfo::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);
	GuildMemberInfo gi{ 0 };
	gi.uid = IFNULL(atoi, _result->data[0]);

	if (is_valid_c_string(_result->data[1]))
		STRCPY_TO_MEMORY_FIXED_SIZE(gi.name, sizeof(gi.name), _result->data[1]);


	gi.pang = IFNULL(atoi, _result->data[2]);
	gi.point = IFNULL(atoi, _result->data[3]);
	gi.position = IFNULL(atoi, _result->data[4]);
	gi.member_uid = IFNULL(atoi, _result->data[5]);
	gi.logon = IFNULL(atoi, _result->data[8]);


	if (_result->data[6] != nullptr)
	{
		std::string mark(_result->data[6]);
		
#if defined(_WIN32)
		memcpy_s(gi.message, sizeof(gi.message), mark.c_str(), mark.size());
#elif defined(__linux__)
		memcpy(gi.Image, mark.c_str(), mark.c_str(), mark.size());
#endif
	}
	else
	{
		std::string mark("");

#if defined(_WIN32)
		memcpy_s(gi.message, sizeof(gi.message), mark.c_str(), mark.size());
#elif defined(__linux__)
		memcpy(gi.Image, "guild_mark", sizeof(gi.Image));
#endif	
	}
	if (_result->data[7] != nullptr) {
		std::string LeaderNickname(_result->data[7]);
#if defined(_WIN32)
		memcpy_s(gi.nick, sizeof(gi.nick), LeaderNickname.c_str(), LeaderNickname.size());
#elif defined(__linux__)
		memcpy(gi.mark_emblem, _result->data[7], sizeof(gi.LeaderNickname));
#endif
	}
	auto it = m_gi.find(gi.member_uid);

	if (it == m_gi.end())	// Add m_gioin ao map
		m_gi[gi.member_uid] = gi;
	
}

response* CmdGuildMemberInfo::prepareConsulta(database& _db) {

	m_gi.clear();
	auto r = procedure(_db, m_szConsulta, std::to_string(m_page));

	checkResponse(r, "nao conseguiu pegar a lista de guild: ");
	return r;
}

std::map<uint32_t,GuildMemberInfo>& CmdGuildMemberInfo::getInfo() {
	return m_gi;
}
GuildMemberInfo& CmdGuildMemberInfo::getInfo(uint32_t _uid) {
	auto it = m_gi.find(_uid);
	GuildMemberInfo gi{ 0 };

	if (it != m_gi.end()) {
		return it->second;
	}
	return gi;
}
GuildMemberInfo& stdA::CmdGuildMemberInfo::getInfo(std::string _name)
{
	for (auto gi : m_gi)
	{
		if (std::string(gi.second.name) == _name)
		{
			return gi.second;
		}
	}
	GuildMemberInfo gi{ 0 };
	return gi;
}
void CmdGuildMemberInfo::setInfo(GuildMemberInfo& _gi) {
	//m_gi = _gi;
}