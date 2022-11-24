// Arquivo cmd_scratch_card_rate.cpp
// Implementa��o da classe CmdScratchCardRate

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_scratch_card_rate.hpp"

using namespace stdA;

CmdScratchCardRate::CmdScratchCardRate(bool _waiter) : pangya_db(_waiter), m_rate() {
}

CmdScratchCardRate::~CmdScratchCardRate() {
}


void CmdScratchCardRate::lineResult(result_set::ctx_res* _result, uint32_t /*_index_result*/) {

	checkColumnNumber(3, (uint32_t)_result->cols);

	ctx_scratch_card_rate rate{ 0 };

	rate.Nome = std::string( _result->data[0]);
	rate.Tipo = SCRATCH_CARD_TYPE(IFNULL(atoi, _result->data[1]));
	rate.Prob = IFNULL(atoi, _result->data[2]);
	m_rate[rate.Tipo]= rate;
}

response* CmdScratchCardRate::prepareConsulta(database& _db) {

	auto r = consulta(_db, m_szConsulta);

	checkResponse(r, "nao conseguiu pegar os scratch card itens ativos !");

	return r;
}

ctx_scratch_card_rate& CmdScratchCardRate::getInfo(SCRATCH_CARD_TYPE _type) {
	
	ctx_scratch_card_rate rate{ 0 };

	for (auto& el : m_rate) {

		if (el.second.Tipo == _type) {

			rate = el.second;
		}
	}
	return rate;

}

std::map< SCRATCH_CARD_TYPE, ctx_scratch_card_rate >& CmdScratchCardRate::getInfo() {

return	m_rate;
}