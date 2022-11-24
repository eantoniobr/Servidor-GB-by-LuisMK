// Arquivo pangya_client_st.h
// Criado em 01/04/2018 as 22:34 por Acrisio
// Definição das estruturas usadas no cliente

#pragma once
#ifndef _STDA_PANGYA_CLIENT_ST_H
#define _STDA_PANGYA_CLIENT_ST_H

#include "../../Projeto IOCP/TYPE/pangya_st.h"
#include <map>
namespace stdA {
    
    struct client_info  {
        void clear() { memset(this, 0, sizeof(client_info)); };

		char m_client_version[20];		// Cliente versão "855.00"
		unsigned long m_packet_version;	// Packet Version 2016121900

		unsigned long m_uid;		// Player Unico ID
		unsigned long m_oid;		// Player Online ID
		unsigned long m_guid;		// Game Server Unico ID
		unsigned long m_luid;		// Login Server Unico ID
		unsigned long m_muid;		// Message Server Unico ID
		unsigned long m_ruid;		// Rank Server Unico ID
		unsigned long m_cuid;		// Canal Unico ID
		unsigned long m_sluid;		// sala Unico ID
		unsigned long m_cap;		// Player Capability
		unsigned long m_TTL;		// Time To Live[TTL]
		char m_nickname[22];		// Player Nickname
		char m_id[22];				// Player ID
		char m_pass[32];			// Player Password
		unsigned char m_level;		// Player Level
		char m_keys[2][8];			// Player Keys of authentic to Game Server
		char m_web_key[8];			// Web Key
		unsigned char m_TRWK;		// Type Request Web Key

		char link_gacha[1024];		// Link do Gacha
		char link_guild[1024];		// Link da Guild
		char link_point[1024];		// Link do payment
		char link_entrance[1024];	// Link Entrance
		char link_weblink[3][1024];	// 3 Link do Weblink

		long volatile m_RCLOP;		// Recebe Canais Ler Outros Pacotes
		long volatile m_SCLOP;		// Recebe Canais Ler Outros Pacotes
		long volatile m_RC;			// Recebe Canais
		long volatile m_SC;			// Recebe Canais

		
    };

	struct server_list {
		void clear() {
			if (a_servers != nullptr)
				delete[] a_servers;

			memset(this, 0, sizeof(server_list));
		};
		size_t num_servers;
		ServerInfo *a_servers;
	};

	struct ChannelInfo {
		void clear() {
			memset(this, 0, sizeof(ChannelInfo));
		};
		char name[64];
		short max_user;
		short curr_user;
		unsigned char id;
		uint32_t flag;
		uint32_t flag2;
		
	};

	struct canal_list {
		void clear() {
			if (a_canais != nullptr)
				delete[] a_canais;

			memset(this, 0, sizeof(canal_list));
		};
		size_t num_canais;
		ChannelInfo *a_canais;
	};

	// Sala Guild Info, 66 bytes
	struct RoomGuildInfo {
		void clear() {
			memset(this, 0, sizeof(RoomGuildInfo));
			/*guild_1_uid = ~0;
			guild_2_uid = ~0;*/
		};
		uint32_t guild_1_uid;
		uint32_t guild_2_uid;
		char guild_1_mark[9];				// mark string o pangya JP não usa aqui fica 0
		char guild_2_mark[9];				// mark string o pangya JP não usa aqui fica 0
		unsigned short guild_1_index_mark;
		unsigned short guild_2_index_mark;
		char guild_1_nome[18];
		char guild_2_nome[18];
	};

	// Sala Grand Prix Info, 16 bytes
	struct RoomGrandPrixInfo {
		void clear() {
			memset(this, 0, sizeof(RoomGrandPrixInfo));
		};
		uint32_t dados_typeid;
		uint32_t rank_typeid;
		uint32_t tempo;
		uint32_t active;
	};

