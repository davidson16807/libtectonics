
// std libraries
#include <iostream>
#include <string>
#include <random>       // rngs

// gl libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// glm libraries
#define GLM_FORCE_PURE      // disable anonymous structs so we can build with ISO C++

// in house libraries
#include <series/types.hpp>                            // floats
#include <series/common.hpp>                           // max
#include <series/statistic.hpp>                        // mean
#include <series/glm/random.hpp>                       // get_elias_noise
#include <meshes/mesh.hpp>                           // subdivide
#include <grids/SpheroidGrid/string_cast.hpp>        // to_string
#include <update/OrbitalControlState.hpp>            // OrbitalControlState
#include <update/OrbitalControlUpdater.hpp>          // OrbitalControlUpdater
#include <view/ColorscaleSurfacesShaderProgram.hpp>  // ColorscaleSurfacesShaderProgram


int main() {
  // initialize GLFW
  if (!glfwInit()) {
    std::cout << stderr << " ERROR: could not start GLFW3" << std::endl;
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // needed for MacOS
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // we don't want the old OpenGL

  // open a window
  GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
  if (!window) {
    std::cout << stderr << " ERROR: could not open window with GLFW3" << std::endl;
    glfwTerminate();
    return 1;
  }

  // create a GLEW context
  glfwMakeContextCurrent(window);

  // initialize GLEW 
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << stderr << " ERROR: Failed to initialize GL" << std::endl;
    return -1;
  }

  // get version info
  const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString(GL_VERSION); // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

  /* OTHER STUFF GOES HERE NEXT */
  // generate mesh
  meshes::mesh icosphere_mesh(meshes::icosahedron.vertices, meshes::icosahedron.faces);
  for (int i = 0; i < 5; ++i)
  {
    icosphere_mesh = meshes::subdivide(icosphere_mesh); series::normalize(icosphere_mesh.vertices, icosphere_mesh.vertices);
  }

  // initialize grid from mesh
  rasters::SpheroidGrid icosphere_grid(icosphere_mesh.vertices, icosphere_mesh.faces);

  // generate random raster over grid
  std::mt19937 generator(2);
  series::floats vertex_color_values = series::floats(icosphere_grid.vertex_count);
  series::floats vertex_displacements = series::floats(icosphere_grid.vertex_count);
  series::get_elias_noise(icosphere_grid.vertex_positions, generator, vertex_color_values, 100, 0.0001f);
  series::get_elias_noise(icosphere_grid.vertex_positions, generator, vertex_displacements, 100, 0.0001f);
  std::string str_raster = to_string(icosphere_grid, vertex_color_values);
  std::cout << str_raster << std::endl;

  // flatten raster for WebGL
  series::floats flattened_face_vertex_color_values(icosphere_grid.flattened_face_vertex_ids.size());
  series::floats flattened_face_vertex_displacements(icosphere_grid.flattened_face_vertex_ids.size());
  series::get(vertex_color_values,  icosphere_grid.flattened_face_vertex_ids, flattened_face_vertex_color_values);
  series::get(vertex_displacements, icosphere_grid.flattened_face_vertex_ids, flattened_face_vertex_displacements);

  // initialize control state
  update::OrbitalControlState control_state;
  control_state.min_zoom_distance = 1.0f;
  control_state.log2_height = 2.0f;
  control_state.angular_position = glm::vec2(45.0f, 30.0f) * 3.14159f/180.0f;
  
  // initialize view state
  view::ViewState view_state;
  view_state.projection_matrix = glm::perspective(
    3.14159f*45.0f/180.0f, 
    640.0f/480.0f, 
    1e-3f, 1e16f
  );
  view_state.view_matrix = control_state.get_view_matrix();
  // view_state.projection_type = view::ProjectionType::heads_up_display;
  // view_state.projection_matrix = glm::mat4(1);
  // view_state.view_matrix = glm::mat4(1);
  view::ColorscaleSurfacesViewState<float> colorscale_state;
  colorscale_state.max_value = series::max(flattened_face_vertex_color_values);
  colorscale_state.sealevel = series::mean(flattened_face_vertex_displacements);

  // initialize shader program
  view::ColorscaleSurfacesShaderProgram colorscale_program;  

  // initialize data for shader program
  series::floats points = {
   0.0f,  0.5f,  0.0f,
   0.5f, -0.5f,  0.0f,
  -0.5f, -0.5f,  0.0f
  };

  series::floats colors = {
   1.0f,  
   0.0f,  
   0.0f
  };

  // initialize MessageQueue for MVU architecture
  messages::MessageQueue message_queue;
  message_queue.activate(window);

  while(!glfwWindowShouldClose(window)) {
      // wipe drawing surface clear
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      colorscale_program.draw(
        icosphere_grid.flattened_face_vertex_coordinates.vector(), 
        flattened_face_vertex_color_values.vector(), 
        flattened_face_vertex_displacements.vector(),
        // points.vector(),
        // colors.vector(),
        // colors.vector(),
        colorscale_state,
        view_state
      );
      // put stuff we've been drawing onto the display
      glfwSwapBuffers(window);

      std::queue<messages::Message> message_poll = message_queue.poll();
      while (!message_poll.empty())
      {
        update::OrbitalControlUpdater::update(control_state, message_poll.front(), control_state);
        message_poll.pop();
      }
      // control_state.angular_position.x += 1.0f * 3.1415926f/180.0f;
      view_state.view_matrix = control_state.get_view_matrix();
  }

  // close GL context and any other GLFW resources
  message_queue.deactivate(window);
  glfwTerminate();
  return 0;
}
