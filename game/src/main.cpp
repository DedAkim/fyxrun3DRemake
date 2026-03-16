#include <glext/native_gl.hpp>
#include <winmgr.hpp>
#include <shaders/ogl_shader.hpp>
#include <transform/transform.hpp>
#include <models/obj.hpp>
#include <camera/camera.hpp>
#include <physics/collider.hpp>
#include "controls.hpp"

#include <ctime>

int main(int argc, char** argv)
{
	std::srand(std::time(0)); 

	WindowManager window("Hello", 1280, 720);

	// Сборка шейдеров
	OpenGLShader shader("shaders/light.vs", "shaders/light.fs");
	
	// Добавление моделек и текстурок
	ObjModel model_player("models/Speckle.obj");
	ObjModel model_cube("models/stoopid.obj");
	ObjModel model_car("models/textured_car.obj");
	ObjModel model_map("models/pole.obj");
	ObjModel model_cactus("models/cactus.obj");
	ObjModel model_brick("models/bricks.obj");
	ObjModel model_bicycle("models/velik.obj");
	ObjModel model_tumbleweed("models/tumbleweed.obj");

	GLTexture texture_player("textures/speckle.png");
	GLTexture texture_car("textures/car_map_hd.png");
	GLTexture texture_road("textures/way.png");
	GLTexture texture_map("textures/night_sand.png");
	GLTexture texture_cactus("textures/green.png");
	GLTexture texture_brick("textures/fuck.png");
	GLTexture texture_bicycle("textures/cool_bicycle.png");
	GLTexture texture_tumbleweed("textures/brown.png");

	/*------------------------------*/

	// Позиции коллизий
	vec3 player = {0, 0, 0.5};
	vec3 map1 = {5, -1.1, 0};
	vec3 map2 = {-5, -1.1, 0};
	vec3 car1 = {0.5, 0, -15};
	vec3 car2 = {-0.5, 0, -15};
	vec3 bicycle = {0, 0, -45};
	vec3 tumbleweed = {-11, 0.01, -2.2};

	/*------------------------------*/

	//Создание коллизий

	/*------------------------------*/

	// Игрок
  	AabbCollision abPlayer;
  	abPlayer.createFromObject(&model_player);
  	if(abPlayer.isValid())
  	{
    	printf("AABB 1 Valid\n");
  	}
	PhysObject phPlayer;
	phPlayer.position = player;
	phPlayer.old_position = player;
	phPlayer.velocity = {0.0f, 0.0f, 0.0f};
	phPlayer.collision = abPlayer;

	/*------------------------------*/

	// Стены
  	AabbCollision abMap1;
	abMap1.createFromObject(&model_map);
  	if(abMap1.isValid())
  	{
    	printf("AABB 2 Valid\n");
  	}
  	PhysObject phMap1;
  	phMap1.position = map1;
  	phMap1.old_position = map1;
  	phMap1.velocity = {0.0f, 0.0f, 0.0f};
  	phMap1.collision = abMap1;

  	AabbCollision abMap2;
	abMap2.createFromObject(&model_map);
  	if(abMap2.isValid())
  	{
    	printf("AABB 3 Valid\n");
  	}
  	PhysObject phMap2;
  	phMap2.position = map2;
  	phMap2.old_position = map2;
  	phMap2.velocity = {0.0f, 0.0f, 0.0f};
  	phMap2.collision = abMap2;

	/*------------------------------*/
	
	//Машинки
  	AabbCollision abCar1;
	abCar1.createFromObject(&model_car);
  	if(abCar1.isValid())
  	{
    	printf("AABB 4 Valid\n");
  	}
	abCar1.setScale({0.3, 0.3, 0.3});
  	PhysObject phCar1;
  	phCar1.position = car1;
  	phCar1.old_position = car1;
  	phCar1.velocity = {0.0f, 0.0f, 0.0f};
  	phCar1.collision = abCar1;

  	AabbCollision abCar2;
	abCar2.createFromObject(&model_car);
  	if(abCar2.isValid())
  	{
    	printf("AABB 5 Valid\n");
  	}
	abCar2.setScale({0.3, 0.3, 0.3});
  	PhysObject phCar2;
  	phCar2.position = car2;
  	phCar2.old_position = car2;
  	phCar2.velocity = {0.0f, 0.0f, 0.0f};
  	phCar2.collision = abCar2;	

	/*------------------------------*/

	//Велик
	AabbCollision abBicycle;
	abBicycle.createFromObject(&model_bicycle);
  	if(abBicycle.isValid())
  	{
    	printf("AABB 6 Valid\n");
  	}
	abBicycle.setScale({0.1, 0.11, 0.1});
	PhysObject phBicycle;
	phBicycle.position = bicycle;
	phBicycle.old_position = bicycle;
	phBicycle.velocity= {0.0f, 0.0f, 0.0f};
  	phBicycle.collision = abBicycle;	
	
	/*------------------------------*/

	// Иницилизация камеры
	Camera3D mainCamera;
	float posXCam = 1.0f;
	float posZCam = 1.0f;
	mainCamera.setPosition({posXCam, 2.0f, posZCam});
	mainCamera.setShader(&shader);

	/*------------------------------*/

	clock_t lastTime = clock();
	static float min_speed = 10;
	static float max_speed = 25;
	float speed = 10;
	float speed_drop = 0;
	float angle = 180.0f;
	RGB8 sky_color = {0, 0, 0};
	uint8_t day = 150;
	uint8_t night = 150;

	/*------------------------------*/

	// Основной цикл окна

	while(window.isOpen())
	{
		window.clear({0, 0, 0});

		// Бинд шейдера
		shader.bind();

		/*------------------------------*/		

		// Работа с освещением в шейдере 
		shader.setVec3("color", {1, 1, 1});
		shader.setInt("num_lights", 6);

		shader.setVec3("light_color[0]", {0, 0, 0});
		shader.setVec3("light_position[0]", {player.x, 0.5f, player.z});

		shader.setVec3("light_color[1]", {1.f, 1.f, 0});
		shader.setVec3("light_position[1]", {car1.x, 0.5f, car1.z + 1.5f});

		shader.setVec3("light_color[2]", {1.f, 1.f, 0});
		shader.setVec3("light_position[2]", {car2.x, 0.5f, car2.z + 1.5f});

		shader.setVec3("light_color[3]", {1.f, 0, 0});
		shader.setVec3("light_position[3]", {car1.x, 0.5f, car1.z - 1.5f});

		shader.setVec3("light_color[4]", {1.f, 0, 0});
		shader.setVec3("light_position[4]", {car2.x, 0.5f, car2.z - 1.5f});

		shader.setVec3("light_color[5]", {1.f, 1.f, 0});
		shader.setVec3("light_position[5]", {bicycle.x, 0.5f, bicycle.z + 1.5f});


		shader.setVec3("ambient_light", {1, 1, 1});

		/*------------------------------*/

		// Работа с камерой
		mainCamera.calculateMatrix();
		mainCamera.flush();
		mainCamera.setPosition({player.x, 0.5f, player.z + 0.5f});
		mainCamera.setPoint({player.x, -0.1f, player.z});

		/*------------------------------*/
	
		// Время и угол вращения
		clock_t currentTime = clock();
		float deltaTime = float(currentTime - lastTime) / CLOCKS_PER_SEC;
		lastTime = currentTime;

		angle += 3.14159265f * deltaTime;
		if (angle > 6.2831853f)
			angle -= 6.2831853f;

		/*------------------------------*/
/*
		if (sky_color.b < day)
		{
			sky_color.b += 1;
			sky_color.g += 1;
			sky_color.r += 1;
			if(sky_color.b == 200)
			{
				day = 0;
				night = 0;
			}
		}
		if (sky_color.b > night)
		{
			sky_color.b -= 1;
			sky_color.g -= 1;
			sky_color.r -= 1;
			if(sky_color.b == 0)
			{
				day = 200;
				night = 200;
			}
		}
*/
		// Управление
		if(cntrl::isKeyPressed('D'))
		{
			player.x += 2.0f * deltaTime;
		}

		if(cntrl::isKeyPressed('A'))
		{
			player.x -= 2.0f * deltaTime;
		}
/*
		if(cntrl::isKeyPressed('W'))
		{
			player.z -= 2.0f * deltaTime;
		}

		if(cntrl::isKeyPressed('S'))
		{
			player.z += 2.0f * deltaTime;
		}
*/

		/*------------------------------*/

		// Кнопка ускорения
		if(cntrl::isKeyPressed('E'))
		{
			if (speed < max_speed)
			{
				speed += 0.001f;
			}
		}
		else if (speed > min_speed)
		{
			speed = speed - (speed_drop * deltaTime);
			speed_drop += 0.003f;
		}
		else
		{
			speed_drop = 0.0f;
		}

		/*------------------------------*/

		// Работа с коллизиями

		/*------------------------------*/

		// Старая позиция
		phPlayer.old_position = phPlayer.position;
		phMap1.old_position = phMap1.position;
		phMap2.old_position = phMap2.position;
		phCar1.old_position = phCar1.position;
		phCar2.old_position = phCar2.position;
		phBicycle.old_position = phBicycle.position;

		/*------------------------------*/

		// Коллизии
		phPlayer.collision = abPlayer;
		phPlayer.collision.translate(player);

		phMap1.collision = abMap1;
		phMap1.collision.translate(map1);
		phMap2.collision = abMap2;
		phMap2.collision.translate(map2);

		phCar1.collision = abCar1;
		phCar1.collision.translate(car1);
		phCar2.collision = abCar2;
		phCar2.collision.translate(car2);

		phBicycle.collision = abBicycle;
		phBicycle.collision.translate(bicycle);

		/*------------------------------*/
	
		// Взаимодействие коллизий
		if(Collider::intersects(phPlayer.collision, phMap1.collision))
		{
			player = Collider::resolveWithSliding(phPlayer, phMap1.collision);
			phPlayer.position = player;
		}
		if(Collider::intersects(phPlayer.collision, phMap2.collision))
		{
			player = Collider::resolveWithSliding(phPlayer, phMap2.collision);
			phPlayer.position = player;
		}
		if(Collider::intersects(phPlayer.collision, phCar1.collision))
		{
			player = Collider::resolveWithSliding(phPlayer, phCar1.collision);
			phPlayer.position = player;

			system("start game.exe");

			exit(-1);
		}
		if(Collider::intersects(phPlayer.collision, phCar2.collision))
		{
			player = Collider::resolveWithSliding(phPlayer, phCar2.collision);
			phPlayer.position = player;

			system("start game.exe");

			exit(-1);
		}
		if(Collider::intersects(phPlayer.collision, phBicycle.collision))
		{
			player = Collider::resolveWithSliding(phPlayer, phBicycle.collision);
			phPlayer.position = player;

			system("start game.exe");

			exit(-1);
		}

		/*------------------------------*/

		// Новая позиция
		phPlayer.position = player;
		phMap1.position = map1;
		phMap2.position = map2;

		car1 = {car1.x, car1.y, car1.z + (deltaTime * speed)};
		car2 = {car2.x, car2.y, car2.z + (deltaTime * speed)};
		bicycle = {bicycle.x, bicycle.y, bicycle.z + (deltaTime * speed)};
		if (car1.z > 10.0f)
		{
			int min = -15, max = -21;
    		float randomNum = min + std::rand() % (max - min + 1);
			car1 = {car1.x, car1.y, randomNum};
			if (car1.z == car2.z && car1.z == bicycle.z)
			{
				car1 = {car1.x, car1.y, -25};
			}
		}
		if (car2.z > 6.0f)
		{
		    int min = -22, max = -25;
    		float randomNum = min + std::rand() % (max - min + 1);
			car2 = {car2.x, car2.y, randomNum};
			if (car2.z == car1.z && car2.z == bicycle.z)
			{
				car2 = {car2.x, car2.y, -30};
			}
		}
		if (bicycle.z > 18.0f)
		{
			int min = -33, max = -43;
			float randomNum = min + std::rand() % (max - min + 1);
			bicycle = {bicycle.x, bicycle.y, randomNum};
			if (bicycle.z == car1.z && bicycle.z == car2.z)
			{
				bicycle = {bicycle.x, bicycle.y, -48};
			}
		}

		tumbleweed = {tumbleweed.x + (1 * deltaTime), tumbleweed.y, tumbleweed.z};
		if(tumbleweed.x > 10.0f)
		{
			int min = -11, max = -19;
			float randomNum = min + std::rand() % (max - min + 1);
			tumbleweed = {randomNum, tumbleweed.y, tumbleweed.z};
		}

		phCar1.position = car1;
		phCar2.position = car2;
		phBicycle.position = bicycle;

		/*------------------------------*/

		// Трансформация модели и рендер модели

		/*------------------------------*/

		// Игрок
		Transform transform_player;
		transform_player.translateTo(phPlayer.position);
		transform_player.rotateTo(Trygonometry::radians(180.0f), {0, 1, 0});
		transform_player.scaleTo({1, 1, 1});
		shader.setMat4("uModel", transform_player.getModel());
		texture_player.bind();
		GLImmediateRender::drawElements(model_player.getBuffers(), model_player.getNativeIndexCount());

		/*------------------------------*/

		// Стены(невидемые ууууу)
		Transform transform_map1;
		transform_map1.translateTo(map1);
		transform_map1.scaleTo({1, 1, 1});
		shader.setMat4("uModel", transform_map1.getModel());
		texture_map.bind();
		GLImmediateRender::drawElements(model_map.getBuffers(), model_map.getNativeIndexCount());
	
		Transform transform_map2;
		transform_map2.translateTo(map2);
		transform_map2.scaleTo({1, 1, 1});
		shader.setMat4("uModel", transform_map2.getModel());
		texture_map.bind();
		GLImmediateRender::drawElements(model_map.getBuffers(), model_map.getNativeIndexCount());

		/*------------------------------*/		

		//Машинки
		Transform transform_car1;
		transform_car1.translateTo(car1);
		transform_car1.scaleTo({0.3, 0.3, 0.3});
		shader.setMat4("uModel", transform_car1.getModel());
		texture_car.bind();
		GLImmediateRender::drawElements(model_car.getBuffers(), model_car.getNativeIndexCount());

		Transform transform_car2;
		transform_car2.translateTo(car2);
		transform_car2.scaleTo({0.3, 0.3, 0.3});
		shader.setMat4("uModel", transform_car2.getModel());
		texture_car.bind();
		GLImmediateRender::drawElements(model_car.getBuffers(), model_car.getNativeIndexCount());

		/*------------------------------*/

		// Дорога
		for (float i = -19; i < 21; i+=2)
		{
			Transform transform_road;
			transform_road.translateTo({0, -1.1, i});
			transform_road.scaleTo({1, 1, 1});
			shader.setMat4("uModel", transform_road.getModel());
			texture_road.bind();
			GLImmediateRender::drawElements(model_cube.getBuffers(), model_cube.getNativeIndexCount());
		}
		/*------------------------------*/

		//Кактусы :3
		Transform transform_cactus1;
		transform_cactus1.translateTo({-2.5, 0, -1.5});
		transform_cactus1.scaleTo({0.3, 0.3, 0.3});
		shader.setMat4("uModel", transform_cactus1.getModel());
		texture_cactus.bind();
		GLImmediateRender::drawElements(model_cactus.getBuffers(), model_cactus.getNativeIndexCount());

		Transform transform_cactus2;
		transform_cactus2.translateTo({3, 0, -2});
		transform_cactus2.scaleTo({0.3, 0.3, 0.3});
		shader.setMat4("uModel", transform_cactus2.getModel());
		texture_cactus.bind();
		GLImmediateRender::drawElements(model_cactus.getBuffers(), model_cactus.getNativeIndexCount());

		Transform transform_cactus3;
		transform_cactus3.translateTo({-1.2, 0, -3});
		transform_cactus3.scaleTo({0.3, 0.3, 0.3});
		shader.setMat4("uModel", transform_cactus3.getModel());
		texture_cactus.bind();
		GLImmediateRender::drawElements(model_cactus.getBuffers(), model_cactus.getNativeIndexCount());

		Transform transform_cactus4;
		transform_cactus4.translateTo({4, 0, -4});
		transform_cactus4.scaleTo({0.3, 0.3, 0.3});
		shader.setMat4("uModel", transform_cactus4.getModel());
		texture_cactus.bind();
		GLImmediateRender::drawElements(model_cactus.getBuffers(), model_cactus.getNativeIndexCount());

		/*------------------------------*/

		//Кирпич ( [||] )
		Transform tranform_brick;
		tranform_brick.translateTo({1.1, -0.1, -0.5});
		tranform_brick.rotateTo(Trygonometry::radians(270.0f), {0, 1, 0});
		tranform_brick.scaleTo({0.23, 0.23, 0.23});
		shader.setMat4("uModel", tranform_brick.getModel());
		texture_brick.bind();
		GLImmediateRender::drawElements(model_brick.getBuffers(), model_brick.getNativeIndexCount());

		/*------------------------------*/

		//Велик врум врум
		Transform tranform_bicycle;
		tranform_bicycle.translateTo(bicycle);
		tranform_bicycle.rotateTo(Trygonometry::radians(180.0f), {0, 1, 0});
		tranform_bicycle.scaleTo({0.1, 0.11, 0.1});
		shader.setMat4("uModel", tranform_bicycle.getModel());
		texture_bicycle.bind();
		GLImmediateRender::drawElements(model_bicycle.getBuffers(), model_bicycle.getNativeIndexCount());

		/*------------------------------*/

		//Перекати-поле -w-

		Transform tranform_tumbleweed;
		tranform_tumbleweed.translateTo(tumbleweed);
		tranform_tumbleweed.rotateTo(angle, {0, 1, -1});
		tranform_tumbleweed.scaleTo({0.1, 0.1, 0.1});
		shader.setMat4("uModel", tranform_tumbleweed.getModel());
		texture_tumbleweed.bind();
		GLImmediateRender::drawElements(model_tumbleweed.getBuffers(), model_tumbleweed.getNativeIndexCount());

		/*------------------------------*/
		
		// Меняем кадр на подготовленный
		window.swapBuffers();
	}
}
