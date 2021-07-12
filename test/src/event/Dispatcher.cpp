#include <doctest.h>

#include <engine/engine.hpp>

class DemoEvent final : public IEvent {
 public:
  inline DemoEvent(const int val) : m_val(val) {}
  inline int val() const { return m_val; }

 private:
  int m_val = 0;
};

struct DemoObject {
  DemoObject() { m_val = 0; }

  void on_event(DemoEvent* e) { m_val = e->val(); }

  int m_val;
};

TEST_CASE("Dispatcher") {
  Dispatcher* dispatcher = Dispatcher::GetInstance();
  DemoObject* obj = new DemoObject();

  dispatcher->RegisterAction<DemoObject, DemoEvent>(obj, &DemoObject::on_event);
  dispatcher->Trigger(DemoEvent(100));

  CHECK(obj->m_val == 100);
}