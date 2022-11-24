// Arquivo cmd_guild_info.hpp
// Criado em 05/07/2022 
// Defini��o da classe CmdGuildInfoList

#pragma once
#ifndef _STDA_CMD_GUILD_INFO_LIST_HPP
#define _STDA_CMD_GUILD_INFO_LIST_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/guild_system_type.hpp"
#include <map>

namespace stdA {
	class CmdGuildInfoList : public pangya_db {
	public:
		explicit CmdGuildInfoList(bool _waiter = false);
		CmdGuildInfoList(uint32_t page_id, uint32_t category, uint32_t _option, std::string search = "%", bool _waiter = false);
		CmdGuildInfoList(uint32_t page_id, bool _waiter = false);
		virtual ~CmdGuildInfoList();

		GuildInfoListEx& getInfo(uint32_t page_id, std::string search = "%");
		GuildInfoList& getInfo(uint32_t page_id);
		GuildInfoList& getInfo(std::string name);
		void set(uint32_t page_id, uint32_t category, uint32_t _option, std::string search = "%");
		std::map <std::string, GuildInfoListEx>& getInfo();
	protected:
		void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
		response* prepareConsulta(database& _db) override;

		// get Class name
		virtual std::string _getName() override { return "CmdGuildInfoList"; };
		virtual std::wstring _wgetName() override { return L"CmdGuildInfoList"; };

	private:
		uint32_t m_page;
		uint32_t m_category;
		std::string m_search;
		uint32_t m_sort;
		std::map <std::string, GuildInfoListEx> m_gi;
		const char* m_szConsulta[2] = {"pangya.ProcGetListGuild","pangya.ProcGetGuilds"
	};

	};
}

#endif // !_STDA_CMD_GUILD_INFO_LIST_HPP
