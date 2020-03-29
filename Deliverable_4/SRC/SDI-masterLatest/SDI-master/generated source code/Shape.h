#ifndef SHAPE_H
#define SHAPE_H

class Shape {

private:
	String number_of_points;

public:
	String shape;

	void getName();

	void connect_last_point();

	void check_number_of_pointa();

	void check_if_points_connected();

private:
	void remove_point();

	void move_point();

public:
	void reset_points();

	void determine_shape();

	Shape();
};

#endif
