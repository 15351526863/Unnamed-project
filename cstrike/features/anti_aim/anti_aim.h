#pragma once

class CUserCmd;
class CBaseUserCmdPB;
class CCSPlayerController;
class C_CSPlayerPawn;

struct QAngle_t;

namespace F::ANTIAIM
{
        inline QAngle_t angStoredViewBackup{};
        void RunAA(CUserCmd* pCmd, CBaseUserCmdPB* pBaseCmd, CCSPlayerController* pLocalController, C_CSPlayerPawn* pLocalPawn);
}
