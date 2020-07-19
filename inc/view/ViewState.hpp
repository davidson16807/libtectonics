#pragma once

// glm libraries
#include <glm/mat4x4.hpp> // *mat4

namespace view 
{
	enum RenderPassType
	{
		solids,
		volumetrics,
		lens_effects,
	};
	enum ProjectionType
	{
		heads_up_display,
		perspective,
		equirectangular,
		equirectangular_texture
	};
	struct ViewState
	{
		glm::mat4 view_matrix;
		glm::mat4 model_matrix;
		glm::mat4 projection_matrix;
		ProjectionType projection_type;
		RenderPassType render_pass;

		ViewState():
			view_matrix(),
			model_matrix(),
			projection_matrix(),
			projection_type(ProjectionType::perspective),
			render_pass(RenderPassType::solids)
		{}
	};


    // TODO: move this to a dedicated namespace for projections
	std::string get_default_clipspace_position_glsl = R"(
	    vec4 get_default_clipspace_position (
	        in  vec4  local_position,
	        in  mat4  model_matrix,
	        in  mat4  view_matrix,
	        in  mat4  projection_matrix,
	        in  int   projection_type,
	        in  float map_projection_offset
	    ) {
	        const float PI = 3.14159265358979;
	        if (projection_type == 0)
	        {
	            return local_position;
	        } 
	        else if (projection_type == 1)
	        {
	            return projection_matrix * view_matrix * model_matrix * local_position;
	        }
	        else if (projection_type >= 2)
	        {
	            vec4 model_position = model_matrix * local_position;
	            vec4 view_position = view_matrix[3];
	            float focus = atan(-view_position.z, view_position.x) + PI + map_projection_offset;
	            float lon_focused = mod(atan(-model_position.z, model_position.x) + PI - focus, 2.*PI) - PI;
	            float lat_focused = asin(model_position.y / length(model_position)); //+ (map_projection_offset*PI);
	            bool is_on_edge = lon_focused >  PI*0.9 || lon_focused < -PI*0.9;
	            vec4 projected_position = vec4(
	                lon_focused, lat_focused, is_on_edge? 0.0 : length(model_position), 1
	            );
	            if (projection_type == 2) 
	            {
	                mat4 scale_matrix = mat4(1);
	                scale_matrix[3] = view_matrix[3];
	                return projection_matrix * scale_matrix * projected_position;
	            }
	            else if(projection_type == 3)
	            {
	                return projected_position;
	            }
	        }
	    }
    )";
}