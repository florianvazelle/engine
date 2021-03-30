#include <cassert>
#include <iostream>
#include <map>
#include <memory>

#include <Engine/Common/Pool.hpp>

#define MAX_ENTITIES 10

class EntityFactory {
public:
  EntityFactory() {}

  // Ajoute un object a la minipool du type correspondant
  template <typename T, typename... Args> T *allocate(Args &&... args) {
    minipool<T> &a = getOrAlloc<T>();
    return a.alloc(std::forward<Args>(args)...);
  }

  // Si la minipool du type existe, on la retourne sinon on la crée
  template <typename T> minipool<T> &getOrAlloc() {
    CollectionBase *&el = m_obdb[typeid(T).name()];  // RTTI
    if (not el) {
      el                 = new Collection<T>();
      Collection<T> *elc = dynamic_cast<Collection<T> *>(el);
      assert(elc);
      minipool<T> &a = elc->elements;
      return a;
    }
    return getObjects<T>();
  }

  // Permet de récupérer tout les objets alloué d'un type
  template <typename T> minipool<T> &getObjects() {
    CollectionBase *&el = m_obdb[typeid(T).name()];  // RTTI
    assert(el);  // Si le pointeur est null, alors il n'y a jamais eu d'allocation pour ce type d'objet
    // TODO : avoid this crash (maybe return empty minipool but we don't want new)
    Collection<T> *elc = dynamic_cast<Collection<T> *>(el);
    assert(elc);
    minipool<T> &a = elc->elements;
    return a;
  }

  // Supprime l'objet contenu dans la pool du type correspondant
  template <typename T> void free(T *object) {
    minipool<T> &a = getObjects<T>();
    return a.free(object);
  }

  ~EntityFactory() {
    for (ObDB::iterator i = m_obdb.begin(); i != m_obdb.end(); ++i) delete i->second;
  }

private:
  EntityFactory(EntityFactory const &);
  EntityFactory &operator=(EntityFactory const &);

  struct CollectionBase {
    virtual ~CollectionBase() {}
  };

  template <typename T> struct Collection : CollectionBase {
    minipool<T> elements;
    Collection() : elements(MAX_ENTITIES) {}
    Collection(size_t arena_size) : elements(arena_size) {}
  };

  typedef std::map<std::string, CollectionBase *> ObDB;
  ObDB m_obdb;
};

/*
    Example usage :

    #include <Engine/Common/EntityFactory.hpp>

    struct Foo {
      Foo() : name("Generic Foo") {}
      char const *name;
    };

    struct Bar {
      std::string name;
    };

    int main() {
      EntityFactory obdb;
      obdb.allocate<Foo>()->name = "My First Foo";
      obdb.allocate<Bar>()->name = "My First Bar";
      {
        Foo *f  = obdb.allocate<Foo>();
        f->name = "My Second Foo";
        Bar *b  = obdb.allocate<Bar>();
        b->name = "My Second Bar";
      }
      obdb.allocate<Foo>();
      obdb.allocate<Bar>();
      {
        std::cout << "Printing Foo Names\n";
        minipool<Foo> &foos = obdb.getObjects<Foo>();
        for (minipool<Foo>::iterator i = foos.begin(); i != foos.end(); ++i) std::cout << "   -> " << i->name << "\n";
      }
      {
        std::cout << "Printing Bar Names\n";
        minipool<Bar> &bars = obdb.getObjects<Bar>();
        for (minipool<Bar>::iterator i = bars.begin(); i != bars.end(); ++i) std::cout << "   -> " << i->name << "\n";
      }
    }
*/