#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <stdexcept>
#include <exception>
#include <vector>

#include <cmath>
#include "Library.h"

double PI = (2 * acos(0.0));

// ================================ SCENE DESCRIPTION ================================ //
Window* window;
bool keyPressed = true;

Vertex* eye;
double FOV;
Vertex* uVector;
Vertex* vVector;
Vertex* wVector;

std::vector<Shape*> shapes;
std::vector<Light*> lights;

Vertex* background_color;
Triangle* triangle;
std::vector<Vertex*> vertices;
Surface* surface;

// MAIN ACTIVITY:
int main()
{
	// ================================ SETUP ================================ //
	window = new Window();

	// BLACK SCREEN
	u32* pixel = window->pixel;
	u32* temp = pixel;
	int color = 0x003180;
	for (int i = 0; i < window->height; ++i)
	{
		for (int j = 0; j < window->width; ++j)
		{
			*pixel = color;
			pixel++;			
		}		
	}
	
	// ================================ RUNNING LOOP ================================ //
	bool running = true;
	while (running)
	{
		// Close Window
		if (!window->processMessages())
		{
			std::cout << "\nClosing Window\n";
			running = false;
		}

		// Color Data
		colorData(window);

		// Display Menu?
		message();

		// User Input
		getKeyInput();
	}

	// ================================ CLOSE PROGRAM ================================ //
	delete window;
	return 0;
}

// GET COLOR DATA FROM WINDOW:
int colorData(Window* window)
{
	return StretchDIBits(
		GetDC(window->m_hWnd),
		0,
		0,
		window->width,
		window->height,
		0,
		0,
		window->width,
		window->height,
		window->memory,
		&window->bitmap_info,
		DIB_RGB_COLORS,
		SRCCOPY
	);
}

// MENU:
void message()
{
	if (keyPressed)
	{
		std::cout << "Please press one of the following numbers to render a scene:\n";
		std::cout << "1 : Red Sphere\n";
		std::cout << "2 : 3 Different Sized Spheres\n";
		std::cout << "3 : Specular Green Sphere and Dull Red Sphere\n";
		std::cout << "4 : Varying Colored Spheres\n";
		std::cout << "5 : Red Triangle\n";
		std::cout << "6 : Purple Sphere in White Hexahedron\n";
		std::cout << "7 : Multiple Light Sources and Varying Shadow Colors on Sphere\n";
		std::cout << "8 : Reflective Red Sphere and Dull Green Sphere\n";
		std::cout << "9 : Multiple Reflective Spheres on Flat Surface\n";
		std::cout << "0 : 2 Large Reflective Spheres\n";
		std::cout << "- : White Star Polygon and Red Sphere on Reflective Surface\n";
	}	
	keyPressed = false;
}

// KEY PRESSED:
void getKeyInput()
{
	char key = _getch();
	try
	{
		switch (key)
		{
			case '1': { collectSceneData("01_one_sphere.cli");  break; }
			case '2': { collectSceneData("02_three_spheres.cli");  break; }
			case '3': { collectSceneData("03_shiny_sphere.cli");  break; }
			case '4': { collectSceneData("04_many_spheres.cli");  break; }
			case '5': { collectSceneData("05_one_triangle.cli");  break; }
			case '6': { collectSceneData("06_icosahedron_and_sphere.cli");  break; }
			case '7': { collectSceneData("07_colorful_lights.cli");  break; }
			case '8': { collectSceneData("08_reflective_sphere.cli");  break; }
			case '9': { collectSceneData("09_mirror_spheres.cli");  break; }
			case '0': { collectSceneData("10_reflections_in_reflections.cli");  break; }
			case '-': { collectSceneData("11_star.cli"); break; }
			default:
			{
				std::string msg = "INVALID KEY INPUT: ";
				msg += key;
				throw std::runtime_error(msg);
			}
		}
	}
	catch (std::exception const& exc)
	{
		std::cerr << exc.what() << ", Please press the number key associated with the scene you want to ray-trace.\n";
	}
}

