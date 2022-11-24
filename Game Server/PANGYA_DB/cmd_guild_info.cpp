// Arquivo cmd_guild_info.cpp
// Criado em 24/03/2018 as 20:23 por Acrisio
// Implementa��o da classe CmdGuildInfo

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_guild_info.hpp"

using namespace stdA;

CmdGuildInfo::CmdGuildInfo(bool _waiter) : pangya_db(_waiter), m_uid(0), m_option(0), m_gi{ 0 } {
}

CmdGuildInfo::CmdGuildInfo(uint32_t _uid, uint32_t _option, bool _waiter) : pangya_db(_waiter), m_uid(_uid), m_option(_option), m_gi{ 0 } {
}

CmdGuildInfo::~CmdGuildInfo() {
}

void CmdGuildInfo::lineResult(result_set::ctx_res* _result, uint32_t /*_index_result*/) {

	checkColumnNumber(13, (uint32_t)_result->cols);

	m_gi.uid = IFNULL(atoi, _result->data[0]);

	if (is_valid_c_string(_result->data[1]))
		STRCPY_TO_MEMORY_FIXED_SIZE(m_gi.name, sizeof(m_gi.name), _result->data[1]);


	m_gi.total_member = IFNULL(atoi, _result->data[2]);


	if (_result->data[3] != nullptr)
	{
		std::string chars = ".png";
		std::string mark(_result->data[3]);

		for (char c : chars) {
			mark.erase(std::remove(mark.begin(), mark.end(), c), mark.end());
		}


#if defined(_WIN32)
		memcpy_s(m_gi.Image, sizeof(m_gi.Image), mark.c_str(), mark.size());
#elif defined(__linux__)
		memcpy(m_gi.Image, mark.c_str(), mark.c_str(), mark.size());
#endif
	}
	else
	{
#if defined(_WIN32)
		memcpy_s(m_gi.Image, sizeof(m_gi.Image), "guild_mark", sizeof(m_gi.Image));
#elif defined(__linux__)
		memcpy(m_gi.Image, "guild_mark", sizeof(m_gi.Image));
#endif	
	}



	//m_gi.index_mark_emblem = (uint32_t)IFNULL(atoi, _result->data[4]); // Guild Mark index esse � usado no JP

	if (is_valid_c_string(_result->data[5]))
	{
		std::string Notice(_result->data[5]);
#if defined(_WIN32)
		memcpy_s(m_gi.Notice, sizeof(m_gi.Notice), Notice.c_str(), Notice.size());
#elif defined(__linux__)
		memcpy(m_gi.Notice, _result->data[5], sizeof(m_gi.Notice));
#endif
	}

	if (is_valid_c_string(_result->data[6]))
	{
		std::string Introducting(_result->data[6]);

#if defined(_WIN32)
		memcpy_s(m_gi.Introducting, sizeof(m_gi.Introducting), Introducting.c_str(), Introducting.size());
#elif defined(__linux__)
		memcpy(m_gi.Introducting, _result->data[6], sizeof(m_gi.Introducting));
#endif
	}
	m_gi.point = IFNULL(atoi, _result->data[7]);
	m_gi.pang = IFNULL(atoi, _result->data[8]);
	m_gi.Position = IFNULL(atoi, _result->data[9]);
	m_gi.LeaderUID = IFNULL(atoi, _result->data[10]);
	if (_result->data[11] != nullptr) {
		std::string LeaderNickname(_result->data[11]);
#if defined(_WIN32)
		memcpy_s(m_gi.LeaderNickname, sizeof(m_gi.LeaderNickname), LeaderNickname.c_str(), LeaderNickname.size());
#elif defined(__linux__)
		memcpy(m_gi.mark_emblem, _result->data[11], sizeof(m_gi.LeaderNickname));
#endif
}
}

response* CmdGuildInfo::prepareConsulta(database& _db) {

	m_gi.clear();

	auto r = procedure(_db, m_szConsulta, std::to_string(m_uid) + ", " + std::to_string(m_option));

	checkResponse(r, "nao conseguiu pegar o guild info do player: " + std::to_string(m_uid) + " na option: " + std::to_string(m_option));

	return r;
}

GuildInfoEx& CmdGuildInfo::getInfo() {
	return m_gi;
}

void CmdGuildInfo::setInfo(GuildInfoEx& _gi) {
	m_gi = _gi;
}

uint32_t CmdGuildInfo::getUID() {
	return m_uid;
}

void CmdGuildInfo::setUID(uint32_t _uid) {
	m_uid = _uid;
}

uint32_t CmdGuildInfo::getOption() {
	return m_option;
}

void CmdGuildInfo::setOption(uint32_t _option) {
	m_option = _option;
}
