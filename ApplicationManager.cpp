#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddLineAction.h"
#include "Actions\AddCircleAction.h"
#include "Actions\AddTriAction.h"
#include "Actions\ChangeColorActions\ChngBkgndClr.h"
#include "Actions\ChangeColorActions\ChngDrawClr.h"
#include "Actions\ChangeColorActions\ChngFillClr.h"
#include "Actions\Select.h"
#include "Actions\Save.h"

Point ApplicationManager::point = { 0, 0 };

void ApplicationManager::reArrangeFigList(int deletedFigs)
{
	int nOfUnDeletedFigs = FigCount - deletedFigs;

	//figList is called by deleteFigures and there are some figures need to be reArranged
	//first getting the notNulled figures from figList
	CFigure** notNulledFigures = new CFigure * [nOfUnDeletedFigs]();//initialize them to NULL
	for (int i = 0, j = 0; i < FigCount && j < nOfUnDeletedFigs; i++)
	{
		if (FigList[i] != NULL)//store it in notNulledFigures
		{
			notNulledFigures[j] = FigList[i];
			FigList[i] = NULL;
			j++;
		}
	}
	//reArrange figList to only contain the notNUlledfigures
	for (int i = 0; i < nOfUnDeletedFigs; i++)
	{
		FigList[i] = notNulledFigures[i];
	}
	delete[] notNulledFigures;
}

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction(Point& p) const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction(p);		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case DRAWING_AREA:
		std::cout << "Action: DRAWING_AREA" << std::endl;
		break;
	case STATUS:		//a click on the status bar ==> no action
		std::cout << "Action: STATUS" << std::endl;
		break;
	case EMPTY:
		std::cout << "Action: EMPTY" << std::endl;
		break;
	case TO_DRAW:
		UI.InterfaceMode = MODE_DRAW;
		pOut->drawToolBar();
		std::cout << "Action: TO_DRAW" << std::endl;
		break;
	case TO_PLAY:
		UI.InterfaceMode = MODE_PLAY;
		pOut->drawToolBar();
		std::cout << "Action: TO_PLAY" << std::endl;
		break;
	case DRAW_LINE:
		std::cout << "Action: DRAW_LINE" << std::endl;
		pAct = new AddLineAction(this);
		break;
	case DRAW_RECT:
		std::cout << "Action: DRAW_RECT" << std::endl;
		pAct = new AddRectAction(this);
		break;
	case DRAW_TRI:
		std::cout << "Action: DRAW_TRI" << std::endl;
		pAct = new AddTriAction(this);
		break;
	case DRAW_CIRC:
		std::cout << "Action: DRAW_CIRC" << std::endl;
		pAct = new AddCircleAction(this);
		break;
	case CHNG_DRAW_CLR:
		std::cout << "Action: CHNG_DRAW_CLR" << std::endl;
		pAct = new ChngDrawClr(this);
		break;
	case CHNG_FILL_CLR:
		std::cout << "Action: CHNG_FILL_CLR" << std::endl;
		pAct = new ChngFillClr(this);
		break;
	case CHNG_BK_CLR:
		std::cout << "Action: CHNG_BK_CLR" << std::endl;
		pAct = new ChngBkgndClr(this);
		break;
	case SELECT:
		std::cout << "Action: SELECT" << std::endl;
		pAct = new Select(this);
		break;
	case DEL:
		std::cout << "Action: DEL" << std::endl;
		break;
	case MOVE:
		std::cout << "Action: MOVE" << std::endl;
		break;
	case COPY:
		std::cout << "Action: COPY" << std::endl;
		break;
	case CUT:
		std::cout << "Action: CUT" << std::endl;
		break;
	case PASTE:
		std::cout << "Action: PASTE" << std::endl;
		break;
	case RESIZE:
		std::cout << "Action: RESIZE" << std::endl;
		break;
	case ROTATE:
		std::cout << "Action: ROTATE" << std::endl;
		break;
	case SEND_BACK:
		std::cout << "Action: SEND_BACK" << std::endl;
		break;
	case BRNG_FRNT:
		std::cout << "Action: BRNG_FRNT" << std::endl;
		break;
	case SAVE:
		std::cout << "Action: SAVE" << std::endl;
		pAct = new Save(this);
		break;
	case LOAD:
		std::cout << "Action: LOAD" << std::endl;
		break;
	case REDO:
		std::cout << "Action: REDO" << std::endl;
		break;
	case UNDO:
		std::cout << "Action: UNDO" << std::endl;
		break;
	case RE_PLAY:
		std::cout << "Action: RE_PLAY" << std::endl;
		break;
	case SHAPE_ONLY:
		std::cout << "Action: SHAPE_ONLY" << std::endl;
		break;
	case CLR_ONLY:
		std::cout << "Action: CLR_ONLY" << std::endl;
		break;
	case SHAPE_N_CLR:
		std::cout << "Action: SHAPE_N_CLR" << std::endl;
		break;
	case AREA:
		std::cout << "Action: AREA" << std::endl;
		break;
	case EXIT:
	{
		pOut->PrintMessage(std::string("<< choose 1 if you want to save and choose 0 if you want to close >>"));//checks if user will save or close
		bool choice = bool (std::stoi(pIn->GetSrting(pOut)));
		pOut->drawCleanStatusBar();
		if (choice == true)
		{
			pAct = new Save(this);
			pAct->Execute();//Execute
			delete pAct;	//Action is not needed any more ==> delete it
			pAct = NULL;
			break;
		}
		else
		{
			std::cout << "Action: EXIT" << std::endl;
			break;
		}
	}
	default:
		break;
	}
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
void ApplicationManager::deleteFigures(CFigure** figsArray, const int size)
{
	int deletedCount = 0;//counter to count the deleted figures
	for (int i = 0; i < size; i++)
	{
		if (figsArray[i] != NULL)//the fig is selected
		{
			delete GetFigure(figsArray[i]);
			GetFigure(figsArray[i]) = NULL;
			figsArray[i] = NULL;//must be nulled here also 
			deletedCount++;
		}
	}
	//rearrange FigList
	reArrangeFigList(deletedCount);
	//need to resize the figList and figCount
	FigCount -= deletedCount;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(Point p) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL

	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->isInsideMe(p))
			return FigList[i];
	}

	return NULL;
}
CFigure* ApplicationManager::GetFigure(int index) const
{
	if(index < FigCount)
		return FigList[index];
}
CFigure*& ApplicationManager::GetFigure(CFigure* fig) 
{
	
	for (int i = 0; i < FigCount; i++)
		if (FigList[i] == fig)
			return FigList[i];

}
int ApplicationManager::getFigCount() const
{
	return FigCount;
}
int ApplicationManager::getIndexOf(CFigure* fig) const
{
	if (fig != NULL)
	{
		for (int i = 0; i < FigCount; i++)
			if (fig == FigList[i])
				return i;
	}
	return -1;
}
int ApplicationManager::FromClrToInt(color c)
{
	if (c.ucBlue == BLACK.ucBlue && c.ucGreen == BLACK.ucGreen && c.ucRed == BLACK.ucRed)
		return 0;
	else if (c.ucBlue == GRAY.ucBlue && c.ucGreen == GRAY.ucGreen && c.ucRed == GRAY.ucRed)
		return 1;
	else if (c.ucBlue == BLUE.ucBlue && c.ucGreen == BLUE.ucGreen && c.ucRed == BLUE.ucRed)
		return 2;
	else if (c.ucBlue == CYAN.ucBlue && c.ucGreen == CYAN.ucGreen && c.ucRed == CYAN.ucRed)
		return 3;
	else if (c.ucBlue == GREEN.ucBlue && c.ucGreen == GREEN.ucGreen && c.ucRed == GREEN.ucRed)
		return 4;
	else if (c.ucBlue == YELLOW.ucBlue && c.ucGreen == YELLOW.ucGreen && c.ucRed == YELLOW.ucRed)
		return 5;
	else if (c.ucBlue == BROWN.ucBlue && c.ucGreen == BROWN.ucGreen && c.ucRed == BROWN.ucRed)
		return 6;
	else if (c.ucBlue == ORANGE.ucBlue && c.ucGreen == ORANGE.ucGreen && c.ucRed == ORANGE.ucRed)
		return 7;
	else if (c.ucBlue == RED.ucBlue && c.ucGreen == RED.ucGreen && c.ucRed == RED.ucRed)
		return 8;
	else //if called by color then 9 means white if it is called by fill the it is nofill
		return 9;
}
void ApplicationManager::saveData(ofstream &OutFile)
{
	OutFile << FromClrToInt(UI.DrawColor) << "," << FromClrToInt(UI.FillColor) << "," << FromClrToInt(UI.BkGrndColor) << std::endl;
	OutFile << FigCount << std::endl;
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(OutFile);
	}
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pOut->ClearDrawArea();
	for(int i=0; i<FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
	
}
