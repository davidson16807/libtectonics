/*
"get_fraction_of_light_reflected_on_surface_head_on" finds the fraction of light that's reflected
by a boundary between materials when striking head on.
It is also known as the "characteristic reflectance" within the fresnel reflectance equation.
The refractive indices can be provided as parameters in any order.
*/
float get_fraction_of_light_reflected_on_surface_head_on(
    in float refractivate_index1, 
    in float refractivate_index2
){
    float n1 = refractivate_index1;
    float n2 = refractivate_index2;
    float sqrtR0 = ((n1-n2)/(n1+n2));
    float R0 = sqrtR0 * sqrtR0;
    return R0;
}
/*
"get_fraction_of_light_reflected_on_surface" returns Fresnel reflectance.
Fresnel reflectance is the fraction of light that's immediately reflected upon striking the surface.
It is the fraction of light that causes specular reflection.
Here, we use Schlick's fast approximation for Fresnel reflectance.
see https://en.wikipedia.org/wiki/Schlick%27s_approximation for a summary 
see Hoffmann 2015 for a gentle introduction to the concept
see Schlick (1994) for implementation details
*/
float get_fraction_of_light_reflected_on_surface(
    in float cos_incident_angle, 
    in float characteristic_reflectance
){
    float R0 = characteristic_reflectance;
    float _1_u = 1.-cos_incident_angle;
    return R0 + (1.-R0) * _1_u*_1_u*_1_u*_1_u*_1_u;
}
/*
"get_rgb_fraction_of_light_reflected_on_surface" returns Fresnel reflectance for each color channel.
Fresnel reflectance is the fraction of light that's immediately reflected upon striking the surface.
It is the fraction of light that causes specular reflection.
Here, we use Schlick's fast approximation for Fresnel reflectance.
see https://en.wikipedia.org/wiki/Schlick%27s_approximation for a summary 
see Hoffmann 2015 for a gentle introduction to the concept
see Schlick (1994) for implementation details
*/
vec3 get_rgb_fraction_of_light_reflected_on_surface(
    in float cos_incident_angle, 
    in vec3 characteristic_reflectance
){
    vec3 R0 = characteristic_reflectance;
    float _1_u = 1.-cos_incident_angle;
    return R0 + (1.-R0) * _1_u*_1_u*_1_u*_1_u*_1_u;
}
/*
"get_fraction_of_light_masked_or_shaded_by_surface" is Schlick's fast approximation for Smith's function
see Hoffmann 2015 for a gentle introduction to the concept
see Schlick (1994) for even more details.
*/
float get_fraction_of_light_masked_or_shaded_by_surface(
    in float cos_view_angle, 
    in float root_mean_slope_squared
){
    float m = root_mean_slope_squared;
    float v = cos_view_angle;
    float k = sqrt(2.*m*m/PI);
    return v/(v-k*v+k); 
}
/*
"get_fraction_of_microfacets_with_angle" 
This is also known as the Beckmann Surface Normal Distribution Function.
This is the probability of finding a microfacet whose surface normal deviates from the average by a certain angle.
see Hoffmann 2015 for a gentle introduction to the concept.
see Schlick (1994) for even more details.
*/
float get_fraction_of_microfacets_with_angle(
    in float cos_angle_of_deviation, 
    in float root_mean_slope_squared
){
    float m = root_mean_slope_squared;
    float t = cos_angle_of_deviation;
    return exp((t*t-1.)/(m*m*t*t))/(m*m*t*t*t*t);
}

