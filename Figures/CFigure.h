#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\Output.h"
#include <fstream>

//Base class for all figures
static int newID = 0; //used to increments ID's

class CFigure
{
protected:
	int ID;			//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	float area;	
	Point center;
	GfxInfo FigGfxInfo;	//Figure graphis info

	
	bool hidden; // ture if the figure is hidden
	FigureType figType;//figure type see DEFS.h
	FigureColorType colortype;//figureColorType see DEFS.h

	
	drawColorType drawclr;//enum used to determine drawing color
	fillColorType fillclr;//enum used to determine fill color
	figureType figtype;//enum used to determine figure type

public:
	CFigure(GfxInfo FigureGfxInfo);
	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	virtual void Draw(Output* pOut) const  = 0 ;		//Draw the figure


	int FromClrToInt(color c);//used to be able to save colors as intgers in save files
	virtual void Resize(float r) = 0;                   //Resize figures
	virtual void PrintInfo(Output* pOut) const = 0;	//print all figure info on the status bar
	virtual void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	virtual void ChngFillClr(color Fclr);	//changes the figure's filling color
	virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file

	
	//Actions member functions
	virtual bool isInsideMe(Point clickedPoint) const = 0;	//check if the point is inside the figure
	virtual void Move(Point newPoint) = 0;		//Move the figure
	virtual void moveBy(Vec2 incr);//moving the critical point by the incremantal vector and then move the whole figure to that new point				
	virtual Point getCriticalPoint() const = 0;
	virtual CFigure* getCopy()const = 0;

	//play mode member functions
	void setHidden(bool h);
	bool isHidden() const;
	virtual bool isMyType(FigureType type) const;		//check if is the same type
	virtual bool isMyFigColorType(FigureColorType figClrType) const; //check is the same color type
	virtual float getArea()const;						//return area
	
private:
	//play mode needs to know the color type of each figure, this function update the color type, if changed
	void changeColorType(color clr); // takes color and change colorType according to that clr

};


#endif