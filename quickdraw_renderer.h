#include <MacTypes.h>
#include <Types.h>
#include <Quickdraw.h>
#include <Scrap.h>
#include <Serial.h>
#include "SerialHelper.h"
#include "microui.h"

static struct context* quickdraw_init(unsigned int width, unsigned int height);
static int quickdraw_handle_event(EventRecord *event, mu_Context *ctx);
static void quickdraw_render(WindowPtr window, mu_Context *ctx);
static int quickdraw_font_get_text_width(mu_Font font, const char *text, int len);
static int text_height(mu_Font font);



/*
 * ==============================================================
 *
 *                          IMPLEMENTATION
 *
 * ===============================================================
 */


// constant keyboard mappings for convenenience
// See Inside Macintosh: Text pg A-7, A-8
int homeKey = (int)0x01;
int enterKey = (int)0x03;
int endKey = (int)0x04;
int helpKey = (int)0x05;
int backspaceKey = (int)0x08;
int deleteKey = (int)0x7F;
int tabKey = (int)0x09;
int pageUpKey = (int)0x0B;
int pageDownKey = (int)0x0C;
int returnKey = (int)0x0D;
int rightArrowKey = (int)0x1D;
int leftArrowKey = (int)0x1C;
int downArrowKey = (int)0x1F;
int upArrowKey = (int)0x1E;
int eitherShiftKey = (int)0x0F;
int escapeKey = (int)0x1B;

// #define QUICKDRAW_GRAPHICS_DEBUGGING
// #define QUICKDRAW_EVENTS_DEBUGGING

typedef struct {
    Ptr Address;
    long RowBytes;
    GrafPtr bits;
    Rect bounds;
    
    BitMap  BWBits;
    GrafPort BWPort;
    
    Handle  OrigBits;
    
} ShockBitmap;

void NewShockBitmap(ShockBitmap *theMap, short width, short height) {

    theMap->bits = 0L;
    SetRect(&theMap->bounds, 0, 0, width, height);
    
    theMap->BWBits.bounds = theMap->bounds;
    theMap->BWBits.rowBytes = ((width+15) >> 4)<<1;         // round to even
    theMap->BWBits.baseAddr = NewPtr(((long) height * (long) theMap->BWBits.rowBytes));

    theMap->BWBits.baseAddr = StripAddress(theMap->BWBits.baseAddr);
    
    OpenPort(&theMap->BWPort);
    SetPort(&theMap->BWPort);
    SetPortBits(&theMap->BWBits);

    SetRectRgn(theMap->BWPort.visRgn, theMap->bounds.left, theMap->bounds.top, theMap->bounds.right, theMap->bounds.bottom);
    SetRectRgn(theMap->BWPort.clipRgn, theMap->bounds.left, theMap->bounds.top, theMap->bounds.right, theMap->bounds.bottom);
    EraseRect(&theMap->bounds);
      
    theMap->Address = theMap->BWBits.baseAddr;
    theMap->RowBytes = (long) theMap->BWBits.rowBytes;
    theMap->bits = (GrafPtr) &theMap->BWPort;
}

ShockBitmap gMainOffScreen;

static struct quickdraw {
    unsigned int width;
    unsigned int height;
} quickdraw;

int widthFor12ptFont[128] = {
    0,
    10,
    10,
    10,
    10,
    10,
    10,
    10,
    10,
    8,
    10,
    10,
    10,
    0,
    10,
    10,
    10,
    11,
    11,
    9,
    11,
    10,
    10,
    10,
    10,
    10,
    10,
    10,
    10,
    10,
    10,
    10,
    4,
    6,
    7,
    10,
    7,
    11,
    10,
    3,
    5,
    5,
    7,
    7,
    4,
    7,
    4,
    7,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    4,
    4,
    6,
    8,
    6,
    8,
    11,
    8,
    8,
    8,
    8,
    7,
    7,
    8,
    8,
    6,
    7,
    9,
    7,
    12,
    9,
    8,
    8,
    8,
    8,
    7,
    6,
    8,
    8,
    12,
    8,
    8,
    8,
    5,
    7,
    5,
    8,
    8,
    6,
    8,
    8,
    7,
    8,
    8,
    6,
    8,
    8,
    4,
    6,
    8,
    4,
    12,
    8,
    8,
    8,
    8,
    6,
    7,
    6,
    8,
    8,
    12,
    8,
    8,
    8,
    5,
    5,
    5,
    8,
    8
};