	// Union Natural e Short Game Flag da sala, que guarda a estrutura de bits da flag da sala de natural e short game
	union uNaturalAndShortGame {
		uNaturalAndShortGame(uint32_t _ul = 0u) : ulNaturalAndShortGame(_ul) {};
		void clear() { ulNaturalAndShortGame = 0u; };
		uint32_t ulNaturalAndShortGame;
		struct {
			uint32_t natural : 1;			// Natural Modo
			uint32_t short_game : 1, : 0;	// Short Game Modo
		}stBit;
	};
	// SalaInfo(servidor me envia)
	struct ServerRoomInfo {
		enum eCOURSE : unsigned char {
			BLUE_LAGOON,
			BLUE_WATER,
			SEPIA_WIND,
			WIND_HILL,
			WIZ_WIZ,
			WEST_WIZ,
			BLUE_MOON,
			SILVIA_CANNON,
			ICE_CANNON,
			WHITE_WIZ,
			SHINNING_SAND,
			PINK_WIND,
			DEEP_INFERNO = 13,
			ICE_SPA,
			LOST_SEAWAY,
			EASTERN_VALLEY,
			CHRONICLE_1_CHAOS,
			ICE_INFERNO,
			WIZ_CITY,
			ABBOT_MINE,
			MYSTIC_RUINS,
			GRAND_ZODIAC = 64,
			RANDOM = 127,
		};
		enum TIPO : uint8_t {
			STROKE,
			MATCH,
			LOUNGE,
			TOURNEY = 4,
			TOURNEY_TEAM,
			GUILD_BATTLE,
			PANG_BATTLE,
			APPROCH = 10,
			GRAND_ZODIAC_INT,
			GRAND_ZODIAC_ADV = 13,
			GRAND_ZODIAC_PRACTICE,
			SPECIAL_SHUFFLE_COURSE = 18,
			PRACTICE,
			GRAND_PRIX,
		};
		enum MODO : uint8_t {
			M_FRONT,
			M_BACK,
			M_RANDOM,
			M_SHUFFLE,
			M_REPEAT,
			M_SHUFFLE_COURSE,
		};
		enum INFO_CHANGE : uint32_t {
			NAME,
			SENHA,
			TIPO,
			COURSE,
			QNTD_HOLE,
			MODO,
			TEMPO_VS,
			MAX_PLAYER,
			TEMPO_30S,
			STATE_FLAG,
			UNKNOWN,
			HOLE_REPEAT,
			FIXED_HOLE,
			ARTEFATO,
			NATURAL,
		};
		ServerRoomInfo(uint32_t _ul = 0u) {	// Valores padrões

			clear();

		};
		void clear() {

			memset(this, 0, sizeof(ServerRoomInfo));//original, 221, editado 220 

			numero = -1;
			senha_flag = 1;
			state = 1;
			_30s = 30;

			guilds.clear(); // Valores inicias
		};
		char nome[64];
		unsigned char senha_flag : 1, : 0;	// Sala sem senha = 1, Sala com senha = 0
		unsigned char state : 1, : 0;		// Sala em espera = 1, Sala em Game = 0
		unsigned char flag;					// Sala que pode entrar depois que começou = 1
		unsigned char max_player;
		unsigned char num_player;
		char key[17];
		unsigned char _30s;					// Modo Multiplayer do pangya acho, sempre 0x1E (dec: 30) no pangya
		unsigned char qntd_hole;
		unsigned char tipo_show;			// esse é o tipo que mostra no pacote, esse pode mudar dependendo do tipo real da sala, fica ou camp, ou VS ou especial, não coloca todos os tipos aqui
		short numero;
		unsigned char modo;
		eCOURSE course;
		uint32_t time_vs;
		uint32_t time_30s;
		uint32_t trofel;
		unsigned short state_flag;			// Quando é sala de 100 player o mais de gm event aqui é 0x100
		RoomGuildInfo guilds;
		uint32_t rate_pang;
		uint32_t rate_exp;
		int		   master;	//Owner_ID		// Tem valores negativos, por que a sala usa ele para grand prix e etc
		unsigned char tipo_ex;			// tipo extended, que fala o tipo da sala certinho
		uint32_t artefato;			// Aqui usa pra GP efeitos especiais do GP
		uNaturalAndShortGame natural;		// Aqui usa para Short Game Também
		RoomGrandPrixInfo grand_prix;

		std::string result()
		{
			return "Nome:" + std::string(nome) + "\t ID:" +std::to_string(numero) + "\t" + "\n TIPO:" + std::to_string(tipo_show) + "\t" + "\n MASTER:" + std::to_string(master) + "\t";
		};
	};
	//sala pacote 049 e 04A
	struct ServerRoomInfoEx : public ServerRoomInfo
	{
		std::string senha;
		uint8_t hole_repeat;
		uint32_t fixed_hole;
		ServerRoomInfoEx()
		{
			ServerRoomInfo::clear();
		}

		void SetSenha()
		{
		}
	};
	//
	struct ClientRoomInfo
	{
		uint8_t option;
		uint32_t time_vs;
		uint32_t time_30s;
		unsigned char max_player;
		unsigned char tipo_show;			// esse é o tipo que mostra no pacote, esse pode mudar dependendo do tipo real da sala, fica ou camp, ou VS ou especial, não coloca todos os tipos aqui
		unsigned char qntd_hole;
		unsigned char course;
		unsigned char modo;
		uNaturalAndShortGame natural;		// Aqui usa para Short Game Também
		char nome[64];
		char senha[64];
		uint32_t artefato;
		ClientRoomInfo(uint32_t _ul = 0u)
		{	// Valores padrões

			clear();
		};
		void clear() {

			memset(this, 0, sizeof(ClientRoomInfo));//original, 221, editado 220 

			option = 0;
		};
	};
	struct ClientRoomInfoEx : public ClientRoomInfo
	{
		uint8_t IsTrainning;
		uint8_t hole_repeat;
		uint32_t fixed_hole;
		ClientRoomInfoEx(uint32_t _ul = 0u)
		{	// Valores padrões

			ClientRoomInfo::clear();
		};
	};
	struct sala_list {
		void clear() {
			if (a_salas != nullptr)
				delete[] a_salas;

			memset(this, 0, sizeof(sala_list));
		};
		
		void add(ServerRoomInfoEx info) {
		};
		size_t num_salas;
		ServerRoomInfoEx* a_salas;
	};
	/*struct ctx_client {

		void clear() { memset(this, 0, sizeof(ctx_client)); };
		char m_client_version[20];		// Cliente versão "855.00"
		unsigned long m_packet_version;	// Packet Version 2016121900
		char m_id[22];				// Player ID
		char m_pass[32];			// Player Password
	};*/
}

#endif !_STDA_PANGYA_CLIENT_ST_H