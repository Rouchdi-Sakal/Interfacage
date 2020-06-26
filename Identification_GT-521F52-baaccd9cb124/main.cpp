#include "mbed.h"
#include "logo.h"
#include "GT511C3.hpp"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"

// init la com serie et du capteur
Serial pc(USBTX, USBRX,9600); // tx, rx
GT511C3 finger(D1,D0);

int pass = 2606;
int code = 0;
int multi = 1;
int id;
uint8_t text[30];
int EnrollID = -1;
unsigned char data[498];
int identificateur;
//variable

void touch_screen();
void init_lcd();
void font_clavier(int on_off);
void font_menu_principal_simple(int on_off);
void font_menu_principal_add(int on_off);
void font_menu_principal(int on_off);
void touch_screen_simple();
void touch_screen_add();
void menu_principal();
void identifier();
void identifier_add();
void ajouter_finger();
void init_finger();
void drawImageLogo(int offsetX, int offsetY);
void codetouche(int touche,int multi);
int menu_clavier();
int progress(int status,char *msg);
//fonction


//affichage de message
int progress(int status,char *msg)
{
    pc.printf("%s\r\n",msg);
    BSP_LCD_ClearStringLine(1);
    sprintf((char*)text,"%s",msg);
    BSP_LCD_DisplayStringAt(0, LINE(1), (uint8_t *)&text, CENTER_MODE );
    return 0;
}
// recuperation du code taper
void codetouche(int touche,int multi)
{
    if (code == 0) {
        code = touche;
        pc.printf("code: %d",code);
        sprintf((char*)text,"code: %d",code);//valider
        BSP_LCD_DisplayStringAt(0, LINE(2), (uint8_t *)&text, RIGHT_MODE);
    } else {
        code *= multi;
        code += touche;
        pc.printf("code: %d",code);
        sprintf((char*)text,"code: %d ",code);//valider
        BSP_LCD_DisplayStringAt(0, LINE(2), (uint8_t *)&text, RIGHT_MODE);
    }
    if(code == pass) {
        code = 0;
        identificateur = 1;
    }
}
// affiche le logo de l'IUT
void drawImageLogo(int offsetX, int offsetY)
{
    int x = 0;
    int y = 0;
    uint32_t* dataPtr = (uint32_t*)logo.data;
    while(y < logo.height) {
        while(x < logo.width) {
            BSP_LCD_DrawPixel(x + offsetX, y + offsetY, *dataPtr);
            dataPtr++;
            x++;
        }
        x = 0;
        y++;
    }
}
// initialisation du capteur
void init_finger()
{
    int sts = 0;
    //int EnrollID = -1;
    unsigned char data[498];

    pc.format(8,Serial::None,1);
    pc.printf("Hello World\n\r");
    pc.printf("Fingerprint reader module \"GT-511C3 / GT-511C31\" test program.\n\r");
    pc.printf("Build: %s %s\n\r",__DATE__,__TIME__);
    pc.printf("Open\n\r");
    sts = finger.Open();
    pc.printf("sts = %d\n\r",sts);

    if(sts == 0) {
        int i;
        pc.printf("FirmwareVersion = %lx\n\r",finger.FirmwareVersion);
        pc.printf("IsoAreaMaxSize = %ld\n\r",finger.IsoAreaMaxSize);
        pc.printf("DeviceSerialNumber = ");
        for(i = 0; i < sizeof(finger.DeviceSerialNumber); i++) {
            pc.printf("%02X",finger.DeviceSerialNumber[i]);
        }
        pc.printf("\n\r");
    }
}
// ajout d'empreinte
void ajouter_finger()
{
    EnrollID++;
    finger.CmosLed( 1);
    finger.Enroll(EnrollID, progress);
    pc.printf("SetTemplate = %d\n", finger.SetTemplate(11,data,498));
    finger.CmosLed(0);
}
// fond pour le menu ajouter empreinte
void font_menu_principal_add(int on_off)
{
    uint8_t text[30];
    int touche = 0;

    if (on_off == 1) {
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(1), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(2), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(3), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(4), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(6), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(7), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(8), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(9), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(11), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(12), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(13), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(16), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(17), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(18), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(19), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(20), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(21), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(20), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(21), (uint8_t *)&text, CENTER_MODE );

        sprintf((char*)text, "   AJOUTER   ");
        BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)&text, LEFT_MODE );
        sprintf((char*)text, "   SUPPRIMER   ");
        BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)&text, RIGHT_MODE);
        sprintf((char*)text, "|   BACK  |");
        BSP_LCD_DisplayStringAt(0, LINE(1), (uint8_t *)&text, RIGHT_MODE );
    }
}
// permet de detecter les touches appuyer dans le menu ajouter
void touch_screen_add()
{
    TS_StateTypeDef TS_State;
    int touche= -1;
    uint16_t x, y;
    uint8_t text[30];
    uint8_t status;
    uint8_t idx;
    uint8_t cleared = 0;
    uint8_t prev_nb_touches = 0;

    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_Clear(LCD_COLOR_BLUE);
    while(1) {
        BSP_TS_GetState(&TS_State);
        font_menu_principal_add(1);
        if (TS_State.touchDetected) {
            if (TS_State.touchDetected < prev_nb_touches) {
                for (idx = (TS_State.touchDetected + 1); idx <= 5; idx++) {
                    BSP_LCD_ClearStringLine(idx);
                }
            }
            prev_nb_touches = TS_State.touchDetected;

            cleared = 0;

            //sprintf((char*)text, "Touches: %d", TS_State.touchDetected);
            //BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);

            for (idx = 0; idx < TS_State.touchDetected; idx++) {
                x = TS_State.touchX[idx];
                y = TS_State.touchY[idx];
                //sprintf((char*)text, "Touch %d: x=%d y=%d    ", touche, x, y);
                //BSP_LCD_DisplayStringAt(0, LINE(0)/*LINE(idx+1)*/, (uint8_t *)&text, LEFT_MODE);
            }

            if((x>=1 &&x<=70)&&(y>=120&&y<=140)) {

                sprintf((char*)text, "ajouter ");//1
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, RIGHT_MODE);
                ajouter_finger();
                BSP_LCD_Clear(LCD_COLOR_BLUE);
            }  else if((x>=380 &&x<=500)&&(y>=120&&y<=140)) {
                sprintf((char*)text,"Suprimer id");
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, RIGHT_MODE);
                finger.DeleteID(id);
                EnrollID = -1;
                touch_screen_simple();
            }  else if((x>=410 &&x<=500)&&(y>=20&&y<=40)) {
                sprintf((char*)text,"Back");
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                touch_screen_simple();
            }
        } else {
            //sprintf((char*)text,"code: %d",0);//valider
            //BSP_LCD_DisplayStringAt(0, LINE(2), (uint8_t *)&text, RIGHT_MODE);
        }
    }
}

