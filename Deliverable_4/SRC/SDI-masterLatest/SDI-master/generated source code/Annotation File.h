#ifndef ANNOTATION FILE_H
#define ANNOTATION FILE_H

class Annotation_File {

public:
	String filename;

private:
	void declare_file();

	void set_file(String a);

public:
	Annotation_File();

	void add_image();

	void remove_image();
};

#endif
