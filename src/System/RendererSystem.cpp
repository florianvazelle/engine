#include <Engine/Common/Registry.hpp>
#include <Engine/System/RendererSystem.hpp>
#include <Engine/Util/Log.hpp>

RTTI_DEFINITION(RendererSystem, ISystem)

void RendererSystem::update() const {
  LOG(LOG_INFO, "[RendererSystem] Update!");
  /**
   * @todo Mettre ici le rendu: seuls les objets visibles méritent d’être affiché.
   * Attention il faut parfois aussi tenir compte des objets hors
   * champs (ombres et lumières, partiellement visibles...)
   */

  Context* context = Context::GetInstance();

  // Flush renderer.
  SDL_SetRenderDrawColor(context->window()->renderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(context->window()->renderer());

  Registry* registry = Registry::GetInstance();
  registry->GetObjectsWithParentTag<IRenderer>(registry->entitiesQuery);

  // registry->results.resize(registry->entitiesQuery.size());
  // for (unsigned int i = 0; i < registry->entitiesQuery.size(); i++) {
  //   IRenderer* irend = registry->GetComponentWithParent<IRenderer>(registry->entitiesQuery[i]);
  //   registry->results[i] = registry->threadPool.push(
  //       [](IRenderer* rend, const Entity& e) { rend->render(e); }, irend,
  //       registry->entitiesQuery[i]);
  // }

  // for (auto&& result : registry->results) result.get();

  for (unsigned int i = 0; i < registry->entitiesQuery.size(); i++) {
    IRenderer* irend = registry->GetComponentWithParent<IRenderer>(registry->entitiesQuery[i]);
    irend->render(registry->entitiesQuery[i]);
  }

  // Draw everything.
  SDL_RenderPresent(context->window()->renderer());
}