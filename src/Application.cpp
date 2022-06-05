#include "Renderer.h"

#include "Sphere.h"

int main()
{
	Camera camera({ 0,0,2 }, { 0,1,0 }, { 0,0,1 }, 1.0f, 90.0f);

	Material matG({ 0,255,0 });
	Material matR({ 255,0,0 });

	Sphere sphere1({ 0,3,0 }, 0.5f, { 0,255,0 }, matG);
	Sphere sphere2({ 0,10,0 }, 6.0f, { 255,0,0 }, matR);

	Scene scene;
	scene.add(&sphere1);
	scene.add(&sphere2);

	Renderer renderer(1280, 720, camera);
	renderer.renderScene(scene);
	renderer.saveImage("image.ppm");
}