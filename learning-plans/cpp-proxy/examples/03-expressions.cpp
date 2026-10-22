#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <proxy/proxy.h>

namespace vendor {
struct Reading { int value; }; // Imagine this comes from a third-party header.
std::string describe(const Reading& r) { return "reading:" + std::to_string(r.value); }
}
PRO_DEF_FREE_AS_MEM_DISPATCH(FreeDescribe, describe);
PRO_DEF_MEM_DISPATCH(MemUseCount, use_count);
struct Described : pro::facade_builder
    ::add_convention<FreeDescribe, std::string() const>::build {};
struct SharedDescribed : pro::facade_builder
    ::add_facade<Described>
    ::add_direct_convention<MemUseCount, long() const noexcept>::build {};

int main() {
  auto source = std::make_shared<vendor::Reading>(vendor::Reading{42});
  pro::proxy<SharedDescribed> p = source;
  assert(p->describe() == "reading:42"); // Indirect: describe(*P), via ADL.
  assert(p.use_count() == 2);            // Direct: P.use_count().
  assert((invoke<MemUseCount, long() const noexcept>(p) == 2));
  std::cout << p->describe() << " owners=" << p.use_count() << '\n';
}
