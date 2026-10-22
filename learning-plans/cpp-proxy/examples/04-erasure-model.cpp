// Teaching model only: borrowed, const access, one operation, no owning storage.
#include <cassert>
#include <concepts>
#include <iostream>
#include <memory>

class AreaView {
  const void* object_;
  double (*call_)(const void*) noexcept;
 public:
  template <class T>
    requires requires(const T& t) {
      { t.area() } noexcept -> std::same_as<double>;
    }
  explicit AreaView(const T& object) noexcept
      : object_(std::addressof(object)),
        call_(+[](const void* p) noexcept {
          return static_cast<const T*>(p)->area();
        }) {}
  template <class T>
  AreaView(const T&&) = delete; // Reject temporary targets.
  double area() const noexcept { return call_(object_); }
};

struct Rectangle {
  double width, height;
  double area() const noexcept { return width * height; }
};
struct Square {
  double side;
  double area() const noexcept { return side * side; }
};
int main() {
  Rectangle r{3, 4};
  Square s{5};
  AreaView a{r}, b{s};
  assert(a.area() + b.area() == 37);
  std::cout << "erased=37\n";
}
