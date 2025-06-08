#include "thirdperson.h"

// used: cheat variables
#include "../../core/variables.h"
// used: interfaces
#include "../../core/interfaces.h"
// used: input structure
#include "../../sdk/interfaces/ccsgoinput.h"
// used: viewsetup, entity system
#include "../../sdk/datatypes/viewsetup.h"
#include "../../sdk/interfaces/cgameentitysystem.h"
// used: entities
#include "../../sdk/entity.h"
// used: game trace
#include "../../sdk/interfaces/cgametracemanager.h"
// used: input system for hotkey
#include "../../utilities/inputsystem.h"

using namespace F::MISC::THIRDPERSON;

void F::MISC::THIRDPERSON::Run(CViewSetup* pView)
{
    if (IPT::IsKeyReleased(C_GET(unsigned int, Vars.nThirdpersonKey)))
        C_GET(bool, Vars.bThirdperson) = !C_GET(bool, Vars.bThirdperson);

    if (!C_GET(bool, Vars.bThirdperson) || pView == nullptr)
        return;

    CCSPlayerController* pLocalController = CCSPlayerController::GetLocalPlayerController();
    if (pLocalController == nullptr)
        return;

    C_CSPlayerPawn* pLocal = I::GameResourceService->pGameEntitySystem->Get<C_CSPlayerPawn>(pLocalController->GetPawnHandle());
    if (pLocal == nullptr)
        return;

    if (pLocal->GetLifeState() != LIFE_ALIVE || pLocal->IsScoped())
    {
        if (I::Input->bInThirdPerson)
            I::Input->bInThirdPerson = false;
        return;
    }

    I::Input->bInThirdPerson = true;

    QAngle_t angView = pView->angView;
    Vector_t vecForward{};
    angView.ToDirections(&vecForward, nullptr, nullptr);

    Vector_t vecEye = pLocal->GetEyePosition();
    Vector_t vecCameraEnd = vecEye - (vecForward * C_GET(float, Vars.flThirdperson));

    Ray_t ray{};
    GameTrace_t trace{};
    TraceFilter_t filter(0x1C3003, pLocal, nullptr, 4);

    I::GameTraceManager->TraceShape(&ray, vecEye, vecCameraEnd, &filter, &trace);

    pView->vecOrigin = trace.m_vecEndPos;
}
