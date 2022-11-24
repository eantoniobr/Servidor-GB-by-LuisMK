// Criado em 25/09/2022 luismk
// Definicao da classe CmdInsertNotice

#pragma once
#ifndef _STDA_CMD_INSERT_NOTICE_HPP
#define _STDA_CMD_INSERT_NOTICE_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"

namespace stdA {
	class CmdInsertNotice : public pangya_db {
		public:
			explicit CmdInsertNotice(bool _waiter = false);
			CmdInsertNotice(uint32_t _server_uid, std::string& _msg, bool _waiter = false);
			virtual ~CmdInsertNotice();

			uint32_t getServerUID();
			void setServerUID(uint32_t _server_uid);

			std::string& getMessage();
			void setMessage(std::string& _msg);

		protected:
			void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
			response* prepareConsulta(database& _db) override;

			std::string _getName() override { return "CmdInsertNotice"; };
			std::wstring _wgetName() override { return L"CmdInsertNotice"; };

		private:
			uint32_t m_server_uid;
			std::string m_msg;

			const char* m_szConsulta = "pangya.ProcInsertNoticeBroadcast";
	};
}

#endif // !_STDA_CMD_INSERT_NOTICE_HPP