// note: if this produces a greater value than the actual length of the text, 
// the cursor will walk off to the right
// too small, it will precede the end of the text
// TODO: fully convert
// TODO: assuming system font for v1, support other fonts in v2
// doing this in a "fast" way by using a precomputed table for a 12pt font
static int quickdraw_font_get_text_width(mu_Font font, const char *text, int len) {

    // writeSerialPort(boutRefNum, "quickdraw_font_get_text_width");

    if (!text || len == 0) {

        return 0;
    }

    int width = 0;

    for (int i = 0; i < len; i++) {

        width += widthFor12ptFont[(int)text[i]];
    }

    return width;
}

static int text_height(mu_Font font) {

  return 12;
}

static void quickdraw_render(WindowPtr window, mu_Context *ctx) {


    OpenPort(&gMainOffScreen.BWPort);
    SetPort(&gMainOffScreen.BWPort);
    SetPortBits(&gMainOffScreen.BWBits);
    EraseRect(&gMainOffScreen.bounds);

    mu_Command *cmd = NULL;

    while (mu_next_command(ctx, &cmd)) {

        int color; // Color QuickDraw colors are integers - see Retro68/InterfacesAndLibraries/Interfaces&Libraries/Interfaces/CIncludes/Quickdraw.h:122 for more info

        switch (cmd->type) {

            // case MU_COMMAND_ICON: {
                
            //         #ifdef QUICKDRAW_GRAPHICS_DEBUGGING

            //             writeSerialPort(boutRefNum, "COMMAND_RECT_FILLED");
            //         #endif


            //         color = blackColor;
                    
            //         ForeColor(color);
            //         Pattern colorPattern = qd.dkGray; //color_to_quickdraw_color(&r->color);

            //         // BackPat(&colorPattern); // inside macintosh: imaging with quickdraw 3-48
            //         PenSize(1.0, 1.0); // no member line thickness on this struct so assume we want a thin line
            //         // might actually need to build this with SetRect, search inside macintosh: imaging with quickdraw
            //         Rect quickDrawRectangle;
            //         quickDrawRectangle.top = cmd->rect.rect.y;
            //         quickDrawRectangle.left = cmd->rect.rect.y;
            //         quickDrawRectangle.bottom = cmd->rect.rect.y + cmd->rect.rect.h;
            //         quickDrawRectangle.right = cmd->rect.rect.x + cmd->rect.rect.w;

            //         FillRect(&quickDrawRectangle, &colorPattern);
            //         FrameRect(&quickDrawRectangle);//, (int)r->rounding, (int)r->rounding); // http://mirror.informatimago.com/next/developer.apple.com/documentation/mac/QuickDraw/QuickDraw-105.html#HEADING105-0
            // }
                
            //     break;

            case MU_COMMAND_CLIP: {
                

                    #ifdef QUICKDRAW_GRAPHICS_DEBUGGING

                        writeSerialPort(boutRefNum, "COMMAND_SCISSOR");
                    #endif

                    // al_set_clipping_rectangle((int)s->x, (int)s->y, (int)s->w, (int)s->h); // TODO: https://www.allegro.cc/manual/5/al_set_clipping_rectangle
                    // this essentially just sets the region of the screen that we are going to write to
                    // initially, i thought that this would be SetClip, but now believe this should be ClipRect, see:
                    // Inside Macintosh: Imaging with Quickdraw pages 2-48 and 2-49 for more info
                    // additionally, see page 2-61 for a data structure example for the rectangle OR 
                    // http://mirror.informatimago.com/next/developer.apple.com/documentation/mac/QuickDraw/QuickDraw-60.html
                    // for usage example
                    Rect quickDrawRectangle;
                    quickDrawRectangle.top = cmd->rect.rect.y;
                    quickDrawRectangle.left = cmd->rect.rect.y;
                    quickDrawRectangle.bottom = cmd->rect.rect.y + cmd->rect.rect.h;
                    quickDrawRectangle.right = cmd->rect.rect.x + cmd->rect.rect.w;

                    ClipRect(&quickDrawRectangle);
                }
            case MU_COMMAND_RECT: {
                
                    #ifdef QUICKDRAW_GRAPHICS_DEBUGGING

                        writeSerialPort(boutRefNum, "COMMAND_RECT_FILLED");
                    #endif


                    color = blackColor;
                    
                    ForeColor(color);
                    Pattern colorPattern = qd.white; //color_to_quickdraw_color(&r->color);

                    // BackPat(&colorPattern); // inside macintosh: imaging with quickdraw 3-48
                    PenSize(1.0, 1.0); // no member line thickness on this struct so assume we want a thin line
                    // might actually need to build this with SetRect, search inside macintosh: imaging with quickdraw
                    Rect quickDrawRectangle;
                    quickDrawRectangle.top = cmd->rect.rect.y;
                    quickDrawRectangle.left = cmd->rect.rect.y;
                    quickDrawRectangle.bottom = cmd->rect.rect.y + cmd->rect.rect.h;
                    quickDrawRectangle.right = cmd->rect.rect.x + cmd->rect.rect.w;

                    FillRect(&quickDrawRectangle, &colorPattern);
                    FrameRect(&quickDrawRectangle);//, (int)r->rounding, (int)r->rounding); // http://mirror.informatimago.com/next/developer.apple.com/documentation/mac/QuickDraw/QuickDraw-105.html#HEADING105-0
                }

                break;
            case MU_COMMAND_TEXT: {

                    
                    #ifdef QUICKDRAW_GRAPHICS_DEBUGGING

                        writeSerialPort(boutRefNum, "COMMAND_TEXT");
                        char log[255];
                        sprintf(log, "%f: %s", 12, cmd->text.str);
                        writeSerialPort(boutRefNum, log);
                    #endif

                    color = blackColor;
                    ForeColor(color);
                    MoveTo(cmd->text.pos.x, cmd->text.pos.y + 12);
                    TextSize(12);

                    DrawText(cmd->text.str, 0, strlen(cmd->text.str));
                }

                break;
        }
    }

    SetPort(window);

    // our offscreen bitmap is the same size as our port rectangle, so we
    // get away with using the portRect sizing for source and destination
    CopyBits(&gMainOffScreen.bits->portBits, &window->portBits, &window->portRect, &window->portRect, srcCopy, 0L);
}

