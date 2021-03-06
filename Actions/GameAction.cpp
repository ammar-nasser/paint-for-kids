#include <assert.h>

#include "GameAction.h"

#include "..\ApplicationManager.h"

GameAction::GameAction(ApplicationManager* pApp, CFigure** figs, const int size, ActionType& actionAfterPlay)
    :
    Action(pApp),
    FiguresDrawn(figs),
    nOfFiguresDrawn(size),
    playAction(actionAfterPlay),
    rng(rd())
{
    assert(size > 0);
    pOut = pManager->GetOutput();
    pIn = pManager->GetInput();
    pointClicked = { 0, 0 };
    nOfRightAns = 0;
    nOfWrongAns = 0;
    gameLable = "NOT_YET";
}


void GameAction::ReadActionParameters()
{
    printGameState();
    playAction = pIn->GetUserAction(pointClicked);
}

void GameAction::Execute()
{
    ReadActionParameters();

    while (!isControlActoin(playAction))
    {
 
        CFigure* fig = pManager->GetFigure(pointClicked);

        if (fig != NULL)
        {
            if (isRightChoise(fig))
                nOfRightAns++;
            else//wrong choise
                nOfWrongAns++;

            fig->setHidden(true);
            pManager->UpdateInterface();
            printGameState();
        }

        if (isGameOver())
        {
            printGrade();

            //the game is over the user should choose a control action
            do
            {
                playAction = pIn->GetUserAction();
            } while (!isControlActoin(playAction));
            break;
        }

        playAction = pIn->GetUserAction(pointClicked);

    }

    pOut->drawCleanStatusBar();
}

bool GameAction::isControlActoin(ActionType act) const
{
    return act == RE_PLAY || act == TO_DRAW || act == SHAPE_ONLY
        || act == SHAPE_N_CLR || act == CLR_ONLY || act == AREA;
}

bool GameAction::isGameOver() const
{
    //game is over when no more right choices
    for (int i = 0; i < nOfFiguresDrawn; i++)
    {
        if (!FiguresDrawn[i]->isHidden())
            if (isRightChoise(FiguresDrawn[i]))
                return false;
    }
    return true;
}

void GameAction::printGameState() const
{
    pOut->PrintMessage("Choose All " + gameLable + " figures, Correct Answers: "
        + std::to_string(nOfRightAns) + " Woring Answers: " + std::to_string(nOfWrongAns));
}

void GameAction::printGrade() const
{
    pOut->PrintMessage("Game Over, Your Grade is " + std::to_string(nOfRightAns) + " out Of " +
        std::to_string(nOfRightAns + nOfWrongAns) + " You can rePlay or switch to draw mode");
}

void GameAction::setGameLabel(std::string str)
{
    gameLable = str;
}


GameAction::~GameAction()
{
    for (int i = 0; i < nOfFiguresDrawn; i++)
    {
        FiguresDrawn[i]->setHidden(false);
    }
}