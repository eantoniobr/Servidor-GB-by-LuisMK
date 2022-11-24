// Arquivo cmd_scratch_card_rate.cpp
// Implementa��o da classe CmdFirstAnniversary

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_1st_anniversary.hpp"

using namespace stdA;

CmdFirstAnniversary::CmdFirstAnniversary(bool _waiter) : pangya_db(_waiter) {
}

CmdFirstAnniversary::~CmdFirstAnniversary() {
}


void CmdFirstAnniversary::lineResult(result_set::ctx_res* _result, uint32_t /*_index_result*/) {
//faz nada 
}

response* CmdFirstAnniversary::prepareConsulta(database& _db) {

	auto r = consulta(_db, m_szConsulta);

	checkResponse(r, "nao conseguiu pegar o aniversario !");

	return r;
}
