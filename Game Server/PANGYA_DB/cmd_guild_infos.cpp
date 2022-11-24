// Arquivo cmd_guild_infos.cpp
// Criado em 24/03/2018 as 20:23 por Acrisio
// Implementa��o da classe CmdGuildInfos

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_guild_infos.hpp"

using namespace stdA;

CmdGuildInfos::CmdGuildInfos(bool _waiter) : pangya_db(_waiter), m_page(0), m_category(0), m_gi() {
}

CmdGuildInfos::CmdGuildInfos(uint32_t _uid, uint32_t _option, bool _waiter) : pangya_db(_waiter), m_page(_uid), m_category(0), m_search(std::string("")), m_sort(_option), m_gi() {
}

stdA::CmdGuildInfos::CmdGuildInfos(uint32_t page_id, uint32_t category, uint32_t _option, std::string search, bool _waiter) : pangya_db(_waiter), m_page(page_id), m_category(category), m_search(search), m_sort(_option), m_gi() {

}


CmdGuildInfos::~CmdGuildInfos() {
}

void CmdGuildInfos::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

	checkColumnNumber((uint32_t)_result->cols, (uint32_t)_result->cols);
	GuildInfoListEx gi{ 0 };
	gi.uid = IFNULL(atoi, _result->data[1]);

	if (is_valid_c_string(_result->data[2]))
		STRCPY_TO_MEMORY_FIXED_SIZE(gi.name, sizeof(gi.name), _result->data[2]);


	gi.total_member = IFNULL(atoi, _result->data[4]);


	if (_result->data[10] != nullptr)
	{
		std::string chars = ".png";
		std::string mark(_result->data[10]);
		if (mark != "guildmark")
		{
			for (char c : chars) {
				mark.erase(std::remove(mark.begin(), mark.end(), c), mark.end());
			}
		}
#if defined(_WIN32)
		memcpy_s(gi.Image, sizeof(gi.Image), mark.c_str(), mark.size());
#elif defined(__linux__)
		memcpy(gi.Image, mark.c_str(), mark.c_str(), mark.size());
#endif
	}
	else
	{
		std::string mark("guild_mark");

#if defined(_WIN32)
		memcpy_s(gi.Image, sizeof(gi.Image), mark.c_str(), mark.size());
#elif defined(__linux__)
		memcpy(gi.Image, "guild_mark", sizeof(gi.Image));
#endif	
	}



	if (is_valid_c_string(_result->data[11]))
	{
		std::string Introducting(_result->data[11]);

#if defined(_WIN32)
		memcpy_s(gi.Introducting, sizeof(gi.Introducting), Introducting.c_str(), Introducting.size());
#elif defined(__linux__)
		memcpy(gi.Introducting, _result->data[11], sizeof(gi.Introducting));
#endif
	}
	gi.point = IFNULL(atoi, _result->data[12]);
	gi.pang = IFNULL(atoi, _result->data[13]);
	gi.LeaderUID = IFNULL(atoi, _result->data[14]);
	if (_result->data[3] != nullptr) {
		std::string LeaderNickname(_result->data[3]);
#if defined(_WIN32)
		memcpy_s(gi.LeaderNickname, sizeof(gi.LeaderNickname), LeaderNickname.c_str(), LeaderNickname.size());
#elif defined(__linux__)
		memcpy(gi.mark_emblem, _result->data[3], sizeof(gi.LeaderNickname));
#endif
	}

	if (_result->data[9] != nullptr) {
		_translateDate(_result->data[9], &gi.GUILD_CREATE_DATE);
	}


	auto it = m_gi.find(gi.uid);

	if (it == m_gi.end())	// Add m_gioin ao map
		m_gi[gi.uid] = gi;
}

response* CmdGuildInfos::prepareConsulta(database& _db) {

	m_gi.clear();
	auto number = (m_page - 1);
	auto r = procedure(_db, m_szConsulta, std::to_string(number) + ", " + std::to_string(m_category) + ", " + _db.makeText(m_search) + ", " + std::to_string(m_sort));

	checkResponse(r, "nao conseguiu pegar a lista de guild: ");
	return r;
}

std::map<uint32_t,GuildInfoListEx>& CmdGuildInfos::getInfo() {
	return m_gi;
}
GuildInfoListEx& CmdGuildInfos::getInfo(uint32_t _uid) {
	auto it = m_gi.find(_uid);
	GuildInfoListEx gi{ 0 };

	if (it != m_gi.end()) {
		return it->second;
	}
	return gi;
}
GuildInfoListEx& stdA::CmdGuildInfos::getInfo(std::string _name)
{
	for (auto gi : m_gi)
	{
		if (std::string(gi.second.name) == _name)
		{
			return gi.second;
		}
	}
	GuildInfoListEx gi{ 0 };
	return gi;
}
void CmdGuildInfos::setInfo(GuildInfoListEx& _gi) {
	//m_gi = _gi;
}