// Compile each CASE separately. Every supported CASE is expected to fail.
#include <memory>
#include <proxy/proxy.h>
PRO_DEF_MEM_DISPATCH(MemRead, read);
struct Readable : pro::facade_builder
    ::add_convention<MemRead, int() const noexcept>::build {};
struct Copyable : pro::facade_builder::add_facade<Readable>
    ::support_copy<pro::constraint_level::nontrivial>::build {};
struct Good { int read() const noexcept { return 1; } };
struct Throws { int read() const { return 1; } };
struct Missing {};

int main() {
#if CASE == 1
  pro::proxy<Readable> p = std::make_unique<Missing>();
#elif CASE == 2
  pro::proxy<Readable> p = std::make_unique<Throws>();
#elif CASE == 3
  pro::proxy<Copyable> p = std::make_unique<Good>();
#elif CASE == 4
  pro::proxy<Readable> p = std::make_unique<Good>();
  auto q = p;
#else
#error Define CASE to a number from 1 to 4
#endif
}
