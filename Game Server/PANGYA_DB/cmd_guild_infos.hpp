// Arquivo cmd_guild_info.hpp
// Criado em 24/03/2018 as 20:18 por Acrisio
// Defini��o da classe CmdGuildInfos

#pragma once
#ifndef _STDA_CMD_GUILD_INFO_HPP
#define _STDA_CMD_GUILD_INFO_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/guild_system_type.hpp"
#include <map>
namespace stdA {
	class CmdGuildInfos : public pangya_db {
		public:
			explicit CmdGuildInfos(bool _waiter = false);
			CmdGuildInfos(uint32_t _uid, uint32_t _option, bool _waiter = false);
			CmdGuildInfos(uint32_t page_id, uint32_t category, uint32_t _option, std::string search = "%", bool _waiter = false);
			//CmdGuildInfos(uint32_t page_id, bool _waiter = false);
			virtual ~CmdGuildInfos();

			std::map<uint32_t, GuildInfoListEx>& getInfo();
			GuildInfoListEx& getInfo(uint32_t _uid);
			GuildInfoListEx& getInfo(std::string _name);
			void setInfo(GuildInfoListEx& _gi);

			uint32_t getUID();
			void setUID(uint32_t _uid);

			uint32_t getOption();
			void setOption(uint32_t _option);

		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdGuildInfos"; };
			virtual std::wstring _wgetName() override { return L"CmdGuildInfos"; };

		private:
			uint32_t m_page;
			uint32_t m_category;
			std::string m_search  = std::string("%");
			uint32_t m_sort;
			std::map<uint32_t,GuildInfoListEx> m_gi;

			const char* m_szConsulta = "pangya.ProcGetListGuild";
	};
}

#endif // !_STDA_CMD_GUILD_INFO_HPP
