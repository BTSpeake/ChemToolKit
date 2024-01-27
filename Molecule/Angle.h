#pragma once 

class Angle {
public:
	Angle() = default;
	~Angle() = default;

	Angle(const Angle&) = delete;
	Angle& operator=(const Angle&) = delete;
};