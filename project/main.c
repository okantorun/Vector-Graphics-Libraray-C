#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "myheader.h"

int main(){

	 Point2D *traver;
	 Point2D *start_roi;
	 Point2D *end_roi;
	 Color c;
	 Figure *fig1,*fig2,*fig3,*fig4,*fig5;
	 /********************************************************/
	 c.red=0;
	 c.blue=0;
	 c.green=1;
	 fig1 = start_figure(500,250);
	 set_thickness_resolution(fig1,1,2);
	 set_color(fig1,c);
	 draw_fx(fig1,tan,0,100);
	 export_eps(fig1,"draw_f(x)");
	 /********************************************************/
	 c.red=0;
	 c.blue=1;
	 c.green=0;

	 fig2=(Figure*)malloc(sizeof(Figure));
	 fig2= start_figure(500,250);
	 set_thickness_resolution(fig2,1,0.5);
	 set_color(fig2,c);
	 draw_polyline(fig2,traver,5);
	 export_eps(fig2,"draw_polyline");

	 /**********************************************************/
	 fig3=(Figure*)malloc(sizeof(Figure));
	 fig3= start_figure(500,250);
	 set_thickness_resolution(fig3,1,0.5);
	 set_color(fig3,c);
	 draw_polygon(fig3,traver);
	 export_eps(fig3,"draw_polygon");
	/*************************************************ELLİPSE*/

	c.red=0;
	c.blue=1;
	c.green=1;
    Point2D* centre=(Point2D*)malloc(sizeof(Point2D));
	Point2D* width_height=(Point2D*)malloc(sizeof(Point2D));
	centre->x=20.0;
	centre->y=20.0;
	width_height->x=50;
	width_height->y=10;

	fig4=(Figure*)malloc(sizeof(Figure));
	fig4= start_figure(500,250);
	set_thickness_resolution(fig4,1,0.5);
	set_color(fig4,c);
	draw_ellipse(fig4, centre, width_height);
    export_eps(fig4,"draw_ellipse");
  
     /*******************************************************APPEND*/
    c.red=1;
	c.blue=0;
	c.green=0;
    fig5=(Figure*)malloc(sizeof(Figure));
    fig5= start_figure(500,250);
    set_thickness_resolution(fig5,1,0.5);
	set_color(fig5,c);
    draw_ellipse(fig5,centre,width_height);
     
	append_figures(fig5,fig1);
	export_eps(fig5,"append.eps");
	/***************************************************************RESİZED_ELLİPSE*/
	end_roi=(Point2D*)malloc(sizeof(Point2D));
    start_roi=(Point2D*)malloc(sizeof(Point2D));
    start_roi->x=-150;
	start_roi->y=0;
	end_roi->x=0;
	end_roi->y=150;
	resize_figure(fig4, start_roi, end_roi);
	export_eps(fig4,"resize_ellipse");

	

	
     
	 return 0;
}