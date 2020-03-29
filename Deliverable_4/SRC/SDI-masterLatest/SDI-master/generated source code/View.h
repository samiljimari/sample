#ifndef VIEW_H
#define VIEW_H

class View {

public:
	String annotation_file;
	String image_display_data;
	String class_display_data;
	String image_folder;
	String class_file;
	String image_sort_type;
	String class_file_operation;

	void parse_image_folder();

	void parse_class_file();

	void parse_annotation_file();

	void display_folder_content();

	void display_class_file_content();

	void display_image();

	void display_annotation_on_image();

	View();
};

#endif
