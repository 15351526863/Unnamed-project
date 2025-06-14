#include "motionblur.h"

#include "../../core/hooks.h"
#include "../../utilities/memory.h"

namespace
{
        void* g_MotionBlurApplyPostCheck = nullptr;
        void* g_PostBlurJumpAddr = nullptr;

       using MotionBlurFn = void(__fastcall*)(void*, unsigned int);

       void ApplyMotionBlur(void* rcx, void*)
       {
               if (g_PostBlurJumpAddr == nullptr)
                       return;

               const auto fn = reinterpret_cast<MotionBlurFn>(g_PostBlurJumpAddr);
               fn(rcx, 0xFFFFFFFFu);
       }
}

namespace F::VISUALS::MOTIONBLUR
{
        bool Setup()
        {
                std::uint8_t* pCheck = MEM::FindPattern(CLIENT_DLL, "48 55 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 80 B9 ? ? ? ? ?");
                if (pCheck == nullptr)
                        return false;

                g_MotionBlurApplyPostCheck = MEM::GetAbsoluteAddress(pCheck + 0x33, 0x1);

                if (!H::hkIsMotionBlurEnabled.Create(pCheck, reinterpret_cast<void*>(&H::IsMotionBlurEnabled)))
                        return false;

                return true;
        }

        void Destroy()
        {
                H::hkIsMotionBlurEnabled.Remove();
        }
}

namespace H
{
        bool CS_FASTCALL IsMotionBlurEnabled(void* a1, void* a2, void* a3)
        {
                g_PostBlurJumpAddr = g_MotionBlurApplyPostCheck;
                ApplyMotionBlur(a3, a2);
                return true;
        }
}
