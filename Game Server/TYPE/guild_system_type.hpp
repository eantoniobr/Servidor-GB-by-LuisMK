// Arquivo papel_shop_type.hpp
// Criado em 29/06/2022 as 18:10 por LuisMK
// Definição de tipo usados na classe GuildSystem

#pragma once
#ifndef _STDA_GUILD_SYTEM_TYPE_HPP
#define _STDA_GUILD_SYTEM_TYPE_HPP

#include <memory>
#include "../../Projeto IOCP/UTIL/util_time.h"

#include <memory.h>

namespace stdA {

#if defined(__linux__)
#pragma pack(1)
#endif
	struct GuildLog {
		GuildLog(uint32_t _ul = 0u) {
			clear();
		};
		void clear() {
			memset(this, 0, sizeof(GuildLog));
			unknown = -1;
		};
		uint32_t unknown;
		uint32_t uid;
		char name[17];
		uint32_t flag;
		SYSTEMTIME reg_date;

	};
	struct GuildMark {
		GuildMark(uint32_t _ul = 0u) {
			clear();
		};
		void clear() {
			memset(this, 0, sizeof(GuildMark));
		};
		uint32_t mark_idx;
		std::string mark_image;
		
	};
	struct GuildMemberInfo {
		GuildMemberInfo(uint32_t _ul = 0u) {
			clear();
		};
		void clear() {
			memset(this, 0, sizeof(GuildMemberInfo));
		};

		uint32_t uid;
		uint32_t member_uid;
		uint32_t position;
		char message[17];
		uint32_t point;
		uint32_t pang;
		char name[17];
		char nick[22];
		unsigned char logon;
	};
	struct GuildInfoList {
		GuildInfoList(uint32_t _ul = 0u) {
			clear();
		};
		void clear() {
			memset(this, 0, sizeof(GuildInfoList));
			uid = 0;
		};
		
		uint32_t uid;
		char name[17];
		uint32_t point;
		uint32_t pang;
		uint32_t total_member;
		SYSTEMTIME GUILD_CREATE_DATE;
		char Introducting[101];
		uint32_t Position;
		uint32_t LeaderUID;
		char LeaderNickname[22];
		char Image[12];
	};

	struct GuildInfoListEx :public GuildInfoList
	{

		GuildInfoListEx(uint32_t _ul = 0u) : GuildInfoList(_ul) {
			clear();
		};
		void clear()
		{
			GuildInfoList::clear();

		};
		uint32_t Page;
	};

#if defined(__linux__)
#pragma pack()
#endif
}

#endif // !_STDA_SCRATCH_CARD_TYPE_HPP
