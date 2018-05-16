#include "../aotjs_runtime.h"

#include <iostream>

using namespace AotJS;

int main() {
  // Variables hoisted...
  Local work;
  Local play;
  Local retval;

  *work = new Function(
    "work",
    0, // argument count
    // no scope capture
    [] (Function& func, Frame& frame) -> Val {
      return new String("work");
    }
  );

  *play = new Function(
    "play",
    0, // argument count
    [] (Function& func, Frame& frame) -> Val {
      return new String("play");
    }
  );

  // todo: operator overloading on Val
  *retval = new String(work->call(Null(), {}).asString() + play->call(Null(), {}).asString());
  //*retval = work->call(Null(), {}) + play->call(Null(), {});

  // should say "workplay"
  std::cout << "should say 'workplay': " << retval->dump() << "\n";

  std::cout << "before gc\n";
  std::cout << engine().dump();
  std::cout << "\n\n";

  engine().gc();

  std::cout << "after gc\n";
  std::cout << engine().dump();
  std::cout << "\n";

  return 0;
}
