#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/System/RendererSystem.hpp>

RTTI_DEFINITION(RendererSystem, ISystem)

void RendererSystem::update(const Context& context) const {
  LOG(LOG_INFO, "[RendererSystem] Update!");
  /**
   * @todo Mettre ici le rendu: seuls les objets visibles méritent d’être affiché.
   * Attention il faut parfois aussi tenir compte des objets hors
   * champs (ombres et lumières, partiellement visibles...)
   */

  // Flush renderer.
  SDL_SetRenderDrawColor(context.window()->renderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(context.window()->renderer());

  Manager* man = Manager::GetInstance();
  man->GetObjectsWithParentTag<IRenderer>(man->entitiesQuery);

  man->results.resize(man->entitiesQuery.size());
  for (unsigned int i = 0; i < man->entitiesQuery.size(); i++) {
    IRenderer* irend = man->GetComponentWithParent<IRenderer>(man->entitiesQuery[i]);
    man->results[i] = man->threadPool.push(
        [](IRenderer* rend, const Context& c, const Entity& e) { rend->render(c, e); }, irend,
        context, man->entitiesQuery[i]);
  }

  for (auto&& result : man->results) result.get();

  // Draw everything.
  SDL_RenderPresent(context.window()->renderer());
}