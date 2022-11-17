#pragma once

#ifndef MAIN_H
#define MAIN_H

#include "Window.h"
#include "Ray.h"
#include "Intersection.h"

// Helper Functions
int colorData(Window* window);
void message();
void getKeyInput();
void collectSceneData(std::string file);
void resetScene();
void renderScene();
Intersection rayIntersectScene(Ray ray);
Vertex colorize(Intersection intersection, Ray ray, int depth);

class MainActivity
{
};

#endif // !MAIN_H