void touch_screen_2()
{
    TS_StateTypeDef TS_State;
    int touche= -1;
    uint16_t x, y;
    uint8_t text[30];
    uint8_t status;
    uint8_t idx;
    uint8_t cleared = 0;
    uint8_t prev_nb_touches = 0;

    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_Clear(LCD_COLOR_BLUE);
    while(1) {
        BSP_TS_GetState(&TS_State);
        font_menu_principal_add(1);
        if (TS_State.touchDetected) {
            if (TS_State.touchDetected < prev_nb_touches) {
                for (idx = (TS_State.touchDetected + 1); idx <= 5; idx++) {
                    BSP_LCD_ClearStringLine(idx);
                }
            }
            prev_nb_touches = TS_State.touchDetected;

            cleared = 0;

            //sprintf((char*)text, "Touches: %d", TS_State.touchDetected);
            //BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);

            for (idx = 0; idx < TS_State.touchDetected; idx++) {
                x = TS_State.touchX[idx];
                y = TS_State.touchY[idx];
                //sprintf((char*)text, "Touch %d: x=%d y=%d    ", touche, x, y);
                //BSP_LCD_DisplayStringAt(0, LINE(0)/*LINE(idx+1)*/, (uint8_t *)&text, LEFT_MODE);
            }

            if((x>=1 &&x<=70)&&(y>=120&&y<=140)) {

                sprintf((char*)text, "ajouter ");//1
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, RIGHT_MODE);
                ajouter_finger();
                BSP_LCD_Clear(LCD_COLOR_BLUE);
            }  else if((x>=380 &&x<=500)&&(y>=120&&y<=140)) {
                sprintf((char*)text,"Suprimer id");
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, RIGHT_MODE);
                finger.DeleteID(id);
                EnrollID = -1;
                touch_screen();
            }  else if((x>=410 &&x<=500)&&(y>=20&&y<=40)) {
                sprintf((char*)text,"Back");
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                touch_screen();
            }
        } else {
            //sprintf((char*)text,"code: %d",0);//valider
            //BSP_LCD_DisplayStringAt(0, LINE(2), (uint8_t *)&text, RIGHT_MODE);
        }
    }
}

