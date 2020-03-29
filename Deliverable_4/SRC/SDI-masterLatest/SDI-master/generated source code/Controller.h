#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {

public:
	String selected_image;
	String selected_class;
	String image_display_data;
	String class_display_data;
	String image_folder_name;
	String class_file_name;
	String image_sort_type;
	String class_file_operation;
	String current_shape_type;
	String shape_operation;

	void find_selected_image();

	void use_selected_image();

	void find_selected_class();

	void use_selected_class();

	void find_selected_annotation_file();

	void use_selected_annotation_file();

	void send_image_display_data();

	Controller();

	void set_image_sort_type();

	void set_class_file_operation();

	void set_shape_type();

	void set_shape_operation();
};

#endif
