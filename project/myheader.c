#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "myheader.h"
#define PI 3.14


Figure * start_figure(double width, double height){
	Figure *f;
	f=(Figure*)malloc(sizeof(Figure));
	f->width=width;
	f->height=height;
	return f;

}
void set_thickness_resolution(Figure *fig,double thickness,double resolution){
	fig->thickness=thickness;
	fig->resolution=resolution;

}

void set_color(Figure * fig, Color c){
	
	fig->color.red=c.red;
	fig->color.green=c.green;
	fig->color.blue=c.blue;
}



void draw_fx(Figure * fig, double f(double x), double start_x, double end_x)
{

	 Point2D *root; 
	 root=(Point2D*)malloc(sizeof(Point2D));
	 fig->point=root; 
	 root->x=start_x;
	 root->y=f(start_x);

	 for(double x=start_x+fig->resolution;x<=end_x; x+=fig->resolution){
	 	root->nextp = (Point2D*)malloc(sizeof(Point2D));
	 	root=root->nextp;
	 	root->x=x;
	 	root->y=f(x);

	 }
	
 
}


void draw_polyline(Figure *fig,Point2D * poly_line, int n){

	int i;
	double width,height;
	

	poly_line=(Point2D*)malloc(sizeof(Point2D));
	fig->point=poly_line;
	poly_line->y=fig->height/2;
	poly_line->x=fig->width/2;
	srand(time(NULL));
	for(i=1;i<n;i++){

		
		poly_line->nextp=(Point2D*)malloc(sizeof(Point2D));
		poly_line->nextp->x=rand()%100;

		
		poly_line->y=rand() % 100;
		poly_line=poly_line->nextp;
	}
	poly_line->nextp=NULL;


	
}
void draw_polygon(Figure *fig,Point2D * poly_line){
	draw_polyline(fig,poly_line,5);


}


void draw_ellipse(Figure* fig,Point2D * centre, Point2D * width_height){
	double i;
	double c_x,c_y;

	Point2D *root=(Point2D*)malloc(sizeof(Point2D));
	c_x=centre->x;
	c_y=centre->y;
	fig->point=root;

	for (i=0;i<=360; i=i+fig->resolution){
		 root->x=c_x+(width_height->x*(cos(i*PI/180.0)));
		 root->y=c_y+(width_height->y*(sin(i*PI/180.0)));
		 root->nextp=(Point2D*)malloc(sizeof(Point2D));
		 root=root->nextp;
		
	 }
	 root->nextp=NULL;
}
/*void scale_figure (Figure * fig , double scale_x, double scale_y){

}*/
void resize_figure(Figure *fig,Point2D *start_roi, Point2D *end_roi){
	
	fig->width =fabs (end_roi->x - start_roi->x);
	fig->height = fabs(end_roi->y - start_roi->y);
	
}
void merge(Point2D *root_p,double x,double y){
	Point2D *traver_p,*new_p;

	traver_p = root_p; 
	while(traver_p->nextp!=NULL)
		traver_p=traver_p->nextp; 

	new_p = (Point2D*)malloc(sizeof(Point2D));
	new_p->x=x;
	new_p->y=y;									//we have reached the last point of the first figure and created the points

	traver_p->nextp=new_p;
}
void append_figures(Figure * fig1, Figure * fig2){
	Point2D *rootp=fig1->point;

	merge(fig1->point,fig2->point->x,fig2->point->y); 

	while(rootp->nextp!=NULL)
		rootp=rootp->nextp;
	rootp->nextp=fig2->point->nextp;			//we connected the second figure to the last point of the first figure,and we've appended the two figures.
}

void export_eps(Figure * fig, char * file_name){
	int i;
	Point2D *traver,*okan; 
	okan=traver;
	
	FILE *fp1;
	fp1=fopen(file_name,"w");
	fclose(fp1);
	FILE *fp;
	fp=fopen(file_name,"a");
	fprintf(fp, "%%!PS-Adobe-3.0 EPSF-3.0\n");
	fprintf(fp, "%%%%BoundingBox:%d %d %d %d\n",0,0,(int)fig->width,(int)fig->height);
	fprintf(fp,"%d setlinewidth\n",(int)fig->thickness);
	fprintf(fp, "%d %d %d setrgbcolor\n",(int)fig->color.red,(int)fig->color.green,(int)fig->color.blue);
	fprintf(fp,"\n%.1f %.1f moveto",fig->width/2.0,fig->height/2.0);
	
	
 	if(strcmp(file_name,"draw_polygon")==0){
 		printf("okan");
	 	traver=fig->point->nextp;
	 	while(traver->nextp!=NULL){
	 		fprintf(fp,"\n%.1f %.1f lineto",traver->x+fig->width/2.0,traver->y+fig->height/2.0);
	 		traver=traver->nextp;
	 	}
	 	fprintf(fp,"\nclosepath");
	 	fprintf(fp,"\nstroke\n");
 	}
 	else if(strcmp(file_name,"draw_polyline")==0){
 		printf("okan\n");
	 	traver=fig->point->nextp;
	 	while(traver->nextp!=NULL){
	 		fprintf(fp,"\n%.1f %.1f lineto",traver->x+fig->width/2.0,traver->y+fig->height/2.0);
	 		traver=traver->nextp;
	 	}

	 	fprintf(fp,"\nstroke\n");
 	}

 	else{
 		traver=fig->point->nextp;
	 	while(traver->nextp!=NULL){
	 		fprintf(fp,"\n%.1f %.1f lineto",traver->x+fig->width/2.0,traver->y+fig->height/2.0);
	 		traver=traver->nextp;
 		}
 		fprintf(fp,"\nstroke\n");
 	}
 	fclose(fp);

}

