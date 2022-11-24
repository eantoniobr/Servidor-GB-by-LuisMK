// Arquivo cmd_change_nick.hpp
// Criado em 18/03/2018 as 13:11 por LuisMK
// Definição da classe CmdChangeNick

#pragma once
#ifndef _STDA_CMD_CHANGE_NICK_HPP
#define _STDA_CMD_CHANGE_NICK_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/pangya_game_st.h"

namespace stdA {
    class CmdChangeNick : public pangya_db {
        public:
            explicit CmdChangeNick(bool _waiter = false);
            CmdChangeNick(uint32_t _uid, std::string nick, bool _waiter = false);
            virtual ~CmdChangeNick();

            uint32_t getCode();

        protected:
            void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
            response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdChangeNick"; };
			virtual std::wstring _wgetName() override { return L"CmdChangeNick"; };

        private:
		uint32_t m_uid;
            uint32_t m_code;
std::string m_nick;
            const char* m_szConsulta = "pangya.ProcUpdateNick";
    };
}

#endif