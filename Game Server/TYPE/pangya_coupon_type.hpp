
#pragma once
#ifndef _STDA_COUPON_TYPE_HPP
#define _STDA_COUPON_TYPE_HPP

#include <memory>
#include "../../Projeto IOCP/UTIL/util_time.h"

#include <memory.h>

namespace stdA {

#if defined(__linux__)
#pragma pack(1)
#endif
	// Coupons Gacha
	struct CouponDesconto {
		CouponDesconto(uint32_t _ul = 0u) {
		clear();
	};
		void clear() {
			memset(this, 0, sizeof(CouponDesconto));
		};
		std::string Nome;
		int32_t _typeid;
		int32_t valor;
	};

#if defined(__linux__)
#pragma pack()
#endif
}

#endif // !_STDA_COUPON_TYPE_HPP
