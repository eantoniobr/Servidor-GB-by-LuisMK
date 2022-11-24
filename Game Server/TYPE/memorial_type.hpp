// Arquivo memorial_type.hpp
// Criado em 21/07/2018 as 18:54 por Acrisio
// Definição dos tipos utilizados pela classe MemorialSystem

#pragma once
#ifndef _STDA_MEMORIAL_TYPE_HPP
#define _STDA_MEMORIAL_TYPE_HPP

#include <vector>
#include <memory>

#include <memory.h>

namespace stdA {

#if defined(__linux__)
#pragma pack(1)
#endif

	enum MEMORIAL_COIN_TYPE : uint32_t {
		MCT_NORMAL,
		MCT_PREMIUM,
		MCT_SPECIAL,
		MCT_CHARACTER
	};
	// 0 = ITEM COMUM
   // 1 = ITEM NORMAL ASA FECHADA
   // 2 = ITEM NORMAL ASA ABERTA
   // 3 = ITEM RARO ASA FECHADA
   // 4 = ITEM RARO ASA ABERTA
	enum MEMORIAL_RARE_TYPE : int32_t
	{
		DEFAULT = -1,
		COOKIES,
		RARE,
		INCOMUM,
		SUPER_RARE,
		SUPER_RARE2
	};
	enum MEMORIAL_RATE_TYPE : uint32_t
	{
		Default = 2,
		Rate1 = 100,
		Rate2 = 200,
		Rate3 = 300,
		Rate4 = 400,
		Rate5 = 500
	}; 
	
	struct ctx_coin_item {
		ctx_coin_item(uint32_t _ul = 0u) {
			clear();
		};
		ctx_coin_item(MEMORIAL_RARE_TYPE _tipo, uint32_t __typeid, uint32_t _qntd)
			: tipo(_tipo), _typeid(__typeid), qntd(_qntd) {
		};
		void clear() { memset(this, 0, sizeof(ctx_coin_item)); };
		MEMORIAL_RARE_TYPE tipo;
		uint32_t _typeid;
		uint32_t qntd;
	};

	struct ctx_coin_item_ex : public ctx_coin_item {
		ctx_coin_item_ex(uint32_t _lc = 0u) {
			clear();
		};
		ctx_coin_item_ex(MEMORIAL_RARE_TYPE _tipo, uint32_t __typeid, uint32_t _qntd, uint32_t _probabilidade, int32_t _gachar_number)
			: ctx_coin_item(_tipo, __typeid, _qntd), probabilidade(_probabilidade), gacha_number(_gachar_number) {
		};
		void clear() { memset(this, 0, sizeof(ctx_coin_item_ex)); };
		uint32_t probabilidade;
		int32_t gacha_number;
	};

	struct ctx_coin {
		ctx_coin(uint32_t _ul = 0u) {
			clear();
		};
		~ctx_coin() {};
		void clear() {

			tipo = MCT_NORMAL;
			_typeid = 0u;
			probabilidade = 100;

			if (!item.empty()) {
				item.clear();
				item.shrink_to_fit();
			}
		};
		MEMORIAL_COIN_TYPE tipo;
		uint32_t _typeid;
		uint32_t probabilidade;
		std::vector< ctx_coin_item_ex > item;
	};


	struct ctx_rate {
		ctx_rate(uint32_t _ul = 0u) {
			clear();
		};
		ctx_rate(MEMORIAL_RARE_TYPE _tipo, uint32_t _probabilidade)
			: tipo(_tipo), probabilidade(_probabilidade) {
		};
		~ctx_rate() {};
		void clear() {

			tipo = COOKIES;
			probabilidade = 100;
		};
		MEMORIAL_RARE_TYPE tipo;
		uint32_t probabilidade;
	};

	struct ctx_memorial_level {
		void clear() { memset(this, 0, sizeof(ctx_memorial_level)); };
		uint32_t level;		// Level
		uint32_t gacha_number;	// número máximo do gacha
	};

	struct ctx_coin_set_item {
		ctx_coin_set_item(uint32_t _ul = 0u) {
			clear();
		};
		~ctx_coin_set_item() {};
		void clear() {
			
			_typeid = 0u;
			tipo = 0u;
			flag = -100;

			if (!item.empty()) {
				item.clear();
				item.shrink_to_fit();
			}
		};
		int32_t flag;
		uint32_t _typeid;
		unsigned char tipo : 1, : 0;		// Tipo 0 e 1, 1 Premium e 0 todos os outros
		std::vector< ctx_coin_item_ex > item;
	};

#if defined(__linux__)
#pragma pack()
#endif
}

#endif // !_STDA_MEMORIAL_TYPE_HPP
