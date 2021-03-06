#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"
#include "ToolBar.h"
#include "ColorWin.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;		//Pointer to the Graphics Window
	ToolBar* toolBar;	//Pointer to the play toolbar
	ColorWin* clrWin;
	//private funcitons
private:
	void clearToolBar() const;			//clears the toolbar
public:
	Output();		

	window* CreateWind(int, int, int , int) const; //creates the application window
	Input* CreateInput()  const;		//creates a pointer to the Input object	
	void openClrWin(WindowColorType);			//create and open clr window
	void closeClrWin();					//close and free the memory of color win

	//this funciton MUST be called whenever the user change the inerface mode.
	//drawing the toolbar according to the UI.InterfaceMode
	void drawToolBar()  const;			//this funciton MUST be called 
	void drawCleanStatusBar() const;	//Clears the status bar
	void ClearDrawArea()  const;		//Clears the drawing area
	void PrintMessage(string msg) const;	//Print a message on Status bar

	void zoomIn() const;
	void zoomOut() const;

	void highlightItem(int);
	void UnhighlightItem(int);
	
	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a rectangle
	void DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected = false) const; //Draw a line
	void DrawCirc(Point P1, int r, GfxInfo CircleGfxInfo, bool selected = false) const; //Draw a circle
	void DrawTri(Point P1, Point P2,Point P3, GfxInfo TriGfxInfo, bool selected = false) const; //Draw a Triangle


	color getCrntDrawColor() const;			//get current drwawing color
	color getCrntFillColor() const;			//get current filling color
	int getCrntPenWidth() const;			//get current pen width
	color getChangedColor() const;			//get color to change from color window

	
	~Output();
};

#endif