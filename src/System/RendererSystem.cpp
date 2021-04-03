#include <Engine/System/RendererSystem.hpp>

#include <Engine/Common/Log.hpp>

RTTI_DEFINITION(RendererSystem, System)

void RendererSystem::update(double deltaTime) {
  LOG("Update!");
  /**
   * @todo Mettre ici le rendu: seuls les objets visibles méritent d’être affiché.
   * Attention il faut parfois aussi tenir compte des objets hors
   * champs (ombres et lumières, partiellement visibles...)
   */
}