#pragma once

#include <stdio.h>

typedef struct mat4
{
	float m[4][4];

	void debug()
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				printf("%.02f ", m[i][j]);
			}

			printf("\n");
		}
	}

	mat4 operator+(const mat4 &other) const
	{
		mat4 result;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				result.m[i][j] = m[i][j] + other.m[i][j];
			}
		}

		return result;
	}

	mat4 operator-(const mat4 &other) const
	{
		mat4 result;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				result.m[i][j] = m[i][j] - other.m[i][j];
			}
		}

		return result;
	}

	mat4 operator*(float scalar) const
	{
		mat4 result;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				result.m[i][j] = m[i][j] * scalar;
			}
		}

		return result;
	}

	mat4 operator*(const mat4 &other) const
	{
		mat4 result;

		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				for (int i = 0; i < 4; i++)
				{
					result.m[row][col] += m[row][i] * other.m[i][col];
				}
			}
		}

		return result;
	}

	mat4 operator/(float scalar) const
	{
		mat4 result;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				result.m[i][j] = m[i][j] / scalar;
			}
		}

		return result;
	}

	float *operator[](int i)
	{
		return m[i];
	}
} mat4; 