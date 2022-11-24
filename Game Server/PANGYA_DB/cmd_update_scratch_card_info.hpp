// Arquivo cmd_update_papel_shop_info.hpp
// Criado em 29/06/2022 POR lUISMK
// Defini��o da classe CmdUpdateScratchCardInfo
//
//#pragma once
//#ifndef _STDA_CMD_UPDATE_SCRATCH_CARD_INFO_HPP
//#define _STDA_CMD_UPDATE_SCRATCH_CARD_INFO_HPP
//
//#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
//#include "../TYPE/pangya_game_st.h"
//
//#if defined(_WIN32)
//#include <Windows.h>
//#elif defined(__linux__)
//#include "../../Projeto IOCP/UTIL/WinPort.h"
//#endif
//
//namespace stdA {
//	class CmdUpdateScratchCardInfo : public pangya_db {
//	public:
//		explicit CmdUpdateScratchCardInfo(bool _waiter = false);
//		CmdUpdateScratchCardInfo(uint32_t _uid, PlayerScratchCardInfo& _ppsi, SYSTEMTIME& _last_update, bool _waiter = false);
//		virtual ~CmdUpdateScratchCardInfo();
//
//		uint32_t getUID();
//		void setUID(uint32_t _uid);
//
//		SYSTEMTIME& getLastUpdate();
//		void setLastUpdate(SYSTEMTIME& _last_update);
//
//		PlayerScratchCardInfo& getInfo();
//		void setInfo(PlayerScratchCardInfo& _ppsi);
//
//	protected:
//		void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
//		response* prepareConsulta(database& _db) override;
//
//		 get Class name
//		virtual std::string _getName() override { return "CmdUpdateScratchCardInfo"; };
//		virtual std::wstring _wgetName() override { return L"CmdUpdateScratchCardInfo"; };
//
//	private:
//		uint32_t m_uid;
//		PlayerScratchCardInfo m_ppsi;
//		SYSTEMTIME m_last_update;
//
//		const char* m_szConsulta = "pangya.ProcUpdateScratchCardInfo";
//	};
//}
//
//#endif // !_STDA_CMD_UPDATE_SCRATCH_CARD_INFO_HPP
