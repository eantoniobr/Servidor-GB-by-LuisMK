// Arquivo cmd_change_nick.cpp
// Criado em 2022 as 13:17 por LuisMK
// Implementação da classe CmdChangeNick

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_change_nick.hpp"
#include "../../Projeto IOCP/UTIL/util_time.h"

#include <memory.h>

using namespace stdA;

CmdChangeNick::CmdChangeNick(bool _waiter) : pangya_db(_waiter), m_uid(0), m_code(0), m_nick{std::string("")} {
};

CmdChangeNick::CmdChangeNick(uint32_t _uid, std::string nick, bool _waiter) : pangya_db(_waiter), m_code(0), m_uid(_uid), m_nick{nick} {
};

CmdChangeNick::~CmdChangeNick() {
};

void CmdChangeNick::lineResult(result_set::ctx_res* _result, uint32_t /*_index_result*/) {

    checkColumnNumber(1, (uint32_t)_result->cols);

	m_code = (uint32_t)IFNULL(atoi, _result->data[0]);
};

response* CmdChangeNick::prepareConsulta(database& _db) {

    auto r = procedure(_db, m_szConsulta, std::to_string(m_uid) + ", " +_db.makeText(m_nick));

    checkResponse(r, "nao conseguiu pegar  o code do nick: " + std::to_string(m_uid));

	return r;
};

uint32_t CmdChangeNick::getCode() {
    return m_code;
};