//permet d'identifier si l'empreinte est bien enregistre ou pas pour le menu ajouter
void identifier_add()
{
    finger.CmosLed(1);
    finger.WaitPress(1);
    if (finger.IsPress()!= 0) {
        finger.Capture(false);
        id = finger.Identify();
        if(id!=-1) {
            pc.printf("Student found!");
            BSP_LCD_SetFont(&Font24);
            BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
            BSP_LCD_Clear(LCD_COLOR_GREEN);
            sprintf((char*)text, "VALIDER");
            BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)&text, CENTER_MODE );
            HAL_Delay(1000);
            BSP_LCD_SetFont(&Font12);
            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            finger.CmosLed(0);
            touch_screen_add();
        } else {
            pc.printf("Student not found");
            BSP_LCD_SetFont(&Font24);
            BSP_LCD_SetBackColor(LCD_COLOR_RED);
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
            BSP_LCD_Clear(LCD_COLOR_RED);
            sprintf((char*)text, "REFUSER");
            BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)&text, CENTER_MODE );
            HAL_Delay(1000);
            BSP_LCD_SetFont(&Font12);
            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        }
        if (id <300) {
            pc.printf("Verified ID:%d",id);
        } else {
            pc.printf("Finger not found");
        }
    }
    finger.CmosLed(0);
}
//permet d'identifier si l'empreinte est bien enregistre ou pas
void identifier()
{
    finger.CmosLed(1);
    finger.WaitPress(1);
    if (finger.IsPress()!= 0) {
        finger.Capture(false);
        int id = finger.Identify();
        if(id!=-1) {
            pc.printf("Student found!");
            BSP_LCD_SetFont(&Font24);
            BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
            BSP_LCD_Clear(LCD_COLOR_GREEN);
            sprintf((char*)text, "VALIDER");
            BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)&text, CENTER_MODE );
            HAL_Delay(1000);
            BSP_LCD_SetFont(&Font12);
            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            identificateur = 2;
        } else {
            pc.printf("Student not found");
            BSP_LCD_SetFont(&Font24);
            BSP_LCD_SetBackColor(LCD_COLOR_RED);
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
            BSP_LCD_Clear(LCD_COLOR_RED);
            sprintf((char*)text, "REFUSER");
            BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)&text, CENTER_MODE );
            HAL_Delay(1000);
            BSP_LCD_SetFont(&Font12);
            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        }
        if ((id <300)&& (id > -1)) {
            pc.printf("Verified ID:%d",id);
            BSP_LCD_SetFont(&Font24);
            BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
            BSP_LCD_Clear(LCD_COLOR_GREEN);
            sprintf((char*)text, "Verified ID:%d",id);
            BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE );
            HAL_Delay(1000);
            BSP_LCD_SetFont(&Font12);
            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            identificateur = 2;
        } else {
            pc.printf("Finger not found");
            BSP_LCD_SetFont(&Font24);
            BSP_LCD_SetBackColor(LCD_COLOR_RED);
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
            BSP_LCD_Clear(LCD_COLOR_RED);
            sprintf((char*)text, "Finger not found");
            BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE );
            HAL_Delay(1000);
            BSP_LCD_SetFont(&Font12);
            BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        }
    }
    finger.CmosLed(0);
}
//fond pour le menu simple identification
void font_menu_principal_simple(int on_off)
{
    uint8_t text[30];
    int touche = 0;

    if (on_off == 1) {
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(1), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(2), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(3), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(4), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(6), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(7), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(8), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(9), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(11), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(12), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(13), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(16), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(17), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(18), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(19), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(20), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(21), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(20), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(21), (uint8_t *)&text, CENTER_MODE );

        sprintf((char*)text, "   IDENTIFICATION    ");
        BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)&text, LEFT_MODE );
        sprintf((char*)text, "        BACK         ");
        BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)&text, RIGHT_MODE );
    }
}
//fond pour le menu ajouter empreinte
void font_menu_add(int on_off)
{
    uint8_t text[30];
    int touche = 0;

    if (on_off == 1) {
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(1), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(2), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(3), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(4), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(6), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(7), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(8), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(9), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(11), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(12), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(13), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(16), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(17), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(18), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(19), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(20), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(21), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(20), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(21), (uint8_t *)&text, CENTER_MODE );

        sprintf((char*)text, "    IDENTIFICATION SIMPLE    ");
        BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)&text, RIGHT_MODE );
        sprintf((char*)text, "    DOUBLE IDENTIFICATION    ");
        BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)&text, LEFT_MODE );
    }
}
//fond pour le menu principal
void font_menu_principal(int on_off)
{
    uint8_t text[30];
    int touche = 0;

    if (on_off == 1) {
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(1), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(2), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(3), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(4), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(6), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(7), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(8), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(9), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(11), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(12), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(13), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(16), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(17), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(18), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(19), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(20), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(21), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(20), (uint8_t *)&text, CENTER_MODE );
        sprintf((char*)text, "|");
        BSP_LCD_DisplayStringAt(0, LINE(21), (uint8_t *)&text, CENTER_MODE );

        sprintf((char*)text, "    IDENTIFICATION SIMPLE    ");
        BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)&text, RIGHT_MODE );
        sprintf((char*)text, "    DOUBLE IDENTIFICATION    ");
        BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)&text, LEFT_MODE );
    }
}
//fond pour le clavier
void font_clavier(int on_off)
{
    uint8_t text[30];
    int touche = 0;

    if (on_off == 1) {
        sprintf((char*)text, "|   DEL   |");
        BSP_LCD_DisplayStringAt(0, LINE(1), (uint8_t *)&text, LEFT_MODE );

        sprintf((char*)text, "|   Back  |");
        BSP_LCD_DisplayStringAt(0, LINE(1), (uint8_t *)&text, RIGHT_MODE );

        sprintf((char*)text, "|   1   |");
        BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)&text, LEFT_MODE );

        sprintf((char*)text, "|   2   |");
        BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)&text, CENTER_MODE );

        sprintf((char*)text, "|   3   |");
        BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)&text, RIGHT_MODE );

        sprintf((char*)text, "|   4   |");
        BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)&text, LEFT_MODE );

        sprintf((char*)text, "|   5   |");
        BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)&text, CENTER_MODE );

        sprintf((char*)text, "|   6   |");
        BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)&text, RIGHT_MODE );

        sprintf((char*)text, "|   7   |");
        BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *)&text, LEFT_MODE );

        sprintf((char*)text, "|   8   |");
        BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *)&text, CENTER_MODE );

        sprintf((char*)text, "|   9   |");
        BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *)&text, RIGHT_MODE );

        sprintf((char*)text, "|   0   |");
        BSP_LCD_DisplayStringAt(0, LINE(20), (uint8_t *)&text, CENTER_MODE );

        sprintf((char*)text, "|   Valider   |");
        BSP_LCD_DisplayStringAt(0, LINE(20), (uint8_t *)&text, RIGHT_MODE );

        //sprintf((char*)text, "|   Finger   |");
        sprintf((char*)text, "|   Annuler   |");
        BSP_LCD_DisplayStringAt(0, LINE(20), (uint8_t *)&text, LEFT_MODE );
    }
}
//permet de detecter les touches appuyer dans le menu principal
void menu_principal()
{
    TS_StateTypeDef TS_State;
    int touche;
    uint16_t x, y;
    uint8_t text[30];
    uint8_t status;
    uint8_t idx;
    uint8_t cleared = 0;
    uint8_t prev_nb_touches = 0;

    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

    status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_Clear(LCD_COLOR_BLUE);

    drawImageLogo(320,0);

    while(1) {
        BSP_TS_GetState(&TS_State);
        font_menu_principal(1);
        if (TS_State.touchDetected) {
            if (TS_State.touchDetected < prev_nb_touches) {
                for (idx = (TS_State.touchDetected + 1); idx <= 5; idx++) {
                    BSP_LCD_ClearStringLine(idx);
                }
            }
            prev_nb_touches = TS_State.touchDetected;

            cleared = 0;

            //sprintf((char*)text, "Touches: %d", TS_State.touchDetected);
            //BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);

            for (idx = 0; idx < TS_State.touchDetected; idx++) {
                x = TS_State.touchX[idx];
                y = TS_State.touchY[idx];
                //sprintf((char*)text, "Touch %d: x=%d y=%d    ", touche, x, y);
                //BSP_LCD_DisplayStringAt(0, LINE(0)/*LINE(idx+1)*/, (uint8_t *)&text, LEFT_MODE);
            }

            if(x<=200) {
                touch_screen();
            } else if(x>=210) {
                touch_screen_simple();
            }
        } else {
            //sprintf((char*)text,"code: %d",0);//valider
            //BSP_LCD_DisplayStringAt(0, LINE(2), (uint8_t *)&text, RIGHT_MODE);
        }
    }
}
// permet de detecter les touches appuyer dans le menu simple identification
void touch_screen_simple()
{
    TS_StateTypeDef TS_State;
    int touche= -1;
    uint16_t x, y;
    uint8_t text[30];
    uint8_t status;
    uint8_t idx;
    uint8_t cleared = 0;
    uint8_t prev_nb_touches = 0;

    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_Clear(LCD_COLOR_BLUE);
    while(1) {
        BSP_TS_GetState(&TS_State);
        font_menu_principal_simple(1);
        if (TS_State.touchDetected) {
            if (TS_State.touchDetected < prev_nb_touches) {
                for (idx = (TS_State.touchDetected + 1); idx <= 5; idx++) {
                    BSP_LCD_ClearStringLine(idx);
                }
            }
            prev_nb_touches = TS_State.touchDetected;

            cleared = 0;

            //sprintf((char*)text, "Touches: %d", TS_State.touchDetected);
            //BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);

            for (idx = 0; idx < TS_State.touchDetected; idx++) {
                x = TS_State.touchX[idx];
                y = TS_State.touchY[idx];
                //sprintf((char*)text, "Touch %d: x=%d y=%d    ", touche, x, y);
                //BSP_LCD_DisplayStringAt(0, LINE(0)/*LINE(idx+1)*/, (uint8_t *)&text, LEFT_MODE);
            }

            if(x<=200) {
                //finger.DeleteAllIDs();
                sprintf((char*)text, "Identification ");//1
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, RIGHT_MODE);
                identifier_add();
                BSP_LCD_Clear(LCD_COLOR_BLUE);

            }  else if(x>=210) {
                sprintf((char*)text,"Back");
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, RIGHT_MODE);
                menu_principal();
            }
        } else {
            //sprintf((char*)text,"code: %d",0);//valider
            //BSP_LCD_DisplayStringAt(0, LINE(2), (uint8_t *)&text, RIGHT_MODE);
        }
    }
}

