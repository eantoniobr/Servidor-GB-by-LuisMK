// Arquivo cmd_coupon_desconto.cpp
// Criado em 16/09/2022 as 22:14 por Luismk
// Implementação da classe CmdCouponDesconto

#if defined(_WIN32)
#pragma pack(1)
#endif

#include "cmd_coupon_desconto.hpp"

using namespace stdA;

CmdCouponDesconto::CmdCouponDesconto(bool _waiter) : pangya_db(_waiter),m_dc{} {
}

CmdCouponDesconto::CmdCouponDesconto(uint32_t _uid, bool _waiter) : pangya_db(_waiter), m_dc{} {
}

CmdCouponDesconto::~CmdCouponDesconto() {
}

CouponDesconto& stdA::CmdCouponDesconto::getInfo(uint32_t _typeid)
{
    // TODO: inserir instrução return aqui

    auto it = m_dc.find(_typeid);

    if (it != m_dc.end()) {

        return it->second;
    }
    CouponDesconto dc{ 0 };
    return dc;
}

void CmdCouponDesconto::lineResult(result_set::ctx_res* _result, uint32_t _index_result) {

    checkColumnNumber(3, (uint32_t)_result->cols);
    CouponDesconto dc{ 0 };
    if (is_valid_c_string(_result->data[0]))
    {
        std::string nome(_result->data[0]);

        dc.Nome = nome;
    }

    if (_result->data[1]  != nullptr) 
        dc._typeid = IFNULL(atoi, _result->data[1]);

    if (_result->data[2] != nullptr)   
        dc.valor = IFNULL(atoi, _result->data[2]);

    auto it = m_dc.find(dc._typeid);

    if (it != m_dc.end())// repetido nao add
    {
       
    }
    else
    {
        m_dc.insert(std::make_pair(dc._typeid, dc));
       
    }

}

response* CmdCouponDesconto::prepareConsulta(database& _db) {

    m_dc.clear();

    auto r = consulta(_db, m_szConsulta);

    checkResponse(r, "nao conseguiu pegar o(s) coupon(s) desconto");

    return r;
}
