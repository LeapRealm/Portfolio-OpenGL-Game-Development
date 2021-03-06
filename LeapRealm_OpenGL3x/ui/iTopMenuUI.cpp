#include "iTopMenuUI.h"

#include "iDimmedUI.h"
#include "iEquipUI.h"
#include "iInventoryUI.h"
#include "iPauseUI.h"
#include "iCreditUI.h"
#include "iSettingUI.h"
#include "iWindow.h"

#define TopMenuHeight 80

iPopup* topMenuUI;
static iImage* imgBg;
iImage** imgTopMenuBtn;

void drawTopMenuBefore(float dt, iPopup* pop);

void loadTopMenuUI()
{
	iPopup* pop = new iPopup();
	iGraphics* g = new iGraphics();

	igImage* icon[5];
	for (int i = 0; i < 5; i++)
		icon[i] = iGraphics::createIgImage("assets/ui/btn_icon_%d.png", i);

	// Background
	iSize size = iSizeMake(devSize.width, TopMenuHeight);
	g->init(size);

	setRGBA(0.39f, 0.40f, 0.44f, 0.4f);
	g->fillRect(0, 0, size.width, size.height);

	Texture* tex = g->getTexture();
	iImage* img = new iImage();
	img->addTexture(tex);
	freeTexture(tex);

	pop->addImage(img);
	imgBg = img;

	// imgTopMenuBtn[5]
	// Pause, Inven, Equip, Map, Setting
	size = iSizeMake(60, 60);

	imgTopMenuBtn = new iImage * [5];
	for (int i = 0; i < 5; i++)
	{
		img = new iImage();
		for (int j = 0; j < 2; j++)
		{
			g->init(size);

			if (j == 0)
				setRGBA(1, 1, 1, 1);
			else
				setRGBA(1, 1, 1, 0.6f);

			g->drawIgImage(icon[i], 0, 0);

			tex = g->getTexture();
			img->addTexture(tex);
			freeTexture(tex);
		}

		pop->addImage(img);
		imgTopMenuBtn[i] = img;
	}

	imgTopMenuBtn[0]->position = iPointMake(10, 10);
	imgTopMenuBtn[1]->position = iPointMake((devSize.width - size.width) / 2 - (size.width * 2), 10);
	imgTopMenuBtn[2]->position = iPointMake((devSize.width - size.width) / 2, 10);
	imgTopMenuBtn[3]->position = iPointMake((devSize.width - size.width) / 2 + (size.width * 2), 10);
	imgTopMenuBtn[4]->position = iPointMake(devSize.width - 10 - size.width, 10);

	pop->style = iPopupStyleMove;
	pop->openPoint = iPointMake(0, -TopMenuHeight);
	pop->closePoint = iPointZero;
	pop->methodDrawBefore = drawTopMenuBefore;

	setRGBA(1, 1, 1, 1);

	for (int i = 0; i < 5; i++)
		delete icon[i];
	topMenuUI = pop;
	delete g;
}

void freeTopMenuUI()
{
	delete topMenuUI;
	delete imgTopMenuBtn;
}

void drawTopMenuBefore(float dt, iPopup* pop)
{
	for (int i = 0; i < 5; i++)
		imgTopMenuBtn[i]->frame = (i == topMenuUI->selected);
}

void drawTopMenuUI(float dt)
{
	topMenuUI->paint(dt);
}

bool keyTopMenuUI(iKeyState state, iPoint p)
{
	if (topMenuUI->isShow == false)
		return false;
	if (topMenuUI->state != iPopupStateProc)
		return true;

	int j = -1;

	switch (state)
	{
	case iKeyStateBegan:
	{
		int s = topMenuUI->selected;
		if (s == -1)
			break;

		if (s == 0)
		{
			audioPlay(snd_eff_mouse_click);
			showDimmedUI(true);
			showPauseUI(true);
		}
		else if (s == 1)
		{
			showEquipUI(true);
		}
		else if (s == 2)
		{
			showInventoryUI(true);
		}
		else if (s == 3)
		{
			showCreditUI(true);
		}
		else
		{
			audioPlay(snd_eff_mouse_click);
			showDimmedUI(true);
			showSettingUI(true);
		}
		break;
	}

	case iKeyStateMoved:
	{
		for (int i = 0; i < 5; i++)
		{
			if (containPoint(p, imgTopMenuBtn[i]->rect(topMenuUI->closePoint)))
			{
				j = i;
				break;
			}
		}

		if (topMenuUI->selected != j && j != -1)
			audioPlay(snd_eff_mouse_hover);

		topMenuUI->selected = j;
		break;
	}

	case iKeyStateEnded:
	{

		break;
	}
	}

	if (containPoint(p, imgBg->rect(topMenuUI->closePoint)))
	{
		return true;
	}

	return false;
}

void showTopMenuUI(bool isShow)
{
	topMenuUI->show(isShow);
}
