// Implementa��o da classe CmdGuildInfoList

#include "cmd_guild_info_list.hpp"

using namespace stdA;
CmdGuildInfoList::CmdGuildInfoList(bool _waiter)
	: pangya_db(_waiter), m_page(1u), m_category(0u), m_search(std::string("%")), m_sort(1u), m_gi() {
}

CmdGuildInfoList::CmdGuildInfoList(uint32_t page_id, uint32_t category, uint32_t _option, std::string search, bool _waiter)
	: pangya_db(_waiter), m_page(page_id), m_category(category), m_search(search), m_sort(_option), m_gi() {
}

CmdGuildInfoList::CmdGuildInfoList(uint32_t page_id, bool _waiter)
	: pangya_db(_waiter), m_page(page_id), m_category(0u), m_search(std::string("%")), m_sort(1u), m_gi()
{
}

CmdGuildInfoList::~CmdGuildInfoList()
{
}

GuildInfoListEx& CmdGuildInfoList::getInfo(uint32_t page_id, std::string search)
{
	// TODO: inserir instrução return aqui
};

GuildInfoList& CmdGuildInfoList::getInfo(uint32_t page_id)
{
	// TODO: inserir instrução return aqui
}

GuildInfoList& stdA::CmdGuildInfoList::getInfo(std::string name)
{
	auto it = m_gi.find(name);

	if (it != m_gi.end()) {


		return it->second;
	}
}

void stdA::CmdGuildInfoList::set(uint32_t page_id, uint32_t category, uint32_t _option, std::string search)
{
	/*PageSelect = page_id; 
	Category = (category);  
	Search = (search);
	sort = (_option);*/
}

std::map<std::string,GuildInfoListEx>& CmdGuildInfoList::getInfo()
{
	return m_gi;
}

void CmdGuildInfoList::lineResult(result_set::ctx_res* _result, uint32_t /*_index_result*/) {

	auto count = (uint32_t)_result->cols;
	checkColumnNumber(count, (uint32_t)_result->cols);

	GuildInfoListEx gi{ 0 };
	gi.uid = IFNULL(atoi, _result->data[1]);

	if (is_valid_c_string(_result->data[2]))
		STRCPY_TO_MEMORY_FIXED_SIZE(gi.name, sizeof(gi.name), _result->data[1]);


	gi.total_member = IFNULL(atoi, _result->data[4]);


	if (_result->data[10] != nullptr)
	{
		std::string chars = ".png";
		std::string mark(_result->data[10]);

		for (char c : chars) {
			mark.erase(std::remove(mark.begin(), mark.end(), c), mark.end());
		}


#if defined(_WIN32)
		memcpy_s(gi.Image, sizeof(gi.Image), mark.c_str(), mark.size());
#elif defined(__linux__)
		memcpy(gi.Image, mark.c_str(), mark.c_str(), mark.size());
#endif
	}
	else
	{
#if defined(_WIN32)
		memcpy_s(gi.Image, sizeof(gi.Image), "guild_mark", sizeof(gi.Image));
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
		memcpy(gi.Introducting, _result->data[4], sizeof(gi.Introducting));
#endif
	}
	gi.point = IFNULL(atoi, _result->data[12]);
	gi.pang = IFNULL(atoi, _result->data[13]);
	gi.LeaderUID = IFNULL(atoi, _result->data[14]);
	if (_result->data[9] != nullptr) {
		std::string LeaderNickname(_result->data[9]);
#if defined(_WIN32)
		memcpy_s(gi.LeaderNickname, sizeof(gi.LeaderNickname), LeaderNickname.c_str(), LeaderNickname.size());
#elif defined(__linux__)
		memcpy(gi.mark_emblem, _result->data[9], sizeof(gi.LeaderNickname));
#endif
	}

	if (_result->data[9] != nullptr) {
		_translateDate(_result->data[9], &gi.GUILD_CREATE_DATE);
	}


	auto it = m_gi.find(gi.name);

	if (it == m_gi.end())	// Add m_gioin ao map
		m_gi[std::string(gi.name)] = gi;
}

response* CmdGuildInfoList::prepareConsulta(database& _db) {
	
	m_gi.clear();

	auto r = procedure(_db, m_szConsulta[0], std::to_string(1) + ", " + std::to_string(0)+", " + _db.makeText(std::string("")) + ", " + std::to_string(1));

	checkResponse(r, "nao conseguiu pegar a lista de guild: ");

	return r;
}
