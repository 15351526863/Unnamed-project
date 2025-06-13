#include "anti_aim.h"

// used: sdk entity
#include "../../sdk/entity.h"
#include "../../sdk/interfaces/cgameentitysystem.h"
#include "../../sdk/interfaces/iengineclient.h"

// used: cheat variables
#include "../../core/variables.h"
#include "../../core/interfaces.h"
#include "../../core/sdk.h"

// used: usercmd
#include "../../sdk/datatypes/usercmd.h"

#include <cmath>

void F::ANTIAIM::RunAA(CUserCmd* pCmd, CBaseUserCmdPB* pBaseCmd, CCSPlayerController* pLocalController, C_CSPlayerPawn* pLocalPawn)
{
        if (!C_GET(bool, Vars.bAntiAim))
                return;

        if (!I::Engine->IsConnected() || !I::Engine->IsInGame())
                return;

        if (!pLocalController || !pLocalController->IsPawnAlive())
                return;

        if (pCmd->nButtons.nValue & IN_USE || pCmd->nButtons.nValue & IN_ATTACK)
                return;

        int32_t nMoveType = pLocalPawn->GetMoveType();
        if (nMoveType == MOVETYPE_NOCLIP || nMoveType == MOVETYPE_LADDER)
                return;

        float flPitch = 0.f;
        float flYaw = 0.f;

        switch (C_GET(int, Vars.iBaseYawType))
        {
        case 1:
                flYaw -= 180.f;
                break;
        case 2:
                flYaw += 180.f;
                break;
        default:
                break;
        }

        switch (C_GET(int, Vars.iPitchType))
        {
        case 1:
                flPitch = 120.f;
                break;
        case 2:
                flPitch = -120.f;
                break;
        case 3:
                flPitch = 0.f;
                break;
        default:
                break;
        }

        pBaseCmd->pViewAngles->angValue.x = flPitch;
        pBaseCmd->pViewAngles->angValue.y += flYaw;

        pBaseCmd->pViewAngles->angValue.x = std::remainderf(pBaseCmd->pViewAngles->angValue.x, 360.f);
        pBaseCmd->pViewAngles->angValue.y = std::remainderf(pBaseCmd->pViewAngles->angValue.y, 360.f);
        pBaseCmd->pViewAngles->angValue.z = 0.f;
}
