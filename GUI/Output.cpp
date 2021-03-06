#include "Output.h"
#include <assert.h>

Output::Output()
{
	//Initialize the toolbars of the two modes
	UI.MaxNItems			= (DRAW_ITM_COUNT > PLAY_ITM_COUNT) ? DRAW_ITM_COUNT : PLAY_ITM_COUNT;

	//this is just one tool bar that will draw itself according to the program mode 
	//it contains the max number of items that can be in draw or play mode so no need for doublicating
	//items, each MenuItem in the tool bar can draw itself according to the index and state and mode,
	//for more information see MenuItem.h
	toolBar = new ToolBar(UI.MaxNItems);

	//DToolBar = new ToolBar(DRAW_ITM_COUNT);
	//Initialize user interface parameters
	UI.InterfaceMode		= MODE_DRAW;
	UI.FreeSpaceInToolBar	= 3;
	UI.MenuItemWidth		= 48;
	UI.MenuItemHeight		= 48;
	UI.BarPadding			= 2;

	UI.width				= UI.MaxNItems * UI.MenuItemWidth + UI.FreeSpaceInToolBar * UI.MenuItemWidth;
	UI.height				= UI.MenuItemHeight * UI.MaxNItems - UI.FreeSpaceInToolBar * UI.MenuItemWidth;
	//UI.height = 800;
	UI.wx					= 200;//the window x position relative to the screen
	UI.wy					= 10;//the window y position relative to the screen // to fit Mohammad screen

	
	UI.StatusBarHeight		= UI.MenuItemHeight + UI.BarPadding;
	UI.ToolBarHeight		= UI.MenuItemHeight + UI.BarPadding;

	UI.ToolBarColor			= color(250, 255, 204);		//toolbar color
	UI.DrawColor			= BLUE;						//Drawing color
	UI.FillColor			= WHITE;					//Filling color
	UI.MsgColor				= BLACK;					//Messages color
	UI.BkGrndColor			= WHITE;					//Background color
	UI.HighlightColor		= color(163, 255, 252);		//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor		= color(250, 255, 204);		//same as the tool bar color
	UI.PenWidth				= 3;						//width of the figures frames

	UI.scalingFactor		= 1.0f;						//scaling factor to zoom IN and out
		
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids");
	//draw the toolbar
	drawToolBar();
	drawCleanStatusBar();

	//initialze the colorWin
	clrWin = NULL;
}

Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}

void Output::openClrWin(WindowColorType clrToChange)
{
	assert(clrWin == NULL);
	clrWin = new ColorWin(clrToChange);
}

void Output::closeClrWin()
{
	delete clrWin;
	std::cout << "color window deleted" << std::endl;
	clrWin = NULL;
}

void Output::zoomIn() const
{
	UI.scalingFactor *= 1.1f;
}

void Output::zoomOut() const
{
	UI.scalingFactor *= 0.9f;
}

void Output::highlightItem(int index)
{
	toolBar->hightlightItem(index);
}

void Output::UnhighlightItem(int index)
{
	toolBar->UnhightlightItem(index);
}

//////////////////////////////////////////////////////////////////////////////////////////
void Output::drawCleanStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);

	//draw black line above the bar
	pWind->SetPen(BLACK, UI.BarPadding);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight , UI.width, UI.height - UI.StatusBarHeight +1);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::drawToolBar() const
{
	clearToolBar();
	int nItems = UI.InterfaceMode == MODE_PLAY ? PLAY_ITM_COUNT : DRAW_ITM_COUNT;
	for (int i = 0; i < nItems; i++)
	{
		std::string itemPath = toolBar->getItem(i)->getPath();
		pWind->DrawImage(itemPath, i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.MenuItemHeight);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::clearToolBar() const
{
	//Clear Tool bar by drawing a filled rectangle
	pWind->SetPen(UI.ToolBarColor, 1);
	pWind->SetBrush(UI.ToolBarColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.MenuItemHeight);

	//Draw black line below the bar
	pWind->SetPen(BLACK, UI.BarPadding);
	pWind->DrawLine(0, UI.MenuItemHeight , UI.width, UI.MenuItemHeight + 1);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight , UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	drawCleanStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight*0.8f), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

color Output::getChangedColor() const
{
	return clrWin->getColorClicked();
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;
	
	//convert from world coordinate to screen coordinate
	worldToScreen(P1);
	worldToScreen(P2);
	
	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
	
}
void Output::DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected ) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = LineGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, LineGfxInfo.BorderWdth);

	
	drawstyle style = FRAME;

	//convert from world coordinate to screen coordinate
	worldToScreen(P1);
	worldToScreen(P2);

	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);

}
void Output::DrawCirc(Point P1, int r, GfxInfo CircleGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = CircleGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, CircleGfxInfo.BorderWdth);

	drawstyle style;
	if (CircleGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircleGfxInfo.FillClr);
	}
	else
		style = FRAME;

	//convert from world coordinate to screen coordinate
	worldToScreen(P1);
	r = int(r * UI.scalingFactor);

	pWind->DrawCircle(P1.x, P1.y, r, style);
}
void Output::DrawTri(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = TriGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, TriGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (TriGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriGfxInfo.FillClr);
	}
	else
		style = FRAME;

	//convert from world coordinate to screen coordinate
	worldToScreen(P1);
	worldToScreen(P2);
	worldToScreen(P3);

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);

}


//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
	delete toolBar;
}

