#ifndef IMAGE FILE HANDLER_H
#define IMAGE FILE HANDLER_H

class Image_file_handler {

public:
	String directory;
	String sort_type;

	void sort_ascending_time();

	void sort_descending_time();

	void sort_ascending_name();

	void sort_descending_name();

private:
	void eligible_images();

public:
	Image_file_handler();
};

#endif
