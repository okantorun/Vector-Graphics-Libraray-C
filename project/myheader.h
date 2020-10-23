#ifndef _MYHEADER_H
#define _MYHEADER_H

typedef struct P2D{

 double x,y;
 struct P2D *nextp;
 
}Point2D;

typedef struct color{
 	double red,green,blue; 
 	
}Color;

typedef struct Figure{
	 double width, height;
	 double thickness,resolution;
	 Color color;
	 Point2D *point;
	 double str_roi_x;
	 double str_roi_y;
	 double end_roi_x;
     double end_roi_y;

	
}Figure;

Figure * start_figure(double width, double height);
void set_thickness_resolution(Figure *fig,double thickness,double resolution);
void set_color(Figure * fig, Color c);
void draw_fx(Figure * fig, double f(double x), double start_x, double end_x);
void draw_polyline(Figure *fig,Point2D * poly_line, int n);
void draw_polygon(Figure *fig,Point2D * poly_line);
void draw_ellipse(Figure* fig,Point2D * centre, Point2D * width_height);
void resize_figure(Figure *fig,Point2D *start_roi, Point2D *end_roi);
void merge(Point2D *root_p,double x,double y);
void append_figures(Figure * fig1, Figure * fig2);
void export_eps(Figure * fig, char * file_name);
#endif
