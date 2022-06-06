#include "Renderer.h"

#include "Sphere.h"

int main()
{
	Camera camera({ 0,0,2 }, { 0,1,0 }, { 0,0,1 }, 1.0f, 90.0f);

	Opaque matG({ 0,1,0 });
	Opaque matP({ 1,0,1 });
	Opaque matB({ 0,0,1 });

	Metal met1({ 1,0,1 }, 0.0f);
	Metal met2({ 0,0,1 }, 0.3f);
	Metal met3({ 1,0,0 }, 0.3f);

	Sphere sphere1({ 0,3,0.5f }, 1.0f, &matG);
	Sphere sphere2({ 0,10,2.5f }, 5.0f, &met1);
	Sphere sphere3({ 0,0,-100.0f }, 100.0f, &met3);

	Scene scene;
	scene.add(&sphere1);
	scene.add(&sphere2);
	scene.add(&sphere3);

	Renderer renderer(1280, 720, camera, scene, 32, 8, 4);
	renderer.renderScene();
	renderer.saveImage("image.ppm");
}