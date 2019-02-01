#include <tice.h>
#include <graphx.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <fileioc.h>
#include <string.h>
//#include <debug.h>

#define lessonWidth 64
#define lessonHeight 32
#define lessonHeightMargin (8 / 3)
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

#define modeREAD "r"
#define modeWRITE "w"

#define classBvarName "classBvar"

enum LessonInfo { NameLocation, TimeStartEnd, TeacherLength };
enum LessonInfo lessonInfo = NameLocation;

void drawLessons();
void drawHelp();
void drawLesson();
enum LessonInfo nextMode();
uint8_t getWeekNumber();
bool getWeekB();

bool weekB;
bool classB;
bool showingHelp;

void main(void) {
    sk_key_t key;
    uint8_t week;
    ti_var_t classBvar;

    gfx_Begin();

    gfx_SetDrawBuffer();

    classBvar = ti_Open(classBvarName, modeREAD);

    weekB = getWeekB();
    classB = ti_GetC(classBvar);

    ti_Close(classBvar);

    drawLessons();

    gfx_SwapDraw();

    while((key = os_GetCSC()) != 9){
        if(showingHelp && key != 0){
            showingHelp = false;
            drawLessons();
            gfx_SwapDraw();
        } else if(key == 1 || key == 4 || key == 54){
            showingHelp = false;
            lessonInfo = nextMode(lessonInfo, key != 4);
            drawLessons();
            gfx_SwapDraw();
        } else if(key == 2 || key == 3 || key == 48){
            showingHelp = false;
            weekB = !weekB;
            drawLessons();
            gfx_SwapDraw();
        } else if(key == 15){
            showingHelp = false;
            classB = !classB;
            classBvar = ti_Open(classBvarName, modeWRITE);
            ti_PutC(classB, classBvar);
            ti_Close(classBvar);
            drawLessons();
            gfx_SwapDraw();
        } else if(key == 45){
            showingHelp = false;
            drawHelp();
            gfx_SwapDraw();
        }
    };

    gfx_End();
    ti_CloseAll();
}
void drawLessons(void){
    uint8_t day;
    uint8_t month;
    uint16_t year;
    char* dateMsg = malloc(32);
    char* dayS = malloc(32);
    char* monthS = malloc(32);
    char* yearS = malloc(32);
    char* weekS = malloc(32);

    memset(dateMsg, 0, sizeof(dateMsg));

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
    drawLesson(2 * lessonWidth, 1 * (lessonHeight + lessonHeightMargin), "Matte", !weekB ? "H341" : "F206", "drada", "01:10", colorMatte, textColorDark, "09:25", "10:35");
    drawLesson(2 * lessonWidth, 2 * (lessonHeight + lessonHeightMargin), "Fysik", "F206", "drada", "00:50", colorFysik, textColorDark, "10:40", "11:30");
    drawLesson(2 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Lunch", "", "", "00:45", colorLunch, textColorLight, "11:30", "12:15");

    //Tordag
    drawLesson(3 * lessonWidth, 0 * (lessonHeight + lessonHeightMargin), "Matte", "F206", "drada", "01:00", colorMatte, textColorDark, "08:00", "09:00");
    drawLesson(3 * lessonWidth, 1 * (lessonHeight + lessonHeightMargin), "Idrott", "", "tejpe", "01:30", colorIdrott, textColorDark, "09:40", "11:10");
    drawLesson(3 * lessonWidth, 2 * (lessonHeight + lessonHeightMargin), "Lunch", "", "", "00:45", colorLunch, textColorLight, "11:35", "12:20");
    if(weekB && !classB){
        drawLesson(3 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Kemi", "H324La", "altla", "01:20", colorKemi, textColorDark, "12:20", "13:40");
        drawLesson(3 * lessonWidth, 4 * (lessonHeight + lessonHeightMargin), "Teknik", "H341", "chuga", "01:30", colorTeknik, textColorLight, "14:00", "15:30");
    } else if(!classB) {
        drawLesson(3 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Teknik", "H341", "chuga", "01:30", colorTeknik, textColorLight, "12:20", "13:50");
        drawLesson(3 * lessonWidth, 4 * (lessonHeight + lessonHeightMargin), "Fysik", "F204La", "drada", "01:20", colorFysik, textColorDark, "14:00", "15:20");
    } else if(weekB){
        drawLesson(3 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Teknik", "H341", "chuga", "01:30", colorTeknik, textColorLight, "12:20", "13:50");
        drawLesson(3 * lessonWidth, 4 * (lessonHeight + lessonHeightMargin), "Kemi", "H324La", "altla", "01:20", colorKemi, textColorDark, "14:00", "15:20");
    } else {
        drawLesson(3 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Fysik", "F204La", "drada", "01:20", colorFysik, textColorDark, "12:20", "13:40");
        drawLesson(3 * lessonWidth, 4 * (lessonHeight + lessonHeightMargin), "Teknik", "H341", "chuga", "01:30", colorTeknik, textColorLight, "14:00", "15:30");
    }
    drawLesson(3 * lessonWidth, 5 * (lessonHeight + lessonHeightMargin), "Resurstid", "", "", "01:00", colorResurstid, textColorLight, "15:30", "16:30");

    //Fredag
    drawLesson(4 * lessonWidth, 1 * (lessonHeight + lessonHeightMargin), "Kemi", "H331", "altla", "01:00", colorKemi, textColorDark, "09:50", "10:50");
    drawLesson(4 * lessonWidth, 2 * (lessonHeight + lessonHeightMargin), "Lunch", "", "", "00:45", colorLunch, textColorLight, "11:00", "11:45");
    drawLesson(4 * lessonWidth, 3 * (lessonHeight + lessonHeightMargin), "Fysik", "F206", "drada", "01:20", colorFysik, textColorDark, "12:10", "13:30");
    drawLesson(4 * lessonWidth, 4 * (lessonHeight + lessonHeightMargin), "Engelska", "B107", "jormo", "01:00", colorEngelska, textColorDark, "13:40", "14:40");
    drawLesson(4 * lessonWidth, 5 * (lessonHeight + lessonHeightMargin), "Matte", "F203", "drada", "01:00", colorMatte, textColorDark, "14:50", "15:50");
    
    boot_GetDate(&day, &month, &year);
    sprintf(dayS, "%d", day);
    sprintf(monthS, "%d", month);
    sprintf(yearS, "%d", year);
    sprintf(weekS, "%d", getWeekNumber());
    
    if(weekB == getWeekB()){
        strcat(dateMsg, dayS);
        strcat(dateMsg, "/");
        strcat(dateMsg, monthS);
        strcat(dateMsg, "-");
        strcat(dateMsg, yearS);
        strcat(dateMsg, ", W: ");
        strcat(dateMsg, weekS);
        strcat(dateMsg, " : ");
    } else
        strcat(dateMsg, "Week ");
    if(!weekB)
        strcat(dateMsg, "A");
    else
        strcat(dateMsg, "B");
    if(!classB)
        strcat(dateMsg, ", c: A");
    else
        strcat(dateMsg, ", c: B");

    gfx_PrintStringXY(dateMsg, LCD_WIDTH / 2 - (gfx_GetStringWidth(dateMsg) / 2), LCD_HEIGHT - lessonHeight / 2);
   
    free(dateMsg);
    memset(dateMsg, 0, sizeof(dateMsg));
    free(dayS);
    free(monthS);
    free(yearS);
    free(weekS);
}
void drawHelp(void){
    showingHelp = true;
    gfx_FillScreen(255);
    gfx_PrintStringXY("Button Help", 15, 10);
    gfx_PrintStringXY("enter - Quit", 10, 3 * 10);
    gfx_PrintStringXY("/\\ , \\/ , 2nd - Swap Display mode", 10, 4 * 10);
    gfx_PrintStringXY("< , > , alpha - Swap Timetable (A/B)", 10, 5 * 10);
    gfx_PrintStringXY("clear - Swap Class (A/B)", 10, 6 * 10);
    gfx_PrintStringXY("I - Show this page", 10, 7 * 10);

    gfx_PrintStringXY("If week is 101, check that the", 10, 9 * 10);
    gfx_PrintStringXY("date is correct. If not, quit and enter", 10, 10 * 10);
    gfx_PrintStringXY("the correct date at mode > SET CLOCK", 10, 11 * 10);
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

uint8_t getWeekNumber(){
    uint8_t day;
    uint8_t month;
    uint16_t year;
    boot_GetDate(&day, &month, &year);
    //day = 1;
    //month = 1;
    //year = 2019;
    if(year == 2019 && month <= 12){
        switch(month){
            case 12:
                day += 30;
            case 11:
                day += 31;
            case 10:
                day += 30;
            case 9:
                day += 31;
            case 8:
                day += 31;
            case 7:
                day += 30;
            case 6:
                day += 31;
            case 5:
                day += 30;
            case 4:
                day += 31;
            case 3:
                day += 28;
            case 2:
                day += 31;
            case 1:
                day += 0;
        }
        return day / 7 + (day % 7 == 1 ? 0 : 1);
    } else {
        return 101;
    }
}

bool getWeekB() {
    switch (getWeekNumber()){
        case 1:
            return false;
        case 2:
            return true;
        case 3:
            return false;
        case 4:
            return true;
        case 5:
            return false;
        case 6:
            return true;
        // V7 Lov
        case 8:
            return false;
        case 9:
            return true;
        case 10:
            return false;
        case 11:
            return true;
        case 12:
            return false;
        case 13:
            return true;
        case 14:
            return false;
        case 15:
            return true;
        // V16 Lov
        case 17:
            return false;
        case 18:
            return true;
        case 19:
            return false;
        case 20:
            return true;
        case 21:
            return false;
        case 22:
            return true;
        case 23:
            return false;
        case 24:
            return true;
    }
    return false;
}