// Arquivo scratch_card_system.hpp
// Criado em 09/07/2018 as 18:07 por Acrisio
// Defini��o da classe ScratchCardSystem

#pragma once
#ifndef _STDA_SCRATCH_CARD_SYSTEM_HPP
#define _STDA_SCRATCH_CARD_SYSTEM_HPP

#if defined(__linux__)
#include "../../Projeto IOCP/UTIL/WinPort.h"
#include <pthread.h>
#include <unistd.h>
#endif

#include "../TYPE/scratch_card_type.hpp"
#include <vector>
#include <map>

#include "../SESSION/player.hpp"

#include "../../Projeto IOCP/TYPE/singleton.h"

#define SCRATCH_CARD_ITEM_MIN_QNTD 1
#define SCRATCH_CARD_ITEM_MAX_QNTD 2
namespace stdA {
	class ScratchCardSystem {
	public:
		ScratchCardSystem();
		virtual ~ScratchCardSystem();

		/*static*/ void load();
		/*static*/ bool isLoad();


		// Check if he has coupon, return id or -1 if not
		/*static*/ WarehouseItemEx* hasCoupon(player& _session);
		bool IsCoupon(uint32_t item);
		std::vector<ctx_scratch_card_item_win> Play(player& _session);

	protected:
		/*static*/ void initialize();

		/*static*/ void clear();

	protected:
		static void SQLDBResponse(uint32_t _msg_id, pangya_db& _pangya_db, void* _arg);
		uint32_t FindRateByType(SCRATCH_CARD_TYPE tipo);

	private:
		//itens
		/*static*/  std::vector<ctx_scratch_card_item > m_ctx_psi;
		//coupons
		/*static*/ std::map< uint32_t, ctx_scratch_card_coupon > m_ctx_psc;
		//rate
			/*static*/ std::map< SCRATCH_CARD_TYPE, ctx_scratch_card_rate > m_rate;
		/*static*/ ctx_scratch_card m_ctx_ps;

		/*static*/ bool m_load;

#if defined(_WIN32)
		CRITICAL_SECTION m_cs;
#elif defined(__linux__)
		pthread_mutex_t m_cs;
#endif
	};

	typedef Singleton< ScratchCardSystem > sScratchCardSystem;
}

#endif // !_STDA_SCRATCH_CARD_SYSTEM_HPP
