#pragma once

#include <engine/Game.hpp>
#include <engine/Scene.hpp>
#include <engine/async/ThreadPool.hpp>
#include <engine/component/renderer/RectRenderer.hpp>
#include <engine/component/renderer/CircleRenderer.hpp>
#include <engine/component/collider/RectCollider.hpp>
#include <engine/component/Transform.hpp>
#include <engine/component/Velocity.hpp>
#include <engine/core/Clock.hpp>
#include <engine/core/Context.hpp>
#include <engine/core/Engine.hpp>
#include <engine/core/Input.hpp>
#include <engine/core/Window.hpp>
#include <engine/ecs/Entity.hpp>
#include <engine/ecs/IComponent.hpp>
#include <engine/ecs/ISystem.hpp>
#include <engine/event/Collide.hpp>
#include <engine/event/EventCallback.hpp>
#include <engine/event/IEvent.hpp>
#include <engine/event/IEventKey.hpp>
#include <engine/event/KeyDown.hpp>
#include <engine/event/KeyUp.hpp>
#include <engine/factory/ComponentFactory.hpp>
#include <engine/event/Dispatcher.hpp>
#include <engine/factory/EntityFactory.hpp>
#include <engine/factory/Registry.hpp>
#include <engine/factory/SystemFactory.hpp>
#include <engine/meta/Hash.hpp>
#include <engine/meta/Log.hpp>
#include <engine/meta/Macro.hpp>
#include <engine/meta/NoCopy.hpp>
#include <engine/meta/NoMove.hpp>
#include <engine/meta/RTTI.hpp>
#include <engine/meta/Random.hpp>
#include <engine/meta/Singleton.hpp>
#include <engine/pool/ComponentArray.hpp>
#include <engine/pool/IPool.hpp>
#include <engine/pool/Pool.hpp>
#include <engine/system/LogicalSystem.hpp>
#include <engine/system/PhysicalSystem.hpp>
#include <engine/system/RendererSystem.hpp>