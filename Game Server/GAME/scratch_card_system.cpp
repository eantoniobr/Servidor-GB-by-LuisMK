// Arquivo scratch_card_system.cpp
// Criado em 29/06/2022 as 18:43 por Acrisio
// Implementa��o da classe ScratchCardSystem

#if defined(_WIN32)
#pragma pack(1)
#endif

#if defined(_WIN32)
#include <WinSock2.h>
#endif

#include "scratch_card_system.hpp"
#include "../../Projeto IOCP/UTIL/exception.h"
#include "../../Projeto IOCP/TYPE/stda_error.h"
#include "../../Projeto IOCP/UTIL/message_pool.h"

#include "../UTIL/lottery.hpp"

#include <algorithm>
#include <ctime>

#include "../../Projeto IOCP/UTIL/iff.h"
#include "../../Projeto IOCP/UTIL/random_gen.hpp"

#include "../PANGYA_DB/cmd_scratch_card_item.hpp"
#include "../PANGYA_DB/cmd_scratch_card_coupon.hpp"

#include "../../Projeto IOCP/DATABASE/normal_manager_db.hpp"

#include "../Game Server/game_server.h"
#include "../PANGYA_DB/cmd_scratch_card_rate.hpp"
uint32_t scartch_card_coupon_typeid[]{ 436207779, 436207664, 436207667, 436207668 };


#define FIND_ELEMENT_ARRAY_OF_ARRAY(_arr1, _arr2) (std::find_if((_arr1), LAST_ELEMENT_IN_ARRAY((_arr1)), [&](auto& _element) { \
	return std::find((_arr2), LAST_ELEMENT_IN_ARRAY((_arr2)), _element) != LAST_ELEMENT_IN_ARRAY((_arr2)); \
}) != LAST_ELEMENT_IN_ARRAY((_arr1))) \

using namespace stdA;

#define CHECK_SESSION(_method) { \
	if (!_session.getState() || !_session.isConnected() || _session.isQuit()) \
		throw exception("[ScratchCardSystem::" + std::string((_method)) + "][Error] player is not connected.", STDA_MAKE_ERROR(STDA_ERROR_TYPE::SCRATCH_CARD_SYSTEM, 2, 0)); \
}

#if defined(_WIN32)
#define TRY_CHECK			 try { \
								EnterCriticalSection(&m_cs);
#elif defined(__linux__)
#define TRY_CHECK			 try { \
								pthread_mutex_lock(&m_cs);
#endif

#if defined(_WIN32)
#define LEAVE_CHECK				LeaveCriticalSection(&m_cs);
#elif defined(__linux__)
#define LEAVE_CHECK				pthread_mutex_unlock(&m_cs);
#endif

