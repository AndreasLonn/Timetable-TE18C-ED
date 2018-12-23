#include <tice.h>
#include <graphx.h>
#include <stdint.h>
#include <stdlib.h>

int8_t lessonWidth = 64;
int8_t lessonHeight = 32;
int8_t lessonHeightMargin = 16 / 6;
int8_t lessonBorderColor = 0;

int8_t colorEngelska = 230;
int8_t colorFysik = 47;
int8_t colorHistoria = 30;
int8_t colorIdrott = 253;
int8_t colorKemi = 63;
int8_t colorLunch = 224;
int8_t colorMatte = 15;
int8_t colorMentorstid = 223;
int8_t colorResurstid = 104;
int8_t colorSvenska = 231;
int8_t colorTeknik = 5;

int8_t textColorDark = 0;
int8_t textColorLight = 255;
int8_t textColorTransparent = 254;

bool showName = true;
bool weekEven = true;

void drawLesson();
void drawLessons();

void main(void) {
    int8_t x = 50;

    sk_key_t key;

    gfx_Begin();
    gfx_SetDrawBuffer();

    drawLessons();

    gfx_SwapDraw();

    while((key = os_GetCSC()) != 9){
        if(key == 1 || key == 4 || key == 15 || key == 54){
            showName = !showName;
            drawLessons();
            gfx_SwapDraw();
        } if(key == 2 || key == 3 || key == 48){
            weekEven = !weekEven;
            drawLessons();
            gfx_SwapDraw();
        }
    };

    gfx_End();
}
void drawLessons(void){
    gfx_FillScreen(255);

    gfx_SetColor(31);
    //Måndag
    drawLesson(0 * lessonWidth, 0 * (lessonHeight + lessonHeightMargin), "Teknik", "B107", colorTeknik, textColorLight, "08:00", "09:30");
    drawLesson(0 * lessonWidth, 1 * (lessonHeight + lessonHeightMargin), "Mentorstid", "B107", colorMentorstid, textColorDark, "09:35", "10:15");
    drawLesson(0 * lessonWidth, 2 * (lessonHeight + lessonHeightMargin), "Matte", "B107", colorMatte, textColorDark, "10:20", "11:40");
    drawLesson(0 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Lunch", "", colorLunch, textColorLight, "11:50", "12:35");
    drawLesson(0 * lessonWidth, 4 * (lessonHeight + lessonHeightMargin), "Svenska", "B107", colorSvenska, textColorDark, "12:55", "14:05");

    drawLesson(0 * lessonWidth, 6 * (lessonHeight + lessonHeightMargin), "Historia", "B107", colorHistoria, textColorDark, "15:40", "17:00");

    //Tisdag
    drawLesson(1 * lessonWidth, 0 * (lessonHeight + lessonHeightMargin), "Svenska", "A158", colorSvenska, textColorDark, "08:10", "09:10");
    drawLesson(1 * lessonWidth, 1 * (lessonHeight + lessonHeightMargin), "Teknik", "B107", colorTeknik, textColorLight, "09:30", "11:00");
    drawLesson(1 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Lunch", "", colorLunch, textColorLight, "11:00", "11:55");
    drawLesson(1 * lessonWidth, 2 * (lessonHeight + lessonHeightMargin), "Kemi", "H329", colorKemi, textColorDark, "11:55", "12:45");
    drawLesson(1 * lessonWidth, 4 * (lessonHeight + lessonHeightMargin), "Engelska", "B107", colorEngelska, textColorDark, "12:55", "14:15");

    //Onsdag
    drawLesson(2 * lessonWidth, 1 * (lessonHeight + lessonHeightMargin), "Matte", weekEven ? "H341" : "F206", colorMatte, textColorDark, "09:25", "10:35");
    drawLesson(2 * lessonWidth, 2 * (lessonHeight + lessonHeightMargin), "Fysik", "F206", colorFysik, textColorDark, "10:40", "11:30");
    drawLesson(2 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Lunch", "", colorLunch, textColorLight, "11:30", "12:15");

    //Tordag
    drawLesson(3 * lessonWidth, 0 * (lessonHeight + lessonHeightMargin), "Matte", "F206", colorMatte, textColorDark, "08:00", "09:00");
    drawLesson(3 * lessonWidth, 1 * (lessonHeight + lessonHeightMargin), "Idrott", "", colorIdrott, textColorDark, "09:40", "11:10");
    drawLesson(3 * lessonWidth, 2 * (lessonHeight + lessonHeightMargin), "Lunch", "", colorLunch, textColorLight, "11:35", "12:20");
    if(weekEven){
        drawLesson(3 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Kemi", "H324La", colorKemi, textColorDark, "12:20", "13:40");
        drawLesson(3 * lessonWidth, 4 * (lessonHeight + lessonHeightMargin), "Teknik", "H341", colorTeknik, textColorLight, "14:00", "15:30");
    } else {
        drawLesson(3 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Teknik", "H341", colorTeknik, textColorLight, "12:20", "13:50");
        drawLesson(3 * lessonWidth, 4 * (lessonHeight + lessonHeightMargin), "Fysik", "F204La", colorFysik, textColorDark, "14:00", "15:20");
    }
    drawLesson(3 * lessonWidth, 5 * (lessonHeight + lessonHeightMargin), "Resurstid", "", colorResurstid, textColorLight, "15:30", "16:30");

    //Fredag
    drawLesson(4 * lessonWidth, 1 * (lessonHeight + lessonHeightMargin), "Kemi", "H331", colorKemi, textColorDark, "09:50", "10:50");
    drawLesson(4 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Lunch", "", colorLunch, textColorLight, "11:00", "11:45");
    drawLesson(4 * lessonWidth, 2 * (lessonHeight + lessonHeightMargin), "Fysik", "F206", colorFysik, textColorDark, "12:10", "13:20");
    drawLesson(4 * lessonWidth, 4 * (lessonHeight + lessonHeightMargin), "Engelska", "B107", colorEngelska, textColorDark, "13:40", "14:40");
    drawLesson(4 * lessonWidth, 5 * (lessonHeight + lessonHeightMargin), "Matte", "H341", colorMatte, textColorDark, "14:50", "15:50");

    gfx_PrintStringXY(weekEven ? "Jamn Vecka" : "Udda Vecka", LCD_WIDTH / 2 - 32, LCD_HEIGHT - lessonHeight / 2);
}

void drawLesson(int16_t x, int16_t y, char *name, char *location, int8_t lessonColor, int8_t textColor, char *timeFrom, char *timeTo){
    gfx_SetColor(lessonColor);
    gfx_FillRectangle(x, y, lessonWidth, lessonHeight);
    gfx_SetColor(lessonBorderColor);
    gfx_Rectangle(x, y, lessonWidth, lessonHeight);
    gfx_SetTextTransparentColor(textColorTransparent);
    gfx_SetTextBGColor(textColorTransparent);
    gfx_SetTextFGColor(textColor);
    if(showName){
        gfx_PrintStringXY(name, x + 2, y + 2);
        gfx_PrintStringXY(location, x + lessonWidth - gfx_GetStringWidth(location) - 2, y + lessonHeight - 10);
    } else {
        gfx_PrintStringXY(timeFrom, x + 2, y + 2);
        gfx_PrintStringXY(timeTo, x + lessonWidth - gfx_GetStringWidth(timeTo) - 2, y + lessonHeight - 10);
    }
}