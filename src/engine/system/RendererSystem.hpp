#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <engine/component/IRenderer.hpp>
#include <engine/core/Context.hpp>
#include <engine/core/Window.hpp>
#include <engine/ecs/ISystem.hpp>
#include <engine/meta/Log.hpp>

class RendererSystem : public ISystem {
 public:
  RTTI_DEFINITION(RendererSystem, ISystem)
  ~RendererSystem() {}

  void update() const {
    LOG(LOG_INFO, "[RendererSystem] Update!");
    /**
     * @todo Mettre ici le rendu: seuls les objets visibles méritent d’être
     * affiché. Attention il faut parfois aussi tenir compte des objets hors
     * champs (ombres et lumières, partiellement visibles...)
     */

    Context* context = Context::GetInstance();

    // Flush renderer.
    SDL_SetRenderDrawColor(context->window()->renderer(), 0, 0, 0,
                           SDL_ALPHA_OPAQUE);
    SDL_RenderClear(context->window()->renderer());

    Registry* registry = Registry::GetInstance();
    registry->GetObjectsWithParentTag<IRenderer>(registry->entitiesQuery);

    registry->results.resize(registry->entitiesQuery.size());
    for (unsigned int i = 0; i < registry->entitiesQuery.size(); i++) {
      IRenderer* irend = registry->GetComponentWithParent<IRenderer>(
          registry->entitiesQuery[i]);
      registry->results[i] = registry->threadPool.push(
          [](IRenderer* rend, const Entity& e) { rend->render(e); }, irend,
          registry->entitiesQuery[i]);
    }

    for (auto&& result : registry->results) result.get();

    // Draw everything.
    SDL_RenderPresent(context->window()->renderer());
  }
};