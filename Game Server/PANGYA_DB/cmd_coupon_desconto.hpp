// Arquivo cmd_coupon_desconto.hpp
// Criado em 16/09/2022 as 22:05 por LUISMK
// Definição da classe CmdCouponDesconto

#pragma once
#ifndef _STDA_CMD_COUPON_DESCONTO_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/pangya_coupon_type.hpp"
#include <map>

namespace stdA {
    class CmdCouponDesconto : public pangya_db {
        public:
            explicit CmdCouponDesconto(bool _waiter = false);
            CmdCouponDesconto(uint32_t _uid, bool _waiter = false);
            virtual ~CmdCouponDesconto();
			 CouponDesconto& getInfo(uint32_t id);

        protected:
            void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
            response* prepareConsulta(database& _db) override;

			// get Class name
			virtual std::string _getName() override { return "CmdCouponDesconto"; };
			virtual std::wstring _wgetName() override { return L"CmdCouponDesconto"; };

        private:
            std::map< uint32_t, CouponDesconto > m_dc;

            // 0x1A000080 Normal, 0x1A000083 Partial
            const char* m_szConsulta = "SELECT Nome,typeid ,valor FROM pangya.pangya_coupon_desconto";
    };
}

#endif