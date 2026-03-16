#include "collider.hpp"

ENGINE_API void AabbCollision::create(const vec3 a, const vec3 b)
{
	min = a;
	max = b;
}

ENGINE_API void AabbCollision::createFromCenter(const vec3 center, const vec3 size)
{
	vec3 halfSize = {size.x * 0.5f, size.y * 0.5f, size.z * 0.5f};

	min.x = center.x - halfSize.x;
	min.y = center.y - halfSize.y;
	min.z = center.z - halfSize.z;

	max.x = center.x + halfSize.x;
	max.y = center.y + halfSize.y;
	max.z = center.z + halfSize.z;
}

ENGINE_API void AabbCollision::createFromObject(ObjModel* model)
{
	vec3 minimum = {FLT_MAX, FLT_MAX, FLT_MAX};
	vec3 maximum = {-FLT_MAX, -FLT_MAX, -FLT_MAX};

	std::cout << model->getNativeTempIndexCount() << "\n";

	for(int index = 0; index < model->getNativeTempIndexCount(); index++)
	{
		vec3 pos = model->getNativeTempPosition(index);
		
		if(pos.x < minimum.x) 
			minimum.x = pos.x;
		
		if(pos.y < minimum.y)
			minimum.y = pos.y;
			
		if(pos.z < minimum.z)
			minimum.z = pos.z;

		if (pos.x > maximum.x)
			maximum.x = pos.x;

		if (pos.y > maximum.y)
			maximum.y = pos.y;

		if (pos.z > maximum.z)
			maximum.z = pos.z;
	}

	if(minimum.x == FLT_MAX)
	{
		minimum = {0.f, 0.f, 0.f};
		maximum = {0.f, 0.f, 0.f};

		std::cout << "Asd22\n";
	}

	min = minimum;
	max = maximum;
}

ENGINE_API void AabbCollision::translate(vec3 xyz)
{
	min.x += xyz.x;
	min.y += xyz.y;
	min.z += xyz.z;

	max.x += xyz.x;
	max.y += xyz.y;
	max.z += xyz.z;
}

ENGINE_API void AabbCollision::setScale(vec3 xyz)
{
	min.x *= xyz.x;
	min.y *= xyz.y;
	min.z *= xyz.z;

	max.x *= xyz.x;
	max.y *= xyz.y;
	max.z *= xyz.z;
}

ENGINE_API vec3 AabbCollision::getCenter()
{
	vec3 center;

	center.x = (min.x + max.x) * 0.5f;
	center.y = (min.y + max.y) * 0.5f;
	center.z = (min.z + max.z) * 0.5f;

	return center;
}

ENGINE_API vec3 AabbCollision::getSize()
{
	vec3 size;

	size.x = max.x - min.x;
	size.y = max.y - min.y;
	size.z = max.z - min.z;

	return size;
}

ENGINE_API vec3 AabbCollision::getMin()
{
	return min;
}

ENGINE_API vec3 AabbCollision::getMax()
{
	return max;
}

ENGINE_API bool AabbCollision::isValid()
{
	return (min.x <= max.x) && (min.y <= max.y) && (min.z <= max.z);
}

ENGINE_API bool Collider::intersects(AabbCollision &a, AabbCollision &b)
{
	return (a.getMin().x <= b.getMax().x && a.getMax().x >= b.getMin().x) && (a.getMin().y <= b.getMax().y && a.getMax().y >= b.getMin().y) && (a.getMin().z <= b.getMax().z && a.getMax().z >= b.getMin().z);
}

ENGINE_API vec3 Collider::resolveWithSliding(PhysObject &obj, AabbCollision &obstacle)
{
	vec3 test_pos_x = obj.old_position;
	test_pos_x.x = obj.position.x;
	
	AabbCollision test_box_x = obj.collision;
	vec3 delta_x = {test_pos_x.x - obj.position.x, test_pos_x.y - obj.position.y, test_pos_x.z - obj.position.z};
	test_box_x.translate(delta_x);
	
	int can_move_x = !intersects(test_box_x, obstacle);

	vec3 test_pos_y = obj.old_position;
	test_pos_y.y = obj.position.y;
	
	AabbCollision test_box_y = obj.collision;
	vec3 delta_y = {test_pos_y.x - obj.position.x, test_pos_y.y - obj.position.y, test_pos_y.z - obj.position.z};
	test_box_y.translate(delta_y);
	
	int can_move_y = !intersects(test_box_y, obstacle);

	vec3 test_pos_z = obj.old_position;
	test_pos_z.z = obj.position.z;

	AabbCollision test_box_z = obj.collision;
	vec3 delta_z = {test_pos_z.x - obj.position.x, test_pos_z.y - obj.position.y, test_pos_z.z - obj.position.z};
	test_box_z.translate(delta_z);

	int can_move_z = !intersects(test_box_z, obstacle);
		
	vec3 final_position = obj.old_position;
	
	if(can_move_x) 
		final_position.x = obj.position.x;

	if(can_move_y) 
		final_position.y = obj.position.y;

	if (can_move_z)
		final_position.z = obj.position.z;
	
	return final_position;
}
