// Arquivo cmd_box_info.hpp
// Criado em 15/07/2018 as 21:57 por Acrisio
// Defini��o da classe CmdBoxRareItem

#pragma once
#ifndef _STDA_BOX_RARE_ITEM_HPP
#define _STDA_BOX_RARE_ITEM_HPP

#include "../../Projeto IOCP/PANGYA_DB/pangya_db.h"
#include "../TYPE/box_type.hpp"
#include <map>

namespace stdA {
	class CmdBoxRareItem : public pangya_db {
	public:
		enum TYPE_PROC : unsigned char {
			OLD, NEW
		};
		explicit CmdBoxRareItem(bool _waiter = false);
		CmdBoxRareItem(uint32_t uid, uint32_t _typeid, TYPE_PROC _type, bool _waiter);
		virtual ~CmdBoxRareItem();

		std::map< uint32_t, ctx_box >& getInfo();
		void setType(uint32_t uid, uint32_t _typeid, TYPE_PROC _type);

	protected:
		void lineResult(result_set::ctx_res* _result, uint32_t _index_result) override;
		response* prepareConsulta(database& _db) override;

		// get Class name
		virtual std::string _getName() override { return "CmdBoxRareItem"; };
		virtual std::wstring _wgetName() override { return L"CmdBoxRareItem"; };

	private:
		std::map< uint32_t, ctx_box > m_box;
		uint32_t IDUSER;
		uint32_t Box_TypeId;
		TYPE_PROC m_type;

		const char* m_szConsulta[2] ={ "pangya.ProcGetBoxInfo","pangya.ProcGetBoxRareItem" };
	};
}

#endif // !_STDA_BOX_RARE_ITEM_HPP
