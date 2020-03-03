#ifndef CLASS FILE HANDLER_H
#define CLASS FILE HANDLER_H

class Class_file_handler {

public:
	String file_name;

	void add_class();

	void remove_class();

	void sort_ascending();

	void sort_descending();

private:
	void set_file_name();

public:
	void get_classes();

	Class_file_handler();
};

#endif
