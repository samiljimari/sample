#ifndef ANNOTATION FILE HANDLER_H
#define ANNOTATION FILE HANDLER_H

class Annotation_file_handler : Annotation_File {

public:
	String file_name;

	void search_annotation_file();

	void save_annotation_file();

	Annotation_file_handler();
};

#endif
