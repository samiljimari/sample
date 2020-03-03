#ifndef MODEL_H
#define MODEL_H

class Model {

public:
	String annotation_file_used;
	String image_used;
	String class_used;

	String eligible_classes;

private:
	void parse_annotation_file();

	void parse_image();

	void parse_class();

public:
	Model();
};

#endif