// COLLECT SCENE DATA:
void collectSceneData(std::string file)
{
	// Clear Scene data
	resetScene();
	
	// Collect new Scene data
	std::fstream scene_data(file, std::ios::in);
	std::string line;

	// Read File
	while (std::getline(scene_data, line))
	{

		// Get words on current line
		std::vector<std::string> words;
		std::string word = "";

		// String Stream of current line
		std::istringstream strings(line);

		// Find Words
		while (strings >> word)
		{
			words.push_back(word);
		}

		// Empty Line
		if (words.empty())
		{
			continue;
		}

		// -------------------------------- Field of View -------------------------------- //
		if (words[0] == "fov")
		{
			FOV = std::stof(words[1]);
		}
		// ------------------------------------- Eye ------------------------------------- //
		else if (words[0] == "eye")
		{
			// Position
			double x = std::stof(words[1]);
			double y = std::stof(words[2]);
			double z = std::stof(words[3]);

			eye = new Vertex(x, y, z);
		}
		// ----------------------------------- U, V, W ----------------------------------- //
		else if (words[0] == "uvw")
		{
			// U-Vector
			double uX = std::stof(words[1]);
			double uY = std::stof(words[2]);
			double uZ = std::stof(words[3]);
			uVector = new Vertex(uX, uY, uZ);

			// V-Vector
			double vX = std::stof(words[4]);
			double vY = std::stof(words[5]);
			double vZ = std::stof(words[6]);
			vVector = new Vertex(vX, vY, vZ);
			
			// W-Vector
			double wX = std::stof(words[7]);
			double wY = std::stof(words[8]);
			double wZ = std::stof(words[9]);
			wVector = new Vertex(wX, wY, wZ);
		}
		// ------------------------------ Background Color ------------------------------- //
		else if (words[0] == "background")
		{
			// Red Green Blue
			double r = std::stof(words[1]);
			double g = std::stof(words[2]);
			double b = std::stof(words[3]);

			background_color = new Vertex(r, g, b);
		}
		// ------------------------------------ Light ------------------------------------ //
		else if (words[0] == "light")
		{
			// Position
			double x = std::stof(words[1]);
			double y = std::stof(words[2]);
			double z = std::stof(words[3]);

			// Red Green Blue
			double r = std::stof(words[4]);
			double g = std::stof(words[5]);
			double b = std::stof(words[6]);

			lights.push_back(new Light(new Vertex(x, y, z), new Vertex(r, g, b)));
		}
		// ----------------------------------- Surface ----------------------------------- //
		else if (words[0] == "surface")
		{
			// Diffused: Red Green Blue
			double dr = std::stof(words[1]);
			double dg = std::stof(words[2]);
			double db = std::stof(words[3]);

			// Ambient: Red Green Blue
			double ar = std::stof(words[4]);
			double ag = std::stof(words[5]);
			double ab = std::stof(words[6]);
			
			// Specular: Red Green Blue
			double sr = std::stof(words[7]);
			double sg = std::stof(words[8]);
			double sb = std::stof(words[9]);

			// Surface Properties
			double spec_power = std::stof(words[10]);
			double k_refl = std::stof(words[11]);

			surface = new Surface(dr, dg, db, ar, ag, ab, sr, sg, sb, spec_power, k_refl);
		}
		// ------------------------------------ Sphere ----------------------------------- //
		else if (words[0] == "sphere")
		{
			// Radius
			double radius = std::stof(words[1]);

			// Position
			double x = std::stof(words[2]);
			double y = std::stof(words[3]);
			double z = std::stof(words[4]);

			shapes.push_back(new Sphere(new Vertex(x, y, z), radius, surface));
		}
		// -------------------------------- Begin Triangle ------------------------------- //
		else if (words[0] == "begin")
		{
			vertices.clear();
			triangle = NULL;
		}
		// ------------------------------------ Vertex ----------------------------------- //
		else if (words[0] == "vertex")
		{
			// Position
			double x = std::stof(words[1]);
			double y = std::stof(words[2]);
			double z = std::stof(words[3]);

			vertices.push_back(new Vertex(x, y, z));
		}
		// --------------------------------- End Triangle -------------------------------- //
		else if (words[0] == "end")
		{
			// Position
			Vertex* v1 = vertices[0];
			Vertex* v2 = vertices[1];
			Vertex* v3 = vertices[2];

			triangle = new Triangle(v1, v2, v3, surface);
			shapes.push_back(triangle);
		}
		// ----------------------------------- Render ------------------------------------ //
		else if (words[0] == "render")
		{
			renderScene();
		}
		// ---------------------------------- Comment ------------------------------------ //
		else if (words[0] == "#")
		{
			continue;
		}
		// ----------------------------------- Error ------------------------------------- //
		else
		{
			std::cout << "ERROR: Something is wrong with the .cli scene files.\n";
		}
	}

	// Close File
	scene_data.close();
}

