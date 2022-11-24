// Arquivo papel_shop_type.hpp
// Criado em 29/06/2022 as 18:10 por LuisMK
// Definição de tipo usados na classe ScratCardSystem

#pragma once
#ifndef _STDA_SCRATCH_CARD_TYPE_HPP
#define _STDA_SCRATCH_CARD_TYPE_HPP

#include <memory>
#include "../../Projeto IOCP/UTIL/util_time.h"

#include <memory.h>


namespace stdA {

#if defined(__linux__)
#pragma pack(1)
#endif


	enum SCRATCH_CARD_TYPE :uint32_t {
		SCT_COMMUN, //tipo = 0(normal)
		SCT_COOKIE, // tipo =1(cookie)
		SCT_RARE //tipo =2(rare ou super rare)
	};

	struct ctx_scratch_card_item {
		void clear() { memset(this, 0, sizeof(ctx_scratch_card_item)); };
		uint32_t _typeid;
		uint32_t probabilidade;
		uint32_t qntd;
		int32_t numero;					// Número que o papel shop já está
		SCRATCH_CARD_TYPE tipo;
		unsigned char active : 1;		// Active 0 ou 1
	};
struct ctx_scratch_card_rate {
	ctx_scratch_card_rate(uint32_t _ul = 0u) {
		clear();
	};
		void clear() { memset(this, 0, sizeof(ctx_scratch_card_rate)); };
		std::string Nome;
		SCRATCH_CARD_TYPE Tipo;
		uint32_t Prob;
	};
	struct ctx_scratch_card {
		void clear() { memset(this, 0, sizeof(ctx_scratch_card)); };
		std::string toString() {
			return "NUMERO=" + std::to_string(numero) + ", LIMITTED_PER_DAY=" + std::to_string((unsigned short)limitted_per_day)
				+ ", UPDATE_DATE=" + _formatDate(update_date);
		};
		uint32_t numero;				// Atual Número do Papel Shop
		unsigned char limitted_per_day : 1; // Limitado por dia, tem uma quantidade que pode jogar	// 0 ou 1
		SYSTEMTIME update_date;				// Date de atualização do dia do papel shop
	};

	struct ctx_scratch_card_item_win {
		ctx_scratch_card_item_win(uint32_t _ul = 0u) {
			clear();
		};
		void clear() { memset(this, 0, sizeof(ctx_scratch_card_item_win)); };
		ctx_scratch_card_item ctx_psi;
		uint32_t qntd;					// Qntd do item que foi sorteado
		void* item;							// stItem, para depois que add no banco de dados, retornar o id, precisa quando envia o pacote de resposta de jogar o papel shop
	};


	struct ctx_scratch_card_coupon {
		void clear() { memset(this, 0, sizeof(ctx_scratch_card_coupon)); }
		uint32_t _typeid;
		unsigned char active : 1;	// 0 ou 1
	};

#if defined(__linux__)
#pragma pack()
#endif
}

#endif // !_STDA_SCRATCH_CARD_TYPE_HPP