// mise en place de la detection des touches
void touch_screen()
{
    TS_StateTypeDef TS_State;
    int touche= -1;
    uint16_t x, y;
    uint8_t text[30];
    uint8_t status;
    uint8_t idx;
    uint8_t cleared = 0;
    uint8_t prev_nb_touches = 0;

    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_Clear(LCD_COLOR_BLUE);
    while(1) {
        BSP_TS_GetState(&TS_State);
        font_clavier(1);
        if (TS_State.touchDetected) {
            if (TS_State.touchDetected < prev_nb_touches) {
                for (idx = (TS_State.touchDetected + 1); idx <= 5; idx++) {
                    BSP_LCD_ClearStringLine(idx);
                }
            }
            prev_nb_touches = TS_State.touchDetected;

            cleared = 0;
            touche = -1;
            //sprintf((char*)text, "Touches: %d", TS_State.touchDetected);
            //BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);

            for (idx = 0; idx < TS_State.touchDetected; idx++) {
                x = TS_State.touchX[idx];
                y = TS_State.touchY[idx];
                //sprintf((char*)text, "Touch %d: x=%d y=%d    ", touche, x, y);
                // BSP_LCD_DisplayStringAt(0, LINE(0)/*LINE(idx+1)*/, (uint8_t *)&text, LEFT_MODE);
            }

            if((x>=1 &&x<=60)&&(y>=20&&y<=40)) {
                finger.DeleteAllIDs();
                BSP_LCD_ClearStringLine(0);
                sprintf((char*)text, "Delete all id ");
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                //BSP_LCD_ClearStringLine(0);
                code = 0;
            }  else if((x>=410 &&x<=500)&&(y>=20&&y<=40)) {
                sprintf((char*)text,"BACK");
                BSP_LCD_ClearStringLine(0);
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                menu_principal();
                code = 0;
            } else if((x>=1 &&x<=60)&&(y>=60&&y<=80)) {
                touche=1;
                BSP_LCD_ClearStringLine(0);
                sprintf((char*)text, "Touches: %d",touche);//1
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                do {} while (!TS_State.touchDetected);
            } else if((x>=200 &&x<=260)&&(y>=60&&y<=80)) {
                touche=2;
                BSP_LCD_ClearStringLine(0);
                sprintf((char*)text,"Touches: %d",touche);//2
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                do {} while (!TS_State.touchDetected);
            } else if((x>=410 &&x<=500)&&(y>=60&&y<=80)) {
                touche=3;
                BSP_LCD_ClearStringLine(0);
                sprintf((char*)text,"Touches: %d",touche);//3
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                do {} while (!TS_State.touchDetected);
            } else if((x>=1 &&x<=60)&&(y>=120&&y<=140)) {
                touche=4;
                BSP_LCD_ClearStringLine(0);
                sprintf((char*)text,"Touches: %d",touche);//4
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                do {} while (!TS_State.touchDetected);
            } else if((x>=200 &&x<=260)&&(y>=115&&y<=135)) {
                touche=5;
                BSP_LCD_ClearStringLine(0);
                sprintf((char*)text,"Touches: %d",touche);//5
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                do {} while (!TS_State.touchDetected);
            } else if((x>=410 &&x<=500)&&(y>=115&&y<=130)) {
                touche=6;
                BSP_LCD_ClearStringLine(0);
                sprintf((char*)text,"Touches: %d",touche);//6
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                do {} while (!TS_State.touchDetected);
            } else if((x>=1 &&x<=60)&&(y>=170&&y<=190)) {
                touche=7;
                BSP_LCD_ClearStringLine(0);
                sprintf((char*)text,"Touches: %d",touche);//7
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                do {} while (!TS_State.touchDetected);
            } else if((x>=200 &&x<=260)&&(y>=180&&y<=200)) {
                touche=8;
                BSP_LCD_ClearStringLine(0);
                sprintf((char*)text,"Touches: %d",touche);//8
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                do {} while (!TS_State.touchDetected);
            } else if((x>=410 &&x<=500)&&(y>=180&&y<=210)) {
                touche=9;
                BSP_LCD_ClearStringLine(0);
                sprintf((char*)text,"Touches: %d",touche);//9
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                do {} while (!TS_State.touchDetected);
            } else if((x>=190 &&x<=260)&&(y>=230&&y<=260)) {
                touche=0;
                BSP_LCD_ClearStringLine(0);
                sprintf((char*)text,"Touches: %d",touche);//0
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                do {} while (!TS_State.touchDetected);
            } else if((x>=1 &&x<=60)&&(y>=230&&y<=260)) {
                sprintf((char*)text,"Touches: Annuler");//finger
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                BSP_LCD_ClearStringLine(2);
                code = 0;
            } else if((x>=370 &&x<=500)&&(y>=230&&y<=260)) {
                sprintf((char*)text,"Touches: valider");//valider
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                BSP_LCD_ClearStringLine(2);
                if(identificateur == 0) {
                    sprintf((char*)text,"Saisir Code SVP");//valider
                    BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                } else if(identificateur == 1) {
                    if(EnrollID == -1) {
                        sprintf((char*)text,"Ajouter empreinte SVP");//valider
                        BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                        ajouter_finger();
                    }
                    sprintf((char*)text,"Saisir empreinte SVP");//valider
                    BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                    identifier();
                }
                if(identificateur == 2) {
                    sprintf((char*)text,"Bienvenue");//valider
                    BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, CENTER_MODE);
                    code = 0;
                    identificateur=0;
                    touch_screen_2();
                } else {
                    code = 0;
                }
            }
            if(code == pass) {
                code = 0;
                identificateur = 1;
            }
        } else {
            //code = code*multi + touche;
            if (touche != -1) {
                codetouche(touche,multi);
            }
            if(multi < 10) {
                multi *= 10;
            }
            touche =-1;
        }
    }
}
// initialisation du LCD
void init_lcd()
{
    uint8_t status;
    int touche = -1;

    BSP_LCD_Init();
    finger.CmosLed(0);
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    HAL_Delay(1000);
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
}
// main principal
int main()
{
    init_lcd();
    init_finger();
    menu_principal();
}