#include "Renderer.h"

#include "Sphere.h"

int main()
{
	Camera camera({ 0,0,2 }, { 0,1,0 }, { 0,0,1 }, 1.0f, 90.0f);

	Opaque matG({ 0,255,0 });
	Opaque matP({ 255,0,255 });
	Opaque matB({ 0,0,255 });

	Sphere sphere1({ 0,3,0.5f }, 1.0f, &matG);
	Sphere sphere2({ 0,10,2.5f }, 5.0f, &matP);
	Sphere sphere3({ 0,0,-100.0f }, 100.0f, &matB);

	Scene scene;
	scene.add(&sphere1);
	scene.add(&sphere2);
	scene.add(&sphere3);

	Renderer renderer(1280, 720, camera, scene, 32, 8);
	renderer.renderScene();
	renderer.saveImage("image.ppm");
}