// RESET SCENE DESCRIPTION:
void resetScene()
{
	eye = NULL;
	FOV = 0.0;
	uVector = NULL;
	vVector = NULL;
	wVector = NULL;

	shapes.clear();
	lights.clear();

	background_color = NULL;
	triangle = NULL;
	vertices.clear();
	surface = NULL;
}

// RENDER SCENE:
void renderScene()
{	
	// K
	double radians = (FOV * PI) / 180;
	double k = std::tan(radians / 2);

	// Directions
	double d = 1 / k;

	// Pixels:
	u32* pixel = window->pixel;
	for (int i = 0; i < window->height; ++i)
	{
		for (int j = 0; j < window->width; ++j)
		{
			// U + V Vectors
			double U = ((2.0 * j) / window->width) - 1;
			double V = ((2.0 * i) / window->height) - 1;

			// Directional Components
			Vertex* x = uVector->uniformScale(U);
			Vertex* y = vVector->uniformScale(V);
			Vertex* z = wVector->uniformScale(-d);

			// Directional Vector
			Vertex* direction = x->add(y->add(z))->normalize();

			// Initialize Ray
			Ray* ray = new Ray(eye, direction);

			// Collect Ray Intersection Data
			Intersection* intersection = rayIntersectScene(ray);

			Vertex* color;

			// Has Intersection?
			if (intersection != NULL)
			{
				color = colorize(intersection, ray, 10);
			}
			else
			{
				color = background_color;
			}

			// Configure Color
			int r = (int)(color->r * 255);
			int g = (int)(color->g * 255);
			int b = (int)(color->b * 255);

			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;
			
			if (r < 0) r = 0;
			if (g < 0) g = 0;
			if (b < 0) b = 0;

			// Final Color
			int hexColor = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);

			// Set Pixel Color
			*pixel++ = hexColor;
			//std::cout << "RGB: (" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")\n";
		}
	}
}

// RAY INTERSECT SCENE
Intersection* rayIntersectScene(Ray* ray)
{
	// Base Cases
	double min_t = INT_MAX;
	Shape* closest_shape = NULL;
	Vertex* closest_intersection = NULL;

	// Check Ray -> Nearest Shape 
	for (Shape* shape : shapes)
	{
		Vertex* temp_point = shape->getRayIntersection(ray);

		// Found Intersection?
		if (temp_point != NULL)
		{
			double distance = temp_point->distance(ray->origin);

			// Found Closer Intersection?
			if (distance > 0 && distance < min_t)
			{
				min_t = distance;
				closest_intersection = temp_point;
				closest_shape = shape;
			}
		}
	}

	// No Intersections?
	if (closest_intersection == NULL)
	{
		return new Intersection(NULL, NULL, -1.0);
	}

	// Has Closest Intersection?
	else
	{
		return new Intersection(closest_shape, closest_intersection, min_t);
	}

	return NULL;
}

