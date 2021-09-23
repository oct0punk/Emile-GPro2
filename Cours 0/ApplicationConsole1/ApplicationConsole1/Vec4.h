#pragma once
struct Vec4 {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;


	
	void Set(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
										 
										 
										 
	Vec4 Add(Vec4 vec) {				 
		Vec4 newVec;					 
		newVec.x = this->x + vec.x;		 
		newVec.y = this->y + vec.y;		 
		newVec.z = this->z + vec.z;		 
		newVec.w = this->w + vec.w;		 
										 
		return newVec;
	}

	void Incr(Vec4 vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;
	}

	void Incr(float f) {
		x += f;
		y += f;
		z += f;
		w += f;
	}

	void Get() {

	}
};