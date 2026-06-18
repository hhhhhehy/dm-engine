#pragma once
#include "humanplayer.h"

class CHumanPlayerMgr : public xSingletonClass<CHumanPlayerMgr>
{
public:
	CHumanPlayerMgr(void);
	virtual ~CHumanPlayerMgr(void);
	//通过名字查找玩家
	CHumanPlayer* FindbyName(const char* pszName);
	//通过Id查找玩家
	CHumanPlayer* FindbyId(UINT id);
	//新建玩家
	CHumanPlayer* NewPlayer();
	//释放玩家
	BOOL DeletePlayer(CHumanPlayer* pPlayer);
	//添加玩家的名字到集合
	BOOL AddPlayerNameList(CHumanPlayer* pPlayer, const char* pszName);
	//获取在线玩家数量
	int getCount() { return m_HumanPlayers.GetCount(); }
	//获取在线玩家列表
	CIndexListEx<CHumanPlayer>* GetPlayerList() { return &m_HumanPlayers; }
private:
	CIndexListEx<CHumanPlayer> m_HumanPlayers;
	CNameHash m_PlayerNameHash; // 所有玩家名字集合
};