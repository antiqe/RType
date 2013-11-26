#include "Core.hpp"
#include "DataModule.hpp"
#include "EventModule.hpp"
#include "RenderModule.hpp"
#include "StateModule.hpp"
#include "SourceModule.hpp"
#include "FactoryModule.hpp"
#include "NetworkModule.hpp"

int main()
{
  Engine::Core*		app = Engine::Core::getInstance();

  Engine::Core::messagefactory = new MessageFactory;
  Engine::Core::gameObjectFactory = new GameObjectFactory;

  app->setFrame(60);
  app->setModule(new SourceModule);
  app->setModule(new DataModule);
  app->setModule(new StateModule);
  app->setModule(new EventModule);
  app->setModule(new RenderModule);
  app->setModule(new NetworkModule);
  app->run();
  Engine::Core::kill();

  return (0);
}