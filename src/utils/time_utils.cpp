#include "time_utils.h"

#include <GLFW/glfw3.h>

namespace unnes {

double getTime() { return glfwGetTime(); }

}  // namespace unnes