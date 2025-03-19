#include "SpriteCacheDestroyer.hpp"
#include "DelegateUtils.hpp"
#include "BGLib/DotnetExtension/Collections/LRUCache_2.hpp"
#include "GlobalNamespace/LevelBar.hpp"
#include "HMUI/ImageView.hpp"
#include "bsml/shared/BSML/MainThreadScheduler.hpp"

DEFINE_TYPE(CoverCacheFix, SpriteCacheDestroyer);

using namespace DelegateUtils;

namespace CoverCacheFix {
    void SpriteCacheDestroyer::ctor(GlobalNamespace::SpriteAsyncLoader* spriteLoader, GlobalNamespace::StandardLevelDetailViewController* levelDetail) {
        _loader = spriteLoader;
        _view = levelDetail->_standardLevelDetailView;
        destroyDelegate = {&SpriteCacheDestroyer::DestroySprite, this};
    }

    void SpriteCacheDestroyer::Initialize() {
        _loader->_cache->___itemWillBeRemovedFromCacheEvent += destroyDelegate;
        _loader->_cache->_maxNumberElements = 20;
    }

    void SpriteCacheDestroyer::Dispose() {
        _loader->_cache->___itemWillBeRemovedFromCacheEvent -= destroyDelegate;
    }

    void SpriteCacheDestroyer::DestroySprite(StringW key, UnityW<UnityEngine::Sprite> sprite) {
        if (!sprite) return;
        if (_view->_levelBar->_songArtworkImageView->m_Sprite == sprite) return ScheduleReaddition(key, sprite);
        UnityEngine::Object::Destroy(sprite->texture);
		UnityEngine::Object::Destroy(sprite.ptr());
    }

    void SpriteCacheDestroyer::ScheduleReaddition(StringW key, UnityW<UnityEngine::Sprite> sprite) {
        BSML::MainThreadScheduler::ScheduleNextFrame([this, key, sprite]() {
            _loader->_cache->Add(key, sprite);
        });
    }
}