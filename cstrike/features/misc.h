#pragma once
class CUserCmd;
class CBaseUserCmdPB;
class CCSPlayerController;
class C_CSPlayerPawn;
class CViewSetup;

namespace F::MISC
{
        void OnMove(CUserCmd* pCmd, CBaseUserCmdPB* pBaseCmd, CCSPlayerController* pLocalController, C_CSPlayerPawn* pLocalPawn);

       namespace THIRDPERSON
       {
               void Run(CViewSetup* pView);
       }
}