static int quickdraw_handle_event(EventRecord *event, mu_Context *ctx) { 
    // see: inside macintosh: toolbox essentials 2-4
    // and  inside macintosh toolbox essentials 2-79

    WindowPtr window;
    FindWindow(event->where, &window); 
    // char *logb;
    // sprintf(logb, "quickdraw_handle_event event %d", event->what);
    // writeSerialPort(boutRefNum, logb);

    switch (event->what) {
        case updateEvt: {
                return 1;
            }
            break;
        case osEvt: { 
            // the quicktime osEvts are supposed to cover mouse movement events
            // notice that we are actually calling input_motion in the EventLoop for the program
            // instead, as handling this event directly does not appear to work for whatever reason
            // TODO: research this
            writeSerialPort(boutRefNum, "osEvt");

                switch (event->message) {

                    case mouseMovedMessage: {

                        #ifdef QUICKDRAW_EVENTS_DEBUGGING
                            
                            writeSerialPort(boutRefNum, "mouseMovedMessage");
                        #endif

                        Point tempPoint;
                        SetPt(&tempPoint, event->where.h, event->where.v);
                        GlobalToLocal(&tempPoint);
                        

                        int x = tempPoint.h;
                        int y = tempPoint.v;

                        // event->where should have coordinates??? or is it just a pointer to what the mouse is over?
                        // TODO need to figure this out
                        mu_input_mousemove(ctx, x, y); // TODO figure out mouse coordinates - not sure if this is right

                        break;
                    }

                    return 1;
                }
            }
            break;
        
        case mouseUp: 
            #ifdef QUICKDRAW_EVENTS_DEBUGGING

                writeSerialPort(boutRefNum, "mouseUp!!!");
            #endif
        case mouseDown: {

            #ifdef QUICKDRAW_EVENTS_DEBUGGING

                writeSerialPort(boutRefNum, "mouseUp/Down");
            #endif
            
            short part = FindWindow(event->where, &window);

			switch (part) {
                case inContent: {
                    // event->where should have coordinates??? or is it just a pointer to what the mouse is over?
                    // TODO need to figure this out
                    #ifdef QUICKDRAW_EVENTS_DEBUGGING

                        writeSerialPort(boutRefNum, "mouseUp/Down IN DEFAULT ZONE!!!!");
                    #endif

                    // this converts the offset of the window to the actual location of the mouse within the window
                    Point tempPoint;
                    SetPt(&tempPoint, event->where.h, event->where.v);
                    GlobalToLocal(&tempPoint);
                    
                    if (!event->where.h) {
                        
                        #ifdef QUICKDRAW_EVENTS_DEBUGGING

                            writeSerialPort(boutRefNum, "no event location for mouse!!!!");
                        #endif

                        return 1;
                    }

                    int x = tempPoint.h;
                    int y = tempPoint.v;

                    #ifdef QUICKDRAW_EVENTS_DEBUGGING

                        char logx[255];
                        sprintf(logx, "mouse location at time of click h: %d,  v: %d", x, y);
                        writeSerialPort(boutRefNum, logx);
                    #endif

                    // mu_input_mousemove(ctx, x, y); // you can enable this if you don't want to use motion tracking
                    // in the Mac event loop handler as in the nuklear quickdraw sample, and this will allow mouse clicks to
                    // work properly, but will not allow hover states to work
                    
                    if (event->what == mouseDown) {

                        mu_input_mousedown(ctx, x, y, 1);
                    } else {

                        mu_input_mouseup(ctx, x, y, 1);
                    }
                }
                break;
                return 1;
            }
            
            break;
        case keyDown:
		case autoKey: {/* check for menukey equivalents */

                char charKey = event->message & charCodeMask;
                int key = (int)charKey;


                #ifdef QUICKDRAW_EVENTS_DEBUGGING

                    writeSerialPort(boutRefNum, "keyDown/autoKey");

                    char logy[255];
                    sprintf(logy, "key pressed: key: '%c', 02x: '%02X', return: '%02X', %d == %d ??", key, key, returnKey, (int)(key), (int)(returnKey));
                    writeSerialPort(boutRefNum, logy);
                #endif

                const Boolean isKeyDown = event->what == keyDown;

                if (event->modifiers & cmdKey) {/* Command key down */

                    if (isKeyDown) {

                        // AdjustMenus();						/* enable/disable/check menu items properly */
                        // DoMenuCommand(MenuKey(key));
                    }
                    
                    if (key == 'c') {
                        
                        // // input_key(ctx, KEY_COPY, 1);
                    } else if (key == 'v') {
                        
                        // // input_key(ctx, KEY_PASTE, 1);
                    } else if (key == 'x') {
                        
                        // // input_key(ctx, KEY_CUT, 1);
                    } else if (key == 'z') {
                        
                        // // input_key(ctx, KEY_TEXT_UNDO, 1);
                    } else if (key == 'r') {
                        
                        // // input_key(ctx, KEY_TEXT_REDO, 1);
                    } 
                } else if (key == eitherShiftKey) {
                    
                    // input_key(ctx, KEY_SHIFT, isKeyDown);
                } else if (key == deleteKey) {
                    
                    // input_key(ctx, KEY_DEL, isKeyDown);
                } else if (key == enterKey) {
                    
                    // input_key(ctx, KEY_ENTER, isKeyDown);
                } else if (key == returnKey) {
                    
                    // input_key(ctx, KEY_ENTER, isKeyDown);
                } else if (key == tabKey) {
                    
                    // input_key(ctx, KEY_TAB, isKeyDown);
                } else if (key == leftArrowKey) {
                    
                    // input_key(ctx, KEY_LEFT, isKeyDown);
                } else if (key == rightArrowKey) {
                    
                    // input_key(ctx, KEY_RIGHT, isKeyDown);
                } else if (key == upArrowKey) {
                    
                    // input_key(ctx, KEY_UP, isKeyDown);
                } else if (key == downArrowKey) {
                    
                    // input_key(ctx, KEY_DOWN, isKeyDown);
                } else if (key == backspaceKey) {
                    
                    // input_key(ctx, KEY_BACKSPACE, isKeyDown);
                } else if (key == escapeKey) {
                    
                    // // input_key(ctx, KEY_TEXT_RESET_MODE, isKeyDown);
                } else if (key == pageUpKey) {
                 
                    // input_key(ctx, KEY_SCROLL_UP, isKeyDown);
                } else if (key == pageDownKey) {
                    
                    // input_key(ctx, KEY_SCROLL_DOWN, isKeyDown);
                } else if (key == homeKey) {

                    // // input_key(ctx, KEY_TEXT_START, isKeyDown);
                    // input_key(ctx, KEY_SCROLL_START, isKeyDown);
                } else if (key == endKey) {

                    // // input_key(ctx, KEY_TEXT_END, isKeyDown);
                    // input_key(ctx, KEY_SCROLL_END, isKeyDown);
                } else {

                    #ifdef QUICKDRAW_EVENTS_DEBUGGING

                        writeSerialPort(boutRefNum, "default keydown/autokey event");
                    #endif

                    if (key > 127) {
                        // invalid char
                        mu_input_text(ctx, "?");
                    } else {
                        char ascii_c[2] = {(char)key, '\0'};
                        mu_input_text(ctx, ascii_c);
                    }
                }

                return 1;
            }
			break;
        default: {
                #ifdef QUICKDRAW_EVENTS_DEBUGGING

                    writeSerialPort(boutRefNum, "default unhandled event");
                #endif
            
                return 1; 
            }
            break;
        }
    }
}

// it us up to our "main" function to call this code
static struct context* quickdraw_init(unsigned int width, unsigned int height) {

    NewShockBitmap(&gMainOffScreen, width, height);
}

static void quickdraw_shutdown(void) {

    memset(&quickdraw, 0, sizeof(quickdraw));
}
        

        