#if defined(_WIN32)
#define CATCH_CHECK(_method) }catch (exception& e) { \
								LeaveCriticalSection(&m_cs); \
								\
								_smp::message_pool::getInstance().push(new message("[ScratchCardSystem::" + std::string(_method) + "][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));
#elif defined(__linux__)
#define CATCH_CHECK(_method) }catch (exception& e) { \
								pthread_mutex_unlock(&m_cs); \
								\
								_smp::message_pool::getInstance().push(new message("[ScratchCardSystem::" + std::string(_method) + "][ErrorSystem] " + e.getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));
#endif

#define END_CHECK			 } \

ScratchCardSystem::ScratchCardSystem() : m_load(false), m_ctx_ps{ 0 }, m_ctx_psc{}, m_ctx_psi{} {

#if defined(_WIN32)
	InitializeCriticalSection(&m_cs);
#elif defined(__linux__)
	INIT_PTHREAD_MUTEXATTR_RECURSIVE;
	INIT_PTHREAD_MUTEX_RECURSIVE(&m_cs);
	DESTROY_PTHREAD_MUTEXATTR_RECURSIVE;
#endif

	// Inicializa
	initialize();

}

ScratchCardSystem::~ScratchCardSystem() {

	clear();

#if defined(_WIN32)
	DeleteCriticalSection(&m_cs);
#elif defined(__linux__)
	pthread_mutex_destroy(&m_cs);
#endif
}

void ScratchCardSystem::initialize() {

	TRY_CHECK;

	ctx_scratch_card_coupon ctx_psc{ 0 };
	for (size_t i = 0; i < 4; i++)
	{
		ctx_psc._typeid = scartch_card_coupon_typeid[i];
		if (ctx_psc._typeid != 0)
		{
			ctx_psc.active = 1;
		}

		auto it = m_ctx_psc.find(ctx_psc._typeid);

		if (it == m_ctx_psc.end())	// N�o tem add um novo coupon
			m_ctx_psc[ctx_psc._typeid] = ctx_psc;
	}


	// Load Item(s)
	CmdScratchCardItem cmd_psi(true);	// Waiter

	snmdb::NormalManagerDB::getInstance().add(0, &cmd_psi, nullptr, nullptr);

	cmd_psi.waitEvent();

	if (cmd_psi.getException().getCodeError() != 0)
		throw cmd_psi.getException();

	m_ctx_psi = cmd_psi.getInfo();
	// Load Rate(s)
	CmdScratchCardRate cmd_psr(true);	// Waiter

	snmdb::NormalManagerDB::getInstance().add(0, &cmd_psr, nullptr, nullptr);

	cmd_psr.waitEvent();

	if (cmd_psr.getException().getCodeError() != 0)
		throw cmd_psr.getException();

	m_rate = cmd_psr.getInfo();

	if (m_ctx_psi.size() <= 0 || m_rate.size() <= 0)
	{
		_smp::message_pool::getInstance().push(new message("[ScratchCardSystem::initialize][Log] Scratch Card System nao Carregado com sucesso!", CL_FILE_LOG_AND_CONSOLE));
	}

	// Carregado com sucesso!
	m_load = true;

	LEAVE_CHECK;

	CATCH_CHECK("initialize");

	// Relança para o server toma as providências
	throw;

	END_CHECK;
}

void ScratchCardSystem::clear() {

#if defined(_WIN32)
	EnterCriticalSection(&m_cs);
#elif defined(__linux__)
	pthread_mutex_lock(&m_cs);
#endif

	m_ctx_ps = { 0 };

	if (!m_ctx_psi.empty()) {
		m_ctx_psi.clear();
	}

	if (!m_ctx_psc.empty())
		m_ctx_psc.clear();

	m_load = false;

#if defined(_WIN32)
	LeaveCriticalSection(&m_cs);
#elif defined(__linux__)
	pthread_mutex_unlock(&m_cs);
#endif
}
void ScratchCardSystem::load() {

	if (isLoad())
		clear();

	initialize();
}

bool ScratchCardSystem::isLoad() {

	bool isLoad = false;

#if defined(_WIN32)
	EnterCriticalSection(&m_cs);
#elif defined(__linux__)
	pthread_mutex_lock(&m_cs);
#endif

	isLoad = (m_load && !m_ctx_psi.empty() && !m_ctx_psc.empty());

#if defined(_WIN32)
	LeaveCriticalSection(&m_cs);
#elif defined(__linux__)
	pthread_mutex_unlock(&m_cs);
#endif

	return isLoad;
}


WarehouseItemEx* ScratchCardSystem::hasCoupon(player& _session) {
	CHECK_SESSION("hasCoupon");

	WarehouseItemEx* pWi = nullptr;

	TRY_CHECK;

	for (auto& el : m_ctx_psc) {

		if (el.second.active && (pWi = _session.m_pi.findWarehouseItemByTypeid(el.second._typeid)) != nullptr) {

			LEAVE_CHECK;

			return pWi;
		}
	}

	LEAVE_CHECK;

	CATCH_CHECK("hasCoupon");
	END_CHECK;

	return nullptr;
}

bool ScratchCardSystem::IsCoupon(uint32_t item)
{


	TRY_CHECK;

	for (auto& el : m_ctx_psc) {

		if (el.second.active && el.second._typeid == item) {

			LEAVE_CHECK;

			return true;
		}
	}

	LEAVE_CHECK;

	CATCH_CHECK("hasCoupon");
	END_CHECK;

	return false;
};
std::vector<ctx_scratch_card_item_win> ScratchCardSystem::Play(player& _session)
{
	CHECK_SESSION("SC_Prize");

	std::vector< ctx_scratch_card_item_win > v_item;

	ctx_scratch_card_item_win ctx_b{ 0 };
	if (!isLoad())
	{
		_smp::message_pool::getInstance().push(new message("[ScratchCardSystem::Error][ErrorSystem] " + std::string("caramba, tu não sabe que tem carregar a tabela nao? scratchy_item e a tabela, blz?"), CL_FILE_LOG_AND_CONSOLE));
		throw exception("[ScratchCardSystem::Play][Error] O Scratch Card System nao foi carregado ainda, carregue ele primeiro antes de tentar ganhar uns itens, seu lezarento", STDA_MAKE_ERROR(STDA_ERROR_TYPE::PAPEL_SHOP_SYSTEM, 3, 0));
	}
	TRY_CHECK;

	Lottery lottery((uint64_t)&m_ctx_psi);

	// Pega o Rate do Game Server
	auto rate_cookie_server = sgs::gs::getInstance().getInfo().rate.papel_shop_cookie_item / 100.f;
	auto rate_rare_server = sgs::gs::getInstance().getInfo().rate.scratchy / 100.f;
	bool event_x2 = (sgs::gs::getInstance().getInfo().rate.scratchy) / 100 >= 2;

	for (auto& el : m_ctx_psi)
		if (el.active && (el.numero == -1 || el.numero == m_ctx_ps.numero))
			lottery.push((uint32_t)(el.probabilidade * (el.tipo == SCT_COOKIE ? rate_cookie_server : (el.tipo == SCT_RARE ? rate_rare_server : /*(NORMAL)*/1.f))), (size_t)&el);

	uint16_t num = 1;
	if (event_x2)
	{
		num = SCRATCH_CARD_ITEM_MIN_QNTD + (sRandomGen::getInstance().rIbeMt19937_64_chrono() % (SCRATCH_CARD_ITEM_MAX_QNTD - SCRATCH_CARD_ITEM_MIN_QNTD + 1));
	}

	//vai que não consegue calcular a quantidade de giros
	if (num == 0)
	{
		num = SCRATCH_CARD_ITEM_MIN_QNTD;
	}
	Lottery::LotteryCtx* lc = nullptr;
	do {

		CHECK_SESSION("RASPADINHA");

		// Sortea um valor
		lc = lottery.spinRoleta();

		if (lc == nullptr)
			throw exception("[ScractCardSystem::Play][Error] nao conseguiu sortear item. Bug viu, procura um programador e resolve isso rapido !", STDA_MAKE_ERROR(STDA_ERROR_TYPE::PAPEL_SHOP_SYSTEM, 1, 0));

		ctx_b.clear();

		auto ctx_psi = (ctx_scratch_card_item*)lc->value;

		// Player já tem o item, e nao pode ter duplicate, sortea um novo para ele
		if ((!sIff::getInstance().IsCanOverlapped(ctx_psi->_typeid) || sIff::getInstance().getItemGroupIdentify(ctx_psi->_typeid) == iff::CAD_ITEM) && _session.m_pi.ownerItem(ctx_psi->_typeid))
			continue;

		if (ctx_psi->tipo == SCT_RARE)
		{
			num = SCRATCH_CARD_ITEM_MIN_QNTD;
		}



		// Raro Item Sempre é a qntd minima
		if (ctx_psi->tipo == SCT_RARE)
		{
			//caramba, pq é tão dificil adicionar dados corretos? isso é uma prevecao de dados..
			//ant-bug-de-lammer haha
			if (ctx_psi->qntd == 0)
			{
				ctx_b.qntd = 1;
			}
		}

		//vai que ele não tem pratica, caramba, mas é a segunda vez né haha
		if (ctx_psi->tipo != SCT_RARE && ctx_psi->qntd == 0)
		{
			ctx_b.qntd = (sRandomGen::getInstance().rIbeMt19937_64_chrono() % (3 - 1 + 1));
		}

		//sei la, vai que ele não sabe o que é QUANTIDADE, haha ;)
		if (ctx_psi->qntd == 0)
		{
			ctx_b.qntd = (sRandomGen::getInstance().rIbeMt19937_64_chrono() % (3 - 1 + 1));
		}

		// Item, so faco uma setagem, nada de mais né, ant debug
		ctx_b.qntd = ctx_psi->qntd;
		ctx_b.ctx_psi = *ctx_psi;

		// Add Item ao vector de itens ganhados
		v_item.push_back(ctx_b);

		// Decrementa o num, já que o item foi dropad0
		num--;//SO FAZIA 1 SORTEIO, VOU FAZER 2, PQ EU QUERO, BLZ?!

	} while (num > 0);

	LEAVE_CHECK;

	CATCH_CHECK("SC_Prize");
	END_CHECK;

	return v_item;
}


void ScratchCardSystem::SQLDBResponse(uint32_t _msg_id, pangya_db& _pangya_db, void* _arg) {

#ifdef _DEBUG
	// Classe estatica não pode passar o ponteiro dela, por ser estática, então passa nullptr
	if (_arg == nullptr)
		// Static class
		_smp::message_pool::getInstance().push(new message("[ScratchCardSystem::SQLDBResponse][WARNING] _arg is nullptr", CL_FILE_LOG_AND_CONSOLE));
#endif // _DEBUG

	// Por Hora só sai, depois faço outro tipo de tratamento se precisar
	if (_pangya_db.getException().getCodeError() != 0) {
		_smp::message_pool::getInstance().push(new message("[ScratchCardSystem::SQLDBResponse][Error] " + _pangya_db.getException().getFullMessageError(), CL_FILE_LOG_AND_CONSOLE));
		return;
	}

	switch (_msg_id) {
	case 1: // Update Scratch Card Config
	{

		break;
	}
	case 2:	// Update Scratch Card Player Info
	{
		// Aqui não usa por que é um update
		break;
	}
	case 3:	// Update Scratch Card Last Day Update do player
	{
		// Aqui não usa por que é um update
		break;
	}
	case 0:
	default:
		break;
	}
}

uint32_t stdA::ScratchCardSystem::FindRateByType(SCRATCH_CARD_TYPE tipo)
{

	TRY_CHECK;
	for (auto& el : m_rate) {

		if (el.second.Tipo == tipo) {

			LEAVE_CHECK;

			return el.second.Prob;
		}
	}

	LEAVE_CHECK;

	CATCH_CHECK("FindRateByType");
	END_CHECK;

	return 1;
}