// COLORIZE
Vertex* colorize(Intersection* intersection, Ray* ray, int depth)
{
	// Unpack Interection Data
	Shape* shape = intersection->shape;
	Vertex* point = intersection->point;

	// No Intersection?
	if (shape == NULL)
	{
		return background_color;
	}

	// Normal Vector
	Vertex* normal;
	if (shape->getType() == "SPHERE")
	{
		normal = (point->sub(shape->center))->normalize();
	}
	else if (shape->getType() == "TRIANGLE")
	{
		normal = shape->normal;
	}
	else
	{
		throw "NOT A VAILD SHAPE";
	}

	// Color Values
	double R = 0;
	double G = 0;
	double B = 0;

	// Reflections?
	if (depth > 0 && shape->surface->k_refl > 0)
	{
		Vertex* refl_dir = (ray->direction->sub(normal->uniformScale(2 * normal->dot(ray->direction))))->normalize();
		Ray* refl_ray = new Ray(point->add(normal->uniformScale(0.0001)), refl_dir);
		Intersection* refl_intersection = rayIntersectScene(refl_ray);

		// Reflect to another shape?
		Vertex* refl_color;
		if (refl_intersection->shape != NULL && refl_intersection->shape != shape)
		{
			refl_color = colorize(refl_intersection, refl_ray, depth - 1);
		}
		else
		{
			refl_color = background_color;
		}

		// Set Total R G B color values
		R += refl_color->r * shape->surface->k_refl;
		G += refl_color->g * shape->surface->k_refl;
		B += refl_color->b * shape->surface->k_refl;
	}
	
	// Light Value Inputs
	for (Light* light : lights)
	{
		// Light Vector
		Vertex* light_vector = (light->position->sub(point))->normalize();

		// Shadow Ray
		Ray* shadow_ray = new Ray(point->add(normal->uniformScale(0.0001)), light_vector);
		Intersection* shadow_intersection = rayIntersectScene(shadow_ray);
		int shadow_term = 1;

		// Under Shadow?
		if (shadow_intersection->shape != NULL && shadow_intersection->t < light->position->distance(point))
		{
			shadow_term = 0;
		}

		// Half-way Vector
		Vertex* h_vector = (light_vector->sub(ray->direction))->normalize();

		// Specular Coefficient
		double spec_coeff = pow(max(0, h_vector->dot(normal)), shape->surface->spec_power);

		// Specular Color
		double spec_r = shape->surface->sr * light->color->r * spec_coeff;
		double spec_g = shape->surface->sg * light->color->g * spec_coeff;
		double spec_b = shape->surface->sb * light->color->b * spec_coeff;

		// Diffuse Coefficient
		double diff_coeff = max(0, normal->dot(light_vector));

		// Diffuse Color
		double diff_r = shape->surface->dr * light->color->r * diff_coeff;
		double diff_g = shape->surface->dg * light->color->g * diff_coeff;
		double diff_b = shape->surface->db * light->color->b * diff_coeff;

		// Combine Specular + Diffuse + Shading
		R += (diff_r + spec_r) * shadow_term;
		G += (diff_g + spec_g) * shadow_term;
		B += (diff_b + spec_b) * shadow_term;
		//std::cout << "RED: " + std::to_string(R) + "\n";
		//std::cout << "GREEN: " + std::to_string(G) + "\n";
		//std::cout << "BLUE: " + std::to_string(B) + "\n";
	}

	// Ambient Contribution
	R += shape->surface->ar;
	G += shape->surface->ag;
	B += shape->surface->ab;

	//std::cout << "FINAL RED: " + std::to_string(surface->ar) + "\n";
	//std::cout << "FINAL GREEN: " + std::to_string(surface->ag) + "\n";
	//std::cout << "FINAL BLUE: " + std::to_string(surface->ab) + "\n";

	// Return resulting RGB
	return new Vertex(R, G, B);
}