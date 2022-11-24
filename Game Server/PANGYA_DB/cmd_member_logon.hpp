#pragma once
#ifndef _STDA_CMD_MEMBER_LOGON_HPP
#define _STDA_CMD_MEMBER_LOGON_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
namespace stdA {
	class CmdMemberLogon : public pangya_db {
	public:
		explicit CmdMemberLogon(bool _waiter = false);
		CmdMemberLogon(uint32_t _uid, bool _waiter = false);
		virtual ~CmdMemberLogon();

	protected:
		void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
		response* prepareConsulta(database& _db) override;

		// get Class name
		virtual std::string _getName() override { return "CmdMemberLogon"; };
		virtual std::wstring _wgetName() override { return L"CmdMemberLogon"; };

	private:
		uint32_t m_uid;
		const char* m_szConsulta = "UPDATE pangya.account SET Logon = 0, LastLeaveTime = getdate() WHERE game_server_id = ";
	};
}

#endif // !_STDA_CMD_MEMBER_LOGON_HPP