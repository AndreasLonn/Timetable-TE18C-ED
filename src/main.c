#include <tice.h>
#include <graphx.h>
#include <stdint.h>
#include <stdlib.h>

#define lessonWidth 64
#define lessonHeight 32
#define lessonHeightMargin (16 / 6)
#define lessonBorderColor 0

#define colorEngelska 230
#define colorFysik 47
#define colorHistoria 30
#define colorIdrott 253
#define colorKemi 63
#define colorLunch 224
#define colorMatte 15
#define colorMentorstid 223
#define colorResurstid 104
#define colorSvenska 231
#define colorTeknik 5

#define textColorDark 0
#define textColorLight 255
#define textColorTransparent 254

enum LessonInfo { NameLocation, TimeStartEnd, TeacherLength };
enum LessonInfo lessonInfo = NameLocation;
bool weekB = false;

void drawLesson();
void drawLessons();
enum LessonInfo nextMode();

void main(void) {

    sk_key_t key;

    gfx_Begin();
    gfx_SetDrawBuffer();

    drawLessons();

    gfx_SwapDraw();

    while((key = os_GetCSC()) != 9){
        if(key == 1 || key == 4 || key == 15 || key == 54){
            lessonInfo = nextMode(lessonInfo, key != 1);
            drawLessons();
            gfx_SwapDraw();
        } if(key == 2 || key == 3 || key == 48){
            weekB = !weekB;
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
    drawLesson(0 * lessonWidth, 0 * (lessonHeight + lessonHeightMargin), "Teknik", "B107", "chuga", "01:30", colorTeknik, textColorLight, "08:00", "09:30");
    drawLesson(0 * lessonWidth, 1 * (lessonHeight + lessonHeightMargin), "Mentorstid", "B107", "selfr, altla", "00:40", colorMentorstid, textColorDark, "09:35", "10:15");
    drawLesson(0 * lessonWidth, 2 * (lessonHeight + lessonHeightMargin), "Matte", "B107", "drada", "01:20", colorMatte, textColorDark, "10:20", "11:40");
    drawLesson(0 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Lunch", "", "", "00:45", colorLunch, textColorLight, "11:50", "12:35");
    drawLesson(0 * lessonWidth, 4 * (lessonHeight + lessonHeightMargin), "Svenska", "B107", "selfr", "01:10", colorSvenska, textColorDark, "12:55", "14:05");

    drawLesson(0 * lessonWidth, 6 * (lessonHeight + lessonHeightMargin), "Historia", "B107", "olser", "01:20", colorHistoria, textColorDark, "15:40", "17:00");

    //Tisdag
    drawLesson(1 * lessonWidth, 0 * (lessonHeight + lessonHeightMargin), "Svenska", "A158", "selfr", "01:00", colorSvenska, textColorDark, "08:10", "09:10");
    drawLesson(1 * lessonWidth, 1 * (lessonHeight + lessonHeightMargin), "Teknik", "B107", "chuga", "01:30", colorTeknik, textColorLight, "09:30", "11:00");
    drawLesson(1 * lessonWidth, 2 * (lessonHeight + lessonHeightMargin), "Lunch", "", "", "00:55", colorLunch, textColorLight, "11:00", "11:55");
    drawLesson(1 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Kemi", "H329", "altla", "00:50", colorKemi, textColorDark, "11:55", "12:45");
    drawLesson(1 * lessonWidth, 4 * (lessonHeight + lessonHeightMargin), "Engelska", "B107", "jormo", "01:20", colorEngelska, textColorDark, "12:55", "14:15");

    //Onsdag
    drawLesson(2 * lessonWidth, 1 * (lessonHeight + lessonHeightMargin), "Matte", weekB ? "H341" : "F206", "drada", "01:10", colorMatte, textColorDark, "09:25", "10:35");
    drawLesson(2 * lessonWidth, 2 * (lessonHeight + lessonHeightMargin), "Fysik", "F206", "drada", "00:50", colorFysik, textColorDark, "10:40", "11:30");
    drawLesson(2 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Lunch", "", "", "00:45", colorLunch, textColorLight, "11:30", "12:15");

    //Tordag
    drawLesson(3 * lessonWidth, 0 * (lessonHeight + lessonHeightMargin), "Matte", "F206", "drada", "01:00", colorMatte, textColorDark, "08:00", "09:00");
    drawLesson(3 * lessonWidth, 1 * (lessonHeight + lessonHeightMargin), "Idrott", "", "tejpe", "01:30", colorIdrott, textColorDark, "09:40", "11:10");
    drawLesson(3 * lessonWidth, 2 * (lessonHeight + lessonHeightMargin), "Lunch", "", "", "00:45", colorLunch, textColorLight, "11:35", "12:20");
    if(weekB){
        drawLesson(3 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Kemi", "H324La", "altla", "01:20", colorKemi, textColorDark, "12:20", "13:40");
        drawLesson(3 * lessonWidth, 4 * (lessonHeight + lessonHeightMargin), "Teknik", "H341", "chuga", "01:30", colorTeknik, textColorLight, "14:00", "15:30");
    } else {
        drawLesson(3 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Teknik", "H341", "chuga", "01:30", colorTeknik, textColorLight, "12:20", "13:50");
        drawLesson(3 * lessonWidth, 4 * (lessonHeight + lessonHeightMargin), "Fysik", "F204La", "drada", "01:20", colorFysik, textColorDark, "14:00", "15:20");
    }
    drawLesson(3 * lessonWidth, 5 * (lessonHeight + lessonHeightMargin), "Resurstid", "", "", "01:00", colorResurstid, textColorLight, "15:30", "16:30");

    //Fredag
    drawLesson(4 * lessonWidth, 1 * (lessonHeight + lessonHeightMargin), "Kemi", "H331", "altla", "01:00", colorKemi, textColorDark, "09:50", "10:50");
    drawLesson(4 * lessonWidth, 2 * (lessonHeight + lessonHeightMargin), "Lunch", "", "", "00:45", colorLunch, textColorLight, "11:00", "11:45");
    drawLesson(4 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Fysik", "F206", "drada", "01:10", colorFysik, textColorDark, "12:10", "13:20");
    drawLesson(4 * lessonWidth, 4 * (lessonHeight + lessonHeightMargin), "Engelska", "B107", "jormo", "01:00", colorEngelska, textColorDark, "13:40", "14:40");
    drawLesson(4 * lessonWidth, 5 * (lessonHeight + lessonHeightMargin), "Matte", "H341", "drada", "01:00", colorMatte, textColorDark, "14:50", "15:50");

    gfx_PrintStringXY(!weekB ? "Vecka A" : "Vecka B", LCD_WIDTH / 2 - 32, LCD_HEIGHT - lessonHeight / 2);
}

void drawLesson(int16_t x, int16_t y, char *name, char *location, char *teacher, char *length, int8_t lessonColor, int8_t textColor, char *timeFrom, char *timeTo){
    gfx_SetColor(lessonColor);
    gfx_FillRectangle(x, y, lessonWidth, lessonHeight);
    gfx_SetColor(lessonBorderColor);
    gfx_Rectangle(x, y, lessonWidth, lessonHeight);
    gfx_SetTextTransparentColor(textColorTransparent);
    gfx_SetTextBGColor(textColorTransparent);
    gfx_SetTextFGColor(textColor);
    switch (lessonInfo){
        case NameLocation:
            gfx_PrintStringXY(name, x + 2, y + 2);
            gfx_PrintStringXY(location, x + lessonWidth - gfx_GetStringWidth(location) - 2, y + lessonHeight - 10);
            break;
        case TimeStartEnd:
            gfx_PrintStringXY(timeFrom, x + 2, y + 2);
            gfx_PrintStringXY(timeTo, x + lessonWidth - gfx_GetStringWidth(timeTo) - 2, y + lessonHeight - 10);
            break;
        case TeacherLength:
            gfx_PrintStringXY(teacher, x + 2, y + 2);
            gfx_PrintStringXY(length, x + lessonWidth - gfx_GetStringWidth(length) - 2, y + lessonHeight - 10);
            break;
    }
}

enum LessonInfo nextMode(enum LessonInfo currentLessonInfo, bool up) {
    switch (currentLessonInfo){
        case NameLocation:
            return up ? TimeStartEnd : TeacherLength;
        case TimeStartEnd:
            return up ? TeacherLength : NameLocation;
        default:
            return up ? NameLocation : TimeStartEnd;
    }
}