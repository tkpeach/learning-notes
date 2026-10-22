#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <proxy/proxy.h>

PRO_DEF_MEM_DISPATCH(MemArea, area);
struct Shape : pro::facade_builder
    ::add_convention<MemArea, double() const noexcept>::build {};

struct Rectangle {
  double width, height;
  double area() const noexcept { return width * height; }
};
struct Square {
  double side;
  double area() const noexcept { return side * side; }
};

// The consumer is not a template and does not know Rectangle or Square.
double area_of(const pro::proxy<Shape>& shape) { return shape->area(); }

// Traditional virtual baseline: adapters are needed for these existing types.
struct VirtualShape {
  virtual double area() const noexcept = 0;
  virtual ~VirtualShape() = default;
};
template <class T>
struct Adapter final : VirtualShape {
  T value;
  explicit Adapter(T v) : value(v) {}
  double area() const noexcept override { return value.area(); }
};

int main() {
  std::vector<pro::proxy<Shape>> shapes;
  shapes.push_back(pro::make_proxy<Shape, Rectangle>(3.0, 4.0));
  shapes.push_back(pro::make_proxy<Shape, Square>(5.0));
  double proxy_total = 0;
  for (const auto& s : shapes) proxy_total += area_of(s);

  std::vector<std::unique_ptr<VirtualShape>> baseline;
  baseline.push_back(std::make_unique<Adapter<Rectangle>>(Rectangle{3, 4}));
  baseline.push_back(std::make_unique<Adapter<Square>>(Square{5}));
  double virtual_total = 0;
  for (const auto& s : baseline) virtual_total += s->area();
  assert(proxy_total == 37 && proxy_total == virtual_total);
  std::cout << "proxy=37 virtual=37\n";
}
