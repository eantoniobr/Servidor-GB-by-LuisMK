// Arquivo cmd_insert_scratch_card_rare_win_log.hpp
// Defini��o da classe CmdInsertScratchCardRareWinLog

#pragma once
#ifndef _STDA_CMD_INSERT_SCRATCH_CARD_RARE_WIN_LOG_HPP
#define _STDA_CMD_INSERT_SCRATCH_CARD_RARE_WIN_LOG_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/scratch_card_type.hpp"

namespace stdA {
	class CmdInsertScratchCardRareWinLog : public pangya_db {
	public:
		explicit CmdInsertScratchCardRareWinLog(bool _waiter = false);
		CmdInsertScratchCardRareWinLog(uint32_t _uid, ctx_scratch_card_item_win& _ctx_psb, bool _waiter = false);
		virtual ~CmdInsertScratchCardRareWinLog();

		uint32_t getUID();
		void setUID(uint32_t _uid);

		ctx_scratch_card_item_win& getInfo();
		void setInfo(ctx_scratch_card_item_win& _ctx_psb);

	protected:
		void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
		response* prepareConsulta(database& _db) override;

		// get Class name
		virtual std::string _getName() override { return "CmdInsertScratchyRareWin"; };
		virtual std::wstring _wgetName() override { return L"CmdInsertScratchyRareWin"; };

	private:
		uint32_t m_uid;
		ctx_scratch_card_item_win m_ctx_psb;

		const char* m_szConsulta = "pangya.ProcInsertScratchyRareWin";
	};
}

#endif // !_STDA_CMD_INSERT_SCRATCH_CARD_RARE_WIN_LOG_HPP
