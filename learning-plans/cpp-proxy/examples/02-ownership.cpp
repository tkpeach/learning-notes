#include <cassert>
#include <iostream>
#include <memory>
#include <type_traits>
#include <proxy/proxy.h>

PRO_DEF_MEM_DISPATCH(MemGet, get);
PRO_DEF_MEM_DISPATCH(MemSet, set);
struct Cell {
  int value;
  int get() const noexcept { return value; }
  void set(int v) noexcept { value = v; }
};
struct Mutable : pro::facade_builder
    ::add_convention<MemGet, int() const noexcept>
    ::add_convention<MemSet, void(int) noexcept>::build {};
struct Copyable : pro::facade_builder
    ::add_facade<Mutable>
    ::support_copy<pro::constraint_level::nontrivial>::build {};

static_assert(!std::is_copy_constructible_v<pro::proxy<Mutable>>);
static_assert(pro::proxiable<std::unique_ptr<Cell>, Mutable>);
static_assert(!pro::proxiable<std::unique_ptr<Cell>, Copyable>);
static_assert(pro::inplace_proxiable_target<Cell, Copyable>);

int main() {
  Cell local{1};
  pro::proxy<Copyable> borrowed = &local;
  auto borrowed_copy = borrowed;
  borrowed_copy->set(2);
  assert(local.value == 2); // Copying Cell* aliases the same Cell.
  borrowed.reset();
  assert(local.value == 2); // Reset does not destroy the local Cell.

  auto shared = std::make_shared<Cell>(Cell{10});
  pro::proxy<Copyable> shared_proxy = shared;
  auto shared_copy = shared_proxy;
  shared_copy->set(11);
  assert(shared_proxy->get() == 11 && shared.use_count() == 3);

  auto value = pro::make_proxy<Copyable, Cell>(20);
  auto value_copy = value;
  value_copy->set(21);
  assert(value->get() == 20 && value_copy->get() == 21);

  pro::proxy<Mutable> unique = std::make_unique<Cell>(Cell{30});
  auto moved = std::move(unique);
  assert(moved->get() == 30); // Do not assume a general moved-from contract.

  pro::proxy_view<Mutable> view = &local;
  view->set(3);
  assert(local.value == 3);

  pro::proxy<Mutable> empty;
  Cell* null_cell = nullptr;
  pro::proxy<Mutable> holds_null_pointer = null_cell;
  assert(!empty.has_value());
  assert(holds_null_pointer.has_value()); // Contains a P, but *P is not valid.
  // Never call holds_null_pointer->get().
  std::cout << "borrow=3 shared=11 value=20/21 unique=30\n"
               "empty=false stored-null=true\n";
}
