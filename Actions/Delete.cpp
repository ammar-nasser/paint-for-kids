#include "Delete.h"
#include "..\ApplicationManager.h"
Delete::Delete(ApplicationManager* pApp, CFigure** selectedFigs, const int size)
	:
	Action(pApp),
	figsToDelete(selectedFigs), 
	nToDeleted(size)
{
}

void Delete::ReadActionParameters()
{
	//already readed by select action, i.e. selected figure will be deleted
}

void Delete::Execute()
{
	pManager->deleteFigures(figsToDelete, nToDeleted);
}

Delete::~Delete()
{
	pManager->GetOutput()->UnhighlightItem(ITM_DEL);
}
