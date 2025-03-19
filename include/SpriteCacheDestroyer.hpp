#pragma once

#include "custom-types/shared/macros.hpp"
#include "Zenject/IInitializable.hpp"
#include "System/IDisposable.hpp"
#include "GlobalNamespace/SpriteAsyncLoader.hpp"
#include "UnityEngine/Sprite.hpp"
#include "GlobalNamespace/StandardLevelDetailViewController.hpp"
#include "GlobalNamespace/StandardLevelDetailView.hpp"
#include "DelegateUtils.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(CoverCacheFix, SpriteCacheDestroyer, System::Object, std::vector<Il2CppClass*>({classof(Zenject::IInitializable*), classof(System::IDisposable*)}),
    
    DECLARE_CTOR(ctor, GlobalNamespace::SpriteAsyncLoader* spriteLoader, GlobalNamespace::StandardLevelDetailViewController* levelView);

    DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &Zenject::IInitializable::Initialize);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &System::IDisposable::Dispose);

    DECLARE_INSTANCE_METHOD(void, DestroySprite, StringW key, UnityW<UnityEngine::Sprite> value);
    DECLARE_INSTANCE_METHOD(void, ScheduleReaddition, StringW key, UnityW<UnityEngine::Sprite> value);

    DECLARE_INSTANCE_FIELD(GlobalNamespace::SpriteAsyncLoader*, _loader);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::StandardLevelDetailView*, _view);

    public:
    DelegateUtils::DelegateW<System::Action_2<StringW, UnityW<UnityEngine::Sprite>>> destroyDelegate;
)