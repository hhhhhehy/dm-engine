#include "stdafx.h"
#include "GameServer.h"
#include "server.h"
#include "fmttextfile.h"
#include "monsterex.h"
#include "scriptobject.h"

CServerForm g_Form;
CServer* g_pServer = nullptr;

// 提供额外的崩溃信息
static const char* GetServerAdditionalInfo()
{
	static char info[512];
	sprintf_s(info, sizeof(info),
		"服务器名称: %s"
		"在线玩家数: %u"
		"运行时间: %u 秒"
		"当前地图数: %u",
		SERVER_NAME,
		0, // 这里可以添加实际的玩家数量
		0, // 这里可以添加实际的运行时间
		0  // 这里可以添加实际的地图数量
	);
	return info;
}

int main(int argc, char* argv[])
{
	// 初始化崩溃处理器
	CRASH_HANDLER_INIT();
	CRASH_HANDLER_SETPATH("..\\日志\\");
	CrashHandler::SetAdditionalInfoCallback(GetServerAdditionalInfo);

	TRY_INIT
	CLogFile::GetInstance()->Init("..\\日志\\龙路引擎");
	// 组合命令行参数
	char cmdLine[256] = { 0 };
	for (int i = 1; i < argc; i++)
	{
		if (i > 1) strcat(cmdLine, " ");
		strcat(cmdLine, argv[i]);
	}
	g_Form.Create(SERVER_NAME, cmdLine);
	g_Form.SetArenaReserve(256 * 1024);
	g_pServer = CServer::GetInstance();
	g_pServer->SetServerName(SERVER_NAME);
	g_pServer->SetIoConsole(&g_Form);
	g_Form.SetInputListener(g_pServer);
	g_Form.SetServer(g_pServer);
	g_Form.SetStatus(TRUE);
	return g_Form.EnterMessageLoop();
}